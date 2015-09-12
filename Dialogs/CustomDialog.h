#pragma once
#ifndef __WX_DIALOGS_CUSTOMFRAME_H__
#define __WX_DIALOGS_CUSTOMFRAME_H__

#include <wx/wx.h>

class CustomDialog : public wxDialog
{
public:
	CustomDialog(const wxString& title);
};
#endif