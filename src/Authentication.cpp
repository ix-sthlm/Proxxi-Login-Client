/***************************************************************
 * Name:      Authentication.cpp
 * Purpose:   Account validation and information
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-09
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/
#include "../headers/Authentication.h"
int Authentication::login(const string username, const string password)
{
    int statusCode = 0;
    if(CURLComm::post("https://bruse.proxxi.org?do=login","uname="+username+"&pass="+password))
    {
        string data = CURLComm::get("https://bruse.proxxi.org");
        std::size_t loc = data.find( "inloggad som", 0 );
        if(loc != string::npos) //Found string "inloggad som"
            statusCode = 1;     // "OK" status, this is a valid login

        loc = data.find( "Ditt medlemskap", 0 );
        if(loc != string::npos)
            statusCode = 2;     //This accounts memebership has expired

        loc = data.find( "internetaccess prata", 0 );
        if(loc != string::npos)
            statusCode = 3;     //This accounts internet access has been revoked
        return statusCode;
    }
    return -1;  //If the post did not sucseed.
}
void Authentication::logout()
{
    CURLComm::get("https://bruse.proxxi.org/index.php?do=logout");
}
string Authentication::getRealName()
{
    string data = CURLComm::get("https://bruse.proxxi.org");
    //string realname = "";
    string line = "";
    //string::size_type loc = data.find( "inloggad som", 0 );
    std::size_t loc = data.find( "inloggad som", 0 );
    if(loc != string::npos)
    {
        line = data.substr((loc-30),30);
        loc = line.find("1>",0);
        line = line.substr(loc+2, 30);
        for(int pos = loc, numofspaces = 0; numofspaces < 2; pos++){
            if(line[pos] == ' '){
                numofspaces++;
            }
            //realname += data[pos];
        }
    }
    return line;
}
bool Authentication::validateSessionStatus()
{
    string data = CURLComm::get("https://bruse.proxxi.org/keep-alive.php");
    std::size_t loc = data.find( "OK", 0 );
    if(loc != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
    /*
    We might get more junk data, so we go back to searching for it (above)
    if (data.compare("OK") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
    */
}
bool Authentication::multiLoginComputer(const string hostname, const string password)
{
    CURLComm::post("https://bruse.proxxi.org/multlogg.php?do=login&amp;from=/multlogg.php","host="+hostname+"&pass="+password);
    string data = CURLComm::get("https://bruse.proxxi.org/multlogg.php?do=login&from=/multlogg.php");
    std::size_t loc = data.find( hostname, 0 );
    if(loc != string::npos)
    {
        return true;
    }
    else
    {
        return false;
    }
}
