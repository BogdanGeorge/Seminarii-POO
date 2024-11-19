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

	BankAccount& operator=(const BankAccount& bankAccount)
	{
		cout << "Operatorul = este apelat" << endl;

		if (&bankAccount != this)
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

	BankAccount operator+(const BankAccount& account)
	{
		BankAccount bankAccountCopy = *this;
		bankAccountCopy.balance = this->balance + account.balance;

		return bankAccountCopy;
	}

	BankAccount operator+(const double balance)
	{
		BankAccount bankAccountCopy = *this;
		bankAccountCopy.balance = this->balance + balance;

		return bankAccountCopy;
	}

	int operator[](int index)
	{
		if (index < 0 || index >= nbOfTransactions) {

			/*	throw new exception("Index este invalid");*/
			return -1;
		}

		return this->transactions[index];
	}

	explicit operator double()
	{
		return this->balance;
	}

	void operator ()(string accountHolder, double balance)
	{
		this->setAccountHolder(accountHolder);
		this->balance = balance;
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

		if (transactions != nullptr) {
			delete[] transactions;
			transactions = nullptr;

		}

		nbOfTransactions = 0;
		counter--;
	}

	friend BankAccount operator+(const double balance, const BankAccount& bankAccount);
	friend ostream& operator<<(ostream& out, const BankAccount& bankAccount);
	friend istream& operator>>(istream& in, BankAccount& bankAccount);
};


int BankAccount::counter = 0;

BankAccount operator+(const double balance, const BankAccount& bankAccount)
{
	BankAccount bankAccountCopy = bankAccount;
	bankAccountCopy.balance = bankAccountCopy.balance + balance;

	return bankAccountCopy;

}

ostream& operator<<(ostream& out, const BankAccount& bankAccount)
{
	out << bankAccount.accountHolder << " " << bankAccount.balance;

	return out;
}
istream& operator>>(istream& in, BankAccount& bankAccount) {

	cout << "Introduceti un sold:";

	double balance;
	in >> balance;

	bankAccount.setBalance(balance);

	cout << "Introduceti bank account holder name: ";


	// Daca bankAccount.accountHolder ar fi char* si nu string cum e in cazul nostru
	//char* accountHolderTempCharArr = new char[accountHolderTemp.length()];
	//strcpy_s(accountHolderTempCharArr, accountHolderTemp.length(), accountHolderTemp.c_str());
	//bankAccount.setAccountHolder(accountHolderTempCharArr);


	string accountHolderTemp;
	in >> accountHolderTemp;

	bankAccount.setAccountHolder(accountHolderTemp);

	return in;
}

void main()
{
	BankAccount bogdanBankAccount("Bogdan", 10, BankAccountStatus::active);
	BankAccount johnBankAccount("John", 20, BankAccountStatus::active);
	BankAccount georgeBankAccount = bogdanBankAccount + johnBankAccount;
	georgeBankAccount.printBankAccount();
	georgeBankAccount = georgeBankAccount;

	georgeBankAccount = georgeBankAccount + 2;
	georgeBankAccount.printBankAccount();

	georgeBankAccount = 6 + georgeBankAccount;
	georgeBankAccount.printBankAccount();

	int tranz[] = { 1,2,3 };
	georgeBankAccount.setTransactions(tranz, 3);
	cout << georgeBankAccount[2] << endl;

	double balance = (double)georgeBankAccount;
	cout << balance << endl;

	georgeBankAccount("George", 1);
	georgeBankAccount.printBankAccount();

	cout << "Test" << endl;

	cout << georgeBankAccount << endl << bogdanBankAccount << endl;
	cin >> georgeBankAccount >> bogdanBankAccount;
	cout << georgeBankAccount << endl << bogdanBankAccount << endl;

}