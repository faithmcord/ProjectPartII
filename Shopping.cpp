#include "Shopping.h"
#include "Product.h"
#include "Customer.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>



using namespace std;

Shopping::Shopping() 
{
    nextID = generateTransactionID();
}

/*
getShoppingInputs function:
Used to get shopping inputs from the user.

parameter: 
customer

Return:
void
*/
void Shopping::getShoppingInputs(const Customer& customer) {
    cout << "Enter UserID: U_";
    cin >> userID;
    userID = "U_" + userID;

    ifstream file("customers.txt");
    string line;
    string trimmedLine;
    string prevLine;
    bool customerFound;

    //iterate text file, find username, and set customerID from found username
    while (getline(file, line)) 
    {
        istringstream ss(line);
        ss >> trimmedLine;
        if (trimmedLine == userID) 
        { 
            customerFound = true;
            customerID = prevLine;
            break;  
        }
        else 
        {
            prevLine = trimmedLine;
        }
    }
    file.close();

    // If customer is found, allow shopping
    if (!customerFound) 
    {
        cout << "You are not registered!" << endl;
        return;
    }
    else
    {
        //valid
        startShopping(customer);
    }
}

/*
startShopping function:
Used to start shopping once a user is logged in

parameter: 
customer - from getShoppingInputs()

Return:
void
*/
void Shopping::startShopping(const Customer& customer) {
    cout << endl << "Logged in as: " << userID << endl << endl;

    printShoppingMenu();

    int inp;
    string productID;
    while (true) 
    {
        cout << endl << "(" << userID << ") " << "Select a number from the menu: ";
        cin >> inp;
        cout << endl;

        // Invalid input - not an integer or (integer not in valid 1-4 range)
        if (cin.fail() || (inp < 1 || inp > 6)) 
        {
            cin.clear();    // Clear error
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore characters until a new line
            cout << "Invalid input." << endl;
        }
        // Valid input
        else 
        {
            // inp should now direct user to selected item
            switch (inp) {
                case 1:
                    viewProducts();
                    break;

                case 2:
                    viewCart();
                    break;

                case 3:
                    viewProducts();     //ADDING ALSO PRINTS PRODUCTS -- can remove?
                    cout << "Enter ProdID to add to cart: Prod";
                    cin >> productID;
                    addtoCart("Prod" + productID);
                    break;

                case 4:
                    viewCart();        //REMOVING ALSO PRINTS CART -- can remove? idk it looks maybe bad but also makes sense
                    if (!cart.empty()) {
                        cout << endl << "Enter ProdID to remove from cart: Prod";
                        cin >> productID;
                        removefromCart("Prod" + productID); 
                    }
                    break;

                case 5:
                    checkout(); 
                    break;

                case 6:
                    cout << "Exiting Shopping" << endl;
                    cout << endl;
                    printMainMenu();
                    return;
            }
        }
    }
}

/*
viewProducts function:
Used to View what items are available

Return:
void 
*/
void Shopping::viewProducts() {
    ifstream file("products.txt");
    string line;
    while (getline(file, line)) 
    {
        cout << line << endl;
    }
    file.close();
}

/*
viewCart function:
Used to View what items are in your cart

Return:
void 
*/
void Shopping::viewCart() {

    //empty cart
    if (cart.empty()) 
    {
        cout << "Your cart is empty!" << endl;
    }
    //not empty cart
    else 
    {
        cout << "Cart: ";
        for(size_t i = 0; i < cart.size(); i++)    //size_t = unsigned int. cart.size is that type so keep matching types for comparison
        {
            //add comma between items
            if (i > 0)
                cout << ", ";
            else{
                //nothing
            }
            cout << cart[i];
        }
    }
}

/*
addtoCart function:
Used to add items to your shopping cart

Parameter:
ProductID - id of the product you are wanting in your cart

Return:
void 
*/
void Shopping::addtoCart(const string& productID) 
{
    ifstream file("products.txt");
    string line;
    string trimmedLine;

    while(getline(file, line))
    {
        istringstream ss(line);
        ss >> trimmedLine;
        if(trimmedLine == productID)
        {
            cart.push_back(productID);
            cout << productID << " has been added to your cart" << endl;
            return;
        }
        else
        {
            //nothing
        }
        
    }
    cout << "Invalid Product" << endl;
}

