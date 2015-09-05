#pragma once
#include <wx/wx.h>
#include <wx/socket.h>

class MyFrame : public wxFrame
{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
	wxButton* m_pBtnServer;
	wxButton* m_pBtnClient;
};

enum MyEnum
{
	ID_BTN_SERVER = 0,
	ID_BTN_CLIENT = 1,
	ID_SOCKET_SERVER = 2,
	ID_SOCKET_CLIENT = 3,
	ID_SOCKET_CONN = 4,
};

class BtnServer : public wxButton
{
public:
	BtnServer(wxWindow* parent, const wxString& label);

	wxDECLARE_EVENT_TABLE();

private:
	void OnClicked(wxCommandEvent& event);
	void OnServerEvent(wxSocketEvent& event);
	void OnSocketEvent(wxSocketEvent& event);

private:
	wxSocketServer* m_pServer;
};

class BtnClient : public wxButton
{
public:
	BtnClient(wxWindow* parent, const wxString& label);

	wxDECLARE_EVENT_TABLE();

private:
	void OnClicked(wxCommandEvent& event);
	void OnClientEvent(wxSocketEvent& event);
	void OnSocketEvent(wxSocketEvent& event);
private:
	wxSocketServer* m_pClient;
};
