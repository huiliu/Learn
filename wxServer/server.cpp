#include "server.h"

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{

	wxPanel* pPanel = new wxPanel(this, wxID_ANY);
	wxSizer* pSizer = new wxBoxSizer(wxHORIZONTAL);

	m_pBtnServer = new BtnServer(pPanel, "Start Server");

	m_pBtnClient = new BtnClient(pPanel, "Start Client");

	pSizer->Add(m_pBtnServer);
	pSizer->Add(m_pBtnClient);

	pPanel->SetSizer(pSizer);


}

wxBEGIN_EVENT_TABLE(BtnServer, wxButton)
EVT_BUTTON(ID_BTN_SERVER, BtnServer::OnClicked)
wxEND_EVENT_TABLE()


wxBEGIN_EVENT_TABLE(BtnClient, wxButton)
EVT_BUTTON(ID_BTN_CLIENT, BtnClient::OnClicked)
wxEND_EVENT_TABLE()

BtnServer::BtnServer(wxWindow* parent, const wxString& label)
	: wxButton(parent, ID_BTN_SERVER, label)
{

}

void BtnServer::OnClicked(wxCommandEvent& event)
{
	{
		wxIPV4address addr;
		addr.Service(3000);

		/*wxSocketServer**/ m_pServer = new wxSocketServer(addr);
		if (!m_pServer->IsOk())
		{
			wxLogMessage("failed to open socket!");
			return;
		}

		wxIPV4address realIp;
		if (m_pServer->GetLocal(realIp))
		{
			wxLogMessage("Server Listening at %s:%u", realIp.IPAddress(), realIp.Service());
		}

		m_pServer->SetEventHandler(*this, ID_BTN_SERVER);
		m_pServer->SetNotify(wxSOCKET_CONNECTION_FLAG);
		m_pServer->Notify(true);
	}
}


void BtnServer::OnServerEvent(wxSocketEvent& event)
{
	switch (event.GetSocketEvent())
	{
	case wxSOCKET_CONNECTION:
	{
		wxLogMessage("New connect comming in!");
	}
	break;
	default:
		break;
	}

	wxSocketBase* pSock = m_pServer->Accept(false);

	if (nullptr == pSock)
	{
		return;
	}

	pSock->SetEventHandler(*this, ID_SOCKET_CONN);
	pSock->SetNotify(wxSOCKET_INPUT_FLAG | wxSOCKET_LOST_FLAG);
	pSock->Notify(true);
}


void BtnServer::OnSocketEvent(wxSocketEvent& event)
{

}

BtnClient::BtnClient(wxWindow* parent, const wxString& label)
	: wxButton(parent, ID_BTN_CLIENT, label)
{

}

void BtnClient::OnClicked(wxCommandEvent& event)
{
	wxIPV4address ip;
	
}

void BtnClient::OnClientEvent(wxSocketEvent& event)
{

}

void BtnClient::OnSocketEvent(wxSocketEvent& event)
{

}