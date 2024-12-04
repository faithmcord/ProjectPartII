#include "Customer.h"
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <fstream>


using namespace std;

Customer::Customer() : age(0), rewardPoints(0) {
    nextID = generateUserID();
}

/*
getCustomerInput function:
used for new customer input before registration

parameter: 
none

Return:
bool - true/false depending on if registration was successful or not
*/
bool Customer::getCustomerInput() {
    string username;
    string firstName;
    string lastName;
    string creditCard;
    int age;
    int rewardPoints;

    cout << "Please enter username (minimum length 10, maximum 3 digits): U_";
    cin >> username;
    username = "U_" + username;

    if(!usernameValidation(username)) 
    {
        cout << "Invalid username" << endl;
        return false;
    }
    else 
    {
        //nothing
    }

    cout << "\nPlease enter your first name: ";
    cin >> firstName;

    cout << endl << "Please enter your last name: ";
    cin >> lastName;

    if(!nameValidation(firstName) || !(nameValidation(lastName))) 
    {
        cout << "\nInvalid Name" << endl;
        return false;
    }
    else 
    {
        //nothing
    }

    cout << "\nPlease enter your creditCard: ";
    cin >> creditCard;
    cout << endl;
    if(!cardValidation(creditCard)) 
    {
        cout << "Invalid Credit Card" << endl;
        return false;
    }
    else 
    {
        //nothing
    }

    cout << "Please enter your age: ";
    cin >> age;
    cout << endl;
    if(!ageValidation(age)) 
    {
        cout << "Invalid Age" << endl;
        return false;
    }
    else 
    {
        //nothing
    }
    cout << "Please enter reward points: ";
    cin >> rewardPoints;
    cout << endl;
    if(!rewardValidation(rewardPoints)) 
    {
        cout << "Invalid reward points" << endl;
        return false;
    }
    else 
    {
        //nothing
    }

    //call registerCustomer and return result
    //true if successful registration
    //false if registration fails
    return registerCustomer(username, firstName, lastName, age, creditCard, rewardPoints);
}

/*
registerCustomer function:
used to register new customers in the system

parameter: 
username, first name, last name, age, and credit card
data comes from getCustomerData user input

Return:
bool - true/false depending if the credentials are valid
username must satisfy the following requirements:
    - starts with "U_"
    - is minimum 10 characters long
    - no more than 3 digits
*/
bool Customer::registerCustomer(const string& username, const string& firstName, const string& lastName, int age, const string& creditCard, int rewardPoints)
{
    //set Customer
    this -> username = username;
    this -> firstName = firstName;
    this -> lastName = lastName;
    this -> age = age;
    this -> creditCard = creditCard;
    this -> rewardPoints = rewardPoints;

    this->userID = "Cust" + to_string(nextID);
    nextID++;

    //successful customer creation
    cout << "Successful Registration" << endl;
    return true;

}


/*
usernameValidation function:
Used to check if the inputed username is valid or not.

parameter: 
username - inputed from the user

Return:
bool - true/false depending if the username is valid or not
*/
bool Customer::usernameValidation(const string& username)
{
    if (username.length() < 10 || username[0] != 'U' || username[1] != '_')
    {
        return false;
    }
    else
    {
        //valid
    }

    //check integers in username
    int count = 0;
    for (int i = 0; i < username.length(); i++)
    {
        if (isdigit(username[i]))
        {
            count += 1;
        }
        else
        {
            //nothing
        }
    }
    if(count > 3)
    {
        return false;
    }
    else
    {
        //valid
    }

    //check for unique username
    ifstream file("customers.txt");
    string line;
    string trimmedLine;
    while (getline(file, line)) {
        istringstream ss(line);
        ss >> trimmedLine;
        if (username == trimmedLine) 
        {
            return false;
        }
        else {
            //valid
        }
    }
    file.close();

    return true;
}

/*
nameValidation function:
Used to check if the inputed name is valid or not.

parameter: 
name - inputed from the user

Return:
bool - true/false depending if the name is valid or not
*/
bool Customer::nameValidation(const string& name)
{
    if (name.length() > 12)
    {
        return false;
    }
    else
    {
        //valid
    }
    for (int i = 0; i < name.length(); i++)
    {
        if ((isdigit(name[i])) || !(isalpha(name[i])))
        {
            return false;
        }
        else
        {
            //valid
        }
    }
    return true;
}

