#include "Storage.h"
#include <fstream>
#include <ostream>
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>
#include <unordered_map>

using namespace std;


Storage::Storage() : customerCount(0), productCount(0), transactionCount(0) 
{
    // Check existing customer count in customers.txt
    ifstream file("customers.txt");
    string line;
    while (getline(file, line)) 
    {
        if (line.find("Customer") != string::npos) 
        {
            customerCount++;
        }
        else
        {
            //nothing
        }
    }
    file.close();

    //check existing product count in products.txt
    ifstream file2("products.txt");
    while (getline(file2, line)) 
    {
        if (line.find("Product") != string::npos) 
        {
            productCount++;
        }
        else
        {
            //nothing
        }
    }
    file2.close();

     //check existing transaction count in transactions.txt
    ifstream file3("transactions.txt");
    while (getline(file3, line)) 
    {
        if (line.find("Transaction") != string::npos) 
        {
            transactionCount++;
        }
        else
        {
            //nothing
        }
    }
    file3.close();

}

/*
addCustomer function:
Used to add a customer from the list.

parameter: 
customer - inputed from the user

Return:
void - appened to the text file
*/
void Storage::addCustomer(const Customer& customer) 
{
    ofstream file("customers.txt", ios::app);  // open in append mode (is this necessary)

    //file opens
    if (file.is_open()) 
    {
        customerCount++;
        file << "Customer " << customerCount << endl; 
        file << customer.getCustomerToString();   //make a customer toString that returns all data
        file.close();
    }
    else 
    {
        //file cannot open
        cout << "Error opening customers.txt";
    }
}

/*
removeCustomer function:
Used to remove a customer from the list and rewrite the text file.

parameter: 
customer - inputed from the user

Return:
void - rewrite to the text file
*/
void Storage::removeCustomer(const Customer& customer) 
{
    ifstream file("customers.txt");
    string removeUserID;
    cout << "What is the ID of the customer: Cust";
    cin >> removeUserID;
    removeUserID = "Cust" + removeUserID;

    vector<string> customerFile;
    string line;

    while(getline(file, line))
    {
        if(line.find("Customer") != string::npos)
        {
            getline(file,line);
        }
        else
        {
            //nothing
        }
        if(line.find(removeUserID) == string::npos)
        {
            customerFile.push_back(line);
        }
        else
        {
            for(int i = 0; i < 5; i++)
            {
                getline(file,line);
            }
        }
    }
    file.close();


    //rewrite to customer file
    int lineCount = 0;
    customerCount = 1;
    ofstream outputFile("customers.txt");
    for (const string& outputLine : customerFile) 
    {

        if (lineCount % 6 == 0) 
        {
            outputFile << "Customer " << customerCount++ << endl;  // Add "Customer _"
        }
        else
        {
            //nothing
        }
        outputFile << outputLine << endl;  // Write remaining lines back to the file
        lineCount++;
    }

    outputFile.close();  // Close the output file
    cout << "Customer with ID " << removeUserID << " has been removed." << endl; 
}




/*
viewCustomers function:
Used to view a specific customer given CustID

parameter: 
Customer - input from user

Return:
void - print
*/
void Storage::viewCustomer() 
{
    cout << "Enter CustID: Cust";
    string custID;
    cin >> custID;
    custID = "Cust" + custID;

    //try to open file
    ifstream file("customers.txt");
    if (!file.is_open()) 
    {
        return;
    }
    else 
    {
        //nothing
    }

    bool found = false;
    string line;
    string trimmedLine;
    int lineCounter = 0;
    while (getline(file, line)) 
    {
        istringstream ss(line);
        ss >> trimmedLine;
        if (found) 
        {
            cout << trimmedLine << endl;
            lineCounter++;
            if (lineCounter == 5) 
            {  //prints out the next 5 lines for that customer info then stops
                break;
            }
            else 
            {
                //nothing
            }
        }
        else if (custID == trimmedLine) 
        {
            found = true;
        }
        else 
        {
            //nothing
        }
    }

}




/*
addProduct function:
Used to add a product to storage

parameter: 
product - inputed from the user from getProductInput

Return:
void - appened to the text file
*/
void Storage::addProduct(const Product& product) 
{
    ofstream file("products.txt", ios::app);  // open in append mode (is this necessary)

    //file opens
    if (file.is_open()) 
    {
        productCount++;
        file << "Product " << productCount << endl; 
        file << product.getProdToString();   //make a customer toString that returns all data
        file.close();
    }
    else 
    {
        //file cannot open
        cout << "Error opening products.txt";
    }
}


