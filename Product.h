#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>

using namespace std;

class Product 
{
    public:
    
        //constructor
        Product();
        
        //get data for product
        bool getProductInput();

        //register a product based on getProductInput() data
        bool addProduct(const string& name, double price, int amount);

        //getters
        string getID() const;
        string getName() const;
        double getPrice();
        int getAmount();

        string getProdToString() const;


    private:
        int nextID;      //keeps track of the next ID to be added
        string ID;
        string name;
        double price;
        int amount;

        //methods
        int extractProductID();

};



#endif // PRODUCT_H