#pragma once

#include <iostream>
#include <string>
#include "curl/curl.h"
#include "rlutil.h"
#include <cstdio>
#include <cstring>
#include <fstream>

using namespace std;
using namespace rlutil;

// Calling the function to create a folder (based on whic OS is running).
void createDirectory(string name);

void GetWallpaper(string ChampName, string DirName = "") {

	saveDefaultColor();
	int count;
	int filesize;

	setColor(MAGENTA);
	cout << "[" << ChampName << "]\n";
	
	if (!DirName.empty())
		createDirectory(DirName);

	FILE *fp;
// This creates a pointer to a file descriptor
	string filename;
	CURL *curl = curl_easy_init(); //https://curl.haxx.se/libcurl/c/curl_easy_init.html
// This initializes curl.
	CURLcode result = CURLE_OK; //https://curl.haxx.se/libcurl/c/libcurl-errors.html
// This is the result that the download returns, so you can check for errors.

	if(curl) {
// If curl is initilized, continue.
		for(int i = 0; result == CURLE_OK; i++) {
// Loop until result is != CURLE_OK
			filename = ChampName + "_" + to_string(i) + ".jpg";
			string url = "http://ddragon.leagueoflegends.com/cdn/img/champion/splash/" + filename;
			fp = fopen(((DirName.empty() ? "" : DirName + "/") + filename).c_str(),"wb"); //http://www.cplusplus.com/reference/cstdio/fopen/
// Opens the file, with mode "wb": "w" stands for writing, "b" for binary.
// "w"-Mode: It creates the file if it doesn't exist.
// "b"-Mode: .jpg is a binary file not like .txt.
			if (fp == NULL) {
				cerr << "Error opening file: " << strerror(errno) << endl;
				curl_easy_cleanup(curl);
			}
				curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); //https://curl.haxx.se/libcurl/c/CURLOPT_URL.html
// Set the url for the file to download.
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL); //https://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
				curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp); //https://curl.haxx.se/libcurl/c/CURLOPT_WRITEDATA.html
// [LAST 2] Setting up to/and write to the file.
				//curl_easy_setopt(curl, CURLOPT_VERBOSE, 1); //https://curl.haxx.se/libcurl/c/CURLOPT_VERBOSE.html
// Prints lots of information about the HTTP request. (Not neccessary).
				curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);//https://curl.haxx.se/libcurl/c/CURLOPT_FAILONERROR.html
// When url is 404, don't download the 404-page.
				result = curl_easy_perform(curl);
// Actual download and returning the result.
				fclose(fp);
				
				count = i;
				ifstream file(DirName + "/" + filename);
				file.seekg(0, ios::end);
				filesize = static_cast<int>(file.tellg());
				filesize = filesize / 1000;
				if (filesize != 0) {
					resetColor();
					cout << "Skin ";
					setColor(BROWN);
					cout << count;
					resetColor();
					cout << " downloaded, size: ";
					setColor(BROWN);
					cout << filesize;
					resetColor();
					cout << " KB.\n";
				}
		}

		if(result != CURLE_HTTP_RETURNED_ERROR) {
			/*	
			If errors have occured, besides HTTP server returning an error code
			that is >= 400. Tell us wath's wrong with 'result'.
			*/
			setColor(LIGHTRED);
			cerr << "Failed to initialize download-engine.\n" << string(curl_easy_strerror(result)) << endl;
		}

		if (!filename.empty()) {
		//Remove the last file where the error occurred
		if (remove(((DirName.empty() ? "" : DirName + "/") + filename).c_str()))
		cerr << "Failed to remove (" << filename << "): " << strerror(errno) << endl;
		}
		curl_easy_cleanup(curl);
	}
	else {
		setColor(LIGHTRED);
		cerr << "Failed to initialize download-engine.\n" << endl;
	}

	cout << "\n";

}

