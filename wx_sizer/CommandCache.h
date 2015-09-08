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
	INT32					m_nCachedCursor;		// ��ǰ���λ��[0, m_vecCachedCommand.size)
	const INT32				m_nCachedMaxCount;		// ��󻺴���
	std::deque<CmdCacheEntry>	m_vecCachedCommand;		// ��¼��ʷ����
};

#endif