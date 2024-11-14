#include<iostream>
#include<string>
using namespace std;

enum BankAccountStatus
{
	active = 2,
	suspended,
};

class BankAccount {
private:
	static int counter;
	const int id;
	string accountHolder;
	double balance;
	BankAccountStatus status;
	int* transactions;
	int nbOfTransactions;
public:
	BankAccount() : id(counter + 1)
	{
		cout << "Default constructor called" << endl;
		transactions = nullptr;
		nbOfTransactions = 0;
		balance = 1;
		status = BankAccountStatus::active;
		counter++;
	}

	BankAccount(string accountHolder, double balance, BankAccountStatus status) : BankAccount()
	{
		cout << "Constructor cu parametri apelat: " << endl;

		setStatus(status);
		setBalance(balance);
		setAccountHolder(accountHolder);
	}

	BankAccount(const BankAccount& account) : id(account.id)
	{
		cout << "Constructor de copiere este apelat" << endl;
		transactions = nullptr;
		setStatus(account.status);
		setBalance(account.balance);
		setAccountHolder(account.accountHolder);
		setTransactions(account.transactions, account.nbOfTransactions);
	}

	BankAccount& operator=(BankAccount& bankAccount)
	{
		cout << "Operatorul = este apelat" << endl;

		if (&bankAccount != this) // ca sa evitam situatia auto-asignarii 
		{
			setStatus(bankAccount.status);
			setBalance(bankAccount.balance);
			setAccountHolder(bankAccount.accountHolder);
			setTransactions(bankAccount.transactions, bankAccount.nbOfTransactions);
		}

		return *this;
	}

	bool operator!()
	{
		return balance <= 0;
	}

	BankAccount operator++() {
		this->balance = this->balance + 1;

		return *this;
	}


	BankAccount operator++(int i) {
		BankAccount bankAccountCopy = *this;
		this->balance = this->balance + 1;


		return bankAccountCopy;
	}

	void setTransactions(int* transactions, int nbOfTransactions)
	{
		if (this->transactions != nullptr)
		{
			delete[] this->transactions;
		}

		this->nbOfTransactions = nbOfTransactions;
		this->transactions = new int[nbOfTransactions];

		for (int i = 0; i < nbOfTransactions; i++)
		{
			this->transactions[i] = transactions[i];

		}
	}

	int* getTransactions() {
		int* copy = new int[nbOfTransactions];
		for (int i = 0; i < nbOfTransactions; i++)
			copy[i] = transactions[i];
		return copy;
	}


	double getBalance() {
		return this->balance;
	}

	BankAccountStatus getStatus() {
		return this->status;

	}

	void setBalance(double balance) {
		if (balance < 0) {
			this->balance = 0;
			this->status = BankAccountStatus::suspended;
		}
		else {
			this->balance = balance;
		}
	}

	void setStatus(BankAccountStatus _status) {
		this->status = _status;
	}

	void setAccountHolder(string accountHolder) {
		this->accountHolder = accountHolder;
	}

	void printBankAccount()
	{
		cout << endl;
		cout << "Id este: " << this->id << endl;
		cout << "Detinatorul contului este: " << this->accountHolder << endl;
		cout << "statusul este: " << this->status << endl;
		cout << "soldul este: " << this->balance << endl;
		cout << endl;
	}

	static int getCounter() {
		return counter;
	}

	~BankAccount()
	{
		cout << "Destructor apelat" << endl;
		counter--;
		delete[] transactions;
		nbOfTransactions = 0;
		transactions = nullptr;
	}

	//friend BankAccount operator++(BankAccount& bankaccount, int i);
};

// Varianta prin care supraincarcam operatorul++ de postincrementare prin functie globala
// daca vrem sa folosim varianta prin functie globala trebuie comentat/sters operatorul++ de postincrementare din clasa, altfel vom avea erori de compilare de ambiguitate
// Totodata avand in vedere ca folosim proprietati private in functia globala trebuie sa declaram functia ca friend in interiorul clasei
// 
//BankAccount operator++(BankAccount& bankaccount, int i) {
//	BankAccount copy = bankaccount;
//	bankaccount.balance = bankaccount.balance + 1;
//
//	return copy;
//}


int BankAccount::counter = 0;

void main()
{
	BankAccount firstBankAccount("Bogdan", 10, BankAccountStatus::active);
	BankAccount secondBankAccount("John", 20, BankAccountStatus::active);
	BankAccount thirdBankAccount("Martin", 30, BankAccountStatus::active);

	firstBankAccount = secondBankAccount = thirdBankAccount;

	firstBankAccount.printBankAccount();
	int tranz[2];
	tranz[0] = 342;
	tranz[1] = 728;
	firstBankAccount.setTransactions(tranz, 2);
	int* vector = firstBankAccount.getTransactions();

	vector[0] = 200;
	delete[] vector;

	if (!firstBankAccount) {
		cout << "Bank account is empty" << endl;
	}
	else {
		cout << "Bank account has balance" << endl;
	}

	int a = 1;
	int b = 1;

	int c = a++;
	int d = ++b;

	cout << a << " " << c << endl;
	cout << b << " " << d << endl;

	BankAccount bankAccount = ++firstBankAccount;
	BankAccount fifthBankAccount = firstBankAccount++;
	fifthBankAccount.printBankAccount();

	firstBankAccount.printBankAccount();
	bankAccount.printBankAccount();
}