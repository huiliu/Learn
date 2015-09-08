#include "KeyEventHandler.h"
#include <cassert>
#include "CommandCache.h"
#include "CliCtrl.h"

KeyEventHandler* KeyEventHandler::GetHandler(long keycode)
{
	switch (keycode)
	{
	case WXK_UP:
		return new UpKeyHandler();
	case WXK_DOWN:
		return new DownKeyHandler();
	case WXK_RETURN:
		return new ReturnKeyHandler();
	case WXK_BACK:
		return new BackKeyHandler();
	case WXK_CONTROL_X:
		return new CutKeyHandler();
	case WXK_TAB:
		return new TabKeyHandler();
	default:
		return new DefaultKeyHandler();
	}
	return nullptr;
}

void DefaultKeyHandler::Process(wxKeyEvent& event)
{
	long col, row, lastPoint;
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	lastPoint = pTextCtrl->GetLastPosition();
	pTextCtrl->PositionToXY(lastPoint, &col, &row);
	if (row != pTextCtrl->GetNumberOfLines() - 1)
	{
		return;
	}
	event.Skip(true);
}

void UpKeyHandler::Process(wxKeyEvent& event)
{
	long col,
		row,
		lastPoint,
		lastLineStartPoint;

	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	lastPoint = pTextCtrl->GetLastPosition();
	pTextCtrl->PositionToXY(lastPoint, &col, &row);
	lastLineStartPoint = pTextCtrl->XYToPosition(2, row);
	
	CommandCache& CmdCache = pTextCtrl->GetCommandCacheList();
	const CmdCacheEntry& cmd = CmdCache.MoveBackword();
	
	pTextCtrl->Replace(lastLineStartPoint, lastPoint, cmd.first);
}

void DownKeyHandler::Process(wxKeyEvent& event)
{
	long col,
		row,
		lastPoint,
		lastLineStartPoint;

	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	lastPoint = pTextCtrl->GetLastPosition();
	pTextCtrl->PositionToXY(lastPoint, &col, &row);
	lastLineStartPoint = pTextCtrl->XYToPosition(2, row);

	CommandCache& CmdCache = pTextCtrl->GetCommandCacheList();
	const CmdCacheEntry& cmd = CmdCache.MoveForeword();

	pTextCtrl->Replace(lastLineStartPoint, lastPoint, cmd.first);
}

void ReturnKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long lastPoint = pTextCtrl->GetLastPosition();
	
	long col, row, lastLineStartPoint;
	pTextCtrl->PositionToXY(pTextCtrl->GetLastPosition(), &col, &row);
	lastLineStartPoint = pTextCtrl->XYToPosition(0, row) + LINEPREFIX.size();
	
	wxString curCmd = pTextCtrl->GetRange(lastLineStartPoint, lastPoint);

	// ToDO: do something

	pTextCtrl->GetCommandCacheList().AppendCommand(curCmd);
	pTextCtrl->AppendCliPrompt();
}

void BackKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long insertPoint = pTextCtrl->GetInsertionPoint();
	long col, row;
	pTextCtrl->PositionToXY(insertPoint, &col, &row);

	if (row != pTextCtrl->GetNumberOfLines() - 1)
	{
		return;
	}

	if (col <= LINEPREFIX.size())
	{
		return;
	}
	event.Skip(true);
}

void CutKeyHandler::Process(wxKeyEvent& event)
{
	// 屏蔽Ctrl-X操作
	return;
}

wxString join(std::vector<std::string>& vecString, char c)
{
	wxString result;
	for (auto& item : vecString)
	{
		result += item + c;
	}
	return result.Strip(wxString::both);
}

void TabKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long insertPoint = pTextCtrl->GetInsertionPoint();
	
	long col, row;
	pTextCtrl->PositionToXY(insertPoint, &col, &row);
	if (pTextCtrl->GetNumberOfLines() - 1 != row)
	{
		return;
	}

	long cmdStartPosition = pTextCtrl->XYToPosition(0, row) + LINEPREFIX.size();
	long lastPosition = pTextCtrl->GetLastPosition();
	// 字符数必须>= 2才能进行补全
	if (lastPosition < cmdStartPosition + AUTO_COMPLETE_MIN_LEN &&
		cmdStartPosition != lastPosition)
	{
		return;
	}
	wxString CmdPrefix = pTextCtrl->GetRange(cmdStartPosition, lastPosition);

	std::vector<std::string> vecCommand;
	pTextCtrl->CommadStartswith(CmdPrefix.c_str(), vecCommand);
	// 没有匹配
	if (vecCommand.empty())
	{
		return;
	}
	// 只有一个匹配
	if (1 == vecCommand.size())
	{
		// 由于返回字符是匹配得到的，故使用字符长度判断两个字符串是否相等
		if (CmdPrefix.size() != vecCommand[0].size())
		{
			pTextCtrl->Replace(cmdStartPosition, lastPosition, vecCommand[0]);
		}
		return;
	}
	// 有多个匹配
	pTextCtrl->AppendAutoCompleteCommad(join(vecCommand, '\t'));
}
