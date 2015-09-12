#pragma once
#include <wx/wx.h>

class BoxFrame : public wxFrame
{
public:
	BoxFrame(const wxString& title);
	~BoxFrame();

private:
	wxPanel* m_pPanel;
};