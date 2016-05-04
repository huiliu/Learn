#pragma once
class iSubscriber;

class iPublisher
{
public:
	iPublisher();
	virtual ~iPublisher();
	int start();
	virtual int subscriber(int type, iSubscriber* pSub) = 0;
	virtual int unsubscriber(int type, iSubscriber* pSub) = 0;
};

