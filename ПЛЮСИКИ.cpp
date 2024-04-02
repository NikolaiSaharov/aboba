#include <iostream>
#include <string>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;
    double calculateInterest() {
        return balance * (interestRate / 100) / 12;
    }

public:
    BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance), interestRate(0) {}

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Проценты после пополнения на счете " << accountNumber << ": " << calculateInterest() << endl;
        }
    }

    bool withdraw(double amount) {
        if (amount > 0 && balance >= amount) {
            balance -= amount;
            cout << "Проценты после снятия средств с счета " << accountNumber << ": " << calculateInterest() << endl;
            return true;
        }
        return false;
    }

    double getBalance() {
        return balance;
    }

    double getInterest() {
        return calculateInterest();
    }

    void setInterestRate(double interestRate) {
        this->interestRate = interestRate;
    }

    int getAccountNumber() {
        return accountNumber;
    }

    friend bool transfer(BankAccount& from, BankAccount& to, double amount);
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (from.withdraw(amount)) {
        to.deposit(amount);
        cout << "Проценты после перевода со счета " << from.getAccountNumber() << " на счет " << to.getAccountNumber() << ": " << endl;
        cout << "Проценты на счете " << from.getAccountNumber() << ": " << from.getInterest() << endl;
        cout << "Проценты на счете " << to.getAccountNumber() << ": " << to.getInterest() << endl;
        return true;
    }
    return false;
}

int main() {
    BankAccount account1(123456, 1000);
    BankAccount account2(654321, 500);

    account1.setInterestRate(5); 
    account2.setInterestRate(3);

    int choice;
    double amount;

    while (true) {
        cout << "Выберите действие:" << endl;
        cout << "1. Пополнить счет" << endl;
        cout << "2. Снять средства" << endl;
        cout << "3. Перевести средства" << endl;
        cout << "4. Выйти" << endl;

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Введите сумму для пополнения счета: ";
                cin >> amount;
                account1.deposit(amount);
                break;
            case 2:
                cout << "Введите сумму для снятия средств: ";
                cin >> amount;
                if (account1.withdraw(amount)) {
                    cout << "Средства успешно сняты" << endl;
                } else {
                    cout << "Недостаточно средств на счете" << endl;
                }
                break;
            case 3:
                cout << "Введите сумму для перевода: ";
                cin >> amount;
                if (transfer(account1, account2, amount)) {
                    cout << "Перевод успешно выполнен" << endl;
                } else {
                    cout << "Перевод невозможен" << endl;
                }
                break;
            case 4:
                return 0;
            default:
                cout << "Неверный выбор" << endl;
        }

        cout << "Баланс счета 1: " << account1.getBalance() << endl;
        cout << "Баланс счета 2: " << account2.getBalance() << endl;
    }

    return 0;
}