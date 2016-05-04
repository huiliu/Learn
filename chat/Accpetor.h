#pragma once
#include "iSubscriber.h"
#include <memory>

class iPublisher;

class Accpetor :
	public iSubscriber
{
public:
	Accpetor();
	virtual ~Accpetor();

	int init();
	int fini();

};

