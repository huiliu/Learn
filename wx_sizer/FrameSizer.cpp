#include "FrameSizer.h"
#include "CommandCache.h"
#include "KeyEventHandler.h"


FrameSizer::FrameSizer(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	m_pTextCtrl = new CliCtrl(this, ID_TEXTCTRL, LINEPREFIX,
		wxDefaultPosition, 
		wxDefaultSize, 
		wxTE_MULTILINE/*|wxTE_RICH2*/);
}

CliCtrl::CliCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style)
	: wxTextCtrl(parent, id, value, pos, size, style/*, wxTextValidator(wxFILTER_ALPHA)*/)
	, m_CachedCmd(10)
{
	SetBackgroundColour(wxColor("#000000"));
	SetForegroundColour(wxColor("#ffffff"));

	SetInsertionPointEnd();
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
	this->AppendText("\n"+LINEPREFIX);
}

wxBEGIN_EVENT_TABLE(CliCtrl, wxTextCtrl)
EVT_CHAR(CliCtrl::OnChar)
EVT_CONTEXT_MENU(CliCtrl::OnContextMenu)
wxEND_EVENT_TABLE()