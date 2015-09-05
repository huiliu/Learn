#include "FrameSizer.h"

FrameSizer::FrameSizer(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	m_pTextCtrl = new MyTextCtrl(this, ID_TEXTCTRL, LINEPREFIX,
		wxDefaultPosition, 
		wxDefaultSize, 
		wxTE_MULTILINE);
}

MyTextCtrl::MyTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style)
	: wxTextCtrl(parent, id, value, pos, size, style/*, wxTextValidator(wxFILTER_ALPHA)*/)
{
	SetBackgroundColour(wxColor("#000000"));
	SetForegroundColour(wxColor("#ffffff"));

	SetInsertionPoint(10);
}

void MyTextCtrl::OnKeyUp(wxKeyEvent& event)
{
	wxStreamToTextRedirector redirect(this);
	//std::cout << "Hello world!" << std::endl;

	return;
}

void MyTextCtrl::OnEnter(wxCommandEvent& event)
{
// 	wxString linePrefix("> ");
// 	wxStreamToTextRedirector redirect(this);
// 	std::cout << linePrefix;
}

void MyTextCtrl::OnChar(wxKeyEvent& event)
{
	wxStreamToTextRedirector redirect(this);
	
	switch (event.GetKeyCode())
	{
	case WXK_BACK:
	{
		long pos = this->GetInsertionPoint();
		wxString c = this->GetRange(pos - 2, pos);
		if (LINEPREFIX == c)
		{
			return;
		}
		this->Replace(pos - 1, pos, "");
	}
		break;
	case WXK_RETURN:
		std::cout << "\n" << LINEPREFIX;
		return;
	default:
		event.Skip(true);
		break;
	}
}

wxBEGIN_EVENT_TABLE(MyTextCtrl, wxTextCtrl)
EVT_KEY_UP(MyTextCtrl::OnKeyUp)
EVT_TEXT_ENTER(ID_TEXTCTRL, MyTextCtrl::OnEnter)
EVT_CHAR(MyTextCtrl::OnChar)
wxEND_EVENT_TABLE()