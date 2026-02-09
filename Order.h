#pragma once
#include<iostream>
#include "Cart.h"
#include <vector>
using namespace std;

struct singleOrder {  //Structure to represent an item in the order
    vector<string> itemNames;  //Vector to hold names of items in the order
    int totalPrice;
    singleOrder* nextOrderItem;
};

struct singleOrderHistoryItem {  //Structure to represent an item in the order history
    vector<string> itemNames;  //Vector to hold names of items in the order history
    int totalPrice;
    string deliveryAddress , contactNumber , paymentMethod;
    singleOrderHistoryItem* nextOrderHistoryItem;
};

singleOrder* orderQueueHead = nullptr; //Global head pointer for Order queue
singleOrder* orderQueueTail = nullptr; //Global tail pointer for Order queue

singleOrderHistoryItem* orderHistoryStackTop = nullptr; //Top of Order History stack

bool orderHistoryFetched = false; //Flag to indicate if order history has been fetched

class Order {
public:     
    void displayOrderHistory() {
        if(!orderHistoryFetched) {  //Fetch order history from file only if not already fetched
            //Read current logged-in user from CurrentUser.txt
            ifstream readCurrentUserFile("CurrentUser.txt");
            string currentUsername;
            if(readCurrentUserFile.is_open()) {
                getline(readCurrentUserFile, currentUsername);
                readCurrentUserFile.close();
            } else {
                currentUsername = "UnknownUser";
            }
            cout << "\n\n\t\t\tYour Order History\n\n";
            fetchOrderHistoryFromFile(currentUsername);
            iterateAndDisplayOrderHistoryStack();
        } else {  //If already fetched, just display
            cout << "\n\n\t\t\tYour Order History\n\n";
            iterateAndDisplayOrderHistoryStack();
        }
    }

    void iterateAndDisplayOrderHistoryStack() {
        if(orderHistoryStackTop == nullptr) {
            cout << "\nNo order history found.\n";
            return;
        }
        singleOrderHistoryItem* currentHistoryItem = orderHistoryStackTop;
        int orderCount = 1;
        while(currentHistoryItem != nullptr) {
            cout << "Order " << orderCount << ":\n";
            cout << "Total Price: " << currentHistoryItem->totalPrice << " Rs\n";
            cout << "Delivery Address: " << currentHistoryItem->deliveryAddress << "\n";
            cout << "Contact Number: " << currentHistoryItem->contactNumber << "\n";
            cout << "Payment Method: " << currentHistoryItem->paymentMethod << "\n";
            cout << "Items: ";
            for(int i = 0; i < currentHistoryItem->itemNames.size(); i++) {
                cout << currentHistoryItem->itemNames[i] << " . ";
            }
            cout << "\n\n";
            currentHistoryItem = currentHistoryItem->nextOrderHistoryItem;
            orderCount++;
        }
    }

    void fetchOrderHistoryFromFile(string currentUsername) {
        ifstream readOrdersFile("Orders.txt");
        if(readOrdersFile.is_open()) {
            string line;
            while(getline(readOrdersFile, line)) {  //Read each line from Orders.txt
                stringstream ss(line);
                string username;
                ss >> username;
                if(username == currentUsername) {  //If the order belongs to the current user
                    singleOrderHistoryItem* newHistoryItem = new singleOrderHistoryItem();
                    int totalPrice;
                    string itemNames;  //For reading comma-separated item names
                    ss >> totalPrice;
                    newHistoryItem->totalPrice = totalPrice;
                    ss >> newHistoryItem->deliveryAddress >> newHistoryItem->contactNumber >> newHistoryItem->paymentMethod  >> itemNames;
                    newHistoryItem->itemNames.clear();
                    //Split itemNames by commas and store in vector
                    stringstream itemSS(itemNames);
                    string itemName;
                    while(getline(itemSS, itemName, ',')) {
                        newHistoryItem->itemNames.push_back(itemName);
                    }
                    newHistoryItem->nextOrderHistoryItem = orderHistoryStackTop;
                    orderHistoryStackTop = newHistoryItem;
                }
            }
            readOrdersFile.close();
            orderHistoryFetched = true; //Set flag to true after fetching
        }
    }

