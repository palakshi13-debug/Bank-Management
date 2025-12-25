#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
public:
    int accNo;
    string name;
    double balance;

    void create() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
    }

    void display() {
        cout << "\nAccount Number: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: ₹" << balance << endl;
    }
};

void createAccount() {
    BankAccount acc;
    ofstream file("accounts.txt", ios::app);
    acc.create();
    file << acc.accNo << endl
         << acc.name << endl
         << acc.balance << endl;
    file.close();
    cout << "\n Account Created Successfully!\n";
}

void showAccount(int num) {
    BankAccount acc;
    ifstream file("accounts.txt");
    bool found = false;

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        if (acc.accNo == num) {
            acc.display();
            found = true;
            break;
        }
    }
    file.close();

    if (!found)
        cout << "\n Account not found!\n";
}

void depositWithdraw(int num, bool isDeposit) {
    BankAccount acc;
    ifstream file("accounts.txt");
    ofstream temp("temp.txt");
    bool found = false;
    double amount;

    while (file >> acc.accNo) {
        file.ignore();
        getline(file, acc.name);
        file >> acc.balance;

        if (acc.accNo == num) {
            cout << "Enter Amount: ";
            cin >> amount;

            if (!isDeposit && amount > acc.balance) {
                cout << " Insufficient Balance!\n";
            } else {
                acc.balance += (isDeposit ? amount : -amount);
                cout << " Transaction Successful!\n";
            }
            found = true;
        }

        temp << acc.accNo << endl
             << acc.name << endl
             << acc.balance << endl;
    }

    file.close();
    temp.close();
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "\n Account not found!\n";
}

int main() {
    int choice, accNo;

    do {
        cout << "\n===== BANK ACCOUNT MANAGEMENT SYSTEM =====";
        cout << "\n1. Create Account";
        cout << "\n2. Display Account";
        cout << "\n3. Deposit Money";
        cout << "\n4. Withdraw Money";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createAccount();
            break;
        case 2:
            cout << "Enter Account Number: ";
            cin >> accNo;
            showAccount(accNo);
            break;
        case 3:
            cout << "Enter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, true);
            break;
        case 4:
            cout << "Enter Account Number: ";
            cin >> accNo;
            depositWithdraw(accNo, false);
            break;
        case 5:
            cout << "Thank you for using the system!\n";
            break;
        default:
            cout << " Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
