#pragma once
#include <wx/wx.h>

enum MyEnum
{
	ID_TEXTCTRL = 1
};


class FrameSizer : public wxFrame
{
public:
	FrameSizer(const wxString& title);

private:
	wxTextCtrl* m_pTextCtrl;
};

class MyTextCtrl : public wxTextCtrl
{
public:
	MyTextCtrl(wxWindow* parent, wxWindowID id, const wxString& value, const wxPoint& pos, const wxSize& size, int style);

	void OnKeyUp(wxKeyEvent& event);
	void OnChar(wxKeyEvent& event);
	void OnEnter(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};

const wxString LINEPREFIX("> ");