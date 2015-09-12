#pragma once
#include <wx/wx.h>

class FileFrame : public wxFrame
{
public:
	FileFrame(const wxString& title);
	~FileFrame();

	void OnOpen(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnSave(wxCommandEvent& event);

private:
	wxTextCtrl* m_pTc;
};