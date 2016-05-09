// boost_datetime_sync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

using namespace boost::asio::ip;

static const int port = 9090;
class Server
{
public:
	Server(boost::asio::io_service& io);
	~Server();

	void start();

public:
	std::string make_datetime_string() const;

private:

	void onAccept(boost::system::error_code& ec);
	void onRead(boost::system::error_code& ec);
	void onWrite(boost::system::error_code& ec, size_t bytes_size);

private:
	tcp::acceptor m_acceptor;
};

Server::Server(boost::asio::io_service& io)
	: m_acceptor(io, tcp::endpoint(tcp::v4(), port))
{
}

Server::~Server()
{
}

void Server::start()
{
	for (;;)
	{
		tcp::socket socket(m_acceptor.get_io_service());
		m_acceptor.accept(socket);

		boost::system::error_code ec;
		boost::asio::write(socket, boost::asio::buffer(make_datetime_string()), ec);
	}
}

std::string Server::make_datetime_string() const
{
	return "hello pworld!";
}

class Client
{
public:
	Client(boost::asio::io_service& io);
	~Client();

	void start();

private:
	tcp::socket m_socket;
};

void Client::start()
{
	tcp::resolver resolver(m_socket.get_io_service());
	tcp::resolver::query query("127.0.0.1", "9090");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	
	
	boost::asio::connect(m_socket, endpoint_iterator);

	for (;;)
	{
		boost::array<char, 128> buff;
		boost::system::error_code ec;

		size_t sz = m_socket.read_some(boost::asio::buffer(buff), ec);
		if (ec == boost::asio::error::eof)
		{
			break;
		}
		else if (ec)
		{
			throw boost::system::system_error(ec);
		}

		std::cout << buff.data() << std::endl;
	}
}

Client::Client(boost::asio::io_service& io)
	: m_socket(io)
{
}

Client::~Client()
{
}


int main()
{
	boost::asio::io_service io;

	Server server(io);
	///Client client(io);

	server.start();
	//client.start();

	io.run();
    return 0;
}

