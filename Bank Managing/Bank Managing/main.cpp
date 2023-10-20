#include <iostream>
#include <string>
#include <vector>

class Account {
protected:
    std::string accountNumber;
    double balance;

public:
    Account(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    virtual void deposit(double amount) {
        balance += amount;
        std::cout << "Deposit of $" << amount << " successful. New balance: $" << balance << std::endl;
    }

    virtual void withdraw(double amount) {
        if (amount <= balance) {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful. New balance: $" << balance << std::endl;
        }
        else {
            std::cout << "Insufficient funds. Withdrawal unsuccessful." << std::endl;
        }
    }

    virtual void displayBalance() {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Current Balance: $" << balance << std::endl;
    }
};

class SavingsAccount : public Account {
private:
    double interestRate;

public:
    SavingsAccount(const std::string& accNum, double initialBalance, double interest)
        : Account(accNum, initialBalance), interestRate(interest) {}

    void applyInterest() {
        double interestAmount = balance * interestRate;
        deposit(interestAmount);
        std::cout << "Interest applied. New balance: $" << balance << std::endl;
    }

    void displayBalance() override {
        std::cout << "Savings Account Number: " << accountNumber << std::endl;
        std::cout << "Current Balance: $" << balance << std::endl;
    }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;

public:
    CheckingAccount(const std::string& accNum, double initialBalance, double limit)
        : Account(accNum, initialBalance), overdraftLimit(limit) {}

    void withdraw(double amount) override {
        if (amount <= (balance + overdraftLimit)) {
            balance -= amount;
            std::cout << "Withdrawal of $" << amount << " successful. New balance: $" << balance << std::endl;
        }
        else {
            std::cout << "Exceeded overdraft limit. Withdrawal unsuccessful." << std::endl;
        }
    }

    void displayBalance() override {
        std::cout << "Checking Account Number: " << accountNumber << std::endl;
        std::cout << "Current Balance: $" << balance << std::endl;
    }
};

int main() {
    // Create a savings account and a checking account
    SavingsAccount savingsAccount("123456789", 1000.0, 0.05);
    CheckingAccount checkingAccount("987654321", 500.0, 200.0);

    // Perform transactions on the accounts
    savingsAccount.displayBalance();
    savingsAccount.deposit(500.0);
    savingsAccount.applyInterest();
    savingsAccount.withdraw(200.0);
    savingsAccount.displayBalance();

    checkingAccount.displayBalance();
    checkingAccount.deposit(1000.0);
    checkingAccount.withdraw(800.0);
    checkingAccount.displayBalance();

    return 0;
}