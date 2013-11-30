/***************************************************************
 * Name:      libPLC.cpp
 * Purpose:   Various helping methods used by the Proxxi Login Client
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#include "../headers/LibPLC.h"

void LibPLC::displayMessage(wxString msg, wxString title)
{
    wxMessageBox(msg, title);
}
bool LibPLC::askQuestion(wxWindow *parent, wxString q, wxString f)
{
    wxMessageDialog yesNoDialog(parent, q, f, wxYES_NO);
    if(yesNoDialog.ShowModal() == wxID_YES)
    {
        return true;
    }
    else
    {
        return false;
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
void LibPLC::configurationMenu(string cfgName)
{
    system("@ECHO --Proxxi Login Client Configuration-- & @echo Configuration will be reloaded upon file close... & notepad PLC_cfg.ini");
}

void LibPLC::readConfiguration(string cfgName, bool &cfgNetworkShares, bool &cfgWindowCloseAllowed)
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

LPWSTR LibPLC::ConvertToLPWSTR( const string& s )
{
  LPWSTR ws = new wchar_t[s.size()+1]; // +1 for zero at the end
  copy( s.begin(), s.end(), ws );
  ws[s.size()] = 0; // zero at the end
  return ws;
}

void LibPLC::runSystemCommandSilently(string command, string inFolder)
{
    #if defined _WIN64 || defined _WIN32
    ShellExecute(NULL,_T("open"),_T("cmd"),LibPLC::ConvertToLPWSTR("/q /c "+command),LibPLC::ConvertToLPWSTR(inFolder),SW_SHOWMINIMIZED);
    #endif
}

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
void LibPLC::disconnectNetworkShares(bool cfgNetworkShares)
{
    if(cfgNetworkShares)
    {
        #if defined _WIN64 || defined _WIN32
            string unMountHomeCMD = "net use H: /delete /Y";
            string unMountPublicCMD = "net use G: /delete /Y";
            string unMountPublic2CMD = "net use O: /delete /Y";
            string unMountPublicUploadCMD = "net use U: /delete /Y";
            string shellExecuteArguments = "/q /c "+unMountHomeCMD+" & "+unMountPublicCMD+" & "+unMountPublic2CMD+" & "+unMountPublicUploadCMD;
            runSystemCommandSilently(shellExecuteArguments, "C:\\Windows\\System32");
            shellExecuteArguments = "/q /c del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Media (G).lnk\"";
            shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Akkas (O).lnk\"";
            shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\Upload (U).lnk\"";
            shellExecuteArguments += " & del /F /Q \"C:\\Users\\%USERNAME%\\Desktop\\My Documents (H).lnk\"";
            runSystemCommandSilently(shellExecuteArguments, "C:\\Proxxi_Login_Client");
        #endif
    }

}
