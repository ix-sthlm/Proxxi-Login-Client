/***************************************************************
 * Name:      Kira_Login_Client_CPP_EditionMain.cpp
 * Purpose:   Application mainframe.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-30(r0)
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#include "Proxxi_Login_ClientMain.h"
#include <wx/msgdlg.h>

#if defined _WIN64 || defined _WIN32
#include <windows.h>
#include <Lmcons.h>
#else   //Presume the system is a UNIX compatible system
#include <stdlib.h>
#endif
#include "headers/libPLC.h"
#include "headers/CURLComm.h"
#include "headers/LoginValidation.h"
#include "headers/FileIO.h"
wxString wxRealName;
wxString wxLoginName;
wxString wxPassword;
wxString wxAppVersion = wxT("2013-11-30(R0)");  //Used int the "about" box
wxString wxTitle = wxT("Proxxi Login Client V"+wxAppVersion);
wxString wxLoginTimeText = wxT("Inloggningstid: 0T 0M 0S");
string cfgName = "PLC_cfg.ini";
int updateTimerSecs = 0;
int updateRetryCountdown = 0;
int logonTime = 0;
int failedRequests = 0;
bool connected = false;
bool networkSharesMounted = false;
bool cfgNetworkShares = false;
bool cfgWindowCloseAllowed = true;
//(*InternalHeaders(Proxxi_Login_ClientFrame)
#include <wx/bitmap.h>
#include <wx/icon.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/image.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(Proxxi_Login_ClientFrame)
const long Proxxi_Login_ClientFrame::ID_titleLabel = wxNewId();
const long Proxxi_Login_ClientFrame::ID_tf_username = wxNewId();
const long Proxxi_Login_ClientFrame::ID_tf_Password = wxNewId();
const long Proxxi_Login_ClientFrame::ID_userloginLabel = wxNewId();
const long Proxxi_Login_ClientFrame::ID_loginButton = wxNewId();
const long Proxxi_Login_ClientFrame::ID_logoutButton = wxNewId();
const long Proxxi_Login_ClientFrame::ID_LOGONTIMELABEL = wxNewId();
const long Proxxi_Login_ClientFrame::ID_copyrightLabel = wxNewId();
const long Proxxi_Login_ClientFrame::ID_PANEL = wxNewId();
const long Proxxi_Login_ClientFrame::id_changeConfig = wxNewId();
const long Proxxi_Login_ClientFrame::ID_About = wxNewId();
const long Proxxi_Login_ClientFrame::ID_sessionTimer = wxNewId();
//*)

BEGIN_EVENT_TABLE(Proxxi_Login_ClientFrame,wxFrame)
    //(*EventTable(Proxxi_Login_ClientFrame)
    //*)
END_EVENT_TABLE()

Proxxi_Login_ClientFrame::Proxxi_Login_ClientFrame(wxWindow* parent,wxWindowID id)
{
    wxString wxLoginName = LibPLC::getLoginName();
    //(*Initialize(Proxxi_Login_ClientFrame)
    wxMenuItem* MenuAbout;
    wxMenu* Menu1;
    wxMenu* helpMenu;
    wxMenuBar* MenuBar1;

    Create(parent, id, _("PROXXI LOGIN CLIENT V"+wxAppVersion), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(346,396));
    SetMinSize(GetSize());
    SetMaxSize(GetSize());
    {
        if(FileIO::fileExists("Avatar_Window_Icon.png"))
        {
            wxIcon FrameIcon;
            FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("Avatar_Window_Icon.png"))));
            SetIcon(FrameIcon);
        }
    }
    Panel = new wxPanel(this, ID_PANEL, wxPoint(40,40), wxSize(346,396), wxTAB_TRAVERSAL, _T("ID_PANEL"));
    Panel->SetBackgroundColour(wxColour(39,43,57));
    titleLabel = new wxStaticText(Panel, ID_titleLabel, _("PROXXI LOGIN CLIENT\n"), wxPoint(40,16), wxDefaultSize, 0, _T("ID_titleLabel"));
    titleLabel->SetForegroundColour(wxColour(255,255,255));
    titleLabel->SetBackgroundColour(wxColour(39,43,57));
    wxFont titleLabelFont(18,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    titleLabel->SetFont(titleLabelFont);
    tfUsername = new wxTextCtrl(Panel, ID_tf_username, (wxLoginName), wxPoint(64,72), wxSize(224,32), 0, wxDefaultValidator, _T("ID_tf_username"));
    wxFont tfUsernameFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    tfUsername->SetFont(tfUsernameFont);
    tfPassword = new wxTextCtrl(Panel, ID_tf_Password, _(""), wxPoint(64,120), wxSize(224,32), wxTE_PASSWORD, wxDefaultValidator, _T("ID_tf_Password"));
    wxFont tfPasswordFont(12,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    tfPassword->SetFont(tfPasswordFont);
    userloginLabel = new wxStaticText(Panel, ID_userloginLabel, _("Vänligen logga in\n"+wxLoginName), wxPoint(64,160), wxSize(288,48), 0, _T("ID_userloginLabel"));
    userloginLabel->SetForegroundColour(wxColour(255,255,255));
    userloginLabel->SetBackgroundColour(wxColour(39,43,57));
    wxFont userloginLabelFont(18,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    userloginLabel->SetFont(userloginLabelFont);
    loginButton = new wxButton(Panel, ID_loginButton, _("Logga in"), wxPoint(64,256), wxSize(104,32), 0, wxDefaultValidator, _T("ID_loginButton"));
    loginButton->SetForegroundColour(wxColour(255,255,255));
    loginButton->SetBackgroundColour(wxColour(0,72,36));
    loginButton->SetDefault();
    logoutButton = new wxButton(Panel, ID_logoutButton, _("Logga ut"), wxPoint(192,256), wxSize(96,32), 0, wxDefaultValidator, _T("ID_logoutButton"));
    logoutButton->SetForegroundColour(wxColour(255,255,255));
    logoutButton->SetBackgroundColour(wxColour(117,0,3));
    labelLogonTime = new wxStaticText(Panel, ID_LOGONTIMELABEL, (wxLoginTimeText), wxPoint(104,304), wxSize(146,26), 0, _T("ID_LOGONTIMELABEL"));
    labelLogonTime->SetForegroundColour(wxColour(108,119,115));
    labelLogonTime->SetBackgroundColour(wxColour(39,43,57));
    wxFont labelLogonTimeFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    labelLogonTime->SetFont(labelLogonTimeFont);
    copyrightLabel = new wxStaticText(Panel, ID_copyrightLabel, _("© Erik Welander (Kira)"), wxPoint(104,344), wxSize(146,26), 0, _T("ID_copyrightLabel"));
    copyrightLabel->SetForegroundColour(wxColour(108,119,115));
    copyrightLabel->SetBackgroundColour(wxColour(39,43,57));
    wxFont copyrightLabelFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    copyrightLabel->SetFont(copyrightLabelFont);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    menuChangeConfiguration = new wxMenuItem(Menu1, id_changeConfig, _("Ändra Konfiguration"), wxEmptyString, wxITEM_NORMAL);
    Menu1->Append(menuChangeConfiguration);
    MenuBar1->Append(Menu1, _("Alternativ"));
    helpMenu = new wxMenu();
    MenuAbout = new wxMenuItem(helpMenu, ID_About, _("Om"), wxEmptyString, wxITEM_NORMAL);
    helpMenu->Append(MenuAbout);
    MenuBar1->Append(helpMenu, _("Hjälp"));
    SetMenuBar(MenuBar1);
    sessionTimer.SetOwner(this, ID_sessionTimer);
    //sessionTimer.Start(1000, false);

    Center();
    Connect(ID_tf_Password,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OntfPasswordTextEnter);
    Connect(ID_loginButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnloginButtonClick);
    Connect(ID_logoutButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnlogoutButtonClick);
    Connect(id_changeConfig,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnOpenConfigurationMenu);
    Connect(ID_About,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnAbout);
    Connect(ID_sessionTimer,wxEVT_TIMER,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnsessionTimerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnClose);
    //*)
    logoutButton->Disable();
    LibPLC::readConfiguration(cfgName, cfgNetworkShares, cfgWindowCloseAllowed);
}

Proxxi_Login_ClientFrame::~Proxxi_Login_ClientFrame()
{
    //(*Destroy(Proxxi_Login_ClientFrame)
    //*)
}

void Proxxi_Login_ClientFrame::OnQuit(wxCommandEvent& event)
{
    //Close();
    handleClosing();
}
void Proxxi_Login_ClientFrame::OnClose(wxCloseEvent& event)
{
    handleClosing();
}
void Proxxi_Login_ClientFrame::OnAbout(wxCommandEvent& event)
{
    aboutProgram();
}

void Proxxi_Login_ClientFrame::OnloginButtonClick(wxCommandEvent& event)
{
    login();
}

void Proxxi_Login_ClientFrame::OnlogoutButtonClick(wxCommandEvent& event)
{
    logout();
}

void Proxxi_Login_ClientFrame::OntfPasswordTextEnter(wxCommandEvent& event)
{
    login();
}

void Proxxi_Login_ClientFrame::OnOpenConfigurationMenu(wxCommandEvent& event)
{
    configurationMenu();
}

void Proxxi_Login_ClientFrame::OnsessionTimerTrigger(wxTimerEvent& event)
{
    timerTriggered();
}


/************************************************
* METHODS FOR THE GUI (Migrate to libPLC?)
*************************************************/

