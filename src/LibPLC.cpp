/***************************************************************
 * Name:      libPLC.cpp
 * Purpose:   Various helping methods used by the Proxxi Login Client
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-16
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#include "../headers/LibPLC.h"

void LibPLC::displayMessage(wxString msg, wxString title)
{
    wxMessageBox(msg, title);
}
bool LibPLC::askYesNoQuestion(wxWindow *parent,wxString question,wxString frameName)
{
    wxMessageDialog yesNoDialog(parent, question, frameName, wxYES_NO);
    if(yesNoDialog.ShowModal() == wxID_YES)
    {
        return true;
    }
    else
    {
        return false;
    }
}
wxString LibPLC::askQuestion(wxWindow *parent, const wxString message, const wxString title)
{
    wxTextEntryDialog dialog(parent, message,title, _(""));
    if(dialog.ShowModal() == wxID_OK)
    {
        return dialog.GetValue();
    }
    else
    {
        return _("");
    }
}
wxString LibPLC::askQuestionMasked(wxWindow *parent, const wxString message, const wxString title)
{

    wxPasswordEntryDialog dialog(parent, message,title, _(""));
    if(dialog.ShowModal() == wxID_OK)
    {
        return dialog.GetValue();
    }
    else
    {
        return _("");
    }
}
wxString LibPLC::getLoginName()
{
    #if defined _WIN64 || defined _WIN32
    char *USER=getenv("username");
    wxString wxLoginName = wxString::FromUTF8(USER);
    #else
    char *USER=getenv("USER");
    wxString wxLoginName = wxString::FromUTF8(USER);
    #endif
    return wxLoginName;
}
string LibPLC::getHostname()
{
    return runAndCapture("hostname");
}
string LibPLC::getIPAddress()
{
    #if defined _WIN64 || defined _WIN32
    string data = runAndCapture("ipconfig");
    std::size_t loc = data.find( "10.0", 0 );
    if(loc != string::npos)
    {
        return data.substr(loc,10);
    }
    #endif
    return "";
}

void LibPLC::configurationMenu(const string cfgName)
{
    system("@echo --Proxxi Login Client Configuration-- & @echo Configuration will be reloaded upon file close... & notepad PLC_cfg.ini");
}

void LibPLC::readConfiguration(const string cfgName, bool &cfgNetworkShares, bool &cfgWindowCloseAllowed)
{
    if(FileIO::fileExists(cfgName))
    {
        string* data = FileIO::readConfig(cfgName);
        //data = FileIO::readConfig(cfgName);
        if(data[0].substr(21,1).compare("1") == 0)
            cfgNetworkShares = true;
        else
            cfgNetworkShares = false;
        if(data[1].substr(21,1).compare("1") == 0)
            cfgWindowCloseAllowed = true;
        else
            cfgWindowCloseAllowed = false;
    }
    else
    {
        FileIO::generateDefaultConfig(cfgName);
        cfgNetworkShares = true;
        cfgWindowCloseAllowed = true;
    }
}
#if defined _WIN64 || defined _WIN32
LPWSTR LibPLC::ConvertToLPWSTR( const string& s )
{
  LPWSTR ws = new wchar_t[s.size()+1]; // +1 for zero at the end
  copy( s.begin(), s.end(), ws );
  ws[s.size()] = 0; // zero at the end
  return ws;
}
#endif

string LibPLC::runAndCapture(const string cmd)
{
    #if defined _WIN64 || defined _WIN32
    FILE* pipe = _popen(cmd.c_str(), "r");
    #else
    FILE* pipe = popen(cmd.c_str(), "r");
    #endif
    if (!pipe) return "";
    char buffer[128];
    string result = "";
    while(!feof(pipe)) {
    	if(fgets(buffer, 128, pipe) != NULL)
    		result += buffer;
    }
    #if defined _WIN64 || defined _WIN32
    _pclose(pipe);
    #else
    pclose(pipe);
    #endif
    return result;
}
void LibPLC::run(const string command)
{
    #if defined _WIN64 || defined _WIN32
        ShellExecute(NULL,_T("open"),_T("cmd"),LibPLC::ConvertToLPWSTR("/Q /C "+command),NULL,SW_SHOWMINIMIZED);
        //ShellExecute(NULL,_T("open"),_T("cmd"),LibPLC::ConvertToLPWSTR("/Q /C "+command),LibPLC::ConvertToLPWSTR(inFolder),SW_SHOWMINIMIZED);
    #endif
}
void LibPLC::openWebPage(const string url)
{
       #if defined _WIN64 || defined _WIN32
       ShellExecute(NULL, _T("open"), LibPLC::ConvertToLPWSTR(url),NULL, NULL, SW_SHOWMINIMIZED);
       #endif
}
void LibPLC::mountNetworkShares()
{
    #if defined _WIN64 || defined _WIN32
    string publicUploadCMD = "net use P: \\\\10.0.0.20\\Skyrim /P:No";
    string neosNetworkShare = "net use N: \\\\10.0.0.1\\NeosServer /P:No";
    string copyShortcutsCMD = "copy \"Public(Skyrim).lnk\" \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
    copyShortcutsCMD += " & copy NeosServer.lnk \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
    run("echo Mounting network shares... & "+publicUploadCMD+" & "+neosNetworkShare+" & echo Copying shortcuts... & "+copyShortcutsCMD);
    #endif
}
void LibPLC::disconnectNetworkShares()
{
    #if defined _WIN64 || defined _WIN32
    string unMountPublicCMD = "net use P: /delete /Y";
    unMountPublicCMD += " & ney yse N: /delete /Y";
    string deleteShortcutsCMD = "del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Public(Skyrim).lnk\"";
    deleteShortcutsCMD += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\NeosServer.lnk\"";
    run("echo Disconnecting network shares... & "+unMountPublicCMD+" & echo Removing shortcuts... & "+deleteShortcutsCMD);
    #endif
}
/*
void LibPLC::mountNetworkShares(bool cfgNetworkShares, wxString wxLoginName, wxString wxPassword)
{
    if(cfgNetworkShares)
    {

        #if defined _WIN64 || defined _WIN32
            string usr = string(wxLoginName.mb_str());
            string pass = string(wxPassword.mb_str());
            string mountHomeCMD = "net use H: \"\\\\10.0.0.5\\profiles\\My Documents\" /User:PROXXI\\"+usr+" "+pass+" /P:No";
            string mountPublicCMD = "net use G: \\\\10.0.0.5\\Everest\\saved\\Media /User:PROXXI\\"+usr+" "+pass+" /P:No";
            string mountPublic2CMD = "net use O: \\\\10.0.0.5\\Akkas /User:PROXXI\\"+usr+" "+pass+" /P:No";
            string mountPublicUploadCMD = "net use U: \\\\10.0.0.5\\Everest\\Upload\\Upload /User:PROXXI\\"+usr+" "+pass+" /P:No";
            string shellExecuteArguments = mountHomeCMD+" & "+mountPublicCMD+" & " +mountPublic2CMD+" & "+mountPublicUploadCMD;
            runSystemCommandSilently(shellExecuteArguments, "C:\\Windows\\System32");
            shellExecuteArguments = "copy \"Media (G).lnk\" \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
            shellExecuteArguments += " & copy \"Akkas (O).lnk\" \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
            shellExecuteArguments += " & copy \"Upload (U).lnk\" \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
            shellExecuteArguments += " & copy \"My Documents (H).lnk\" \"C:\\Users\\%USERNAME%\\Desktop\\\" /Y";
            runSystemCommandSilently(shellExecuteArguments, "C:\\Proxxi_Login_Client");
        #endif
    }
}

void LibPLC::disconnectNetworkShares()
{
    #if defined _WIN64 || defined _WIN32
        string unMountHomeCMD = "net use H: /delete /Y";
        string unMountPublicCMD = "net use G: /delete /Y";
        string unMountPublic2CMD = "net use O: /delete /Y";
        string unMountPublicUploadCMD = "net use U: /delete /Y";
        string shellExecuteArguments = unMountHomeCMD+" & "+unMountPublicCMD+" & "+unMountPublic2CMD+" & "+unMountPublicUploadCMD;
        runSystemCommandSilently(shellExecuteArguments, "C:\\Windows\\System32");
        shellExecuteArguments = "del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Media (G).lnk\"";
        shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Akkas (O).lnk\"";
        shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Upload (U).lnk\"";
        shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\My Documents (H).lnk\"";
        runSystemCommandSilently(shellExecuteArguments, "C:\\Proxxi_Login_Client");
    #endif
}
*/
