#include "FontFrame.h"
#include "wx/fontdlg.h"


FontFrame::FontFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* pPanel = new wxPanel(this, -1);

	wxMenuBar* pMenubar = new wxMenuBar;
	wxMenu* pFile = new wxMenu;

	pFile->Append(ID_FONT_DIALOG, wxT("Change Font"));
	pMenubar->Append(pFile, wxT("&File"));
	SetMenuBar(pMenubar);

	Connect(ID_FONT_DIALOG, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(FontFrame::OnSelectFont));

	m_pSt = new wxStaticText(pPanel, wxID_ANY, wxT("Hello World!"));

	Centre();
}

void FontFrame::OnSelectFont(wxCommandEvent& event)
{
	wxFontDialog* pFontDlg = new wxFontDialog(this);
	if (wxID_OK == pFontDlg->ShowModal())
	{
		m_pSt->SetFont(pFontDlg->GetFontData().GetChosenFont());
	}
}