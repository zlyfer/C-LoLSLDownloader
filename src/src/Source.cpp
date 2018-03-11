#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#define _SCL_SECURE_NO_WARNINGS
#endif

#include <iostream>
#include <string>
#include "rlutil.h"
#include <fstream>
#include "GetWallpaper.h"
#include <cstring>
#include <istream>
#include <map>
#include <exception>

using namespace std;
using namespace rlutil;

// Including based on which OS is running.
#ifdef _WIN32
#include <windows.h>	// For Windows.
#else					// For non Windows.
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif
// Creating folder based on which OS is running.
void createDirectory(string name) {
#ifdef _WIN32			// For Windows.
CreateDirectoryA(name.c_str(), NULL);
#else					// For non Windows.
struct stat st = { };
if (stat(name.c_str(), &st) == -1) {
mkdir(name.c_str(), 0755);
}
#endif
}


map<string, int> colors;


int main() {

colors.insert(make_pair ("BLACK", BLACK));
colors.insert(make_pair ("BLUE", BLUE));
colors.insert(make_pair ("GREEN", GREEN));
colors.insert(make_pair ("CYAN", CYAN));
colors.insert(make_pair ("RED", RED));
colors.insert(make_pair ("MAGENTA", MAGENTA));
colors.insert(make_pair ("BROWN", BROWN));
colors.insert(make_pair ("GREY", GREY));
colors.insert(make_pair ("DARKGREY", DARKGREY));
colors.insert(make_pair ("LIGHTBLUE", LIGHTBLUE));
colors.insert(make_pair ("LIGHTGREEN", LIGHTGREEN));
colors.insert(make_pair ("LIGHTCYAN", LIGHTCYAN));
colors.insert(make_pair ("LIGHTRED", LIGHTRED));
colors.insert(make_pair ("LIGHTMAGENTA", LIGHTMAGENTA));
colors.insert(make_pair ("YELLOW", YELLOW));
colors.insert(make_pair ("WHITE", WHITE));

	string addchamp = "0";
	string ChampName;
	/*
	string wallpaper_dir = "Wallpaper";
	int size_color = BROWN;
	int champ_color = MAGENTA;
	int skin_color = BROWN;
	*/

	// Variables for the settings-read-out.
	string wallpaper_dir;
	int size_color;
	int champ_color;
	int skin_color;

	saveDefaultColor();
	setConsoleTitle("LoL - Wallpaper - Downloader //./ by Frederik Shull");

	ifstream settings;
	settings.open("settings.ini");
	
	if (settings.is_open()) {
		setColor(GREEN);
		cout << "settings.ini loaded successfully.\n";
		resetColor();
		string text;
		int count = 0;
		while (getline(settings, text)) {
			char *str = new char[text.size() + 1];
			copy(text.begin(), text.end(), str);
			str[text.size()] = '\0';
			char *p = strtok(str, " \r\t");
			while (p) {
				string line = p;
				count++;
				size_t seperator = line.find("="); // Find the "=" in e.g. "wallpaper_dir=Wallpaper" in line.
				if (seperator != string::npos) {
					string var = line.substr(0, seperator); // Copies all before the "=" in "wallpaper_dir=Wallpaper" from line to var.
					string attr = line.substr(seperator+1, -1); // Copies all after the "=" in "wallpaper_dir=Wallpaper" from line in attr.
					if(var == "wallpaper_dir") {
						//Check if 'attr' is a valid folder format!
						wallpaper_dir = attr;
						cout << "Option " << var << " set to " << attr << ".\n"; 
					}
					else if(var == "size_color") {
						try {
							size_color = colors.at(attr);
							cout << "Option " << var << " set to ";
							setColor(size_color);
							cout << attr << ".\n";
							resetColor();
						}
						catch (exception&) {
							cerr << "Unrecognized color '" << attr << "' in settings.ini at line " << count << "." << endl;
						}
					}
					else if(var == "champ_color") {
						try {
							champ_color = colors.at(attr);
							cout << "Option " << var << " set to ";
							setColor(champ_color);
							cout << attr << ".\n";
							resetColor();
						}
						catch (exception&) {
							cerr << "Unrecognized color '" << attr << "' in settings.ini at line " << count << "." << endl;
						}
					}
					else if(var == "skin_color") {
						try {
							skin_color = colors.at(attr);
							cout << "Option " << var << " set to ";
							setColor(skin_color);
							cout << attr << ".\n";
							resetColor();
						}
						catch (exception&) {
							cerr << "Unrecognized color '" << attr << "' in settings.ini at line " << count << "." << endl;
						}
					}
					else {
						cerr << "Unrecognized option '" << var << "' in settings.ini at line " << count << "." << endl;
					}
				}
				else {
					cerr << "Error in settings.ini at line " << count << "." << endl;
				}
				p = strtok(NULL, " \r\t");
			}
			delete[] str;
		}
	}
	else {
		setColor(YELLOW);
		cerr << "Failed to load settings.ini, using default settings instead.\n";
	}




	ifstream ChampList;
	ChampList.open("champions.ini");
	if (ChampList.is_open()) {

		setColor(LIGHTGREEN);
		cout << "champions.ini loaded successfully.\n\n";

		resetColor();
		cout << "Championlist: ";

		// Following is the same like but just multiplatform:
		/*
		while (getline(ChampList, ChampName)) {
		cout << ChampName;
		}		
		*/
		setColor(MAGENTA);
		while (getline(ChampList, ChampName)) {
			char *str = new char[ChampName.size() + 1];
			copy(ChampName.begin(), ChampName.end(), str);
			str[ChampName.size()] = '\0';
			char *p = strtok(str, " \r\t");
			while (p) {
				cout << p << " ";
				p = strtok(NULL, " \r\t");
			}
			delete[] str;
		}

		resetColor();
		cout
			<< "\n\nType a champion name to add a new champion and press enter.\n"
			<< "Type in '0' and press enter to skip/finish.\n";
		do {
			cout << "Championname: ";
			cin >> addchamp;

			if (addchamp != "0") {
				ofstream AddChamp;
				AddChamp.open("champions.ini", ofstream::app);
				if (AddChamp.is_open()) {
					AddChamp << addchamp << "\n";
				}
			}
		} while (addchamp != "0");
		cout << endl;
		
		ifstream ChampList;
		ChampList.open("champions.ini");
		if (ChampList.is_open()) {
		// Following is the same like above but just multiplatform:
		/*
		while (getline(ChampList, ChampName)) {
		GetWallpaper(ChampName, "Wallpaper");
		}
		*/
		while (getline(ChampList, ChampName)) {
			char *str = new char[ChampName.size() + 1];
			copy(ChampName.begin(), ChampName.end(), str);
			str[ChampName.size()] = '\0';
			char *p = strtok(str, " \r\t");
			while (p) {
				GetWallpaper(p, "Wallpaper");
				p = strtok(NULL, " \r\t");
			}
			delete[] str;
			}
		}

		resetColor();
		cout << "All Wallpaper downloaded. Press any key to exit..";
		cin.get();
		cin.get();
	}
	else {
		setColor(LIGHTRED);
		cout << "Failed to load champions.ini.\n\n";
		resetColor();
		cout << "Press any key to exit..";
		cin.get();
	}
	return 0;
}