#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

using namespace std;

class Customer 
{
    public:
    
        //constructor
        Customer();
        
        //get data for customer
        bool getCustomerInput();

        //register a customer
        bool registerCustomer(const string& username, const string& firstName, const string& lastName, int age, const string& creditCard, int rewardPoints);

        //getters
        string getUserID() const;
        string getUsername() const;
        string getFirstName() const;
        string getLastName() const;
        int getAge();
        string getCreditCard() const;
        int getRewardPoints();
        string getCustomerToString() const;
        string getCustomerBirthYear() const;


    private:
        int nextID;
        string username;
        string firstName;
        string lastName;
        int age;
        string creditCard;
        string userID;
        int rewardPoints;

        //methods
        bool usernameValidation(const string& username);
        bool nameValidation(const string& name);
        bool ageValidation(int age);
        bool cardValidation(const string& creditCard);
        int generateUserID();
        bool rewardValidation(int rewardPoints);
};



#endif // CUSTOMER_H