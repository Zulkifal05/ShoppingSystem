#pragma once
#include<iostream>
#include "Cart.h"
#include "Order.h"
#include "Category.h"
using namespace std;

class Menu : public Cart, public Order, public Category {
public:
    void displayMainMenu() {
        string choice;
        cout << "\n\n\t\t\tWelcome to the Shopping System\n\n";
        while(true) {
            cout << "\nA. Categories\n\t1- Garments\n\t2- Cosmetics\n\t3- Electronics\n\t4- Appliances\n\t5- Furniture\nB. View Cart\nC. Order History\nD. Logout\n\n";
            cout << "Please select an option from the menu above : ";
            cin >> choice;

            if((choice == "1") || (choice == "2") || (choice == "3") || (choice == "4") || (choice == "5")) {
                displayCategories(choice);
            }
            else if((choice == "B") || (choice == "b")) {
                displayCart();
            }
            else if((choice == "C") || (choice == "c")) {
                displayOrderHistory();
            }
            else if((choice == "D") || (choice == "d")) {
                cout << "\nLogging out... Goodbye!\n";
                break;
            }
            else {
                cout << "\nInvalid option selected. Please try again.\n";
            }
        }
    }
};