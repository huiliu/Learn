#pragma once

#ifndef __WX_SIZER_CLI_FRAME__
#define __WX_SIZER_CLI_FRAME__

#include <wx/wx.h>

class FrameSizer : public wxFrame
{
public:
	FrameSizer(const wxString& title);

private:
	wxTextCtrl* m_pTextCtrl;
};

#endif