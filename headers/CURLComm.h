/***************************************************************
 * Name:      CURLComm.cpp
 * Purpose:   A CURL Application library used for the "Kira_Login_Client_CPP_Edition"
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-03-09
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   GNU GPL
 * Special thanks to: Zenwood (http://www.zedwood.com/article/cpp-libcurl-static-class)
 * for having the best CURL implementation example around.
 * This work is heavily influinced by you
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
    string get(const string url);
    bool post(const string url, const string postData);
    string curlIt(const string url, const string postData);
    //Used internally, do not call
    int write_to_string(char *data, size_t size, size_t nmemb, string *buffer);
};
#endif //CURL_Comm.h
