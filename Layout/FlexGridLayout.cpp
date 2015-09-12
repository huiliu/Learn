#include "FlexGridLayout.h"

FlexGridFrame::FlexGridFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title)
{
	m_pPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* phBox = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer* pFGs = new wxFlexGridSizer(3, 2, 9, 25);

	wxStaticText* ptitle = new wxStaticText(m_pPanel, -1, wxT("Title"));
	wxStaticText* pauthor = new wxStaticText(m_pPanel, -1, wxT("Author"));
	wxStaticText* preview = new wxStaticText(m_pPanel, -1, wxT("Review"));

	wxTextCtrl* tc1 = new wxTextCtrl(m_pPanel, wxID_ANY);
	wxTextCtrl* tc2 = new wxTextCtrl(m_pPanel, wxID_ANY);
	wxTextCtrl* tc3 = new wxTextCtrl(m_pPanel, wxID_ANY, wxT(""),
		wxPoint(-1,-1),
		wxSize(-1,-1),
		wxTE_MULTILINE);

	pFGs->Add(ptitle);
	pFGs->Add(tc1, 1, wxEXPAND);
	pFGs->Add(pauthor);
	pFGs->Add(tc2, 1, wxEXPAND);
	pFGs->Add(preview, 1, wxEXPAND);
	pFGs->Add(tc3,1, wxEXPAND);

	pFGs->AddGrowableRow(2, 1);
	pFGs->AddGrowableCol(1, 1);

	phBox->Add(pFGs, 1, wxALL | wxEXPAND, 15);
	
	m_pPanel->SetSizer(phBox);
	
	Centre();
}