#pragma once
#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__
#include <vector>


class Polynomial
{
public:
	Polynomial(int max_item)
		: m_degree(0)
		, m_maxDegree(max_item + 1)
	{
		m_coef.reserve(m_maxDegree);
		m_coef.assign(m_maxDegree, 0);
	}

	~Polynomial()
	{

	}

public:

	// 多项式是否为零
	bool	isZero();

	// 返回指数为expon项的系数
	float	Coef(int expon) const;

	// 返回最大指数
	int		LeadExp() const;

	// 向多项式中添加一项 coef * x ^ expon
	void	Attach(float coef, int expon);

	// 移除指数为expon的项
	void	Remove(int expon);

public:

	// 乘以一项
	void SingleMult(float coef, int expon);

	// 两个多项式相加
	void Add(const Polynomial& other);

	// 两个多项式相乘
	void Mult(const Polynomial& other);

public:
	void Display();


private:
	// 记录当前最大指数
	int					m_degree;
	// 最大指数
	int					m_maxDegree;
	// 系数
	std::vector<float>	m_coef;
};

#endif