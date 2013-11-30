/***************************************************************
 * Name:      CURLComm.cpp
 * Purpose:   A CURL Application library used for the "Kira_Login_Client_CPP_Edition"
 * Author:    Erik Welander (erik.welander@hotmail.com)
 * Version:   2013-11-30
 * Copyright: Erik Welander (https://www.facebook.com/erik.welander)
 * License:   Creative Commons "by-nc-nd"
 **************************************************************/
 #include "../headers/CURLComm.h"

//Thank Tim Yates for this function:
//http://stackoverflow.com/questions/2376824/libcurl-http-request-to-save-respond-into-variable-c
size_t write_to_string(void *ptr, size_t size, size_t count, void *stream) {
  ((string*)stream)->append((char*)ptr, 0, size*count);
  return size*count;
}

//This method posts data to a web server and returns a boolean value if the POST was successful
bool CURLComm::postDataToWebServer(string s_url,
                         string username_php_var, string username,
                         string password_php_var, string password)
{
     bool success = false;
     CURL *curl;
     CURLcode res;

      //Init all CURL functions, In windows, this will also init the winsock stuff
      curl_global_init(CURL_GLOBAL_ALL);

      // get a curl handle
      curl = curl_easy_init();
      if(curl)
      {
        // First set the URL that is about to receive our POST. This URL can
        //   just as well be a https:// URL.
        curl_easy_setopt(curl, CURLOPT_URL, s_url.c_str());

        //Disable SSL verifying, accept all certificates.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        //Create a string query with the data we want to send.
        string query = username_php_var+"="+username+"&"+password_php_var+"="+password;

        //Specify that the CURL operation is a POST operation
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, query.c_str());

        //Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        //cleanup data
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        //Check for errors
        if(res == CURLE_OK)
            success = true;
        else
          //fprintf(stderr, "curl_easy_perform() failed: %s\n",
          //curl_easy_strerror(res));
          success = false;
  }
  return success;
}

//This method visits a web server and returns its HTML data
string CURLComm::saveDataFromWebServer(string s_url)
{
 CURL *curl;
 CURLcode res;
 //Will hold all the HTML data
 string data = "";

  // Init all CURL functions, In windows, this will also init the winsock stuff
  curl_global_init(CURL_GLOBAL_ALL);

  // Get a curl handle
  curl = curl_easy_init();
  if(curl)
  {
        // First set the URL that is about to receive our POST. This URL can
        //   just as well be a https:// URL.
        curl_easy_setopt(curl, CURLOPT_URL, s_url.c_str());

        //Disable SSL verifying, accept all certificates.
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        //Defines the write method used by CURL to write back data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_to_string);

        //Defines the variable that the result of the write function should be put into
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data);

        //Perform the request, res will get the return code
        res = curl_easy_perform(curl);

        //Clean up used CURL data
        curl_easy_cleanup(curl);
        curl_global_cleanup();

        //Check for errors
        /*
        if(res == CURLE_OK){

        }
        else
        {
          //fprintf(stderr, "curl_easy_perform() failed: %s\n",
          //curl_easy_strerror(res));
        }
        */
  }
  return data;
}

//This method visits a web server and returns a boolean value of the availability of said web server.
bool CURLComm::visitWebServer(string s_url)
{
  bool success = false;
  CURL *curl;
  CURLcode res;

  //Init all CURL functions, In windows, this will also init the winsock stuff
  curl_global_init(CURL_GLOBAL_ALL);

  // Get a curl handle
  curl = curl_easy_init();
  if(curl) {
    /* First set the URL that is about to receive our POST. This URL can
       just as well be a https:// URL.*/
    curl_easy_setopt(curl, CURLOPT_URL, s_url.c_str());

    //Disable SSL verifying, accept all certificates.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

    //Perform the request, res will get the return code
    res = curl_easy_perform(curl);

    //Clean up used CURL data
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    //Check for errors
    if(res == CURLE_OK)
        success = true;
    else
      //fprintf(stderr, "curl_easy_perform() failed: %s\n",
      //curl_easy_strerror(res));
      success = false;
  }
  return success;
}

