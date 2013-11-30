/***************************************************************
 * Name:      Proxxi_Login_ClientApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Created:   2013-11-03
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:
 **************************************************************/

#include "Proxxi_Login_ClientApp.h"

//(*AppHeaders
#include "Proxxi_Login_ClientMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Proxxi_Login_ClientApp);

bool Proxxi_Login_ClientApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Proxxi_Login_ClientFrame* Frame = new Proxxi_Login_ClientFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
