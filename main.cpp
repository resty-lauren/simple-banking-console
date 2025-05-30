#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

class BankAccount
{
private:
    std::string customerName, customerAddress;
    char accountCategory;
    double currentBalance;
    std::string accountNumber;

public:
    void createAccount();
    void addFunds();
    void withdrawFunds();
    void showAccountInfo();
    void generateAccountNumber();
};

void BankAccount::generateAccountNumber()
{
    accountNumber = "BA" + std::to_string(rand() % 100000 + 10000);
}

void BankAccount::createAccount()
{
    std::cin.ignore();
    std::cout << "Enter customer name: ";
    getline(std::cin, customerName);

    std::cout << "Enter customer address: ";
    getline(std::cin, customerAddress);

    std::cout << "\nAccount Types Available:\n";
    std::cout << "[S] - Savings Account (3% Interest)\n";
    std::cout << "[C] - Current Account (No Interest)\n";
    std::cout << "Select account type: ";
    std::cin >> accountCategory;

    if (accountCategory >= 'a' && accountCategory <= 'z')
        accountCategory = accountCategory - 'a' + 'A';

    if (accountCategory != 'S' && accountCategory != 'C')
    {
        std::cout << "Invalid selection! Setting to Savings Account by default.\n";
        accountCategory = 'S';
    }

    std::cout << "Account type selected: "
              << (accountCategory == 'S' ? "Savings" : "Current") << std::endl;

    std::cout << "Enter initial deposit amount: ";
    std::cin >> currentBalance;

    while (currentBalance < 0)
    {
        std::cout << "Initial deposit must be positive. Enter again: ";
        std::cin >> currentBalance;
    }

    generateAccountNumber();

    std::cout << "\n*** ACCOUNT CREATED SUCCESSFULLY ***\n";
    std::cout << "Welcome to Bank, " << customerName << "!\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Initial Balance: " << std::fixed << std::setprecision(2) << currentBalance << std::endl;
}

void BankAccount::addFunds()
{
    double depositAmount;

    std::cout << "\n--- DEPOSIT TRANSACTION ---\n";
    std::cout << "Account: " << accountNumber << "\n";
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << currentBalance << "\n";
    std::cout << "Enter deposit amount: ";
    std::cin >> depositAmount;

    if (depositAmount <= 0)
    {
        std::cout << "Invalid amount! Deposit must be positive.\n";
        return;
    }

    currentBalance += depositAmount;

    std::cout << "\n*** DEPOSIT COMPLETED ***\n";
    std::cout << "Amount Deposited: " << std::fixed << std::setprecision(2) << depositAmount << "\n";
    std::cout << "Updated Balance: " << std::fixed << std::setprecision(2) << currentBalance << std::endl;
}

void BankAccount::showAccountInfo()
{
    std::cout << "\n========== ACCOUNT SUMMARY ==========\n";
    std::cout << "Account Number: " << accountNumber << "\n";
    std::cout << "Customer Name: " << customerName << "\n";
    std::cout << "Address: " << customerAddress << "\n";
    std::cout << "Account Type: " << (accountCategory == 'S' ? "Savings Account" : "Current Account") << "\n";
    std::cout << "Current Balance: " << std::fixed << std::setprecision(2) << currentBalance << "\n";
    std::cout << "===================================\n";
}

void BankAccount::withdrawFunds()
{
    double withdrawAmount;

    std::cout << "\n--- WITHDRAWAL TRANSACTION ---\n";
    std::cout << "Account: " << accountNumber << "\n";
    std::cout << "Available Balance: " << std::fixed << std::setprecision(2) << currentBalance << "\n";
    std::cout << "Enter withdrawal amount: ";
    std::cin >> withdrawAmount;

    if (withdrawAmount <= 0)
    {
        std::cout << "Invalid amount! Withdrawal must be positive.\n";
        return;
    }

    if (withdrawAmount > currentBalance)
    {
        std::cout << "Transaction Failed: Insufficient Balance!\n";
        std::cout << "Available: " << std::fixed << std::setprecision(2) << currentBalance << std::endl;
        return;
    }

    currentBalance -= withdrawAmount;

    std::cout << "\n*** WITHDRAWAL COMPLETED ***\n";
    std::cout << "Amount Withdrawn: " << std::fixed << std::setprecision(2) << withdrawAmount << "\n";
    std::cout << "Remaining Balance: " << std::fixed << std::setprecision(2) << currentBalance << std::endl;
}

void showMainMenu()
{
    std::cout << "\n==========================================\n";
    std::cout << "      SIMPLE BANKING CONSOLE SYSTEM\n";
    std::cout << "==========================================\n";
    std::cout << "[1] Create New Account\n";
    std::cout << "[2] Make Deposit\n";
    std::cout << "[3] Make Withdrawal\n";
    std::cout << "[4] View Account Details\n";
    std::cout << "[5] Exit System\n";
    std::cout << "==========================================\n";
    std::cout << "Choose an option (1-5): ";
}

int main()
{
    BankAccount userAccount;
    int userChoice;
    bool hasActiveAccount = false;

    std::cout << "******************************************\n";
    std::cout << "   WELCOME TO SIMPLE BANKING CONSOLE!\n";
    std::cout << "******************************************\n";

    while (true)
    {
        showMainMenu();
        std::cin >> userChoice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: Please enter a valid number!\n";
            continue;
        }

        switch (userChoice)
        {
        case 1:
            userAccount.createAccount();
            hasActiveAccount = true;
            break;

        case 2:
            if (!hasActiveAccount)
            {
                std::cout << "No account found! Please create an account first.\n";
            }
            else
            {
                userAccount.addFunds();
            }
            break;

        case 3:
            if (!hasActiveAccount)
            {
                std::cout << "No account found! Please create an account first.\n";
            }
            else
            {
                userAccount.withdrawFunds();
            }
            break;

        case 4:
            if (!hasActiveAccount)
            {
                std::cout << "No account found! Please create an account first.\n";
            }
            else
            {
                userAccount.showAccountInfo();
            }
            break;

        case 5:
            std::cout << "\nThank you for choosing Simple Banking Console!\n";
            std::cout << "Have a great day!\n";
            return 0;

        default:
            std::cout << "Invalid option! Please select 1-5.\n";
            break;
        }
    }

    return 0;
}