#include "FileFrame.h"

FileFrame::FileFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title)
{
	wxMenuBar* pMenuBar = new wxMenuBar;
	wxMenu* pFile = new wxMenu;
	pFile->Append(wxID_OPEN, wxT("&Open"));
	pFile->AppendSeparator();
	pFile->Append(wxID_SAVE, wxT("&Save"));
	pFile->Append(wxID_EXIT, wxT("&Exit"));

	pMenuBar->Append(pFile, wxT("&File"));

	SetMenuBar(pMenuBar);

	Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(FileFrame::OnOpen));
	Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(FileFrame::OnSave));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(FileFrame::OnExit));

	m_pTc = new wxTextCtrl(this, -1, wxT(""), wxPoint(-1, -1), wxSize(-1, -1), wxTE_MULTILINE);
	Centre();
}

FileFrame::~FileFrame()
{

}

void FileFrame::OnOpen(wxCommandEvent& event)
{
	wxFileDialog* pFileDlg = new wxFileDialog(this);
	if (pFileDlg->ShowModal() == wxID_OK)
	{
		wxString fileName = pFileDlg->GetPath();
		m_pTc->LoadFile(fileName);
	}
}

void FileFrame::OnSave(wxCommandEvent& event)
{
	wxFileDialog* pFileDlg = new wxFileDialog(this);
	if (pFileDlg->ShowModal() == wxID_OK)
	{
		wxString fileName = pFileDlg->GetPath();
		m_pTc->SaveFile(fileName);
	}
}

void FileFrame::OnExit(wxCommandEvent& event)
{
	Close();
}