#include "FrameSizer.h"
#include <wx/wx.h>
#include "trie.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();

};


bool MyApp::OnInit()
{
	wxFrame* pFrame = new FrameSizer("FrameSizer");
	pFrame->Show(true);

	return true;
}

IMPLEMENT_APP(MyApp);

