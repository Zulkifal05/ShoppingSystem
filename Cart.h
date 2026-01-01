#pragma once
#include <iostream>
using namespace std;

struct cartItem {  //Structure to represent an item in the cart
    string categoryName , itemName;
    int stockAvailable, price;
    cartItem *nextCartItem;
};

cartItem* headCartItem = nullptr; //Global head pointer for Cart linked list

class AddtoCart {  //Class to add items to cart
public:
    void addToCart(string categoryName, string itemName, int stockAvailable, int price) {
        cartItem* newCartItem = new cartItem();
        newCartItem->categoryName = categoryName;
        newCartItem->itemName = itemName;
        newCartItem->stockAvailable = stockAvailable;
        newCartItem->price = price;
        newCartItem->nextCartItem = nullptr;

        // Adding the new item to the cart (linked list)
        if(headCartItem == nullptr) {  //If cart is empty, new item becomes the head
            headCartItem = newCartItem;
        } else {  //Else, append to the start of the list
            newCartItem->nextCartItem = headCartItem;
            headCartItem = newCartItem;
        }
    }
};

class Cart {
public:
    void displayCart() {
        cout << "\nDisplaying Cart... (Functionality not implemented in this snippet)\n";
    }
};
