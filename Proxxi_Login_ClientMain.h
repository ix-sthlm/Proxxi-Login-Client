/***************************************************************
 * Name:      Proxxi_Login_ClientMain.h
 * Purpose:   Defines Application Frame
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Created:   2013-11-03
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:
 **************************************************************/

#ifndef PROXXI_LOGIN_CLIENTMAIN_H
#define PROXXI_LOGIN_CLIENTMAIN_H

//(*Headers(Proxxi_Login_ClientFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/timer.h>
//*)

class Proxxi_Login_ClientFrame: public wxFrame
{
    public:

        Proxxi_Login_ClientFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Proxxi_Login_ClientFrame();

    private:

        //(*Handlers(Proxxi_Login_ClientFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnloginButtonClick(wxCommandEvent& event);
        void OnlogoutButtonClick(wxCommandEvent& event);
        void OntfPasswordTextEnter(wxCommandEvent& event);
        void OnOpenConfigurationMenu(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnsessionTimerTrigger(wxTimerEvent& event);
        //*)

        //(*Identifiers(Proxxi_Login_ClientFrame)
        static const long ID_titleLabel;
        static const long ID_tf_username;
        static const long ID_tf_Password;
        static const long ID_userloginLabel;
        static const long ID_loginButton;
        static const long ID_logoutButton;
        static const long ID_LOGONTIMELABEL;
        static const long ID_copyrightLabel;
        static const long ID_PANEL;
        static const long id_changeConfig;
        static const long ID_About;
        static const long ID_sessionTimer;
        //*)

        //(*Declarations(Proxxi_Login_ClientFrame)
        wxStaticText* copyrightLabel;
        wxTimer sessionTimer;
        wxButton* logoutButton;
        wxStaticText* userloginLabel;
        wxStaticText* titleLabel;
        wxTextCtrl* tfUsername;
        wxStaticText* labelLogonTime;
        wxButton* loginButton;
        wxMenuItem* menuChangeConfiguration;
        wxTextCtrl* tfPassword;
        wxPanel* Panel;
        //*)

        DECLARE_EVENT_TABLE()

        //GUI Methods
        void handleClosing();
        void aboutProgram();
        void login();
        void logout();
        void timerTriggered();
        void configurationMenu();

        //GUI HELPING METHODS
        void readConfiguration();
        //LPWSTR ConvertToLPWSTR( const string& s ); //http://stackoverflow.com/questions/1200188/how-to-convert-stdstring-to-lpcstr
        wxString getLoginName();
        void displayNoConnectionError();
        void mountNetworkShares();
        void disconnectNetworkShares();
};

#endif // PROXXI_LOGIN_CLIENTMAIN_H
