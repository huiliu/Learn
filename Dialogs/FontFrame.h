#pragma once
#ifndef __WX_DIALOGS_FONTFRAME_H__
#define __WX_DIALOGS_FONTFRAME_H__

#include <wx/wx.h>

class FontFrame : public wxFrame
{
public:
	FontFrame(const wxString& title);

	void OnSelectFont(wxCommandEvent& event);
private:
	wxStaticText* m_pSt;
};

enum MyEnum
{
	ID_FONT_DIALOG = 1,
};

#endif