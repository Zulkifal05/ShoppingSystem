#pragma once
#include<iostream>
#include<fstream>
#include<sstream>
#include "Menu.h"
using namespace std;

class Auth : public Menu {
    string username , password;
    bool isLoggedIn;
public:

    Auth() {
        username = "";
        password = "";
        isLoggedIn = false;
    }

    void authMenu() {
        string choice;
        cout << "\t\t\tShopping System\n\n";

        while (true) {
            cout << "1. Login\n2. Register\n3. Exit\n";
            cout << "Enter your choice: ";
            getline(cin,choice);
            if ((choice == "1") || (choice == "2") || (choice == "3")) {
                break;
            }
            else {
                cout << "Invalid choice. Please try again.\n";
            }
        }

        if(choice == "1") {
            login();
        }
        else if(choice == "2") {
            registerUser();
        }
    }

    void registerUser() {
        cout << "\t\t\tRegister\n";
        while (true) {
            bool userExists = false;
            cout << "\nEnter username (Without Spaces) : ";
            cin >> username;
            cout << "\nEnter password (Without Spaces) : ";
            cin >> password;

            ifstream readFile("Users.txt");

            if(!readFile.is_open()) {
                cout << "Error opening file. Exiting.....\n";
                return;
            }

            string line;  //Check for if username already exists
            while(getline(readFile,line)) {
                stringstream ss(line);
                string storedUsername, storedPassword;  
                ss >> storedUsername;
                if(storedUsername == username) {    
                    cout << "Username already exists. Please try again.\n";
                    readFile.close();
                    userExists = true;
                    break;
                }   
            }

            if(!userExists) {  //If username does not exist, register the user
                readFile.close();
                ofstream writeFile("Users.txt", ios::app);
                if(!writeFile.is_open()) {
                    cout << "Error opening file. Exiting.....\n";
                    return;
                }
                writeFile << username << " " << password << "\n";
                writeFile.close();
                cout << "\nRegistration successful.....\n";
                isLoggedIn = true;

                ofstream writeCurrentUserFile("CurrentUser.txt");  //Store current logged in user
                if(writeCurrentUserFile.is_open()) {
                    writeCurrentUserFile << username;
                    writeCurrentUserFile.close();
                }
                break;
            }
        }

        if(isLoggedIn) {  //If registration is successful, display main menu
            displayMainMenu();
        }
    }

    void login() {
        cout << "\t\t\tLogin\n";

        while(true) {
            cout << "\nEnter username (Without Spaces) : ";
            cin>>username;
            cout << "\nEnter password (Without Spaces) : ";
            cin>>password;

            ifstream readFile("Users.txt");
            string line , savedUserName , savedPassword;

            if(!readFile.is_open()) {
                cout << "Error opening file. Exiting.....\n";
                return;
            }

            while(getline(readFile,line)) {  //Check for matching username and password
                stringstream ss(line);
                ss >> savedUserName >> savedPassword;

                if((savedUserName == username) && (savedPassword == password)) {
                    readFile.close();
                    cout << "\nLogin Successful.....\n";
                    isLoggedIn = true;

                    ofstream writeCurrentUserFile("CurrentUser.txt");  //Store current logged in user
                    if(writeCurrentUserFile.is_open()) {
                        writeCurrentUserFile << username;
                        writeCurrentUserFile.close();
                    }
                    break;
                }
            }

            if(isLoggedIn) {
                break;
            }
            else {
                cout << "\nInvalid username or password. Please try again.\n";
            }
        }

        if(isLoggedIn) {  //If login is successful, display main menu
            displayMainMenu();
        }
    }
};
