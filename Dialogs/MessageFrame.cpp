#include "MessageFrame.h"

MessageFrame::MessageFrame(const wxString& title)
	: wxFrame(nullptr, wxID_ANY, title)
{
	wxPanel* pPanel = new wxPanel(this, wxID_ANY);

	wxBoxSizer* phBox = new wxBoxSizer(wxHORIZONTAL);
	wxGridSizer* pgs = new wxGridSizer(2, 2, 2, 2);

	wxButton* btn1 = new wxButton(pPanel, ID_INFO, wxT("Info"));
	wxButton* btn2 = new wxButton(pPanel, ID_ERROR, wxT("出错"));
	wxButton* btn3 = new wxButton(pPanel, ID_QUESTION, wxT("Ques"));
	wxButton* btn4 = new wxButton(pPanel, ID_ALERT, wxT("Alert"));

	Connect(ID_INFO, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageFrame::ShowMesg1));
	Connect(ID_ERROR, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageFrame::ShowMesg2));
	Connect(ID_QUESTION, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageFrame::ShowMesg3));
	Connect(ID_ALERT, wxEVT_COMMAND_BUTTON_CLICKED,
		wxCommandEventHandler(MessageFrame::ShowMesg4));

	pgs->Add(btn1, 1, wxEXPAND);
	pgs->Add(btn2, 1, wxEXPAND);
	pgs->Add(btn3, 1, wxEXPAND);
	pgs->Add(btn4, 1, wxEXPAND);

	phBox->Add(pgs, 1, wxALL, 15);
	pPanel->SetSizer(phBox);
	
	Centre();
}

MessageFrame::~MessageFrame()
{

}

void MessageFrame::ShowMesg1(wxCommandEvent& event)
{
	wxMessageDialog* pdialog = new wxMessageDialog(nullptr, wxT("下载完成！"),
		wxT("iInfo"), wxOK|wxICON_INFORMATION);
	pdialog->ShowModal();
}

void MessageFrame::ShowMesg2(wxCommandEvent& event)
{
	wxMessageDialog* pdialog = new wxMessageDialog(nullptr, wxT("下载完成！"),
		wxT("iInfo"), wxOK | wxICON_ERROR);
	pdialog->ShowModal();
}

void MessageFrame::ShowMesg3(wxCommandEvent& event)
{
	wxMessageDialog* pdialog = new wxMessageDialog(nullptr, wxT("下载完成！"),
		wxT("iInfo"), wxYES_NO|wxNO_DEFAULT | wxICON_QUESTION);
	int ret = pdialog->ShowModal();
	if (wxID_YES == ret)
	{
		wxMessageBox(wxT("你点击了Yes!"), wxT("通知"));
	}
	else if ( wxID_NO == ret)
	{
		wxMessageBox(wxT("你点击了NO"), wxT("通知"));
	}
}

void MessageFrame::ShowMesg4(wxCommandEvent& event)
{
	wxMessageDialog* pdialog = new wxMessageDialog(nullptr, wxT("下载完成！"),
		wxT("iInfo"), wxOK | wxICON_EXCLAMATION);
	int ret = pdialog->ShowModal();
	if (wxID_OK == ret)
	{
		wxMessageBox(wxT("你点击了OK!"), wxT("通知"));
	}
}