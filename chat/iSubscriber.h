#pragma once

class iMessage;

class iSubscriber
{
public:
	iSubscriber();
	virtual ~iSubscriber();
	virtual void handle_message(iMessage* pMsg) = 0;
};

