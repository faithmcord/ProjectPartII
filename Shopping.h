#ifndef SHOPPING_H
#define SHOPPING_H

#include <vector>
#include <string>
#include "Customer.h"
#include "Product.h"
#include "Storage.h"
#include "utils.h"

using namespace std;

class Shopping {
    vector<string> cart; // This is the shopping cart

public:

    Shopping();
    void getShoppingInputs(const Customer& customer);
    void startShopping(const Customer& customer); 
    void viewProducts();
    void addtoCart(const string& productID);
    void removefromCart(const string& productID); 
    void viewCart();
    void checkout(); 
    int calculateCart(const string& productID);
    bool transaction();
    string getTransactionToString() const;
    


private:
    int checkoutPrice;
    string customerID;
    string userID;
    int rewardPoints;
    int nextID;
    string transactionID;

    int generateTransactionID();
   
};

#endif // SHOPPING_H
