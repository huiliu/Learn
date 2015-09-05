/////////////////////////////////////////////////////////////////////////////
// Name:        minimal.cpp
// Purpose:     Minimal wxWidgets sample
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id$
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

class MyFrame;
enum MyEnum
{
	ID_HELLO = 1
};

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
	void OnHello(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_HELLO, MyFrame::OnHello)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);
bool MyApp::OnInit()
{
	MyFrame* pFrame = new MyFrame("Hello", wxPoint(100, 100), wxSize(640, 480));
	pFrame->Show(true);
	//SetTopWindow(pFrame);

	return true;
}


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	:wxFrame(nullptr, wxID_ANY, title, pos, size)
{
	wxMenu* pMenu = new wxMenu;
	pMenu->Append(ID_HELLO, "&Hello...\tCtrl-H",
		"Help String shown in status bar");
	pMenu->AppendSeparator();
	pMenu->Append(wxID_EXIT);

	wxMenu* pMenuHelp = new wxMenu;
	pMenuHelp->Append(wxID_ABOUT);

	wxMenuBar* pMenuBar = new wxMenuBar;
	pMenuBar->Append(pMenu, "&File");
	pMenuBar->Append(pMenuHelp, "&Help");

	SetMenuBar(pMenuBar);

	CreateStatusBar();
	SetStatusText("Welcome to Wxwidgets!");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("This is a wxwidgets' Hello World sample",
		"About Hello world", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
	wxLogMessage("Hello world from wxwidgets!");
}

