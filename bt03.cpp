#include <iostream>
#include <string>
#include <vector>

class Account {
protected:
    std::string accountNumber;
    std::string ownerName;
    double balance;
public:
    Account(std::string number, std::string name, double initialBalance)
        : accountNumber(number), ownerName(name), balance(initialBalance) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "da nap " << amount << " vao tai khoan.\n";
        } else {
            std::cout << "so tien khong hop le.\n";
        }
    }

    virtual bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            std::cout << "da rut " << amount << " tu tai khoan.\n";
            return true;
        } else {
            std::cout << "khong the rut tien. so du khong du hoac so tien khong hop le.\n";
            return false;
        }
    }

    virtual void displayInfo() const {
        std::cout << "so tai khoan: " << accountNumber << "\nchu tai khoan: " << ownerName 
                  << "\nso du: " << balance << "\n";
    }

    virtual ~Account() {}
};

class SavingsAccount : public Account {
private:
    double interestRate;
public:
    SavingsAccount(std::string number, std::string name, double initialBalance, double rate)
        : Account(number, name, initialBalance), interestRate(rate) {}

    void applyInterest() {
        double interest = balance * interestRate;
        deposit(interest);
        std::cout << "da cong lai: " << interest << "\n";
    }

    void displayInfo() const override {
        Account::displayInfo();
        std::cout << "lai suat: " << (interestRate * 100) << "%\n";
    }
};

class CheckingAccount : public Account {
private:
    double overdraftLimit;
public:
    CheckingAccount(std::string number, std::string name, double initialBalance, double limit)
        : Account(number, name, initialBalance), overdraftLimit(limit) {}

    bool withdraw(double amount) override {
        if (amount > 0 && (balance + overdraftLimit) >= amount) {
            balance -= amount;
            std::cout << "da rut " << amount << " tu tai khoan.\n";
            return true;
        } else {
            std::cout << "vuot qua gioi han thau chi hoac so tien khong hop le.\n";
            return false;
        }
    }

    void displayInfo() const override {
        Account::displayInfo();
        std::cout << "gioi han thau chi: " << overdraftLimit << "\n";
    }
};

class Bank {
private:
    std::vector<Account*> accounts;
public:
    void addAccount(Account* account) {
        accounts.push_back(account);
    }

    void displayAllAccounts() const {
        for (const auto& account : accounts) {
            account->displayInfo();
            std::cout << "------------------------\n";
        }
    }

    ~Bank() {
        for (auto account : accounts) {
            delete account;
        }
    }
};

int main() {
    Bank myBank;
    myBank.addAccount(new SavingsAccount("SA001", "Nguyen Van A", 1000000, 0.05));
    myBank.addAccount(new CheckingAccount("CA001", "Tran Thi B", 2000000, 500000));

    std::cout << "thong tin tat ca tai khoan:\n";
    myBank.displayAllAccounts();

    return 0;
}
