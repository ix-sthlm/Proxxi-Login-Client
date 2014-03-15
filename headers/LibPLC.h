/***************************************************************
 * Name:      libPLC.h
 * Purpose:   Various helping methods used by the Proxxi Login Client
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-09
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/
#ifndef LibPLC_H
#define LibPLC_H
#include <wx/msgdlg.h>
#include <wx/textdlg.h>
#include <string>
#include <stdio.h>
#include <wx/string.h>
#if defined _WIN64 || defined _WIN32
#include <windows.h>
#endif
#include "../headers/FileIO.h"
using std::string;
namespace LibPLC{
    void displayMessage(const wxString msg,const wxString title);
    bool askYesNoQuestion(wxWindow *parent,wxString question,wxString frameName);
    wxString askQuestion(wxWindow *parent, const wxString title,const wxString message);
    wxString askQuestionMasked(wxWindow *parent, const wxString title,const wxString message);
    wxString getLoginName();
    void run(const string command);
    void openWebPage(const string url);
    string runAndCapture(const string cmd);
    void configurationMenu(const string cfgName);
    void readConfiguration(const string cfgName, bool &cfgNetworkShares, bool &cfgWindowCloseAllowed);
    LPWSTR ConvertToLPWSTR(const string& s);
    void runSystemCommandSilently(const string command);
    void mountNetworkShares();
    void disconnectNetworkShares();
    string getHostname();
    string getIPAddress();
}
#endif //LibPLC.h
