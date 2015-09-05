
#include <wx/wx.h>
#include <wx/socket.h>
#include "server.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	wxSocketServer* m_pServ;
};

bool MyApp::OnInit()
{
	wxFrame* pFrame = new MyFrame("NetServer", wxDefaultPosition, wxDefaultSize);
	pFrame->Show(true);

	wxIPV4address host;
	host.AnyAddress();
	host.Service(3000);

	m_pServ = new wxSocketServer(host, wxSOCKET_NOWAIT);	

	return true;
}

IMPLEMENT_APP(MyApp);