#pragma once
#include <wx/wx.h>

class FlexGridFrame : public wxFrame
{
public:
	FlexGridFrame(const wxString& title);
private:
	wxPanel* m_pPanel;
};