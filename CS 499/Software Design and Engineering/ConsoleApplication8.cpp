// ConsoleApplication8.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;


class InvestmentCompany {
private:
    //constructor for singleton
    InvestmentCompany() {
        //original data from reverse engineered project
        clients[0] = { "Bob Jones", 1 };
        clients[1] = { "Sarah Davis", 1 };
        clients[2] = { "Amy Friendly", 1 };
        clients[3] = { "Johnny Smith", 1 };
        clients[4] = { "Carol Spears", 1 };

        password = "123";
    }

 
    // Static instance pointer
    static InvestmentCompany* instance;


    struct Client {
        string name;
        int serviceOption; 
        // 1 = Brokerage, 2 = Retirement
    };

    //data
    Client clients[5];
    string password;

public:
    // get singleton instance
    static InvestmentCompany* getInstance() {
        if (instance == nullptr) {
            instance = new InvestmentCompany();
        }
        return instance;
    }

    // Check user login
    int checkUserPermissionAccess() {
        string inputname;
        string inputpass;

        cout << "Enter your username: " << endl;
        cin >> inputname;
        cout << "Enter your password: " << endl;
        cin >> inputpass;

        if (inputpass == password) {
            return 1;
        }
        else {
            return 2;
        }
    }

    // Display client information
    void displayInfo() {
        cout << "Client's Name Service Selected (1 = Brokerage, 2 = Retirement)" << endl;
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << clients[i].name
                << " selected option " << clients[i].serviceOption << endl;
        }
    }

    // Change customer choice
    void changeCustomerChoice() {
        int clientNum;
        int newOption;

        cout << "Enter the number of the client that you wish to change" << endl;
        cin >> clientNum;

        if (clientNum < 1 || clientNum > 5) {
            cout << "Invalid client number" << endl;
            return;
        }

        cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << endl;
        cin >> newOption;

        if (newOption == 1 || newOption == 2) {
            clients[clientNum - 1].serviceOption = newOption;
        }
        else {
            cout << "Invalid option" << endl;
        }
    }

 
    void run() {
        cout << "Created by Neema" << endl;
        cout << "Hello! Welcome to our Investment Company" << endl;

        // Login loop
        int loginStatus = checkUserPermissionAccess();
        while (loginStatus != 1) {
            cout << "Invalid Password. Please try again" << endl;
            loginStatus = checkUserPermissionAccess();
        }

        // Menu driver
        int choice = 0;
        while (choice != 3) {
            cout << "What would you like to do?" << endl;
            cout << "DISPLAY the client list (enter 1)" << endl;
            cout << "CHANGE a client's choice (enter 2)" << endl;
            cout << "Exit the program.. (enter 3)" << endl;
            cin >> choice;

            if (choice == 1) {
                displayInfo();
            }
            else if (choice == 2) {
                changeCustomerChoice();
            }
        }

        cout << "Thank you for using our Investment Company system!" << endl;
    }
};

//this is our singleton instance which we will set to null which when getInstance is called will create the single instance
InvestmentCompany* InvestmentCompany::instance = nullptr;

int main() {
    // Get singleton instance and run application
    InvestmentCompany* company = InvestmentCompany::getInstance();
    company->run();

    // Clean up singleton instance
    delete company;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
