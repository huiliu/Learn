// 例子来自：http://theboostcpplibraries.com/boost.asio-network-programming

#include <boost/asio/io_service.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>
#include <iostream>

using namespace boost::asio;
using namespace boost::asio::ip;

io_service ioservice;
tcp::resolver resolv{ ioservice };
tcp::socket tcp_socket{ ioservice };
std::array<char, 4096> bytes;

void read_handler(const boost::system::error_code &ec,
	std::size_t bytes_transferred)
{
	if (!ec)
	{
		std::cout.write(bytes.data(), bytes_transferred);
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

void connect_handler(const boost::system::error_code &ec)
{
	// 3. 如果连接WEB服务器成功
	if (!ec)
	{
		std::string r =
			"GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
		// 向WEB服务器发起请求
		write(tcp_socket, buffer(r));
		// 异步处理WEB服务器返回结果，bytes只有4KB，可能一次装不下所有数据，
		// 远程也可能一次不能将数据发送完成？
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

// 第二个参数tcp::resolver::iterator域名解析的结果，所以可以作为异步连接参数
void resolve_handler(const boost::system::error_code &ec,
	tcp::resolver::iterator it)
{
	// 2. 如果域名解析成功，发起异步连接，连接服务器
	//	  回调connect_handler
	if (!ec)
		tcp_socket.async_connect(*it, connect_handler);
}

int main()
{
	// 1. 进行异步域名解析，回调resolve_handle
	tcp::resolver::query q{ "theboostcpplibraries.com", "80" };
	resolv.async_resolve(q, resolve_handler);
	ioservice.run();
}