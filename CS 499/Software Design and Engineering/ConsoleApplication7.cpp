#include <iostream>
#include <string>
using namespace std;
// found strings by using command strings Project1.o in codio shell
// mov 0x0(%rip),%eax made me think global variable access
//Software Engineering and Design

string name1 = "Bob Jones";
string name2 = "Sarah Davis";
string name3 = "Amy Friendly";
string name4 = "Johnny Smith";
string name5 = "Carol Spears";
int var1 = 1;  // dont really know these values from the dissasembly 
int var2 = 1;  // 
int var3 = 1;  // 
int var4 = 1;  // 
int var5 = 1;  // 
int client_num;
int new_option;
string password = "123"; // guessing this was some hard coded password
int login_status;

int CheckUserPermissionAccess() {
    string inputname;
    string inputpass;

    cout << "Enter your username: " << endl;
    cin >> inputname;
    cout << "Enter your password: " << endl;
    cin >> inputpass;
    //thinking this is what "123" password is used for
    if (inputpass == password) {
        return 1;
    }
    else {
        return 2;
    }
}
void DisplayInfo() {
    cout << "Client's Name Service Selected (1 = Brokerage, 2 = Retirement)" << endl;
    cout << "1. " << name1 << " selected option " << var1 << endl;
    cout << "2. " << name2 << " selected option " << var2 << endl;
    cout << "3. " << name3 << " selected option " << var3 << endl;
    cout << "4. " << name4 << " selected option " << var4 << endl;
    cout << "5. " << name5 << " selected option " << var5 << endl;
}
void ChangeCustomerChoice() {
    cout << "Enter the number of the client that you wish to change" << endl;
    cin >> client_num;
    cout << "Please enter the client's new service choice (1 = Brokerage, 2 = Retirement)" << endl;
    cin >> new_option;

    // had to figure out all these compares
    if (client_num == 1) {
        var1 = new_option;
    }
    if (client_num == 2) {
        var2 = new_option;
    }
    if (client_num == 3)
    {
        var3 = new_option;
    }
    if (client_num == 4)
    {
        var4 = new_option;
    }
    if (client_num == 5) {
        var5 = new_option;
    }
}
int main() {
    //Prompt Instruction 4 
    //For example, you could add a "Created by (name)" statement for when the program opens, or a statement of your choice.
    cout << "Created by Neema" << endl;

    cout << "Hello! Welcome to our Investment Company" << endl;
    login_status = CheckUserPermissionAccess();

    // login loop
    while (login_status != 1) {
        cout << "Invalid Password. Please try again" << endl;
        login_status = CheckUserPermissionAccess();
    }

    //menu driver
    int choice = 0;
    while (choice != 3) {
        cout << "What would you like to do?" << endl;
        cout << "DISPLAY the client list (enter 1)" << endl;
        cout << "CHANGE a client's choice (enter 2)" << endl;
        cout << "Exit the program.. (enter 3)" << endl;
        cin >> choice;

        if (choice == 1) {
            DisplayInfo();
        }
        else if (choice == 2) {
            ChangeCustomerChoice();
        }

    }

    return 0;
}