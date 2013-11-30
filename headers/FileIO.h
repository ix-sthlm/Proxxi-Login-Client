/***************************************************************
 * Name:      FileIO.h
 * Purpose:   Various File IO operations. This library was made to specifically edit just 1 line.
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-02
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/

#ifndef FileIO_H
#define FileIO_H
#include <iostream>
#include <fstream>
#include <string>
using std::string;
using std::ifstream;
using std::ofstream;
namespace FileIO
{
   bool fileExists(string name);
   string* readConfig(string name);
   void generateDefaultConfig(string name);
}


#endif



