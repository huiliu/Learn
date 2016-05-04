// chat.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <winsock2.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <assert.h>
#include <arpa/inet.h>
#include <pthread.h>

#define CHECK_NULL_RETURN(ptr,ret) \
    if (NULL == ptr) {\
        assert(0);\
        return ret;\
    }

#define CHECK_NULL_ASSERT(ptr) \
    if (NULL == ptr) {\
        assert(0);\
        return (void*)0;\
    }

#define CHECK_FD_RETURN(fd,ret) \
    if (fd < 0) {\
        assert(0);\
        return ret;\
    }

static const char* host = "127.0.0.1";
static const char* port = "7890";
int g_acceptor_fd = -1;     // socket acceptor fd
int g_epoll_fd = -1;        // 事件分发器 id
int g_connector_fd = -1;    // client socket fd
int g_communication_fd = -1;        // stdin fd

void check_result(int fd, int code, const char* msg)
{
	if (-1 == fd && code != EINTR) {
		fprintf(stderr, "[%s]%s\n", msg, strerror(code));
		exit(1);
	}
}

// 包装从socket读取数据
int wrap_read(int fd, char* buff, size_t sz)
{
	int count = 0;
again:
	count = read(fd, buff, sz);

	if (count < 0) {
		if (EINTR == errno) {
			goto again;
		}
		else {
			count = 0;
		}
	}
	return count;
}

// 读取sock peer信息
void getpeerinfo(int fd, char* addr, uint32_t* port)
{
	if (-1 == fd || NULL == addr || NULL == port) {
		assert(0);
		return;
	}

	struct sockaddr_in saddr;
	socklen_t   len = sizeof(saddr);

	int ret = getpeername(fd, (struct sockaddr*)&saddr, &len);
	check_result(ret, errno, "getpeername");
	const char* paddr = inet_ntop(AF_INET, &saddr.sin_addr, addr, INET_ADDRSTRLEN);
	assert(NULL != paddr);

	*port = ntohs(saddr.sin_port);
}

// 记录sock peer信息
void log_peer_info(int fd, const char* msg)
{
	char addr[INET_ADDRSTRLEN];
	uint32_t port;

	getpeerinfo(fd, addr, &port);
	fprintf(stdout, "%s %s:%d\n", msg, addr, port);
}

// 创建一个TCP侦听socket
int create_tcp_socket_acceptor(const char* host, const char* port)
{
	CHECK_NULL_RETURN(host, -1);
	CHECK_NULL_RETURN(port, -1);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	check_result(fd, errno, "socket");

	struct addrinfo* res = NULL;
	struct addrinfo hits;

	memset(&hits, 0, sizeof(hits));
	hits.ai_socktype = SOCK_STREAM;

	int ret = getaddrinfo(host, port, &hits, &res);
	if (0 != ret) {
		fprintf(stderr, "[getaddrinfo]: %s\n", gai_strerror(ret));
		freeaddrinfo(res);
		exit(1);
	}

	struct addrinfo* phead = res;
	for (; NULL != phead; phead = phead->ai_next) {
		ret = bind(fd, phead->ai_addr, phead->ai_addrlen);
		check_result(ret, errno, "bind");
		break;
	}
	freeaddrinfo(res);

	ret = listen(fd, 10);
	check_result(ret, errno, "listen");

	return fd;
}

// 建立一个connector
int create_tcp_socket_connector(const char* host, const char* port)
{
	CHECK_NULL_RETURN(host, -1);
	CHECK_NULL_RETURN(port, -1);

	int fd = socket(AF_INET, SOCK_STREAM, 0);
	check_result(fd, errno, "socket");

	struct addrinfo* res = NULL;
	struct addrinfo hits;

	memset(&hits, 0, sizeof(hits));
	hits.ai_socktype = SOCK_STREAM;

	int ret = getaddrinfo(host, port, &hits, &res);
	if (0 != ret) {
		fprintf(stderr, "[getaddrinfo]: %s\n", gai_strerror(ret));
		freeaddrinfo(res);
		exit(1);
	}

	struct addrinfo* phead = res;
	for (; NULL != phead; phead = phead->ai_next) {
		ret = connect(fd, phead->ai_addr, phead->ai_addrlen);
		check_result(ret, errno, "bind");
		break;
	}
	freeaddrinfo(res);

	return fd;
}

// 创建多路分发epoll
int create_epoll_reactor()
{
	int epoll_fd = -1;

	epoll_fd = epoll_create1(EPOLL_CLOEXEC);
	check_result(epoll_fd, errno, "epoll_create1");

	g_epoll_fd = epoll_fd;

	return epoll_fd;
}

static int maintain_reactor(int epoll_fd, int action, int fd, int event_type)
{
	CHECK_FD_RETURN(epoll_fd, -1);
	CHECK_FD_RETURN(fd, -1);

	struct epoll_event event;
	memset(&event, 0, sizeof(event));

	event.events = event_type;
	event.data.fd = fd;

	int ret = epoll_ctl(epoll_fd, action, fd, &event);
	check_result(ret, errno, "epoll_ctl");

	return ret;
}

