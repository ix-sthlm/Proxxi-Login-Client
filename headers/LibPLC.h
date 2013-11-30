/***************************************************************
 * Name:      libPLC.h
 * Purpose:   Various helping methods used by the Proxxi Login Client
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/
#ifndef LibPLC_H
#define LibPLC_H
#include <wx/msgdlg.h>
#include <string>
#include <wx/string.h>
#if defined _WIN64 || defined _WIN32
#include <windows.h>
#endif
#include "../headers/FileIO.h"
using std::string;
namespace LibPLC{
    void displayMessage(wxString msg, wxString title);
    bool askQuestion(wxWindow *parent, wxString q, wxString f);
    wxString getLoginName();
    void configurationMenu(string cfgName);
    void readConfiguration(string cfgName, bool &cfgNetworkShares, bool &cfgWindowCloseAllowed);
    LPWSTR ConvertToLPWSTR( const string& s );
    void runSystemCommandSilently(string command, string inFolder);
    void mountNetworkShares(bool cfgNetworkShares, wxString wxLoginName, wxString wxPassword);
    void disconnectNetworkShares(bool cfgNetworkShares);
}
#endif //LibPLC.h
