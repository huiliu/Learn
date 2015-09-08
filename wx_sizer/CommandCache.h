#pragma once

#ifndef __WX_SIZER_CLI__
#define __WX_SIZER_CLI__

#include <wx/wx.h>
#include <iostream>
#include <deque>
#include <map>

typedef std::pair<wxString, UINT>	CmdCacheEntry;

class CommandCache
{
public:
	CommandCache(INT32 max)
		: m_nCachedCursor(-1)
		, m_nCachedMaxCount(max)
	{

	}

	void AppendCommand(const wxString& cmd);
	
	const CmdCacheEntry& GetCurCmd();
	const CmdCacheEntry& MoveForeword();
	const CmdCacheEntry& MoveBackword();
	const CmdCacheEntry& GetCommand(INT32 index);

	void Clear();

private:
	INT32					m_nCachedCursor;		// 当前光标位置[0, m_vecCachedCommand.size)
	const INT32				m_nCachedMaxCount;		// 最大缓存数
	std::deque<CmdCacheEntry>	m_vecCachedCommand;		// 记录历史命令
};

#endif