// 向事件分发器epoll中注册事件
int register_to_reactor(int epoll_fd, int fd, int type)
{
	int ret = maintain_reactor(epoll_fd, EPOLL_CTL_ADD, fd, type);

	return ret;
}

// 取消事件
int unregister_from_reactor(int epoll_fd, int fd, int type)
{
	int ret = maintain_reactor(epoll_fd, EPOLL_CTL_DEL, fd, type);

	return ret;
}

// 新连接进入事件
int handle_new_connection(int fd, int event_type)
{
	assert(g_acceptor_fd == fd);

	struct sockaddr addr;
	socklen_t len = sizeof(addr);

	int accept_fd = accept(fd, &addr, &len);
	check_result(accept_fd, errno, "accept");
	g_communication_fd = accept_fd;

	log_peer_info(accept_fd, "new connection from: ");

	int ret = register_to_reactor(g_epoll_fd, accept_fd, EPOLLIN);
	check_result(ret, errno, "register_to_reactor");

	return ret;
}

// socket 关闭事件
void handle_socket_close_event(int fd)
{
	log_peer_info(fd, "sock closed: ");
	close(fd);
}

static const int s_recv_buff_size = 4096;

int handle_socket_read(int fd)
{
	char buff[s_recv_buff_size];
	memset(buff, 0, s_recv_buff_size);

	char addr[INET_ADDRSTRLEN];
	uint32_t port = 0;

	getpeerinfo(fd, addr, &port);

	int recv_count = -1;
	while ((recv_count = wrap_read(fd, buff, s_recv_buff_size)) >= 0) {
		if (0 == recv_count) {
			handle_socket_close_event(fd);
			break;
		}
		buff[recv_count] = '\0';
		// write(fd, buff, recv_count);
		fprintf(stdout, "%s say: %s\n", addr, buff);
	}

	return recv_count;
}

// 处理客户端连接
int handle_socket_events(int fd, int event_type)
{
	switch (event_type) {
	case EPOLLIN:
		handle_socket_read(fd);
		break;
	case EPOLLOUT:
		break;
	default:
		fprintf(stderr, "unknow events!\n");
	}
	return 0;
}

int handle_events(int fd, int event_type)
{
	if (fd == g_acceptor_fd) {
		handle_new_connection(fd, event_type);
	}
	else {
		handle_socket_events(fd, event_type);
	}

	return 0;
}

// 分发事件
int dispatch_event(struct epoll_event* pEvents, int count)
{
	assert(NULL != pEvents);
	int i;
	for (i = 0; i < count; ++i) {
		handle_events(pEvents->data.fd, pEvents->events);
		++pEvents;
	}
	return 0;
}

static const int s_max_events = 10;
// 启动事件侦听
void* start_reactor(void* p_epoll_fd)
{
	CHECK_NULL_ASSERT(p_epoll_fd);

	int epoll_fd = *((int*)p_epoll_fd);

	struct epoll_event events[s_max_events];
	while (1) {
		int nfds = epoll_wait(epoll_fd, events, s_max_events, -1);
		check_result(nfds, errno, "epoll_wait");

		dispatch_event(events, nfds);
	}
}

// 创建一个tcp listen socket
void create_tcp_server(int epoll_fd)
{
	int fd = create_tcp_socket_acceptor(host, port);
	assert(fd > 0);
	register_to_reactor(epoll_fd, fd, EPOLLIN);

	g_acceptor_fd = fd;
}

// 创建一个tcp client
void create_tcp_client(int epoll_fd)
{
	int fd = create_tcp_socket_connector(host, port);
	assert(fd > 0);
	register_to_reactor(epoll_fd, fd, EPOLLIN);

	g_connector_fd = fd;
	g_communication_fd = fd;
}

// 读取命令行数据缓冲区大小
static const int s_cli_buff_size = 1024;
void read_from_cli()
{
	char buff[s_cli_buff_size];
	char* pbuff = buff;
	memset(buff, 0, s_cli_buff_size);

	while (1) {
		int count = wrap_read(fileno(stdin), buff, s_cli_buff_size);
		if (count > 0 && g_communication_fd != -1) {
			int sz = 0;
			int temp = 0;
			pbuff = buff;
			while ((temp = write(g_communication_fd, pbuff, count)) >= 0) {
				sz += temp;
				pbuff += temp;
				if (sz >= count) {
					break;
				}
			}
		}
	}
}

static void usage(const char* arg)
{
	fprintf(stderr, "usage: %s %s\n", arg, "<-c | -s>");
	exit(1);
}

int main(int argc, char *argv[])
{
	if (argc <= 1) {
		usage(argv[0]);
	}

	int epoll_fd = create_epoll_reactor();
	assert(epoll_fd > 0);

	int c;
	while ((c = getopt(argc, argv, "chs")) != EOF) {
		switch (c) {
		case 'c':
			create_tcp_client(epoll_fd);
			break;
		case 's':
			create_tcp_server(epoll_fd);
			break;
		default:
			usage(argv[0]);
		}
	}

	pthread_t tid = pthread_create(&tid, NULL, &start_reactor, (void*)&epoll_fd);

	read_from_cli();

	return 0;
}