/*
ageValidation function:
Used to check if the inputed age is valid or not.

parameter: 
age - inputed from the user

Return:
bool - true/false depending if the age is valid or not
*/
bool Customer::ageValidation(int age)
{
    if (age < 18 || age > 100)
    {
        return false;
    }
    else {
        //valid
    }
    string ageStr = to_string(age);
    if (ageStr[0] == '0') 
    {
        return false;
    }
    else
    {
        //valid
    }
    return true;
}

/*
cardValidation function:
Used to check if the inputed credit card is valid or not.

parameter: 
creditCard - inputed from the user

Return:
bool - true/false depending if the credit card is valid or not
*/
bool Customer::cardValidation(const string& creditCard)
{
    if (creditCard.length() != 14 || creditCard[4] != '-' || creditCard[9] != '-' || creditCard[0] == '0')
    {
        return false;
    }
    else
    {
        //valid
    }
    for (int i = 0; i < creditCard.length(); i++)
    {
        if (i == 4 || i == 9)
        {
            continue;
        }
        else
        {
            //skip
        }
        if (!isdigit(creditCard[i]))
        {
            return false;
        }
        else
        {
            //valid
        }
    }
    return true;
}

/*
rewardValidation function:
Used to check if the inputed reward points are valid or not.

parameter: 
rewardPoints - inputed from the user

Return:
bool - true/false depending if the reward points are valid or not
*/
bool Customer::rewardValidation(int rewardPoints)
{
    return rewardPoints > 0;
}

/*
generateUserID function:
Used to generate a customerID for a user.
*/
int Customer::generateUserID()
{
    nextID = 1000000000;
    ifstream file("customers.txt");
    string line;
    string lastID;

    while (getline(file, line)) {
        if (line.find("Cust") == 1) 
        {
            lastID = line;
        }
        else {
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
    else {
        //no lastID, nextID defaults to 10000
    }
    return nextID;
    
}

/*
getUserID function:
Used to return userID.

Return:
string - userID
*/
string Customer::getUserID() const
{
    return userID;
}

/*
getUsername function:
Used to return username.

Return:
string - username
*/
string Customer::getUsername() const
{
    return username;
}

/*
getFirstName function:
Used to return first name of the user.

Return:
string - first name
*/
string Customer::getFirstName() const
{
    return firstName;
}

/*
getLastName function:
Used to return last name of the user.

Return:
string - last name
*/
string Customer::getLastName() const
{
    return lastName;
}

/*
getAge function:
Used to return the age of the user.

Return:
int - age
*/
int Customer::getAge()
{
    return age;
}

/*
getCreditCard function:
Used to return the credit card of the user.

Return:
string - credit card
*/
string Customer::getCreditCard() const
{
    return creditCard;
}

/*
getRewardPoints function:
Used to return the reward points for the user.

Return:
int - reward points
*/
int Customer::getRewardPoints()
{
    return rewardPoints;
}

/*
getCustomerToString function:
Used to return all of the customers details.

Return:
string - customer details
*/
string Customer::getCustomerToString() const
{
    ostringstream customerPrint;

    customerPrint << "\t" << userID << endl;
    customerPrint << "\t" << username << endl;
    customerPrint << "\t" << firstName << endl;
    customerPrint << "\t" << lastName << endl;
    customerPrint << "\t" << getCustomerBirthYear() << endl;
    customerPrint << "\t" << rewardPoints << endl;

    return customerPrint.str();
}

/*
getCustomerBirthYear function:
Used to calculate the users birth year based on their age.

Return:
string - birth year
*/
string Customer::getCustomerBirthYear() const
{
    // Get the current time
    time_t now = time(0);
    tm* localTime = localtime(&now);

    // Get the current year
    int currentYear = 1900 + localTime->tm_year;

    // Calculate the birth year
    int birthYear = currentYear - age;

    return to_string(birthYear);
}