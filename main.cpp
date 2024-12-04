#include "Customer.h"
#include "Product.h"
#include "Storage.h"
#include "Shopping.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void selectRegisterCustomer();
void selectRemoveCustomer();
void selectAddProduct();
void selectRemoveProduct();
void selectShopping();
void selectViewCustomer();
void selectRedeemRewards();

int main()
{
    //print main menu from utils
    printMainMenu();

    //user menu selection
    int inp;
    while (true) {
        cout << endl << "Select a number from the menu: ";
        cin >> inp;
        cout << endl;

        //invalid input - not an integer or (integer not in valid 1-8 range)
        if (cin.fail() || (inp < 1 || inp > 8)) 
        {
            cin.clear();    //clear error
            cin.ignore(numeric_limits<streamsize>::max(),'\n');     //ignore characters size of stream or until a new line

            cout << "Invalid input.";
        }
        //valid input
        else {
            //inp should now direct user to selected item
            switch (inp) {
                case 1:
                    selectRegisterCustomer();
                    break;

                case 2:
                    selectRemoveCustomer();
                    break;
                    
                case 3:
                    selectAddProduct();
                    break;
                    
                case 4:
                    selectRemoveProduct();
                    break;
                    
                case 5:
                    selectShopping();
                    break;
                    
                case 6:
                    selectViewCustomer();
                    break;
                    
                case 7:
                    selectRedeemRewards();
                    break;

                case 8:
                    cout << "Quitting." << endl;
                    exit(0);
                    break;
            }
        }
    }
}

/*
selectRegisterCustomer function:
Used to create a customer to be written to the text file.

Return:
void - call to add addCustomer function
*/
void selectRegisterCustomer() {
    
    Customer customer;
    Storage storage;
    if(customer.getCustomerInput()) 
    {
        //registration inputs successful
        //store customer
        storage.addCustomer(customer);
    }
    else 
    {
        //failged registration inputs
    }
}

/*
selectRemoveCustomer function:
Used to remove a customer from the text file.

Return:
void - call to add removeCustomer function
*/
void selectRemoveCustomer() {
    Customer customer;
    Storage storage;
    storage.removeCustomer(customer);
}

/*
selectAddProduct function:
Used to create a product to be written to the text file.

Return:
void - call to addProduct function
*/
void selectAddProduct() {

    Product product;
    Storage storage;
    if(product.getProductInput()) 
    {
        //registration inputs successful
        //store customer
        storage.addProduct(product);
    }
    else 
    {
        //failged registration inputs
    }

}

/*
selectRemoveProduct function:
Used to Remove a product from the text file.

Return:
void - call to removeProduct function
*/
void selectRemoveProduct() {
    Product product;
    Storage storage;
    string removeProdID;
    cout << "What is the ID of the product: Prod";
    cin >> removeProdID;
    removeProdID = "Prod" + removeProdID;
    storage.removeProduct(removeProdID);

}

/*
selectShopping function:
Used to allow the customer to shop.

Return:
void - call to getShoppingInputs function
*/
void selectShopping() {
    Shopping shopping;
    Customer customer;
    string input;
    shopping.getShoppingInputs(customer);
}

/*
selectViewCustomer function:
Used to view a customer in the text file.

Return:
void - call to viewCustomer function
*/
void selectViewCustomer() {
    Storage storage;
    storage.viewCustomer();

}
/*
selectRedeemRewards function:
Used to allow the user to redeem rewards that they earned.

Return:
void - call to redeemRewards function
*/
void selectRedeemRewards() {
    Storage storage;
    Customer customer;

    storage.redeemRewards(customer);

}