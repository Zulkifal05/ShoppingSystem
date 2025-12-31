#pragma once
#include <iostream>
using namespace std;

class AddtoCart {  //Base class to avoid ambiguity in multiple inheritance
public:
    void addToCart(int itemID) {
        cout << "\nAdding item " << itemID << " to cart... (Functionality not implemented in this snippet)\n";
    }
};

class Cart {
public:
    void displayCart() {
        cout << "\nDisplaying Cart... (Functionality not implemented in this snippet)\n";
    }
};
