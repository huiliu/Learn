#include "GridLayout.h"

GridFrame::GridFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(270,220))
{
	wxMenuBar* pMenubar = new wxMenuBar();
	wxMenu* pFile = new wxMenu;
	SetMenuBar(pMenubar);

	wxBoxSizer* pvbox = new wxBoxSizer(wxVERTICAL);
	
	wxTextCtrl* pTextCtrl = new wxTextCtrl(this,
		-1,
		wxT(""),
		wxDefaultPosition,
		wxDefaultSize,
		wxTE_RIGHT);
	pvbox->Add(pTextCtrl, 0, wxEXPAND | wxTOP | wxBOTTOM, 4);

	wxGridSizer* pGs = new wxGridSizer(4, 5, 3, 3);
	pGs->Add(new wxButton(this, -1, wxT("Cls")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("Bck")), 0, wxEXPAND);
	pGs->Add(new wxStaticText(this, -1, wxT("")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("Close")), 0, wxEXPAND);

	pGs->Add(new wxButton(this, -1, wxT("7")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("8")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("9")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("/")), 0, wxEXPAND);
	
	pGs->Add(new wxButton(this, -1, wxT("4")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("5")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("6")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("*")), 0, wxEXPAND);
	
	pGs->Add(new wxButton(this, -1, wxT("1")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("2")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("3")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("-")), 0, wxEXPAND);
	
	pGs->Add(new wxButton(this, -1, wxT("0")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT(".")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("=")), 0, wxEXPAND);
	pGs->Add(new wxButton(this, -1, wxT("+")), 0, wxEXPAND);

	pvbox->Add(pGs, 1, wxEXPAND);
	SetSizer(pvbox);
	SetMinSize(GetClientSize());
	Centre();
}

GridFrame::~GridFrame()
{
	delete m_pPanel;
}