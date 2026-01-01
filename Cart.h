#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

struct cartItem {  //Structure to represent an item in the cart
    string categoryName , itemName;
    int price, cartItemID;
    cartItem *nextCartItem;
};

cartItem* headCartItem = nullptr; //Global head pointer for Cart linked list

int cartItemIDCounter = 0; //Global counter to assign unique IDs to cart items

class AddtoCart {  //Class to add items to cart
public:
    void addToCart(string categoryName, string itemName, int price) {
        cartItem* newCartItem = new cartItem();
        newCartItem->categoryName = categoryName;
        newCartItem->itemName = itemName;
        newCartItem->price = price;
        newCartItem->nextCartItem = nullptr;
        newCartItem->cartItemID = cartItemIDCounter;  //Assign unique ID
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

class Cart {  //Class to display cart items
public:
    void displayCart() {
        cout << "\n\n\t\tYour Cart Items\n\n";
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
