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
 * 处理字符输入.
 * 只能在最后一行进行输入操作
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
 * 处理up键，返回前一次输入的命令
 */
class UpKeyHandler : public KeyEventHandler
{
public:
	UpKeyHandler() {}
	~UpKeyHandler() {}

	virtual void Process(wxKeyEvent& event);
};

/*
 * 处理down键，返回后一次输入的命令
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
 * 1. 只能在最后一行进行删除操作
 * 2. 不能删除命令行提示符
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
 * 处理Ctrl - X
 */
class CutKeyHandler : public KeyEventHandler
{
public:
	virtual void Process(wxKeyEvent& event);
};

/*
 * 处理TAB
 */
class TabKeyHandler : public KeyEventHandler
{
public:
	virtual void Process(wxKeyEvent& event);
};

#endif // !__WX_SIZER_CLI_KEYEVENTHANDLER__
