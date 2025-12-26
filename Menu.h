#pragma once
#include<iostream>
using namespace std;

class Menu {
public:
    void displayMainMenu() {
        cout << "\t\t\tWelcome to the Shopping System\n\n";
        cout << "1. View Products\n2. View Cart\n3. Checkout\n4. Logout\n";
        cout << "Please select an option from the menu above.\n";
    }
};