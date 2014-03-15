/***************************************************************
 * Name:      Authentication.h
 * Purpose:   Account validation and information
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2014-01-08
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#ifndef LoginValidation_H
#define LoginValidation_H
#include <string>
#include <sstream>
#include "CURLComm.h"
using std::string;
namespace Authentication{
    int login(const string username, const string password);
    void logout();
    int getStatusCode();
    string getRealName();
    bool validateSessionStatus();
    bool multiLoginComputer(const string hostname, const string password);
};
#endif //LoginValidation.h
