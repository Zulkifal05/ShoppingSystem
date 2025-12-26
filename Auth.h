#include<iostream>
#include<fstream>
using namespace std;

class Auth
{
    string username , password;
public:

    Auth() {
        username = "";
        password = "";
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
    }

    void login() {
        cout << "\t\t\tLogin\n";
    }
};
