/***************************************************************
 * Name:      LoginValidation.cpp
 * Purpose:   Account validation.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-08-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/
#include "../headers/LoginValidation.h"
string Login_Validation::getRealName(string data)
{
        string realname = "";
        string line = "";
        string::size_type loc = data.find( "inloggad som", 0 );
        if(loc != string::npos)
        {
            line = data.substr((loc-30),30);
            loc = line.find("1>",0);
            line = line.substr(loc+2, 30);
            for(int pos = loc, numofspaces = 0; numofspaces < 2; pos++){
                if(line[pos] == ' '){
                    numofspaces++;
                }
                realname += data[pos];
            }
        }
        return line;
}
bool Login_Validation::validateSessionStatus(string data)
{
    if (data.compare("OK") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
