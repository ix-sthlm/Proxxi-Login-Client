/***************************************************************
 * Name:      FileIO.cpp
 * Purpose:   Various File IO operations. This library was made to specifically edit just 1 line.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#include "../headers/FileIO.h"

bool FileIO::fileExists(const string name)
{
    bool exist = false;
    ifstream fsConfigR(name.c_str());
    if(fsConfigR)
    {
        exist = true;
    }
    else
    {
        exist = false;
    }
    fsConfigR.close();
    return exist;
}
string* FileIO::readConfig(const string name)
{
    ifstream fsConfigR(name.c_str());
    string* arr = new string[2];
    std::getline(fsConfigR, arr[0]);
    std::getline(fsConfigR, arr[1]);
    fsConfigR.close();
    return arr;
}
void FileIO::generateDefaultConfig(const string name)
{
    ofstream fsConfigW (name.c_str());
    fsConfigW << "MountNetworkShares = 1\r\n";
    fsConfigW << "WindowCloseAllowed = 1\r\n";
    fsConfigW.close();
}
