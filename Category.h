#pragma once
#include <iostream>
#include <iomanip>
#include "Cart.h"
#include <string>
#include <algorithm>  // For using all_of
#include <cctype>     // For using isdigit
using namespace std;

struct Item {  //Structure to represent an item in a category using linked list
    string categoryID , categoryName , itemName;
    int stockAvailable , price , itemID;
    Item *nextItem;
};

Item* headItem = nullptr; //Global head pointer for Item linked list

int minimumItemID , maximumItemID; //Global variables to track min and max item IDs that would be associated with each item in loadCategoryItems function

class Category : public AddtoCart {
public:
    void loadCategoryItems(string category) {  //Function to load items into the linked list
        ifstream readFile("items.txt");
        if(!readFile.is_open()) {
            cout << "Error opening items file.\n";
            return;
        }
        string catID, catName, itemName , line;
        int stock, price;

        int itemIDCounter = 0;  //Counter to assign unique item IDs
        minimumItemID = itemIDCounter;  //Set minimum item ID at the start

        while(getline(readFile,line)) {
            stringstream ss(line);
            ss >> catID >> catName >> itemName >> stock >> price;
            if(catID == category) {  //If the item belongs to the selected category
                Item* newItem = new Item();
                newItem->categoryID = catID;
                newItem->categoryName = catName;
                newItem->itemName = itemName;
                newItem->stockAvailable = stock;
                newItem->price = price;
                newItem->itemID = itemIDCounter;
                newItem->nextItem = nullptr;
                maximumItemID = itemIDCounter;  //Update maximum item ID
                itemIDCounter++;  //Increment item ID counter

                if(headItem == nullptr) {  //If list is empty, new item becomes the head
                    headItem = newItem;
                } else {  //Else, append to the start of the list
                    newItem->nextItem = headItem;
                    headItem = newItem;
                }
            }
        }
        readFile.close();
    }

    void clearCategoryItems() {  //Function to clear the linked list
        Item* current = headItem;
        Item* nextItem;
        while(current != nullptr) {
            nextItem = current->nextItem;
            delete current;
            current = nextItem;
        }
        headItem = nullptr;
    }

    void displayCategoryItems(string selectedCategory) {
        loadCategoryItems(selectedCategory);
        string itemIDInput;
        if(headItem == nullptr) {
            cout << "\n\nNo items available in this category.\n";
            return;
        }
        Item* current = headItem;
        cout << "\n\n\t\tItems in Category -> " << current->categoryName << "\n\n";
        cout << "itemID" << setw(30) << "Item Name" << setw(30) << "Stock" << setw(30) << "Price" << "\n";
        while(current != nullptr) {
            cout << current->itemID << setw(35) << current->itemName << setw(35) << current->stockAvailable << setw(35) << current->price << "\n";
            current = current->nextItem;
        }
        while(true) {  //Loop to allow multiple additions to cart
            cout << "\nEnter the itemID of the item you wish to add to your cart : ";
            cin >> itemIDInput;
            bool isNumber = !itemIDInput.empty() && all_of(itemIDInput.begin(), itemIDInput.end(), ::isdigit);  //Check if input is a number
            if(!isNumber) {  //If not a number, ask again
                cout << "\nInvalid itemID entered. Please try again.\n";
                continue;
            }
            int itemID = stoi(itemIDInput);  //Convert string input to integer
            if((itemID < minimumItemID) || (itemID > maximumItemID)) {
                cout << "\nInvalid itemID entered. Please try again.\n";
            }
            else {  //If valid itemID then add to cart and ask if user wants to add more items
                Item *temp = headItem;  //Pointer to traverse the linked list

                while(temp != nullptr) {  //Traverse the list to find the entered itemID
                    if(temp->itemID == itemID) {
                        break;
                    }
                    temp = temp->nextItem;
                }
                addToCart(temp->categoryName, temp->itemName, temp->stockAvailable, temp->price);  //Call addToCart function from AddtoCart class
                string moreChoice;
                cout << "Do you want more items from this category? (Y/N) : ";
                cin >> moreChoice;
                if((moreChoice == "Y") || (moreChoice == "y")) {
                    continue;
                }
                else {
                    break;
                }
            }
        }
        clearCategoryItems();
    }
};