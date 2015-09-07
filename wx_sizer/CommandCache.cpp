
#include <cassert>
#include "CommandCache.h"

void CommandCache::AppendCommand(const wxString& cmd)
{
	wxString cmdStrip = cmd.Strip(wxString::both);
	if (cmdStrip.IsEmpty())
	{
		return;
	}

	m_vecCachedCommand.push_back(std::make_pair(cmdStrip, cmdStrip.size()));
	if (m_vecCachedCommand.size() > m_nCachedMaxCount)
	{
		m_vecCachedCommand.pop_front();
		return;
	}

	m_nCachedCursor++;
	assert(m_nCachedCursor <= m_nCachedMaxCount - 1);
}

const CmdCacheEntry& CommandCache::MoveForeword()
{
	long cur = m_nCachedCursor++;
	if (m_nCachedCursor >= m_vecCachedCommand.size() - 1)
	{
		m_nCachedCursor = m_vecCachedCommand.size() - 1;
	}

	return GetCommand(cur);
}

const CmdCacheEntry& CommandCache::MoveBackword()
{
	long cur = m_nCachedCursor--;
	if (m_nCachedCursor < 0)
	{
		m_nCachedCursor = 0;
	}
	return GetCommand(cur);
}

const CmdCacheEntry& CommandCache::GetCommand(INT32 index)
{
	if (m_vecCachedCommand.empty())
	{
		return std::make_pair("", 0);
	}

	if (index >= 0 && index < m_vecCachedCommand.size())
	{
		return m_vecCachedCommand.at(index);
	}
	return std::make_pair("", 0);
}

void CommandCache::Clear()
{
	m_vecCachedCommand.clear();
	m_nCachedCursor = -1;
}
