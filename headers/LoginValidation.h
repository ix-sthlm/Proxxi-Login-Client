/***************************************************************
 * Name:      LoginValidation.h
 * Purpose:   Defines the account validation header.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-08-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#ifndef LoginValidation_H
#define LoginValidation_H
#include <string>
#include <sstream>
using std::string;
namespace Login_Validation{
    string getRealName(string data);
    bool validateSessionStatus(string data);
};
#endif //LoginValidation.h
