// boost_datetime_async.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using namespace boost::asio::ip;

class TcpConnection
	: public boost::enable_shared_from_this<TcpConnection>
{
public:
	typedef boost::shared_ptr<TcpConnection> SP_TCPCONNECTION;

	~TcpConnection();

	static SP_TCPCONNECTION create(boost::asio::io_service& io);

	void	start();
	tcp::socket& socket() { return m_socket; }
private:
	TcpConnection(boost::asio::io_service& io);

	// 注意回调函数的参数error_code为const类型
	void OnRead(const boost::system::error_code& ec);
	void OnWrite(const boost::system::error_code& ec, size_t sz);

private:
	tcp::socket m_socket;
	std::string m_message;
};

TcpConnection::TcpConnection(boost::asio::io_service& io)
	:m_socket(io)
{

}

TcpConnection::~TcpConnection()
{
}

TcpConnection::SP_TCPCONNECTION TcpConnection::create(boost::asio::io_service& io)
{
	return SP_TCPCONNECTION(new TcpConnection(io));
}

void TcpConnection::start()
{
	m_message = "hello world!";
	boost::asio::async_write(m_socket, boost::asio::buffer(m_message),
		boost::bind(&TcpConnection::OnWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void TcpConnection::OnRead(boost::system::error_code& ec)
{

}

void TcpConnection::OnWrite(const boost::system::error_code& ec, size_t sz)
{
	std::cout << "Write Bytes: " << sz << std::endl;
}

class TcpServer
{
public:
	TcpServer(boost::asio::io_service& io);
	~TcpServer();

	void start();

private:
	// 注意回调函数的参数error_code为const类型
	void OnAccept(TcpConnection::SP_TCPCONNECTION new_connection, const boost::system::error_code& ec);
	void OnRead(const boost::system::error_code& ec);
	void OnWrite(const boost::system::error_code& ec, size_t bytes_size);

private:
	tcp::acceptor m_acceptor;
};

TcpServer::TcpServer(boost::asio::io_service& io)
	: m_acceptor(io, tcp::endpoint(tcp::v4(), 9090))
{
}

TcpServer::~TcpServer()
{
}

void TcpServer::start()
{
	TcpConnection::SP_TCPCONNECTION spConnection = TcpConnection::create(m_acceptor.get_io_service());
	m_acceptor.async_accept(spConnection->socket(),
		boost::bind(&TcpServer::OnAccept, this, spConnection, boost::asio::placeholders::error));
}


void TcpServer::OnAccept(TcpConnection::SP_TCPCONNECTION new_connection, const boost::system::error_code& ec)
{
	if (!ec)
	{
		new_connection->start();
	}
	start();
}


int main()
{
	boost::asio::io_service io;
	TcpServer server(io);
	server.start();
	io.run();

    return 0;
}

