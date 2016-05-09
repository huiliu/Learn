// �������ԣ�http://theboostcpplibraries.com/boost.asio-network-programming

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
	// 3. �������WEB�������ɹ�
	if (!ec)
	{
		std::string r =
			"GET / HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
		// ��WEB��������������
		write(tcp_socket, buffer(r));
		// �첽����WEB���������ؽ����bytesֻ��4KB������һ��װ�����������ݣ�
		// Զ��Ҳ����һ�β��ܽ����ݷ�����ɣ�
		tcp_socket.async_read_some(buffer(bytes), read_handler);
	}
}

// �ڶ�������tcp::resolver::iterator���������Ľ�������Կ�����Ϊ�첽���Ӳ���
void resolve_handler(const boost::system::error_code &ec,
	tcp::resolver::iterator it)
{
	// 2. ������������ɹ��������첽���ӣ����ӷ�����
	//	  �ص�connect_handler
	if (!ec)
		tcp_socket.async_connect(*it, connect_handler);
}

int main()
{
	// 1. �����첽�����������ص�resolve_handle
	tcp::resolver::query q{ "theboostcpplibraries.com", "80" };
	resolv.async_resolve(q, resolve_handler);
	ioservice.run();
}