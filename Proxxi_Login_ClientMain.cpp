/***************************************************************
 * Name:      Proxxi_Login_ClientMain.cpp
 * Purpose:   Application mainframe.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-09(r0)
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#include "Proxxi_Login_ClientMain.h"
#include <wx/msgdlg.h>
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
const long Proxxi_Login_ClientFrame::ID_tf_username = wxNewId();
const long Proxxi_Login_ClientFrame::ID_tf_Password = wxNewId();
const long Proxxi_Login_ClientFrame::ID_userloginLabel = wxNewId();
const long Proxxi_Login_ClientFrame::ID_loginButton = wxNewId();
const long Proxxi_Login_ClientFrame::ID_logoutButton = wxNewId();
const long Proxxi_Login_ClientFrame::ID_LOGONTIMELABEL = wxNewId();
const long Proxxi_Login_ClientFrame::id_registerNewUser = wxNewId();
const long Proxxi_Login_ClientFrame::id_multibleLogins = wxNewId();
const long Proxxi_Login_ClientFrame::id_changeConfig = wxNewId();
const long Proxxi_Login_ClientFrame::ID_CLOSE = wxNewId();
const long Proxxi_Login_ClientFrame::ID_About = wxNewId();
const long Proxxi_Login_ClientFrame::ID_sessionTimer = wxNewId();
//*)

BEGIN_EVENT_TABLE(Proxxi_Login_ClientFrame,wxFrame)
    //(*EventTable(Proxxi_Login_ClientFrame)
    //*)
    EVT_PAINT(Proxxi_Login_ClientFrame::OnPaint)
END_EVENT_TABLE()

Proxxi_Login_ClientFrame::Proxxi_Login_ClientFrame(wxWindow* parent,wxWindowID id)
{
    wxString wxLoginName = LibPLC::getLoginName();
    updateNetworkInfo();
    wxLoginTimeText += _("\n");
    wxLoginTimeText += wxNetworkInfo;
    //(*Initialize(Proxxi_Login_ClientFrame)
    wxMenuItem* MenuAbout;
    wxMenu* informationMenu;
    wxMenu* Menualternatives;
    wxMenuBar* MenuBar;

    Create(parent, wxID_ANY, wxTitle, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL, _T("wxID_ANY"));
    SetClientSize(wxSize(346,446));
    SetBackgroundColour(wxColour(255,255,255));
    {
    	wxIcon FrameIcon;
    	FrameIcon.CopyFromBitmap(wxBitmap(wxImage(_T("Avatar_Window_Icon.png"))));
    	SetIcon(FrameIcon);
    }
    tfUsername = new wxTextCtrl(this, ID_tf_username, wxLoginName, wxPoint(72,96), wxSize(200,21), 0, wxDefaultValidator, _T("ID_tf_username"));
    wxFont tfUsernameFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    tfUsername->SetFont(tfUsernameFont);
    tfPassword = new wxTextCtrl(this, ID_tf_Password, wxEmptyString, wxPoint(72,136), wxSize(200,21), wxTE_PASSWORD, wxDefaultValidator, _T("ID_tf_Password"));
    wxFont tfPasswordFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    tfPassword->SetFont(tfPasswordFont);
    userloginLabel = new wxStaticText(this, ID_userloginLabel, _("Vänligen logga in\n"+wxLoginName), wxPoint(72,168), wxSize(288,48), 0, _T("ID_userloginLabel"));
    wxFont userloginLabelFont(18,wxSWISS,wxFONTSTYLE_NORMAL,wxBOLD,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    userloginLabel->SetFont(userloginLabelFont);
    loginButton = new wxButton(this, ID_loginButton, _("Logga in"), wxPoint(72,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_loginButton"));
    loginButton->SetForegroundColour(wxColour(255,255,255));
    loginButton->SetBackgroundColour(wxColour(0,72,36));
    logoutButton = new wxButton(this, ID_logoutButton, _("Logga ut"), wxPoint(200,256), wxDefaultSize, 0, wxDefaultValidator, _T("ID_logoutButton"));
    logoutButton->SetForegroundColour(wxColour(255,255,255));
    logoutButton->SetBackgroundColour(wxColour(117,0,3));
    labelLogonTime = new wxStaticText(this, ID_LOGONTIMELABEL, wxLoginTimeText, wxPoint(80,288), wxDefaultSize, 0, _T("ID_LOGONTIMELABEL"));
    wxFont labelLogonTimeFont(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("Tahoma"),wxFONTENCODING_DEFAULT);
    labelLogonTime->SetFont(labelLogonTimeFont);
    MenuBar = new wxMenuBar();
    Menualternatives = new wxMenu();
    MenuItem1 = new wxMenuItem(Menualternatives, id_registerNewUser, _("Registrera ny användare"), wxEmptyString, wxITEM_NORMAL);
    Menualternatives->Append(MenuItem1);
    MenuItem2 = new wxMenuItem(Menualternatives, id_multibleLogins, _("Multi-inlogg"), wxEmptyString, wxITEM_NORMAL);
    Menualternatives->Append(MenuItem2);
    menuChangeConfiguration = new wxMenuItem(Menualternatives, id_changeConfig, _("Ändra Konfiguration"), wxEmptyString, wxITEM_NORMAL);
    Menualternatives->Append(menuChangeConfiguration);
    menuClose = new wxMenuItem(Menualternatives, ID_CLOSE, _("Avsluta\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
    Menualternatives->Append(menuClose);
    MenuBar->Append(Menualternatives, _("Verktyg"));
    informationMenu = new wxMenu();
    MenuAbout = new wxMenuItem(informationMenu, ID_About, _("Om\tF1"), wxEmptyString, wxITEM_NORMAL);
    informationMenu->Append(MenuAbout);
    MenuBar->Append(informationMenu, _("Information"));
    SetMenuBar(MenuBar);
    sessionTimer.SetOwner(this, ID_sessionTimer);
    //sessionTimer.Start(1000, false);
    Center();

    Connect(ID_tf_Password,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OntfPasswordTextEnter);
    Connect(ID_loginButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnloginButtonClick);
    Connect(ID_logoutButton,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnlogoutButtonClick);
    Connect(id_registerNewUser,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnRegisterNewUserMenu);
    Connect(id_multibleLogins,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::onMultibleLoginsMenu);
    Connect(id_changeConfig,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnOpenConfigurationMenu);
    Connect(ID_CLOSE,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnQuit);
    Connect(ID_About,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnAbout);
    Connect(ID_sessionTimer,wxEVT_TIMER,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnsessionTimerTrigger);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&Proxxi_Login_ClientFrame::OnClose);
    //*)
    logoutButton->Disable();
    LibPLC::readConfiguration(cfgName, cfgNetworkShares, cfgWindowCloseAllowed);
}

 //Used for painting the background image
 void Proxxi_Login_ClientFrame::OnPaint(wxPaintEvent& event)
  {
    wxPaintDC paintDC(this);
    //Draw the background image
    paintDC.DrawBitmap(wxBitmap(wxImage(_("Background.png"))),0,0);
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
void Proxxi_Login_ClientFrame::OnRegisterNewUserMenu(wxCommandEvent& event)
{
    registerNewUser();
}
void Proxxi_Login_ClientFrame::onMultibleLoginsMenu(wxCommandEvent& event)
{
    multibleLogins();
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
    if(sessionTimer.IsRunning())
    {
        /*
        userloginLabel->SetForegroundColour(wxColour(0,0,0));
        userloginLabel->SetLabel(_("Loggar ut\n"+wxRealName+_("...")));
        Authentication::logout();
        if(networkSharesMounted)
        {
            LibPLC::disconnectNetworkShares();
        }
        */
        logout();
    }
    if(cfgWindowCloseAllowed)
    {
        exit(0);
    }
}