void Proxxi_Login_ClientFrame::handleClosing()
{
    if(cfgWindowCloseAllowed)
    {
        if(sessionTimer.IsRunning())
        {
            userloginLabel->SetForegroundColour(wxColour(255,255,255));
            userloginLabel->SetLabel(wxT("Loggar ut\n"+wxRealName+wxT("...")));
            CURLComm::visitWebServer("https://bruse.proxxi.org/index.php?do=logout");
            LibPLC::mountNetworkShares(cfgNetworkShares,wxLoginName,wxPassword);
        }
    exit(0);
    }
}

void Proxxi_Login_ClientFrame::aboutProgram()
{
    wxString msg = wxT("PROXXI Login Client");
    msg += wxT("\nVersion: "+wxAppVersion);
    msg += wxT("\nSkapare: Erik Welander (Kira)");
    msg += wxT("\nLicens: Creative Commons \"by-nc-nd\"");
    msg += wxT("\nAttribution (by), non-commersial. Consult me for changes (controlled development)");
    msg += wxT("\n\nSyfte: Detta program har jag skapat för att underlätta det för PROXXIs");
    msg += wxT("\nmedlemmar med syfte att förbättra deras inloggnings och internet upplevelse.");
    msg += wxT("\n\nKlienten är vid detta skede intigrerad med IX system och tillhandahåller nödvändiga");
    msg += wxT("\nrutiner såväl som stabilitets och säkerhetsrutiner utöver bruses hemsida.");
    msg += wxT("\n\nKällkoden finns tillgänglig på: https://github.com/Kira9204/Proxxi-Login-Client");
    msg += wxT("\n\nKontakta mig via proxxi gruppen @ facebook");
    msg += wxT("\nhttps://www.facebook.com/erik.welander eller ");
    msg += wxT("erik.welander@hotmail.com om du har frågor.");
    LibPLC::displayMessage(msg, wxTitle);
}

