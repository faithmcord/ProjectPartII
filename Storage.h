#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include "Customer.h"
#include "Product.h"
#include "Shopping.h"
#include "utils.h"

using namespace std;

class Shopping;

class Storage {

    public:
        Storage();
        void addCustomer(const Customer& customer);
        void removeCustomer(const Customer& customer);
        void addProduct(const Product& product);
        void removeProduct(string removeProdID);
        void addTransaction(const Shopping& shopping);
        void viewCustomer();
        void addRewards(string custID, double points);
        void redeemRewards(const Customer& customer);
        void spendPoints();
        double rewardPoints;
        void viewItems();
        void redeemItem();
        double vacation = 100000.00;
        double giftCard = 1000.00;
        double phone = 50000.00;
        double tickets = 25000.00;
        string redeemedCustomer;
        void changePoints();
        void changeStockAmount(vector<string> cart);
        void rewriteStock(const string& prodID);

    private:
        int customerCount;
        int productCount;
        int transactionCount;

};

#endif // STORAGE_H