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
		counter++; // counter = counter +1;
	}

	BankAccount(string accountHolder, double balance, BankAccountStatus status) : BankAccount()
	{
		cout << "Constructor cu parametri apelat: " << endl;

		setStatus(status);
		setBalance(balance);
		setAccountHolder(accountHolder);
	}

	BankAccount(const BankAccount& account) : BankAccount()
	{
		cout << "Constructor de copiere este apelat" << endl;

		setStatus(account.status);
		setBalance(account.balance);
		setAccountHolder(account.accountHolder);
		setTransactions(account.transactions, account.nbOfTransactions);
	}

	void operator=(BankAccount bankAccount)
	{
		setStatus(bankAccount.status);
		setBalance(bankAccount.balance);
		setAccountHolder(bankAccount.accountHolder);
		setTransactions(bankAccount.transactions, bankAccount.nbOfTransactions);
	}

	void setTransactions(int* transactions, int nbOfTransactions)
	{
		// this->transactions = transactions; Aceasta linie de cod realizeaza o copie superficiala (Shallow Copy),
											// ceea ce poate duce la incalcarea principiului incapsularii, 
											// deoarece membrul `this->transactions` va pointa catre aceeasi zona de memorie ca parametrul primit ( transactions )
											// si ulterior membrul privat al clasei va putea fi modificat din exterior

		// Pentru membrii pointeri, implementarea corecta presupune realizarea unei copii profunde (Deep Copy)
		if (this->transactions != nullptr)
		{
			delete[] this->transactions; // Eliberarea memoriei alocate anterior pentru a evita Memory Leaks
		}

		this->nbOfTransactions = nbOfTransactions;
		this->transactions = new int[nbOfTransactions];

		for (int i = 0; i < nbOfTransactions; i++)
		{
			this->transactions[i] = transactions[i];
		}
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
		cout << "Destructor apelat" << endl;
		counter--;
		delete[] transactions;
	}
};

int BankAccount::counter = 0; // Daca nu initializam membrul static al unei clase va duce la erori de compilare

void main()
{
	cout << BankAccount::getCounter() << endl;

	BankAccount* pointerToAccount = new BankAccount("Gigel", 10, BankAccountStatus::active); // este apelat constructorul cu parametrii
	delete pointerToAccount; // este apelat destructorul

	BankAccount* pointerToAccountWithMalloc = (BankAccount*)malloc(sizeof(BankAccount)); // nu este apelat niciun constructor
	free(pointerToAccountWithMalloc); // nu este apelat destructorul

	cout << "===============================" << endl;

	BankAccount firstBankAccount("Bogdan", 25, BankAccountStatus::active);
	firstBankAccount.printBankAccount();

	// Pentru membrii pointeri de retinut principiul celor 3: Constructor de copiere, Destructor, Operatorul=

	int* vector = new int[2];
	vector[0] = 1;
	vector[1] = 2;

	firstBankAccount.setTransactions(vector, 2);
	vector[0] = 3; // Daca am fi pastrat implementarea cu shallow copy in setTransactions ar fi dus ca transactions[0] din firstBankAccount sa fie modificat la aceasta linie
	firstBankAccount.printBankAccount();

	BankAccount secondAccount = firstBankAccount;
	secondAccount = firstBankAccount; // Este acelasi lucru cu secondAccount.operator=(firstBankAccount);

	secondAccount.printBankAccount();
}