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

	// ����ʽ�Ƿ�Ϊ��
	bool	isZero();

	// ����ָ��Ϊexpon���ϵ��
	float	Coef(int expon) const;

	// �������ָ��
	int		LeadExp() const;

	// �����ʽ�����һ�� coef * x ^ expon
	void	Attach(float coef, int expon);

	// �Ƴ�ָ��Ϊexpon����
	void	Remove(int expon);

public:

	// ����һ��
	void SingleMult(float coef, int expon);

	// ��������ʽ���
	void Add(const Polynomial& other);

	// ��������ʽ���
	void Mult(const Polynomial& other);

public:
	void Display();


private:
	// ��¼��ǰ���ָ��
	int					m_degree;
	// ���ָ��
	int					m_maxDegree;
	// ϵ��
	std::vector<float>	m_coef;
};

#endif