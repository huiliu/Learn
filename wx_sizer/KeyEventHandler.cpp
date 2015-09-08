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
	case WXK_BACK:
		return new BackKeyHandler();
	case WXK_CONTROL_X:
		return new CutKeyHandler();
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
	
	long col, row, lastLineStartPoint, cmdlen;
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
	// ÆÁ±ÎCtrl-X²Ù×÷
	return;
}