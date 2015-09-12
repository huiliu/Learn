#pragma once
#include <wx/wx.h>

class GridFrame : public wxFrame
{
public:
	GridFrame(const wxString& title);
	~GridFrame();
private:
	wxPanel* m_pPanel;
};