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
            cin >> choice;
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
            cout << "\nEnter username: ";
            cin >> username;
            cout << "\nEnter password: ";
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
                break;
            }
        }

        if(isLoggedIn) {  //If registration is successful, display main menu
            displayMainMenu();
        }
    }

    void login() {
        cout << "\t\t\tLogin\n";
    }
};
