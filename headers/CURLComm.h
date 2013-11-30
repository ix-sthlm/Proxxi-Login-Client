/***************************************************************
 * Name:      ProxxiLoginClient.h
 * Purpose:   Defines my CURL Application Library
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-30
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#ifndef CURL_Comm_H
#define CURL_Comm_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#if defined _WIN64 || defined _WIN32
#include <winsock2.h>
#include <windows.h>
#endif
using std::string;
namespace CURLComm {
    bool postDataToWebServer(string s_url,
                             string username_php_var, string username,
                             string password_php_var, string password);
    string saveDataFromWebServer(string s_url);
    bool visitWebServer(string s_url);
};
#endif //CURL_Comm.h
