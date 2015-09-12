#include <wx/wx.h>
#include "MessageFrame.h"
#include "FileFrame.h"
#include "FontFrame.h"

class MyApp :public wxApp
{
public:
	virtual bool OnInit()
	{
		// wxFrame* pFrame = new MessageFrame("Dialog");
		// wxFrame* pFrame = new FileFrame("FileDialog");
		wxFrame* pFrame = new FontFrame("FontDialog");
		pFrame->Show(true);

		return true;
	}
};

wxIMPLEMENT_APP(MyApp);