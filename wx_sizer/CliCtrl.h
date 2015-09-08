#pragma once
#ifndef __WX_SIZER_CLICTRL__
#define __WX_SIZER_CLICTRL__

#include <wx/wx.h>
#include <deque>
#include "CommandCache.h"
#include "TextAutoComplete.h"

enum MyEnum
{
	ID_TEXTCTRL = 1,
};

const int AUTO_COMPLETE_MIN_LEN = 2;		// TAB补全时的最小字符数
const wxString LINEPREFIX("> ");
const wxColour cBgDefaultColour("#000000");
const wxColour cFgDefaultColour("#ffffff");
const wxColour cResultBgColour("#223344");
const wxColour cResultFgColour("#eeffdd");

class CliCtrl : public wxTextCtrl
{
public:
	CliCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style);

	void AddCommand(const char* cmdName, const std::string& cmdHelp);
	void CommadStartswith(const char* prefix, std::vector<std::string>& vecCommands);
	void AppendAutoCompleteCommad(const wxString& data);

	CommandCache& GetCommandCacheList() { return m_CachedCmd; }

	void AppendMsg(const wxString& msg);
	void AppendCliPrompt();
private:

	/* Event Handler */
	void OnChar(wxKeyEvent& event);
	void OnContextMenu(wxContextMenuEvent& event) { return; }	// 禁用右键菜单

private:
	CommandCache		m_CachedCmd;
	TextAutoComplete	m_BuildInCommands;

	wxDECLARE_EVENT_TABLE();

};

#endif