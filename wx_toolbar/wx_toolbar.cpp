#include "wx_toolbar.h"

bool MyApp::OnInit()
{
	wxFrame* pFrame = new MyFrame("wxToolBar", wxPoint(100, 100), wxSize(640, 480));
	pFrame->Show(true);
	
	return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{

	wxMenu* pSubMenu = new wxMenu;
	pSubMenu->Append(wxID_ANY, wxT("Import rss"));
	pSubMenu->Append(wxID_ANY, wxT("Import bookmarks"));
	pSubMenu->Append(wxID_ANY, wxT("Import mail"));

	wxMenu* pMenuFile = new wxMenu;
	pMenuFile->AppendSubMenu(pSubMenu, "&Import");
	pMenuFile->AppendSeparator();
	pMenuFile->Append(wxID_EXIT, wxT("&QUIT"));

	wxMenu* pMenuHelp = new wxMenu;
	pMenuHelp->AppendSeparator();
	pMenuHelp->Append(wxID_ABOUT, "&About", "About the program");

	wxMenuBar* pMenuBar = new wxMenuBar;
	pMenuBar->Append(pMenuFile, "&File");
	pMenuBar->Append(pMenuHelp, "&Help");


	SetMenuBar(pMenuBar);

	CreateStatusBar(3);
	SetStatusText("Welcome to wxToolbar", 2);

	wxBitmap icon(wxT("icon.bmp"), wxBITMAP_TYPE_BMP);

	wxToolBar* pToolbar = new wxToolBar(this, wxID_ANY);
	pToolbar->AddTool(wxID_EXIT, wxT("Exit"), icon.GetSubBitmap(wxRect(0,0,40,40)), wxT("Hello"));
	pToolbar->AddTool(wxID_ABOUT, wxT("About"), icon.GetSubBitmap(wxRect(0, 0, 40, 40)));
	pToolbar->Realize();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("About wxTools", "wxtool", wxOK | wxICON_INFORMATION);
}

wxIMPLEMENT_APP(MyApp);