void Proxxi_Login_ClientFrame::aboutProgram()
{
    wxString msg = _("Proxxi Login Client (IX systems communicator)");
    msg += _("\nVersion: "+wxAppVersion);
    msg += _("\nSkapare: Erik Welander (Kira)");
    msg += _("\nhttps://www.facebook.com/erik.welander");
    msg += _("\nerik.welander@hotmail.com");
    msg += _("\nhttp://erik.snekabel.se/");
    msg += _("\nLicens: Creative Commons \"by-nc-nd\"");
    msg += _("\nAttribution (by), non-commersial. Consult me for changes (controlled development)");
    msg += _("\nProxxi loggan är skapad av Linus Wahlgren.");
    msg += _("\n\nSyfte: Detta program har jag skapat åt PROXXIS och IX medlemmar för att förbättra,");
    msg += _("\nunderlätta och säkra deras interaktion mot IX system.");
    msg += _("\n\nKlienten är intregerad med systemen och tillhandahåller");
    msg += _("\nmycket funktionalitet såväl som stabilitet och säkerhetsrutiner utöver bruses hemsida.");
    msg += _("\n\nKällkoden finns tillgänglig på: https://github.com/Kira9204/Proxxi-Login-Client");
    msg += _("\nKontakta mig ifall du stöter på några bugger eller har frågor.");
    LibPLC::displayMessage(msg, wxTitle);
}
void Proxxi_Login_ClientFrame::login()
{
    if(!sessionTimer.IsRunning())
    {
        wxLoginName = tfUsername->GetLineText(0);
        wxPassword = tfPassword->GetLineText(0);
        logonTime = 0;
        updateRetryCountdown = 0;
        failedRequests = 0;
        multiLoginHost = "";
    }
    if(wxPassword.compare(_("")) != 0)  //Only continue if the password is not empty
    {
        string username = string(wxLoginName.mb_str());
        string password = string(wxPassword.mb_str());
        userloginLabel->SetForegroundColour(wxColour(0,0,0));
        userloginLabel->SetLabel(_("Loggar in\n"+wxLoginName+_("...")));
        if(!sessionTimer.IsRunning())
        {
            Authentication::logout();   //Safety measure
        }
        int statusCode = Authentication::login(username,password);
        updateTimerSecs = 0;
        if(statusCode == -1)    //Could not connect to the login server!
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
        else if(statusCode == 0) //Invalid login
        {
            userloginLabel->SetForegroundColour(wxColour(255,0,0));
            userloginLabel->SetLabel(_("Fel:\nIcke godkänd inlogg"));
            tfPassword->Clear();
            sessionTimer.Stop();
            loginButton->Enable();
            logoutButton->Disable();
            if(networkSharesMounted)
            {
                LibPLC::disconnectNetworkShares();
                networkSharesMounted = false;
            }
            connected = false;
            updateTimerSecs = 0;
            updateRetryCountdown = 0;
            failedRequests = 0;
        }
        else if(statusCode == 1) //Valid login
        {

            string realname = Authentication::getRealName();
            wxRealName = wxString::From8BitData(realname.c_str());
            userloginLabel->SetForegroundColour(wxColour(36,148,69));
            userloginLabel->SetLabel(_("Inloggad som:\n"+wxRealName));
            loginButton->Disable();
            logoutButton->Enable();
            sessionTimer.Start(1000);
            if(!networkSharesMounted && cfgNetworkShares)
            {
                LibPLC::mountNetworkShares();
                networkSharesMounted = true;
            }
            if(multiLoginHost.compare("") != 0)
            {
                Authentication::multiLoginComputer(multiLoginHost, password);
            }
            connected = true;
        }
        else if(statusCode == 2)    //This accounts memebership has expired
        {
            string realname = Authentication::getRealName();
            wxRealName = wxString::From8BitData(realname.c_str());
            wxString wxInfoText = _("Utgånget\nmedlemskap");
            wxString wxMsg = _("Medlemskapet för \"");
            wxMsg += wxRealName;
            wxMsg += _("\" har utgått.\n");
            wxMsg += _("Medlemskapet för en användare måste förnyas en gång varje år för att nyttja PROXXI's/IX's resurser.\n");
            wxMsg += _("Kontakta en nyckelbärare för att förnya ditt medlemskap!");
            wxString wxTitle = _("Utgånget medlemskap");
            userloginLabel->SetForegroundColour(wxColour(255,212,42));
            userloginLabel->SetLabel(wxInfoText);
            loginButton->Enable();
            logoutButton->Disable();
            updateLogonTimeLabel();
            LibPLC::displayMessage(wxMsg, wxTitle);
        }
        else if(statusCode == 3)    //This accounts internet access has been revoked
        {
            string realname = Authentication::getRealName();
            wxRealName = wxString::From8BitData(realname.c_str());
            wxString wxInfoText = _("Saknad\nbehörighet");
            wxString wxMsg = _("Medlemmen \"");
            wxMsg += wxRealName;
            wxMsg += _("\" saknar behörighet till internet och IX resurser.\n");
            wxMsg += _("Om du nyligen registrerat dig och får detta medelande så har nyckelbäraren antagligen glömt att ge dig behörighet.\n");
            wxMsg += _("Kontakta i så fall valfri nyckelbäraren igen.\n");
            wxMsg += _("Om du i annat fall stöter på detta medelande så har din behörighet dragits in på grund av brott mot relgerna\n");
            wxMsg += _("Kontakta en nyckelbärare om du vill bestrida detta.");
            wxString wxTitle = _("Saknad behörighet");
            userloginLabel->SetForegroundColour(wxColour(255,0,0));
            userloginLabel->SetLabel(wxInfoText);
            loginButton->Enable();
            logoutButton->Disable();
            updateLogonTimeLabel();
            LibPLC::displayMessage(wxMsg, wxTitle);
        }
    }
}
void Proxxi_Login_ClientFrame::logout()
{
    sessionTimer.Stop();
    Authentication::logout();
    tfUsername->Clear();
    tfPassword->Clear();
    wxLoginName = _("");
    wxPassword = _("");
    userloginLabel->SetForegroundColour(wxColour(255,0,0));
    userloginLabel->SetLabel(wxRealName+_("\nÄr utloggad..."));
    if(networkSharesMounted && cfgNetworkShares)
    {
        LibPLC::disconnectNetworkShares();
    }
    networkSharesMounted = false;
    connected = false;
    multiLoginHost = "";
    loginButton->Enable();
    logoutButton->Disable();
    wxRealName = _("");
    logonTime = 0;
    updateRetryCountdown = 0;
    updateTimerSecs = 0;
    updateLogonTimeLabel();
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
        wxString wxStringTime = wxString::Format(_("%i"),updateRetryCountdown);
        wxString wxInfoText = _("Varning: Inget svar.\nFörsöker igen om:\n");
        wxInfoText += wxStringTime;
        wxInfoText += _(" sekunder...");
        userloginLabel->SetForegroundColour(wxColour(255,212,42));
        userloginLabel->SetLabel(wxInfoText);
        loginButton->Enable();
        logoutButton->Disable();
    }
    if(updateTimerSecs >= 30 && connected && updateRetryCountdown < 1)
    {
        if(Authentication::validateSessionStatus())
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
        if(Authentication::validateSessionStatus())
        {
            updateTimerSecs = 0;
            updateRetryCountdown = 0;
            connected = true;
        }
        else
        {
            login();
        }
    }
    updateLogonTimeLabel();
}
void Proxxi_Login_ClientFrame::updateLogonTimeLabel()
{
    wxString wxStringTime = _("Inloggningstid: ");
    wxStringTime += wxString::Format(_("%i"),((logonTime/60)/60)%24);
    wxStringTime += _("T ");
    wxStringTime += wxString::Format(_("%i"),(logonTime/60)%60);
    wxStringTime += _("M ");
    wxStringTime += wxString::Format(_("%i"),logonTime%60);
    wxStringTime += _("S\n");
    if(failedRequests > 0)
    {
        wxStringTime += _("Förfrågningar utan svar: ");
        wxStringTime += wxString::Format(_("%i"),failedRequests);
        wxStringTime += _("\n");
    }
    wxStringTime += wxNetworkInfo;
    if(multiLoginHost.compare("") != 0)
    {
        wxStringTime += _("Multi-inloggad enhet:");
        wxString wxHostnameString(multiLoginHost.c_str(), wxConvUTF8);
        wxStringTime += wxHostnameString;
    }
    labelLogonTime->SetLabel(wxStringTime);
}
void Proxxi_Login_ClientFrame::configurationMenu()
{   LibPLC::configurationMenu(cfgName);
    LibPLC::readConfiguration(cfgName, cfgNetworkShares, cfgWindowCloseAllowed);
    LibPLC::mountNetworkShares();
}
void Proxxi_Login_ClientFrame::updateNetworkInfo()
{
    string networkInfo = "Datornamn:"+LibPLC::getHostname();
    networkInfo += "IP:"+LibPLC::getIPAddress();
    wxString converted(networkInfo.c_str(), wxConvUTF8);
    wxNetworkInfo = converted;
}
void Proxxi_Login_ClientFrame::registerNewUser()
{
    LibPLC::openWebPage("https://bruse.proxxi.org/create.php");
}
void Proxxi_Login_ClientFrame::multibleLogins()
{
    if(wxPassword.compare(_("")) != 0)
    {
        wxString passStr = LibPLC::askQuestionMasked(this,_("För att kunna fortsätta så måste du identifiera dig själv\nSkriv in ditt lösenord för att låsa upp funktionen"),_("Lås upp"));
        if(wxPassword.compare(passStr) == 0)
        {
            wxString computerStr = LibPLC::askQuestion(this, _("Lösenordet accepterades!\nAnge nu IP addren till enheten som du vill lägga till.\nNotera att denna enhet kommer att vara inloggad tills utloggning och timeout sker!"), _("Ange adress"));
            string password = string(wxPassword.mb_str());
            string hostname = string(computerStr.mb_str());
            if(hostname.compare("") != 0)
            {
                if(Authentication::multiLoginComputer(hostname,password))
                {
                    multiLoginHost = hostname;
                }
                else
                {
                    LibPLC::displayMessage(_("Enhten kunde inte hittas på nätverket eller så saknar du behörighet!\nFörsök med MAC-addressen!"), _("Okänd enhet"));
                }
            }
        }
        else if(wxPassword.compare(_("")) == 0){}
        else
        {
            LibPLC::displayMessage(_("Felaktigt lösenord!"), _("Låst"));
        }
    }
    else
    {
        LibPLC::displayMessage(_("Du har inte loggat in än!"), _("Låst"));
    }
}
void Proxxi_Login_ClientFrame::displayNoConnectionError()
{
    wxString msg = _("Det gick inte att kontakta servern \"bruse\" för att validera inloggingen.");
    msg += _("\nKontrollera att datorn är ansluten till nätverket, om detta problem kvarstår så kontakta mig eller någon av IXs medlemmar.");
    LibPLC::displayMessage(msg, wxTitle);
    userloginLabel->SetForegroundColour(wxColour(255,0,0));
    userloginLabel->SetLabel(_("FEL: Servern svarade\ninte på förfrågan..."));
}