/*
removeProduct function:
Used to remove a product from the list and rewrite the text file.

parameter: 
product - inputed from the user

Return:
void - rewrite to the text file
*/
void Storage::removeProduct(string removeProdID) {

    ifstream file("products.txt");
    vector<string> productFile;
    string line;

    while(getline(file, line))
    {
        if(line.find("Product") != string::npos)
        {
            getline(file,line);
        }
        else
        {
            //nothing
        }
        if(line.find(removeProdID) == string::npos)
        {
            productFile.push_back(line);
        }
        else
        {
            for(int i = 0; i < 3; i++)
            {
                getline(file,line);
            }
        }
    }
    file.close();


    //rewrite to customer file
    int lineCount = 0;
    productCount = 1;
    ofstream outputFile("products.txt");
    for (const string& outputLine : productFile) 
    {

        if (lineCount % 4 == 0) 
        {
            outputFile << "Product " << productCount++ << endl;  // Add "Prod_"
        }
        else
        {
            //nothing
        }
        outputFile << outputLine << endl;  // Write remaining lines back to the file
        lineCount++;
    }

    outputFile.close();  // Close the output file
    cout << "Product with ID " << removeProdID << " has been removed." << endl;


    
}

/*
addTransaction function:
Used to add a transaction to the text file.

parameter: 
shopping

Return:
void - rewrite to the text file
*/
void Storage::addTransaction(const Shopping& shopping) 
{
    ofstream file("transactions.txt", ios::app);  // open in append mode (is this skibidi)

    //file opens
    if (file.is_open()) 
    {
        transactionCount++;
        file << "Transaction " << transactionCount << endl; 
        file << shopping.getTransactionToString();   //transaction to string that returns all transaction data
        file.close();
    }
    else {
        //file cannot open
        cout << "Error opening products.txt";
    }
}


/*
addRewards function:
Used to add rewards to a customer and rewrite the text file.

parameter: 
customer - uses logged in user in shopping()
amount - uses checkoutPrice in shopping()

Return:
void - rewrite to the text file
*/
void Storage::addRewards(string custID, double points) 
{
    ifstream file("customers.txt"); //input file
    vector<string> customerFile;    //output file

    //set up vars
    bool found = false;
    string line;
    string trimmedLine;
    int lineCounter = 0;

    //loop
    while (getline(file, line)) 
    {
        istringstream ss(line);
        ss >> trimmedLine;
        if (found) 
        {
            //target user is found
            cout << custID << " found!" << endl;
            //add customer details first
            for (int i = 0; i < 4; i++) 
            {
                customerFile.push_back(line);
                getline(file, line);
            }
            //process current rewards
            double currentPoints;
            istringstream pointStream(line);
            pointStream >> currentPoints;

            //add new points 
            currentPoints += points;
            customerFile.push_back("\t" + to_string(currentPoints));
            found = false;
        }
        else if (custID == trimmedLine) 
        {
            //set found to true and add current line
            found = true;
            customerFile.push_back(line);
        }
        else 
        {
            //copy the current line
            customerFile.push_back(line);
        }
    }


    //rewrite to customer file
    int lineCount = 0;
    customerCount = 1;
    ofstream outputFile("customers.txt");
    for (const string& outputLine : customerFile) 
    {
        outputFile << outputLine << endl;  // Write remaining lines back to the file
        lineCount++;
    }

    outputFile.close();  // Close the output file
    
}

/*
redeemRewards function:
Used to redeem rewards that a customer has.

parameter: 
customer - uses logged in user in redeeming points()

Return:
void - call to spend points function
*/
void Storage::redeemRewards(const Customer& customer)
{
    string username;
    cout << "What is your username: U_";
    cin >> username;
    username = "U_" + username;

    //try to open file
    ifstream file("customers.txt");
    if (!file.is_open()) 
    {
        return;
    }
    else 
    {
        //nothing
    }

    bool found = false;
    string line;
    string trimmedLine;
    int lineCounter = 0;
    while (getline(file, line)) 
    {
        istringstream ss(line);
        ss >> trimmedLine;

        //what to actually do with the user when they are found
        if (found) 
        {
            for(int i = 0; i < 3; i++)
            {
                getline(file,line);
            }
            rewardPoints = stod(line);
            redeemedCustomer = username;
            spendPoints();
            break;
        }
        //check if user exists
        else if (username == trimmedLine) 
        {
            found = true;
        }
        else 
        {
            //nothing
        }
    }

    if (!found) {
        cout << "User not found!" << endl;
    }
    else {
        //nothing
    }

    file.close();
    return;
}

/*
spendPoints function:
Used to select items from a menu and call functions related to them.

Return:
void - call to functions
*/
void Storage::spendPoints()
{
    cout << endl;
    printRewardMenu();

    //user menu selection
    int inp;
    while (true) 
    {
        cout << endl << "(" << redeemedCustomer << ") Select a number from the menu: ";
        cin >> inp;
        cout << endl;

        //invalid input - not an integer or (integer not in valid 1-8 range)
        if (cin.fail() || (inp < 1 || inp > 4)) 
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
                    viewItems();
                    break;
                case 2:
                    cout << "You currently have " << rewardPoints << " points to spend" << endl;
                    break;
                case 3:
                    viewItems();
                    redeemItem();
                    break;
                case 4:
                    cout << endl;
                    printMainMenu();
                    return;
            }
        }
    }

}

