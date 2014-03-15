/***************************************************************
 * Name:      Proxxi_Login_ClientMain.h
 * Purpose:   Application mainframe.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-09(r0)
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#ifndef PROXXI_LOGIN_CLIENTMAIN_H
#define PROXXI_LOGIN_CLIENTMAIN_H
#include <wx/dcclient.h>
//(*Headers(Proxxi_Login_ClientFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/timer.h>
//*)
#if defined _WIN64 || defined _WIN32
#include <windows.h>
#include <Lmcons.h>
#else   //Presume the system is a UNIX compatible system
#include <stdlib.h>
#endif
#include "headers/libPLC.h"
#include "headers/Authentication.h"
using std::string;

class Proxxi_Login_ClientFrame: public wxFrame
{
    public:

        Proxxi_Login_ClientFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Proxxi_Login_ClientFrame();

    private:
        //Variables
        wxString wxRealName;
        wxString wxLoginName;
        wxString wxPassword;
        wxString wxAppVersion = wxT("2014-03-16(r0)");  //Used int the "about" box
        wxString wxTitle = wxT("Proxxi Login Client V"+wxAppVersion);
        wxString wxLoginTimeText = wxT("Inloggningstid: 0T 0M 0S");
        wxString wxNetworkInfo = wxT("");
        string cfgName = "PLC_cfg.ini";
        string multiLoginHost = "";
        int updateTimerSecs = 0;
        int updateRetryCountdown = 0;
        int logonTime = 0;
        int failedRequests = 0;
        bool connected = false;
        bool networkSharesMounted = false;
        bool cfgNetworkShares = false;
        bool cfgWindowCloseAllowed = true;
        //Private methods
        void OnPaint(wxPaintEvent& event);
        //(*Handlers(Proxxi_Login_ClientFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnloginButtonClick(wxCommandEvent& event);
        void OnlogoutButtonClick(wxCommandEvent& event);
        void OntfPasswordTextEnter(wxCommandEvent& event);
        void OnOpenConfigurationMenu(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnsessionTimerTrigger(wxTimerEvent& event);
        void OntfPasswordText(wxCommandEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void onMultibleLoginsMenu(wxCommandEvent& event);
        void OnRegisterNewUser(wxCommandEvent& event);
        void OnRegisterNewUserMenu(wxCommandEvent& event);
        //*)

        //(*Identifiers(Proxxi_Login_ClientFrame)
        static const long ID_tf_username;
        static const long ID_tf_Password;
        static const long ID_userloginLabel;
        static const long ID_loginButton;
        static const long ID_logoutButton;
        static const long ID_LOGONTIMELABEL;
        static const long id_registerNewUser;
        static const long id_multibleLogins;
        static const long id_changeConfig;
        static const long ID_CLOSE;
        static const long ID_About;
        static const long ID_sessionTimer;
        //*)

        //(*Declarations(Proxxi_Login_ClientFrame)
        wxMenuItem* MenuItem2;
        wxTimer sessionTimer;
        wxMenuItem* MenuItem1;
        wxButton* logoutButton;
        wxStaticText* userloginLabel;
        wxMenuItem* menuClose;
        wxTextCtrl* tfUsername;
        wxStaticText* labelLogonTime;
        wxButton* loginButton;
        wxMenuItem* menuChangeConfiguration;
        wxTextCtrl* tfPassword;
        //*)

        DECLARE_EVENT_TABLE()

        //GUI Methods
        void handleClosing();
        void aboutProgram();
        void login();
        void logout();
        void timerTriggered();
        void configurationMenu();
        void multibleLogins();
        void registerNewUser();
        void updateNetworkInfo();
        void updateLogonTimeLabel();

        //GUI HELPING METHODS
        void readConfiguration();
        #if defined _WIN64 || defined _WIN32
        LPWSTR ConvertToLPWSTR( const string& s ); //http://stackoverflow.com/questions/1200188/how-to-convert-stdstring-to-lpcstr
        #endif
        void displayNoConnectionError();
        void mountNetworkShares();
        void disconnectNetworkShares();
};

#endif // PROXXI_LOGIN_CLIENTMAIN_H