void Proxxi_Login_ClientFrame::login()
{
    if(!sessionTimer.IsRunning())
    {
        wxLoginName = tfUsername->GetLineText(0);
        wxPassword = tfPassword->GetLineText(0);
    }
    string username = string(wxLoginName.mb_str());
    string password = string(wxPassword.mb_str());
    userloginLabel->SetForegroundColour(wxColour(255,255,255));
    userloginLabel->SetLabel(wxT("Loggar in\n"+wxLoginName+wxT("...")));
    if(CURLComm::postDataToWebServer("https://bruse.proxxi.org?do=login","uname",username,"pass",password))
    {
        if(!sessionTimer.IsRunning())
        {
            logonTime = 0;
            updateRetryCountdown = 0;
            failedRequests = 0;
        }
        updateTimerSecs = 0;
        string realname = Login_Validation::getRealName(CURLComm::saveDataFromWebServer("https://bruse.proxxi.org"));
        if(realname.length() > 0)
        {
            wxRealName = wxString::From8BitData(realname.c_str());
            userloginLabel->SetForegroundColour(wxColour(36,148,69));
            userloginLabel->SetLabel(wxT("Inloggad som:\n"+wxRealName));
            loginButton->Disable();
            logoutButton->Enable();
            sessionTimer.Start(1000);
            if(!networkSharesMounted)
            {
                LibPLC::mountNetworkShares(cfgNetworkShares,wxLoginName,wxPassword);
                networkSharesMounted = true;
            }
            connected = true;
        }
        else
        {
            userloginLabel->SetForegroundColour(wxColour(255,0,0));
            userloginLabel->SetLabel(wxT("Fel:\nIcke godkänd inlogg"));
            tfPassword->Clear();
            sessionTimer.Stop();
            loginButton->Enable();
            logoutButton->Disable();
            if(networkSharesMounted)
            {
                LibPLC::disconnectNetworkShares(cfgNetworkShares);
                networkSharesMounted = false;
            }
            connected = false;
            updateTimerSecs = 0;
            updateRetryCountdown = 0;
            failedRequests = 0;
        }
    }
    else
    {
        if(sessionTimer.IsRunning())
        {
            updateRetryCountdown = 10;
            ++failedRequests;
        }
        else
        {
            displayNoConnectionError();
            updateTimerSecs = 0;
            updateRetryCountdown = 0;
            failedRequests = 0;
        }
        connected = false;
    }
}
void Proxxi_Login_ClientFrame::logout()
{
    sessionTimer.Stop();
    CURLComm::visitWebServer("https://bruse.proxxi.org/index.php?do=logout");
    tfUsername->Clear();
    tfPassword->Clear();
    userloginLabel->SetForegroundColour(wxColour(255,0,0));
    userloginLabel->SetLabel(wxRealName+wxT("\nÄr utloggad..."));
    LibPLC::disconnectNetworkShares(cfgNetworkShares);
    loginButton->Enable();
    logoutButton->Disable();
    wxRealName = wxT("");
    connected = false;
    networkSharesMounted = false;
    logonTime = 0;
    updateRetryCountdown = 0;
    updateTimerSecs = 0;
    //labelLogonTime->SetLabel(wxLoginTimeText);
}


