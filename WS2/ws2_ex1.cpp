#include <iostream>

class BankAccount {
    private :
        double balance;
        
    
    public :
        double getBalance() const {
            return balance;
        }

        bool deposit(double amount) {
            if(amount<= 0.0){
                return false;
            }
            balance += amount;
            return true;
        }

        bool withdraw(double amount) {
            if(amount <= 0.0){
                return false;
            }
            if(amount > balance) {
                return false;
            }
            balance -= amount;
            return true;
        }

        BankAccount(double balance) : balance(balance) {}

};

class Transaction {
private:
    BankAccount* from;
    BankAccount* to;
    double amount;

public:
    Transaction(BankAccount* from, BankAccount* to, double amount)
        : from(from), to(to), amount(amount) {}

    bool execute() {
        if(!from->withdraw(amount)) {
            return false;
        }

        if(!to->deposit(amount)) {
            from->deposit(amount);
            return false;
        }
        return true;
    }
};

int main() {
    BankAccount* account1 = new BankAccount(1000.0);
    BankAccount* account2 = new BankAccount(500.0);

    Transaction* transaction = new Transaction(account1, account2, 500.0);
    bool res = transaction->execute();

    if (res) {
        std::cout << "Transaction successful" << std::endl;
    } else {
        std::cout << "Transaction failed" << std::endl;
    }

    std::cout << account1->getBalance() << std::endl;
    std::cout << account2->getBalance() << std::endl;

    delete account1;
    delete account2;
    delete transaction;

    account1 = new BankAccount(1000.0);
    account2 = new BankAccount(500.0);
    transaction = new Transaction(account1, account2, 5000.0);

    res = transaction->execute();
    if (res) {
        std::cout << "Transaction successful" << std::endl;
    } else {
        std::cout << "Transaction failed" << std::endl;
    }

    std::cout << account1->getBalance() << std::endl;
    std::cout << account2->getBalance() << std::endl;

    return 0;
}