    void deleteOrderHistoryStack() {
        singleOrderHistoryItem* currentHistoryItem = orderHistoryStackTop;
        while(currentHistoryItem != nullptr) {
            singleOrderHistoryItem* tempHistoryItem = currentHistoryItem;
            currentHistoryItem = currentHistoryItem->nextOrderHistoryItem;
            delete tempHistoryItem;  //Free memory allocated for each history item
        }
        orderHistoryStackTop = nullptr; //Reset top pointer
    }

    void dispatchOrdersAndDeleteOrdersQueue() {
        singleOrder* currentOrder = orderQueueHead;
        int orderCount = 0;
        while(currentOrder != nullptr) {
            singleOrder* tempOrder = currentOrder;
            currentOrder = currentOrder->nextOrderItem;
            delete tempOrder;  //Free memory allocated for each order
            orderCount++;
        }
        orderQueueHead = orderQueueTail = nullptr; //Reset head and tail pointers
        cout << "\n\t\t\t" << orderCount << " order dispatched.\n\t\tThank you for using our service!\n";
    }
};

class ConfirmOrder : virtual public Order {  //Virtual inheritence because Order is also inherited by menu class directly
public:
    void confirmOrder(vector<string> orderedItemNames, int totalOrderPrice) {  //Function to confirm orders and add in confirmation queue
        string deliveryAddress , contactNumber , paymentMethod;
        cout << "\nEnter your delivery address (Without Spaces): ";
        cin.ignore();
        getline(cin,deliveryAddress);
        cout << "Enter your contact number (Without Spaces): ";
        cin.ignore();
        getline(cin,contactNumber);
        while(true) {
            cout << "Do you want to pay by (1) Cash on Delivery or (2) Online Payment? Enter 1 or 2: ";
            cin >> paymentMethod;
            if(paymentMethod == "1" || paymentMethod == "2") {
                paymentMethod = (paymentMethod == "1") ? "CashonDelivery" : "OnlinePayment";
                break;
            } else {
                cout << "Invalid payment method selected. Please try again.\n";
            }
        }
        //Now, create a new order node and add it to the order queue and write to Orders.txt
        singleOrder* newOrder = new singleOrder();
        newOrder->itemNames = orderedItemNames;
        newOrder->totalPrice = totalOrderPrice;
        newOrder->nextOrderItem = nullptr;
        if(orderQueueTail == nullptr) {  //If queue is empty, initialize head and tail
            orderQueueHead = orderQueueTail = newOrder;
        } else {  //Add new order to the end of the queue
            orderQueueTail->nextOrderItem = newOrder;
            orderQueueTail = newOrder;
        }
        // Write order details to Orders.txt
        ofstream writeOrdersFile("Orders.txt", ios::app);
        if(writeOrdersFile.is_open()) {  //write order details to file if file opens successfully
            //Read current logged-in user from CurrentUser.txt
            ifstream readCurrentUserFile("CurrentUser.txt");
            string currentUsername;
            if(readCurrentUserFile.is_open()) {
                getline(readCurrentUserFile, currentUsername);
                readCurrentUserFile.close();
            } else {
                currentUsername = "UnknownUser";
            }

            writeOrdersFile << currentUsername << " " << newOrder->totalPrice << " " << deliveryAddress << " " << contactNumber << " " << paymentMethod << " ";
            for(int i = 0; i < newOrder->itemNames.size(); i++) {  //Write item names separated by commas
                writeOrdersFile << newOrder->itemNames[i] << ",";
            }
            writeOrdersFile << "\n";
            writeOrdersFile.close();
            deleteOrderHistoryStack(); //Clear existing order history stack to force re-fetch next time
            orderHistoryFetched = false;  //Reset flag
            cout << "\nOrder queued successfully.\n";
        } else {
            cout << "Error: Unable to open Orders.txt for writing.\n";
        }
    }
};