// boost_async_timer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

const size_t count_max = 10;


class Timer
{
public:
	Timer(boost::asio::io_service& io);

	void timer1_handler(const std::string& msg);
	void timer2_handler(const std::string& msg);
private:
	boost::asio::strand			m_strand;
	boost::asio::deadline_timer m_timer1;
	boost::asio::deadline_timer m_timer2;
	size_t m_count;
};

Timer::Timer(boost::asio::io_service& io)
	: m_strand(io)
	, m_timer1(io, boost::posix_time::seconds(1))
	, m_timer2(io, boost::posix_time::seconds(1))
	, m_count(0)
{
	m_timer1.async_wait(m_strand.wrap(boost::bind(&Timer::timer1_handler, this, "Timer 1:")));
	m_timer2.async_wait(m_strand.wrap(boost::bind(&Timer::timer2_handler, this, "Timer 2:")));
}


void Timer::timer1_handler(const std::string& msg)
{
	if (m_count > count_max)
	{
		return;
	}

	std::cout << msg << ++m_count << std::endl;

	m_timer1.expires_at(m_timer1.expires_at() + boost::posix_time::seconds(1));
	m_timer1.async_wait(m_strand.wrap(boost::bind(&Timer::timer1_handler, this, "Timer 1:")));
}

void Timer::timer2_handler(const std::string& msg)
{
	if (m_count > count_max)
	{
		return;
	}

	std::cout << msg << ++m_count << std::endl;

	m_timer2.expires_at(m_timer2.expires_at() + boost::posix_time::seconds(1));
	m_timer2.async_wait(m_strand.wrap(boost::bind(&Timer::timer1_handler, this, "Timer 2:")));
}

int main()
{
	boost::asio::io_service io;

	Timer timer(io);
	boost::thread t(boost::bind(&boost::asio::io_service::run, &io));

	io.run();
	t.join();
	return 0;
}