void Proxxi_Login_ClientFrame::timerTriggered()
{
    ++updateTimerSecs;
    if(connected)
    {
         ++logonTime;
    }
    else
    {
        --updateRetryCountdown;
        wxString wxStringTime = wxString::Format(wxT("%i"),updateRetryCountdown);
        wxString wxInfoText = wxT("Varning: Inget svar.\nFörsöker igen om:\n");
        wxInfoText += wxStringTime;
        wxInfoText += wxT(" sekunder...");
        userloginLabel->SetForegroundColour(wxColour(255,212,42));
        userloginLabel->SetLabel(wxInfoText);
        loginButton->Enable();
        logoutButton->Disable();
    }
    if(updateTimerSecs >= 30 && connected && updateRetryCountdown < 1)
    {
        if(Login_Validation::validateSessionStatus(CURLComm::saveDataFromWebServer("https://bruse.proxxi.org/keep-alive.php")))
        {
            updateTimerSecs = 0;
            updateRetryCountdown = 0;
            connected = true;
        }
        else
        {
            connected = false;
            updateRetryCountdown = 10;
            ++failedRequests;
        }
    }
    else if(!connected && updateRetryCountdown < 1)
    {
        login();
    }
    wxString wxStringTime = wxT("Inloggningstid: ");
    wxStringTime += wxString::Format(wxT("%i"),((logonTime/60)/60)%24);
    wxStringTime += wxT("T ");
    wxStringTime += wxString::Format(wxT("%i"),(logonTime/60)%60);
    wxStringTime += wxT("M ");
    wxStringTime += wxString::Format(wxT("%i"),logonTime%60);
    wxStringTime += wxT("S");
    if(failedRequests > 0)
    {
        wxStringTime += wxT("\nFörfrågningar utan svar: ");
        wxStringTime += wxString::Format(wxT("%i"),failedRequests);
    }
    labelLogonTime->SetLabel(wxStringTime);
}
void Proxxi_Login_ClientFrame::configurationMenu()
{   LibPLC::configurationMenu(cfgName);
    LibPLC::readConfiguration(cfgName, cfgNetworkShares, cfgWindowCloseAllowed);
    LibPLC::mountNetworkShares(cfgNetworkShares,wxLoginName,wxPassword);
}

void Proxxi_Login_ClientFrame::displayNoConnectionError()
{
    wxString msg = wxT("Det gick inte att kontakta servern \"bruse\" för att validera inloggingen.");
    msg += wxT("\nKontrollera att datorn är ansluten till nätverket, om detta problem kvarstår så kontakta mig eller någon av IXs medlemmar.");
    LibPLC::displayMessage(msg, wxTitle);
    userloginLabel->SetForegroundColour(wxColour(255,0,0));
    userloginLabel->SetLabel(wxT("FEL: Servern svarade\ninte på förfrågan..."));
}
