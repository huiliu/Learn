#pragma once
#ifndef __WX_SIZER_CLI_KEYEVENTHANDLER__
#define __WX_SIZER_CLI_KEYEVENTHANDLER__

#include <wx/wx.h>

class KeyEventHandler
{
public:
	KeyEventHandler() {}
	virtual ~KeyEventHandler() {}

	static KeyEventHandler* GetHandler(long keycode);
	virtual void Process(wxKeyEvent& event) = 0;
};

/*
 * �����ַ�����.
 * ֻ�������һ�н����������
 *
 */
class DefaultKeyHandler : public KeyEventHandler
{
public:
	DefaultKeyHandler() {}
	~DefaultKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

/*
 * ����up��������ǰһ�����������
 */
class UpKeyHandler : public KeyEventHandler
{
public:
	UpKeyHandler() {}
	~UpKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

/*
 * ����down�������غ�һ�����������
 */
class DownKeyHandler : public KeyEventHandler
{
public:
	DownKeyHandler() {}
	~DownKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

class ReturnKeyHandler : public KeyEventHandler
{
public:
	ReturnKeyHandler() {}
	~ReturnKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

/*
 * 1. ֻ�������һ�н���ɾ������
 * 2. ����ɾ����������ʾ��
 *
 */
class BackKeyHandler : public KeyEventHandler
{
public:
	BackKeyHandler() {}
	~BackKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

/*
 * ����Ctrl - X
 */
class CutKeyHandler : public KeyEventHandler
{
public:
	virtual void Process(wxKeyEvent& event);
};

/*
 * ����TAB
 */
class TabKeyHandler : public KeyEventHandler
{
public:
	virtual void Process(wxKeyEvent& event);
};

#endif // !__WX_SIZER_CLI_KEYEVENTHANDLER__
