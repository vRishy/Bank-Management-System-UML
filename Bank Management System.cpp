#include <iostream>
#include <vector>

class Account {
private:
    int accountNumber;
    std::string accountHolderName;
    double balance;

public:
    Account(int accNum, const std::string& name, double initialBalance)
        : accountNumber(accNum), accountHolderName(name), balance(initialBalance) {}

    int getAccountNumber() const {
        return accountNumber;
    }

    std::string getAccountHolderName() const {
        return accountHolderName;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        } else {
            std::cout << "Insufficient balance!" << std::endl;
            return false;
        }
    }
};

class Bank {
private:
    std::vector<Account*> accounts;

public:
    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void removeAccount(Account* account) {
        // Find and remove the account from the vector
        for (auto it = accounts.begin(); it != accounts.end(); ++it) {
            if (*it == account) {
                accounts.erase(it);
                break;
            }
        }
    }

    Account* findAccount(int accountNumber) const {
        // Find the account with the given account number
        for (auto account : accounts) {
            if (account->getAccountNumber() == accountNumber) {
                return account;
            }
        }
        return nullptr;  // Account not found
    }
};

int main() {
    Bank bank;

    int choice;
    do {
        std::cout << "Bank Management System" << std::endl;
        std::cout << "1. Add Account" << std::endl;
        std::cout << "2. Deposit" << std::endl;
        std::cout << "3. Withdraw" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int accNum;
                std::string name;
                double initialBalance;

                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Account Holder Name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter Initial Balance: ";
                std::cin >> initialBalance;

                Account* account = new Account(accNum, name, initialBalance);
                bank.addAccount(account);
                std::cout << "Account added successfully!" << std::endl;
                break;
            }
            case 2: {
                int accNum;
                double amount;

                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Deposit Amount: ";
                std::cin >> amount;

                Account* account = bank.findAccount(accNum);
                if (account) {
                    account->deposit(amount);
                    std::cout << "Deposit successful!" << std::endl;
                    std::cout << "Updated Balance: " << account->getBalance() << std::endl;
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 3: {
                int accNum;
                double amount;

                std::cout << "Enter Account Number: ";
                std::cin >> accNum;
                std::cout << "Enter Withdraw Amount: ";
                std::cin >> amount;

                Account* account = bank.findAccount(accNum);
                if (account) {
                    if (account->withdraw(amount)) {
                        std::cout << "Withdrawal successful!" << std::endl;
                        std::cout << "Updated Balance: " << account->getBalance() << std::endl;
                    }
                } else {
                    std::cout << "Account not found!" << std::endl;
                }
                break;
            }
            case 4:
                std::cout << "Exiting the program. Thank you!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (choice != 4);

    // Clean up
    for (auto account : bank.accounts) {
        delete account;
    }

    return 0;
}

