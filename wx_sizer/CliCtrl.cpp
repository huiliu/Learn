#include "CliCtrl.h"
#include "CommandCache.h"
#include "KeyEventHandler.h"

CliCtrl::CliCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style)
	: wxTextCtrl(parent, id, value, pos, size, style/*, wxTextValidator(wxFILTER_ALPHA)*/)
	, m_CachedCmd(10)
{
	SetBackgroundColour(wxColor("#000000"));
	SetForegroundColour(wxColor("#ffffff"));

	SetInsertionPointEnd();
	AddCommand("ls", "list files");
	AddCommand("mkdir", "create dir");
	AddCommand("mkfs", "-t ext3");
}

void CliCtrl::AddCommand(const char* cmdName, const std::string& cmdHelp)
{
	m_BuildInCommands.AppendItem(cmdName, cmdHelp);
}

void CliCtrl::CommadStartswith(const char* prefix, std::vector<std::string>& vecCommands)
{
	m_BuildInCommands.StartWith(prefix, vecCommands);
}

void CliCtrl::AppendAutoCompleteCommad(const wxString& data)
{
	wxString curLine = GetLineText(GetNumberOfLines() - 1);
	AppendText("\n" + data);
	AppendText("\n" + curLine);
}

void CliCtrl::OnChar(wxKeyEvent& event)
{
	int nKeyCode = event.GetKeyCode();

	KeyEventHandler* handler = KeyEventHandler::GetHandler(nKeyCode);
	handler->Process(event);
	return;
}

void CliCtrl::AppendMsg(const wxString& msg)
{
	this->SetDefaultStyle(wxTextAttr(cResultFgColour, cResultBgColour));
	this->AppendText("\n" + msg);

	this->AppendCliPrompt();
}

void CliCtrl::AppendCliPrompt()
{
	this->SetDefaultStyle(wxTextAttr(cFgDefaultColour, cBgDefaultColour));
	this->AppendText("\n" + LINEPREFIX);
}

wxBEGIN_EVENT_TABLE(CliCtrl, wxTextCtrl)
EVT_CHAR(CliCtrl::OnChar)
EVT_CONTEXT_MENU(CliCtrl::OnContextMenu)
wxEND_EVENT_TABLE()