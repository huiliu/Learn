#include <wx/wx.h>
#include "BoxLayoutFrame.h"
#include "GridLayout.h"
#include "FlexGridLayout.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

bool MyApp::OnInit()
{
	// wxFrame* pFrame = new BoxFrame("Layout");
	// wxFrame* pFrame = new GridFrame("GridLayout");
	wxFrame* pFrame = new FlexGridFrame("FlexGridLayout");
	pFrame->Show(true);

	return true;
}

wxIMPLEMENT_APP(MyApp);