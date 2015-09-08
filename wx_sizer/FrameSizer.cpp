#include "FrameSizer.h"
#include "CliCtrl.h"


FrameSizer::FrameSizer(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxDefaultSize)
{
	m_pTextCtrl = new CliCtrl(this, ID_TEXTCTRL, LINEPREFIX,
		wxDefaultPosition, 
		wxDefaultSize, 
		wxTE_MULTILINE | wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB);
}
