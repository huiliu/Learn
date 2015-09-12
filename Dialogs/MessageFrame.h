#pragma once
#include <wx/wx.h>

class MessageFrame : public wxFrame
{
public:
	MessageFrame(const wxString& title);
	~MessageFrame();

	void ShowMesg1(wxCommandEvent& event);
	void ShowMesg2(wxCommandEvent& event);
	void ShowMesg3(wxCommandEvent& event);
	void ShowMesg4(wxCommandEvent& event);
};

enum EnumID
{
	ID_INFO = 1,
	ID_ERROR = 2,
	ID_QUESTION = 3,
	ID_ALERT = 4,
};