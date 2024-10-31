#include<iostream>
using namespace std;

enum BAStatus
{
	active = 2,
	suspended
};

class BankAccount {
private:
	double balance;
	BAStatus status;
public:
	BankAccount()
	{
		cout << "Default constructor called" << endl;
		balance = 1;
		status = BAStatus::active;
	}
	BankAccount(double balance, BAStatus status)
	{
		setStatus(status);
		setBalance(balance);
		cout << "Constructor cu parametri apelat: " << endl;
	}

	BankAccount(const BankAccount& account) {
		cout << "Constructor de copiere este apelat" << endl;

		this->balance = account.balance;
		this->status = account.status;
	}


	BankAccount(BAStatus status)
	{
		setBalance(balance);
		cout << "Constructor cu parametri apelat: " << endl;
	}

	double getBalance() {
		return this->balance;
	}

	BAStatus getStatus() {
		return this->status;

	}

	void setBalance(double balance) {
		if (balance < 0) {
			this->balance = 0;
			this->status = BAStatus::suspended;
		}
		else {
			this->balance = balance;
		}
	}

	void setStatus(BAStatus _status) {
		this->status = _status;
	}

	void printBankAccount() // this = bankAccount* 
	{
		cout << "statusul este: " << this->status << endl; // this->status = (*this).status
		cout << "soldul este: " << this->balance << endl;
	}
};

void printBalance(BankAccount bankAccount) 
{
	cout << bankAccount.getBalance() << endl;
}

int main()
{
	BankAccount account;
	account.printBankAccount();
	account.setBalance(10);
	account.setStatus(BAStatus::suspended);
	BankAccount secondAccount;
	secondAccount.setBalance(20);
	secondAccount.setStatus(BAStatus::active);
	account.printBankAccount();
	secondAccount.printBankAccount();
	BankAccount thirdAccount(-10, BAStatus::active);
	thirdAccount.printBankAccount();

	BankAccount forthAccount = thirdAccount; // constructorul de copiere va fi apelat
	printBalance(thirdAccount); // constructorul de copiere al clasei BankAccount va fi apelat deoarece printBalance primeste parametrul prin valoare,
								// ceea ce determina ca o copie a obiectului thirdAccount sa fie creata in stack-ul functiei printBalance
}