/*
removefromCart function:
Used to remove items from your shopping cart

Parameter:
ProductID - id of the product you are wanting removed from your cart

Return:
void 
*/
void Shopping::removefromCart(const string& productID) 
{
    
    for(int i = 0; i < cart.size(); i++)
    {
        if(cart[i] == productID)
        {
            cart.erase(cart.begin() + i);
            cout << productID << " has been removed from cart" << endl;
            break;
        }
        else
        {
            //nothing
        }
    }
}

/*
checkout function:
Used to checkout the products in the users cart

Return:
void - Checking out
*/
void Shopping::checkout() 
{
    char checkoutInput;
    checkoutPrice = 0;
    Storage storage;
    Shopping shopping;

    if(cart.empty())
    {
        cout << "Checked out nothing!" << endl;
        return;
    }
    else
    {
        //nothing
    }

    viewCart(); 
    cout << endl;

    for(int i = 0; i < cart.size(); i++)
    {
        checkoutPrice += calculateCart(cart[i]);
    }
    cout << "Total: $" << to_string(checkoutPrice) << endl;

    cout << "Do you wish to checkout?(Y/N): ";
    cin >> checkoutInput;
    if(checkoutInput == 'Y' || checkoutInput == 'y')
    {
        
        cout << "Enjoy! ";
        //add rewards
        rewardPoints = checkoutPrice * 10;     //calculate rewardPoints
        storage.changeStockAmount(cart);
        storage.addRewards(customerID, rewardPoints);
        cout << "You earned " << rewardPoints << " points from today's purchase!" << endl;
        
        //add transaction to storage
        transaction();
        storage.addTransaction(*this);

        

        //clear cart
        cart.clear();

    }
    else
    {
        cout << "Canceled" << endl;
        return;
    }

}

/*
calculateCart function:
Used to calculate the price of your shopping cart

Parameter:
ProductID - id of the product

Return:
int- price of the cart
*/
int Shopping::calculateCart(const string& productID)
{
    ifstream file("products.txt");
    string line;
    int price = 0;

    while(getline(file, line))
    {
        if(line.find(productID) != string::npos)
        {
            //skip lines to get the price
            getline(file, line); 
            getline(file, line);

            price = stoi(line);
            return price;
        }
        else
        {
            //nothing
        }
        
    }
    return -1;  //error

}

/*
transaction function:
Used to process a transaction with all of the correct details

Return:
bool - transaction successfull
*/
bool Shopping::transaction()
{
    this->customerID = customerID;
    this->cart = cart;
    this->checkoutPrice = checkoutPrice;
    this->rewardPoints = rewardPoints;
    this->transactionID = "Trans" + to_string(nextID);
    nextID++;

    return true;

}

/*
getTransactionToString function:
Used to print all of the transaction details

Return:
string - trasaction details
*/
string Shopping::getTransactionToString() const
{
    ostringstream transactionPrint;

    transactionPrint << "\t" << transactionID << endl;
    transactionPrint << "\t" << customerID << endl;
    transactionPrint << "\t";
    for(int i = 0; i < cart.size(); i++)
    {
        transactionPrint <<  cart[i];
        if (i != cart.size()-1) 
        {
            transactionPrint << ", ";
        }
        else 
        {
            //nothing
        }
    }
    transactionPrint << endl;
    transactionPrint << "\t" << checkoutPrice << endl;
    transactionPrint << "\t" << rewardPoints << endl;
   

    return transactionPrint.str();
}

/*
generateTransactionID function:
Used to generate the trasaction id

Return:
int - nextID
*/
int Shopping::generateTransactionID()
{
    nextID = 10000;
    ifstream file("transactions.txt");
    string line;
    string lastID;

    while (getline(file, line)) 
    {
        if (line.find("Trans") == 1) 
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
        string numbers = lastID.substr(6);
        nextID = stoi(numbers);
        nextID++;
    }
    else 
    {
        //no lastID, nextID defaults to 10000
    }
    return nextID;
}