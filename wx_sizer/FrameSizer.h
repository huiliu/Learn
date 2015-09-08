#pragma once
#include <wx/wx.h>
#include <deque>
#include "CommandCache.h"

enum MyEnum
{
	ID_TEXTCTRL = 1
};

const wxString LINEPREFIX("> ");
const wxColour cBgDefaultColour("#000000");
const wxColour cFgDefaultColour("#ffffff");
const wxColour cResultBgColour("#223344");
const wxColour cResultFgColour("#eeffdd");

class FrameSizer : public wxFrame
{
public:
	FrameSizer(const wxString& title);

private:
	wxTextCtrl* m_pTextCtrl;
};

class CliCtrl : public wxTextCtrl
{
public:
	CliCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style);

	CommandCache& GetCommandCacheList() { return m_CachedCmd; }

	void AppendMsg(const wxString& msg);
	void AppendCliPrompt();
private:


	/* Event Handler */
	void OnChar(wxKeyEvent& event);
	void OnContextMenu(wxContextMenuEvent& event) { return; }	// ½ûÓÃÓÒ¼ü²Ëµ¥

	wxDECLARE_EVENT_TABLE();

private:
	CommandCache m_CachedCmd;
};
