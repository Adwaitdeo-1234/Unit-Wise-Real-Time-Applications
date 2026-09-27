#include <iostream>
#include <vector>
#include <string>
using namespace std;

// ================= BASE CLASS =================
class Account
{
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    // Constructor
    Account(int accNo, string name, double bal)
    {
        accountNumber = accNo;
        holderName = name;
        balance = bal;
    }

    // Deposit money
    virtual void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Amount deposited successfully.\n";
        }
        else
        {
            cout << "Invalid amount!\n";
        }
    }

    // Withdrawal
    virtual void withdraw(double amount)
    {
        if (amount > 0 && amount <= balance)
        {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        }
        else
        {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    // Virtual interest calculation
    virtual void calculateInterest()
    {
        cout << "Interest calculation depends on account type.\n";
    }

    // Display account details
    virtual void display()
    {
        cout << "\nAccount Number : " << accountNumber;
        cout << "\nHolder Name    : " << holderName;
        cout << "\nBalance        : Rs. " << balance << endl;
    }

    int getAccountNumber()
    {
        return accountNumber;
    }

    virtual ~Account() {}
};


// ================= SAVINGS ACCOUNT =================
class SavingsAccount : public Account
{
private:
    float interestRate;

public:
    SavingsAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal)
    {
        interestRate = 4.0;
    }

    void calculateInterest() override
    {
        double interest = balance * interestRate / 100;

        cout << "Interest Rate : " << interestRate << "%";
        cout << "\nInterest       : Rs. " << interest << endl;
    }

    void display() override
    {
        cout << "\n===== SAVINGS ACCOUNT =====";
        Account::display();
        cout << "Interest Rate  : " << interestRate << "%" << endl;
    }
};


// ================= CURRENT ACCOUNT =================
class CurrentAccount : public Account
{
private:
    double minimumBalance;

public:
    CurrentAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal)
    {
        minimumBalance = 5000;
    }

    void withdraw(double amount) override
    {
        if (amount > 0 && balance - amount >= minimumBalance)
        {
            balance -= amount;
            cout << "Amount withdrawn successfully.\n";
        }
        else
        {
            cout << "Withdrawal denied!";
            cout << "\nMinimum balance of Rs. " << minimumBalance
                 << " must be maintained.\n";
        }
    }

    void calculateInterest() override
    {
        cout << "Current Account does not provide interest.\n";
    }

    void display() override
    {
        cout << "\n===== CURRENT ACCOUNT =====";
        Account::display();
        cout << "Minimum Balance: Rs. " << minimumBalance << endl;
    }
};


// ================= FIXED DEPOSIT ACCOUNT =================
class FixedDepositAccount : public Account
{
private:
    float interestRate;
    int duration;

public:
    FixedDepositAccount(int accNo, string name, double bal)
        : Account(accNo, name, bal)
    {
        interestRate = 7.0;
        duration = 2;
    }

    void withdraw(double amount) override
    {
        cout << "Withdrawal is not allowed before the FD maturity period.\n";
    }

    void calculateInterest() override
    {
        double interest = balance * interestRate * duration / 100;

        cout << "Interest Rate : " << interestRate << "%";
        cout << "\nDuration       : " << duration << " years";
        cout << "\nInterest       : Rs. " << interest << endl;
    }

    void display() override
    {
        cout << "\n===== FIXED DEPOSIT ACCOUNT =====";
        Account::display();
        cout << "Interest Rate  : " << interestRate << "%";
        cout << "\nDuration       : " << duration << " years\n";
    }
};


// ================= MAIN FUNCTION =================
int main()
{
    vector<Account*> accounts;

    // Creating accounts
    SavingsAccount savings(101, "Adwait", 50000);
    CurrentAccount current(102, "Rahul", 30000);
    FixedDepositAccount fd(103, "Amit", 100000);

    // Storing different account types in base-class vector
    accounts.push_back(&savings);
    accounts.push_back(&current);
    accounts.push_back(&fd);

    int choice;
    int accountNumber;
    double amount;

    do
    {
        cout << "\n\n====================================";
        cout << "\n       BANKING MANAGEMENT SYSTEM";
        cout << "\n====================================";
        cout << "\n1. Display All Accounts";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Calculate Interest";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:

            for (Account* acc : accounts)
            {
                acc->display();
            }

            break;


        case 2:

            cout << "Enter Account Number: ";
            cin >> accountNumber;

            cout << "Enter Amount to Deposit: ";
            cin >> amount;

            for (Account* acc : accounts)
            {
                if (acc->getAccountNumber() == accountNumber)
                {
                    acc->deposit(amount);
                    break;
                }
            }

            break;


        case 3:

            cout << "Enter Account Number: ";
            cin >> accountNumber;

            cout << "Enter Amount to Withdraw: ";
            cin >> amount;

            for (Account* acc : accounts)
            {
                if (acc->getAccountNumber() == accountNumber)
                {
                    acc->withdraw(amount);
                    break;
                }
            }

            break;


        case 4:

            cout << "Enter Account Number: ";
            cin >> accountNumber;

            for (Account* acc : accounts)
            {
                if (acc->getAccountNumber() == accountNumber)
                {
                    acc->calculateInterest();
                    break;
                }
            }

            break;


        case 5:

            cout << "\nThank you for using the Banking System!\n";
            break;


        default:

            cout << "\nInvalid choice!";
        }

    } while (choice != 5);

    return 0;
}