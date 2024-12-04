#include "Product.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <fstream>


using namespace std;

Product::Product() {
    nextID = extractProductID();
}


/*
getProductInput function:
used for new product input before registration

parameter: 
none

Return:
bool - true/false depending on if registration was successful or not
*/
bool Product::getProductInput() {
    string name;
    double price;
    int amount;

    cout << "Please enter product's name: ";
    cin >> name;
    cout << endl;

    cout << "Please enter " << name << "'s price: ";
    cin >> price;
    cout << endl;

    cout << "Please enter the amount in stock: ";
    cin >> amount;
    cout << endl;

    //call registerCustomer and return result
    //true if successful registration
    //false if registration fails
    return addProduct(name, price, amount);
}

/*
addProduct function:
used to add a product to the text file

parameter: 
String- Name of product
double- Price of product
int- quantity of product

Return:
bool - true/false depending on if the product added was successful or not
*/
bool Product::addProduct(const string& name, double price, int amount) {
    //check price (must be positive number)
    if (price < 0.0) 
    {
        cout << "Invalid price" << endl;
        return false;
    }
    else 
    {
        //price is positive
    }

    //check amount (must be positive integer)
    if (amount < 0) 
    {
        cout << "Invalid amount" << endl;
        return false;
    }
    else 
    {
        //amount is positive
    }

    //set Product
    this->name = name;
    this->price = price;
    this->amount = amount;


    //set Product ID and increment
    this->ID = "Prod" + to_string(nextID);
    nextID++;

    //successful customer creation
    cout << "Successful Registration" << endl;
    return true;
}

/*
getID function:
Used to return ID of the product.

Return:
string - ID
*/
string Product::getID() const
{
    return ID;
}

/*
getName function:
Used to return the name of the product.

Return:
string - name
*/
string Product::getName() const
{
    return name;
}

/*
getPrice function:
Used to return the price of the product.

Return:
double - price
*/
double Product::getPrice()
{
    return price;
}

/*
getAmount function:
Used to return the quantity of the product.

Return:
int - quantity of product
*/
int Product::getAmount()
{
    return amount;
}

/*
getProdToString function:
Used to return all of the products information.

Return:
string - products information
*/
string Product::getProdToString() const
{
    ostringstream productPrint;

    productPrint << "\t" << ID << endl;
    productPrint << "\t" << name << endl;
    productPrint << "\t" << price << endl;
    productPrint << "\t" << amount << endl;

    return productPrint.str();
}

/*
extractProductID function:
Used to get the product id from the text file.

Return:
int - the next id
*/
int Product::extractProductID() {
    nextID = 10000;
    ifstream file("products.txt");
    string line;
    string lastID;

    while (getline(file, line)) 
    {
        if (line.find("Prod") == 1) 
        {
            lastID = line;
        }
        else 
        {
            //not found
        }
    }
    file.close();

    if (!lastID.empty()) 
    {
        string numbers = lastID.substr(5);
        nextID = stoi(numbers);
        nextID++;
    }
    else 
    {
        //no lastID, nextID defaults to 10000
    }
    return nextID;
}