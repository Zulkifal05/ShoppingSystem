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

singleOrder* orderQueueHead = nullptr; //Global head pointer for Order queue
singleOrder* orderQueueTail = nullptr; //Global tail pointer for Order queue

class ConfirmOrder {
public:
    void confirmOrder(vector<string> orderedItemNames, int totalOrderPrice) {  //Function to confirm orders and add in confirmation queue
        string deliveryAddress , contactNumber , paymentMethod;
        cout << "\nEnter your delivery address: ";
        cin >> deliveryAddress;
        cout << "Enter your contact number: ";
        cin >> contactNumber;
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
            cout << "\nOrder queued successfully.\n";
        } else {
            cout << "Error: Unable to open Orders.txt for writing.\n";
        }
    }
};

class Order {
public:     
    void displayOrderHistory() {
        cout << "\nDisplaying Order History... (Functionality not implemented in this snippet)\n";
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