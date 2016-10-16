#include "iUnKnow.h"



iUnKnow::iUnKnow()
	: m_refCount(0)
{
}


iUnKnow::~iUnKnow()
{
}

long iUnKnow::AddRef()
{
	return ++m_refCount;
}

long iUnKnow::DecRef()
{
	if (--m_refCount)
	{
		delete this;
		return 0;
	}

	return m_refCount;
}