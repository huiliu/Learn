#include "KeyEventHandler.h"
#include <cassert>
#include "CommandCache.h"
#include "FrameSizer.h"

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
	default:
		return new DefaultKeyHandler();
	}
	return nullptr;
}

void UpKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long lastPoint = pTextCtrl->GetLastPosition();
	CommandCache& CmdCache = pTextCtrl->GetCommandCacheList();
	const CmdCacheEntry& cmd = CmdCache.MoveBackword();
	
	pTextCtrl->Replace(lastPoint - cmd.second, lastPoint, cmd.first);
}

void DownKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long lastPoint = pTextCtrl->GetLastPosition();
	CommandCache& CmdCache = pTextCtrl->GetCommandCacheList();
	const CmdCacheEntry& cmd = CmdCache.MoveForeword();

	pTextCtrl->Replace(lastPoint - cmd.second, lastPoint, cmd.first);
}

void ReturnKeyHandler::Process(wxKeyEvent& event)
{
	CliCtrl* pTextCtrl = dynamic_cast<CliCtrl*>(event.GetEventObject());
	long lastPoint = pTextCtrl->GetLastPosition();
	
	long col, row, lastLineLen, cmdlen;
	pTextCtrl->PositionToXY(pTextCtrl->GetLastPosition(), &col, &row);
	lastLineLen = pTextCtrl->GetLineLength(row-1);
	cmdlen = lastLineLen - LINEPREFIX.size();
	
	wxString curCmd = pTextCtrl->GetRange(lastPoint - cmdlen - 1, lastPoint);

	// ToDO: do something

	pTextCtrl->GetCommandCacheList().AppendCommand(curCmd);
	pTextCtrl->AppendCliPrompt();
}