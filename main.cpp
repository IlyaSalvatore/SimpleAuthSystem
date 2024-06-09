#include <iostream>
#include "windows.h"
#include <cstring>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <cstdio>
#include <stdlib.h>

using namespace std;
namespace fs = std::filesystem;

string existfileanswer;
string startlogin;
string startpassword;
int pass;
bool registered;

void file_exists(const fs::path& pathtofile, fs::file_status filestat = fs::file_status{})
{
    if (fs::status_known(filestat) ? fs::exists(filestat) : fs::exists(pathtofile))
    	existfileanswer = "exists";
    else
    	existfileanswer = "notexists";
}


int signin(){
	const char* pathfile = "C:/pswd.txt";

	file_exists(pathfile);

	if (existfileanswer == "exists"){
		cout << "\nSorry, you have a registered account.";
		Sleep(500);
		registered = true;
		return 0;
	}

	else {

		ofstream account("C:/pswd.txt");

		cout << "\nEnter your best login: ";
		string betterlogin;
		cin >> betterlogin;
		Sleep(500);

		cout << "\nEnter your best password: ";
		string betterpassword;
		cin >> betterpassword;

		account << "login=" + betterlogin + "\n";
		account << "password=" + betterpassword;

		Sleep(1000);

		cout << "Good! You already registered! Go to login.";
		registered = true;
		return 0;
	}

}
int login(){
	const char* pathfile = "C:/pswd.txt";
	file_exists(pathfile);

	if (existfileanswer == "exists"){

		std::string line;
		std::ifstream in(pathfile);

		if (in.is_open()) {
        if (in.peek() == std::ifstream::traits_type::eof()) {
            in.close();
            char filename[] = "C:/pswd.txt";
            if (remove(filename) == 0) {
                cout << "\nFile read wrong, file successfully deleted.";
                Sleep(2000);
                exit( 1 );
            } else {
                cout << "\nFile read wrong. Delete file failed. Exit the program";
                Sleep(2000);
                exit( 1 );
            }
        }
     }

		if (in.is_open()) {
        while (std::getline(in, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                if (key == "login") {
                    startlogin = value;
                } else if (key == "password") {
                    startpassword = value;
                }
            }
        }
     }

		pass = 0;

		while (pass == 0) {
			cout << "\nEnter your login: ";
			string urlogin;
			cin >> urlogin;

			if (urlogin == startlogin){
				cout << "\nEnter Your Password: ";
				string urpswd;
				cin >> urpswd;

				if (urpswd == startpassword) {
					cout << "\nGood!\n";
					pass = 1;
					return 0;
				}

				else {
					cout << "\nWrong, repeat.\n";
				}
			}

			else {
				cout << "\nWrong\n";
			}

		}

		in.close();
	}


	else {
		cout << "\nLogin file not founded. Going to SignIn!";
		Sleep(2000);
		signin();
	}

	return 0;
}


int main(){
	cout << "Hello user! You want to login or signin?\n";
	Sleep(500);
	cout << "Print 1 (Login) or 2 (Signin): ";
	int answer;
	cin >> answer;

	if (answer == 1){
		login();
	}
	else if (answer == 2){
		signin();
	}

	else {
		cout << "\nWrong answer. Exit the program.";
		Sleep(1500);
		return 0;
	}

	if (registered == true) {
		login();
	}

	if (pass == 1) {
		cout << "Very nice! U successfully logined!";
		Sleep(5000);
	}
}