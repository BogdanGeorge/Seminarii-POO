#include<iostream>
#include<string>
#include<fstream>

using namespace std;

enum BankAccountStatus
{
	active = 2,
	suspended,
};

class DebitBankAccount;

class BankAccount {
protected:
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
		transactions = nullptr;
		nbOfTransactions = 0;
		balance = 1;
		status = BankAccountStatus::active;
		counter++;
	}

	BankAccount(string accountHolder, double balance, BankAccountStatus status) : BankAccount()
	{
		setStatus(status);
		setBalance(balance);
		setAccountHolder(accountHolder);
	}

	BankAccount(const BankAccount& account) : id(account.id)
	{
		transactions = nullptr;
		setStatus(account.status);
		setBalance(account.balance);
		setAccountHolder(account.accountHolder);
		setTransactions(account.transactions, account.nbOfTransactions);
	}

	BankAccount& operator=(const BankAccount& bankAccount)
	{
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

	string getName() const {
		return this->accountHolder;

	}

	void printBankAccount()
	{
		cout << "Id este: " << this->id << endl;
		cout << "Detinatorul contului este: " << this->accountHolder << endl;
		cout << "statusul este: " << this->status << endl;
		cout << "soldul este: " << this->balance << endl;
	}

	static int getCounter() {
		return counter;
	}

	~BankAccount()
	{
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
	friend ofstream& operator<<(ofstream& in, const DebitBankAccount& debitBankAccount);

};


class DebitBankAccount : public BankAccount
{
private:
	char* cardNumber = nullptr;
	double widrawalFee;
public:
	DebitBankAccount() : BankAccount()
	{
		this->cardNumber = nullptr;
		this->widrawalFee = 0;
	}

	DebitBankAccount(const char* cardNumber, double widrawalFee, string accountHolder, double balance, BankAccountStatus status) : BankAccount(accountHolder, balance, status)
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

	void writeToBinaryFile(const char* fileName)
	{
		ofstream f(fileName, ios::binary);

		int accountHolderLength = this->accountHolder.length();
		f.write((char*)&accountHolderLength, sizeof(accountHolderLength));
		f.write(this->accountHolder.c_str(), accountHolderLength + 1);

		f.write((char*)&this->balance, sizeof(this->balance));

		if (this->cardNumber != nullptr)
		{
			int cardNumberLength = strlen(this->cardNumber);
			f.write((char*)&cardNumberLength, sizeof(cardNumberLength));
			f.write(this->cardNumber, cardNumberLength + 1);
		}
		else
		{
			int cardNumberLength = 0;
			f.write((char*)&cardNumberLength, sizeof(cardNumberLength));
		}

		f.write((char*)&this->widrawalFee, sizeof(this->widrawalFee));

		f.write((char*)&this->nbOfTransactions, sizeof(this->nbOfTransactions));

		for (int i = 0; i < this->nbOfTransactions; i++)
		{
			f.write((char*)&this->transactions[i], sizeof(this->transactions[i]));
		}
	}

	void readFromBinary(const char* fileName)
	{
		ifstream f(fileName, ios::binary);

		int accountHolderLength = 0;
		f.read((char*)&accountHolderLength, sizeof(accountHolderLength));

		char* accountHolderBuffer = new char[accountHolderLength + 1];

		f.read(accountHolderBuffer, accountHolderLength + 1);
		this->accountHolder = accountHolderBuffer;

		delete[] accountHolderBuffer;

		f.read((char*)&this->balance, sizeof(this->balance));

		int cardNumberLength = 0;
		f.read((char*)&cardNumberLength, sizeof(cardNumberLength));

		if (this->cardNumber != nullptr) {
			delete[] this->cardNumber;
			this->cardNumber = nullptr;
		}

		if (cardNumberLength > 0)
		{
			this->cardNumber = new char[cardNumberLength + 1];
			f.read(this->cardNumber, cardNumberLength + 1);
		}


		f.read((char*)&this->widrawalFee, sizeof(this->widrawalFee));

		if (this->transactions != nullptr)
		{
			delete[] this->transactions;
			this->transactions = nullptr;
			this->nbOfTransactions = 0;
		}


		f.read((char*)&this->nbOfTransactions, sizeof(this->nbOfTransactions));

		if (this->nbOfTransactions > 0)
		{
			this->transactions = new int[this->nbOfTransactions];
		}

		for (int i = 0; i < this->nbOfTransactions; i++)
		{
			f.read((char*)&this->transactions[i], sizeof(this->transactions[i]));
		}
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
	friend ofstream& operator<<(ofstream& in, const DebitBankAccount& debitBankAccount);

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
	out << bankAccount.getName() << " " << bankAccount.balance << endl;

	out << "Numarul tranzactiilor: " << bankAccount.nbOfTransactions << endl;
	for (int i = 0; i < bankAccount.nbOfTransactions; i++)
	{
		out << "Tranzactia " << i << ": " << bankAccount.transactions[i] << endl;
	}


	return out;
}

ostream& operator<<(ostream& out, const DebitBankAccount& debitBankAccount)
{
	const BankAccount& bankAccount = debitBankAccount;
	out << bankAccount;

	if (debitBankAccount.cardNumber == nullptr) {
		out << "Numarul cardului este N/A" << endl;
	}
	else {
		out << "Numarul cardului este " << debitBankAccount.cardNumber << endl;
	}

	out << "Comisionul de retragere este " << debitBankAccount.widrawalFee << endl;;

	return out;
}

istream& operator>>(istream& in, BankAccount& bankAccount) {
	cout << "Introduceti bank account holder name: ";

	string accountHolderTemp;
	getline(in, accountHolderTemp);

	bankAccount.setAccountHolder(accountHolderTemp);

	cout << "Introduceti un sold: ";

	double balance;
	in >> balance;
	if (in.good()) {
		cout << "Am preluat soldul cu valoarea " << balance << endl;;
	}
	else {
		cout << "Soldul este invalid" << endl;
	}

	bankAccount.setBalance(balance);

	cout << "Nr tranzactii: ";
	in >> bankAccount.nbOfTransactions;
	if (bankAccount.transactions != nullptr)
	{
		delete[] bankAccount.transactions;
	}
	bankAccount.transactions = new int[bankAccount.nbOfTransactions];
	for (int i = 0; i < bankAccount.nbOfTransactions; i++)
	{
		cout << "Transaction[" << i << "]: ";
		in >> bankAccount.transactions[i];
	}

	return in;
}


istream& operator>>(istream& in, DebitBankAccount& debitBankAccount) {

	BankAccount& bankAccount = debitBankAccount;
	in >> bankAccount;


	cout << "Introduceti card number: ";
	char buffer[12];
	in.ignore();
	in.getline(buffer, 11);

	if (debitBankAccount.cardNumber != nullptr)
	{
		delete[] debitBankAccount.cardNumber;
		debitBankAccount.cardNumber = nullptr;
	}

	if (strcmp(buffer, "NULL") != 0)
	{
		debitBankAccount.cardNumber = new char[12];
		strcpy_s(debitBankAccount.cardNumber, 12, buffer);
	}


	cout << "Introduceti comision de retragere: ";
	in >> debitBankAccount.widrawalFee;

	return in;
}

ofstream& operator<<(ofstream& in, const DebitBankAccount& debitBankAccount)
{
	if (in.is_open()) {
		const BankAccount& bankAccount = debitBankAccount;

		in << bankAccount.accountHolder << endl;
		in << bankAccount.balance << endl;

		in << bankAccount.nbOfTransactions << endl;
		for (int i = 0; i < bankAccount.nbOfTransactions; i++)
		{
			in << bankAccount.transactions[i] << endl;
		}

		if (debitBankAccount.cardNumber == nullptr) {
			in << "NULL" << endl;

		}
		else {
			in << debitBankAccount.cardNumber << endl;
		}

		in << debitBankAccount.widrawalFee << endl;
	}

	return in;
}

void main()
{
	DebitBankAccount bogdanBankAccount("BCR123", 1, "Bogdan", 10, BankAccountStatus::active);
	DebitBankAccount johnBankAccount("ING123", 0, "John", 20, BankAccountStatus::active);
	DebitBankAccount test;

	cin >> test;
	cout << test << endl;

	cout << endl;
	cout << "Citire/scriere fisier text" << endl << endl;

	ofstream f("testBankAccount.txt");
	f << test;
	f.close();

	ifstream frearder("testBankAccount.txt");
	DebitBankAccount secondTest;
	frearder >> secondTest;

	cout << endl;
	cout << secondTest;

	int x = 100000;
	int* xAddr = &x;
	char* xChars = (char*)xAddr;

	cout << endl;
	cout << "Citire/scriere binara" << endl << endl;

	secondTest.writeToBinaryFile("secondTest.bin");

	DebitBankAccount thirdTest;
	thirdTest.readFromBinary("secondTest.bin");

	cout << thirdTest;
}