#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>  // For using all_of
#include <cctype>     // For using isdigit
#include "Order.h"
using namespace std;

struct cartItem {  //Structure to represent an item in the cart
    string categoryName , itemName;
    int price, cartItemID;
    cartItem *nextCartItem;
};

cartItem* headCartItem = nullptr; //Global head pointer for Cart linked list

int cartItemIDCounter = 0; //Global counter to assign unique IDs to cart items
int minCartItemID = cartItemIDCounter; //Global variable to track minimum cart item ID
int maxCartItemID = cartItemIDCounter; //Global variable to track maximum cart item ID

class AddtoCart {  //Class to add items to cart
public:
    void addToCart(string categoryName, string itemName, int price) {
        cartItem* newCartItem = new cartItem();
        newCartItem->categoryName = categoryName;
        newCartItem->itemName = itemName;
        newCartItem->price = price;
        newCartItem->nextCartItem = nullptr;
        newCartItem->cartItemID = cartItemIDCounter;  //Assign unique ID
        maxCartItemID = cartItemIDCounter;  //Update max ID
        cartItemIDCounter++;  //Increment counter for next item

        // Adding the new item to the cart (linked list)
        if(headCartItem == nullptr) {  //If cart is empty, new item becomes the head
            headCartItem = newCartItem;
        } else {  //Else, append to the start of the list
            newCartItem->nextCartItem = headCartItem;
            headCartItem = newCartItem;
        }
    }
};

class Cart : public ConfirmOrder {  //Class to display cart items and manage cart
public:
    void displayCart() {
        cout << "\n\n\t\t\tYour Cart Items\n\n";
        if(headCartItem == nullptr) {
            cout << "Your cart is empty.\n";
            return;
        }
        cartItem* current = headCartItem;
        cout << "ItemID" << setw(30) << "Category" << setw(30) << "Item Name" << setw(30) << "Price" << "\n";
        while(current != nullptr) {
            cout << current->cartItemID << setw(35) << current->categoryName << setw(35) << current->itemName << setw(35) << current->price << "\n";
            current = current->nextCartItem;
        }
        //Prompt user to confirm order of an item from the cart
        string confirmOrderInput;

        while(true) {
            cout << "\nDo you want to confirm the order (Y/N) : ";
            cin >> confirmOrderInput;
            if(confirmOrderInput == "Y" || confirmOrderInput == "y") {  //If user confirms order
                vector<string> orderedItemNames;
                int totalOrderPrice = 0;
                current = headCartItem;
                while(current != nullptr) {  //Collect all item names in the cart for the order and calculate total price
                    orderedItemNames.push_back(current->itemName);
                    totalOrderPrice += current->price;
                    current = current->nextCartItem;
                }
                confirmOrder(orderedItemNames, totalOrderPrice);  //Call the confirmOrder function from ConfirmOrder class and pass the collected item names and total price
                clearCart();  //Clear the cart after confirming the order
                break;
            } else if(confirmOrderInput == "N" || confirmOrderInput == "n") {  //If user does not confirm order
                string continueEditInput;
                cout << "\nDo you want to continue shopping or edit cart (S/E) : ";
                cin >> continueEditInput;
                if(continueEditInput == "S" || continueEditInput == "s") {
                    //Let user continue shopping
                    break;
                } else if(continueEditInput == "E" || continueEditInput == "e") {
                    //Let user edit the cart
                    editCart();
                    break;
                } else {
                    cout << "Invalid input. Please enter S or E.\n";
                }
            } else {
                cout << "Invalid input. Please enter Y or N.\n";
            }
        }
    }

    void editCart() {  //Function to edit cart items (remove items)
        if(headCartItem == nullptr) {
            cout << "\nYour cart is empty. Nothing to edit.\n";
            return;
        }
        string itemIDInput;
        cout << "\nEnter the ItemID of the item you wish to remove from your cart : ";
        cin >> itemIDInput;
        bool isNumber = !itemIDInput.empty() && all_of(itemIDInput.begin(), itemIDInput.end(), ::isdigit);  //Check if input is a number
        if(!isNumber) {  //If not a number, ask again
            cout << "\nInvalid ItemID entered. Please try again.\n";
            return;
        }
        int itemID = stoi(itemIDInput);  //Convert string input to integer
        if((itemID < minCartItemID) || (itemID > maxCartItemID)) {
            cout << "\nInvalid ItemID entered. Please try again.\n";
            return;
        }
        //Removing the item from the cart linked list
        cartItem* current = headCartItem;
        cartItem* previous = nullptr;
        while(current != nullptr && current->cartItemID != itemID) {
            previous = current;
            current = current->nextCartItem;
        }
        if(current == nullptr) {
            cout << "\nItem with ItemID " << itemID << " not found in cart.\n";
            return;
        }
        if(previous == nullptr) {  //Item to be removed is the head
            headCartItem = current->nextCartItem;
        } else {
            previous->nextCartItem = current->nextCartItem;
        }
        delete current;  //Free memory
        cout << "\nItem with ItemID " << itemID << " has been removed from your cart.\n";

    }

    void clearCart() {  //Function to clear the cart linked list
        cartItem* current = headCartItem;
        cartItem* nextCartItem;
        while(current != nullptr) {
            nextCartItem = current->nextCartItem;
            delete current;
            current = nextCartItem;
        }
        headCartItem = nullptr;
    }
};
