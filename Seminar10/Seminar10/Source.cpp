#include<iostream>
#include<string>
using namespace std;

enum BankAccountStatus
{
	active = 2,
	suspended,
};

class AccountHolder
{
private:
	string name;
	int age;
public:
	AccountHolder()
	{
		this->name = "Unknown";
		this->age = 0;
	}

	AccountHolder(string name, int age)
	{
		this->name = name;
		this->age = age;
	}

	string getName() const {
		return this->name;
	}

	friend class BankAccount;
	//friend ostream& operator<<(ostream& out, const BankAccount& bankAccount);
};

class BankAccount {
private:
	static int counter;
	const int id;
	AccountHolder accountHolder;
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

	BankAccount(AccountHolder accountHolder, double balance, BankAccountStatus status) : BankAccount()
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

	void operator ()(AccountHolder accountHolder, double balance)
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

	void setAccountHolder(AccountHolder accountHolder) {
		this->accountHolder = accountHolder;
	}

	string getName() const {
		return this->accountHolder.getName();

	}

	void printBankAccount()
	{
		cout << "Id este: " << this->id << endl;
		cout << "Detinatorul contului este: " << this->accountHolder.name << endl;
		cout << "statusul este: " << this->status << endl;
		cout << "soldul este: " << this->balance << endl;
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


class DebitBankAccount : public BankAccount
{
private:
	char* cardNumber = nullptr;
	double widrawalFee;
public:
	DebitBankAccount() : BankAccount()
	{
		cout << "Constructor DebitBankAccount apelat" << endl;
		this->cardNumber = nullptr;
		this->widrawalFee = 0;
	}

	DebitBankAccount(const char* cardNumber, double widrawalFee, AccountHolder accountHolder, double balance, BankAccountStatus status) : BankAccount(accountHolder, balance, status)
	{
		this->cardNumber = new char[strlen(cardNumber) + 1];
		strcpy_s(this->cardNumber, strlen(cardNumber) + 1, cardNumber);
		this->widrawalFee = widrawalFee;
	}

	DebitBankAccount(const DebitBankAccount& account) : BankAccount(account)
	{
		this->cardNumber = new char[strlen(account.cardNumber) + 1];
		strcpy_s(this->cardNumber, strlen(account.cardNumber) + 1, account.cardNumber);
		this->widrawalFee = account.widrawalFee;
	}

	DebitBankAccount& operator=(const DebitBankAccount& x)
	{
		if (&x != this) {
			BankAccount::operator=(x);

			//BankAccount& bankAccount = *this;
			//bankAccount.operator=(x);

			if (cardNumber != nullptr)
			{
				delete[] cardNumber;
				cardNumber = nullptr;
			}
			if (x.cardNumber != nullptr)
			{
				this->cardNumber = new char[strlen(x.cardNumber) + 1];
				strcpy_s(this->cardNumber, strlen(x.cardNumber) + 1, x.cardNumber);
			}
			this->widrawalFee = x.widrawalFee;
		}
		return *this;
	}

	void printBankAccount()
	{
		cout << endl;

		BankAccount::printBankAccount();

		if (this->cardNumber == nullptr) {
			cout << "Numarul de card este N/A" << endl;
		}
		else
		{
			cout << "Numarul de card este " << this->cardNumber << endl;
		}

		cout << "Comisionul de administrare este: " << this->widrawalFee << endl;
		cout << endl;
	}

	~DebitBankAccount()
	{
		if (cardNumber != nullptr)
		{
			delete[] cardNumber;
			cardNumber = nullptr;
		}
	}

	friend ostream& operator<<(ostream& out, const DebitBankAccount& debitBankAccount);
	friend istream& operator>>(istream& in, DebitBankAccount& debitBankAccount);
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
	//out << bankAccount.accountHolder.name << " " << bankAccount.balance;
	out << bankAccount.getName() << " " << bankAccount.balance;

	return out;
}

ostream& operator<<(ostream& out, const DebitBankAccount& debitBankAccount)
{
	const BankAccount& bankAccount = debitBankAccount;
	out << bankAccount;

	if (debitBankAccount.cardNumber == nullptr) {
		out << " numarul cardului este N/A";
	}
	else {
		out << " numarul cardului este " << debitBankAccount.cardNumber;
	}

	out << " iar comisionul de retragere este " << debitBankAccount.widrawalFee;

	return out;
}

istream& operator>>(istream& in, BankAccount& bankAccount) {

	cout << "Introduceti un sold: ";

	double balance;
	in >> balance;

	bankAccount.setBalance(balance);

	cout << "Introduceti bank account holder name: ";

	string accountHolderTemp;
	in >> accountHolderTemp;

	cout << "Introduceti bank account holder age: ";
	double accountHolderAge;
	in >> accountHolderAge;


	bankAccount.setAccountHolder(AccountHolder(accountHolderTemp, accountHolderAge));

	return in;
}


istream& operator>>(istream& in, DebitBankAccount& debitBankAccount) {

	BankAccount& bankAccount = debitBankAccount;
	in >> bankAccount;

	cout << "Introduceti card number: ";
	string buffer;
	in >> buffer;

	if (debitBankAccount.cardNumber != nullptr)
	{
		delete[] debitBankAccount.cardNumber;
		debitBankAccount.cardNumber = nullptr;
	}

	debitBankAccount.cardNumber = new char[buffer.length() + 1];
	strcpy_s(debitBankAccount.cardNumber, buffer.length() + 1, buffer.c_str());

	cout << "Introduceti comision de retragere: ";
	in >> debitBankAccount.widrawalFee;

	return in;

}

void main()
{
	DebitBankAccount bogdanBankAccount("BCR123", 1, AccountHolder("Bogdan", 20), 10, BankAccountStatus::active);
	DebitBankAccount johnBankAccount("ING123", 0, AccountHolder("John", 30), 20, BankAccountStatus::active);
	DebitBankAccount test = bogdanBankAccount;


	test = johnBankAccount;

	test.printBankAccount();

	cin >> test;
	cout << test << endl;

}