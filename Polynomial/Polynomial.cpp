// Polynomial.cpp : 定义控制台应用程序的入口点。
//

#include "Polynomial.h"
#include <iostream>

bool Polynomial::isZero()
{
	return m_degree > 0;
}

float Polynomial::Coef(int expon) const
{
	if (expon > m_maxDegree)
		return 0;

	return m_coef.at(expon);
}

int Polynomial::LeadExp() const
{
	return m_degree;
}

void Polynomial::Attach(float coef, int expon)
{
	if (expon > m_maxDegree)
	{
		return;
	}

	if (expon > m_degree)
	{
		m_degree = expon;
	}

	m_coef[expon] += coef;
}

void Polynomial::Remove(int expon)
{
	if (expon > m_degree)
	{
		return;
	}

	if ( expon < m_degree)
	{
		m_coef[expon] = 0;
	}

	for (int i = m_degree; i >= 0; --i)
	{
		// 浮点与0比较可能有问题
		if (0 != m_coef[i])
		{
			m_degree = i;
			break;
		}
	}
}

void Polynomial::SingleMult(float coef, int expon)
{
	if (m_degree + expon >= m_maxDegree)
	{
		return;
	}

	for (int i = m_degree; i >= 0; --i)
	{
		if (0 != m_coef[i])
		{
			m_coef[i + expon] = m_coef[i] * coef;
			m_coef[i] = 0;
		}
	}

	m_degree += expon;
}

void Polynomial::Add(const Polynomial& other)
{

	if (LeadExp() < other.LeadExp())
	{
		m_degree = other.LeadExp();
	}

	for (int i = 0; i <= m_degree; i++)
	{
		m_coef[i] += other.Coef(i);
	}
}

void Polynomial::Mult(const Polynomial& other)
{
	if (LeadExp() + other.LeadExp() > m_maxDegree)
	{
		return;
	}

	std::vector<float> result;
	result.reserve(m_maxDegree);
	result.assign(m_maxDegree, 0);

	for (int i = 0; i <= other.LeadExp(); ++i)
	{
		for (int j = 0; j <= LeadExp(); ++j)
		{
			result[j + i] += other.Coef(i) * Coef(j);
		}
	}

	m_degree += other.LeadExp();
	m_coef.swap(result);
}

void Polynomial::Display()
{
	std::cout << "A(x) = ";
	for (int i = m_degree; i >= 0; --i)
	{
		if (0 != m_coef[i])
			std::cout << m_coef[i];
		if (0 != i)
		{
			std::cout << " * x ^ " << i << " + ";
		}
		
	}

	std::cout << std::endl;
}