/*
viewItems function:
Used to view reward items.

Return:
void - print items and prices
*/
void Storage::viewItems()
{
    cout << "****************************************" << endl;
    cout << "*           Reward Items               *" << endl;
    cout << "*           ------------               *" << endl;
    cout << "*     1. Vacation: " << vacation << " Points       *"<< endl;
    cout << "*     2. Phone: " << phone << " Points           *"<< endl;
    cout << "*     3. Concert Tickets: " << tickets << " Points *"<< endl;
    cout << "*     4. Gift Card: " << giftCard << " Points        *"<< endl;
    cout << "****************************************" << endl;
}

/*
redeemItem function:
Used to spend reward points and call to change the text file.

Return:
void - successful purchase or not
*/
void Storage::redeemItem()
{
    //hash table for easy item lookup
    unordered_map<string, pair<string, int>> rewards = {
        {"1", {"a Vacation", vacation}},
        {"2", {"a Phone", phone}},
        {"3", {"Concert Tickets", tickets}},
        {"4", {"a Gift Card", giftCard}}
    };

    //item = user choice
    string item;
    cout << endl << "(" << redeemedCustomer << ") Enter item you would like to redeem: ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, item);

    //look for item in table, check if user has enough points
    if (rewards.find(item) != rewards.end()) {
        int requiredPoints = rewards[item].second;  //access the second value from the pair
        if (rewardPoints >= requiredPoints) {
            cout << "You redeemed " << rewards[item].first << "!" << endl;     //access the first value from the pair
            rewardPoints -= requiredPoints;
            changePoints();
        }
        else {
            cout << "Not enough points" << endl;
        }
    }
    else {
        cout << "Invalid item" << endl;
    }
}

/*
changePoints function:
Used to rewrite reward points to the customer file.

Return:
void - rewrite to the text file
*/
void Storage::changePoints()
{
    //open file
    ifstream file("customers.txt"); 
    if (!file.is_open()) 
    {
        cout << "Failed to open file" << std::endl;
        return;
    }
    else
    {
        //nothing
    }

    //var setup
    vector<string> lines;      
    string line;
    bool found = false;

    //loop file line by line
    while (getline(file, line)) 
    {
        istringstream iss(line);
        string trimmedLine;
        iss >> trimmedLine;
        lines.push_back(line); 

        //user found!
        if (trimmedLine == redeemedCustomer) 
        {
            found = true;

            for (int i = 0; i < 4; ++i) 
            {
                getline(file, line);
                lines.push_back(line);
            }

            lines.back() = "\t" + std::to_string(rewardPoints); 
        }
        else
        {
            //user not found
        }
    }
    file.close(); 

    if (found) 
    {
        ofstream outFile("customers.txt");
        for (const auto& outputLine : lines) {
            outFile << outputLine << endl; 
        }
        outFile.close();
    } 
    else 
    {
        std::cout << "Customer not found" << std::endl;
    }
}

/*
changeStockAmount function:
Used to grab the product ids from the cart and send them to a function.

parameter: 
 cart - The items in the customers shopping cart

Return:
void - call to function
*/
void Storage::changeStockAmount(vector<string> cart)
{
    for(int i = 0; i < cart.size(); i++)
    {
        rewriteStock(cart[i]);
    }
}

/*
rewriteStock function:
Used to rewrite the quantity of the products file based on the items that the customer bought.

parameter: 
prodID - used to find the items in the text file

Return:
void - rewrite to the text file
*/
void Storage::rewriteStock(const string& prodID)
{
    ifstream file("products.txt"); //input file
    vector<string> productsFile;    //output file

    //set up vars
    bool found = false;
    string line;
    string trimmedLine;
    int lineCounter = 0;

    //loop
    while (getline(file, line)) 
    {
        istringstream ss(line);
        ss >> trimmedLine;
        if (found) 
        {
            //add customer details first
            for (int i = 0; i < 2; i++) 
            {
                productsFile.push_back(line);
                getline(file, line);
            }
            //process current rewards
            int currentAmount;
            istringstream pointStream(line);
            pointStream >> currentAmount;

            //add new points 
            currentAmount -= 1;
            if(currentAmount == 0)
            {
                removeProduct(prodID);
                return;
            }
            else
            {
            productsFile.push_back("\t" + to_string(currentAmount));
            found = false;
            }
        }
        else if (prodID == trimmedLine) 
        {
            //set found to true and add current line
            found = true;
            productsFile.push_back(line);
        }
        else 
        {
            //copy the current line
            productsFile.push_back(line);
        }
    }


    //rewrite to customer file
    int lineCount = 0;
    customerCount = 1;
    ofstream outputFile("products.txt");
    for (const string& outputLine : productsFile) 
    {
        outputFile << outputLine << endl;  // Write remaining lines back to the file
        lineCount++;
    }

    outputFile.close();  // Close the output file
}