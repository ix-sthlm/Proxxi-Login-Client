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
 #include "../headers/CURLComm.h"

//Thank Zenwood for this fuction:
//http://www.zedwood.com/article/cpp-libcurl-static-class
int CURLComm::write_to_string(char *data, size_t size, size_t nmemb, string *buffer)
{
  int result = 0;
  if(buffer != NULL)
  {
    buffer->append(data, size * nmemb);
    result = size * nmemb;
  }
  return result;
}
string CURLComm::get(const string url)
{
    return CURLComm::curlIt(url, "");
}
bool CURLComm::post(const string url, const string postData)
{
    if(CURLComm::curlIt(url, postData).compare("OK") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string CURLComm::curlIt(const string url, const string postData)
{

    string data = "";
    CURL *curl;
    CURLcode result;

    //Init all CURL functions, In windows, this will also init the winsock stuff
    curl_global_init(CURL_GLOBAL_ALL);
    //get a curl handle
    curl = curl_easy_init();
    if(curl)
    {
        //First set the URL that is about to receive our POST. This URL can
        //just as well be a https:// URL.
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        //include header information in the output?
        curl_easy_setopt(curl, CURLOPT_HEADER, 0L);
        //Follow any redirects from the webserver?
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        //Disable SSL verifying, accept all certificates.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        //Used to verify that the hostname matches the hostname in the certificate.
        //1 to check the existence of a common name in the SSL peer certificate.
        //2 to check the existence of a common name and also verify that it matches the hostname provided.
        //This should i pretty much all cases be at 2
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST,  2L);
        //Specifies the file that we will read our cookies from
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, "cookies.txt");
        //Specifies the file that we will write our cookies to
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, "cookies.txt");
        //The writefuction that will be used to recieve all output data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);
        //The string buffer that we will use to recieve all of our data
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        if(postData.compare("") != 0)
        {
          curl_easy_setopt(curl, CURLOPT_POST,1);
          curl_easy_setopt(curl, CURLOPT_POSTFIELDS,postData.c_str());
        }

      //And off we go!
      //Attempt to retrieve the remote page
      result = curl_easy_perform(curl);
      //Clean up CURL
      curl_easy_cleanup(curl);
      // So how did it go?
      if (result == CURLE_OK)
      {
          if(postData.compare("") != 0)
          {
              //A POST wont retrieve any HTML information, but we want some kind of confirmation that everything went well
              return "OK";
          }
          return data;
      }
      else
      {
          return "ERROR";
      }
    }
    //If CURL failed to initialize itself
    return data;
}
