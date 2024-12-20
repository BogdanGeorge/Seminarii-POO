#include <iostream>
#include <string>
using namespace std;

// Gestiunea angajatilor

class argumentInvalidException : public exception {
private:
	string message;
public:
	argumentInvalidException(const char* message) : exception(message) {
		cout << "argumentInvalidException constructor a fost apelat" << endl;
	}
};

class Employee
{
private:
	string name;
	string company;
	double salary;

public:
	Employee(string name, string company, double salary)
	{
		this->name = name;
		this->company = company;
		setSalary(salary);
	}

	void setSalary(double salary)
	{
		if (salary < 0) {
			throw argumentInvalidException("Salary este mai mic decat 0");
		}

		this->salary = salary;
	}

	virtual void printDetails()
	{
		cout << "Numele angajatului este " << name << " si acesta lucreaza la compania " << company << " avand salariul " << salary;
	}

	virtual bool isEligibleForSalaryIncrease() = 0;
};

class SoftwareEngineer : public Employee {
private:
	string programmingLanguage;
public:
	SoftwareEngineer(string name, string company, double salary, string programmingLanguage) : Employee(name, company, salary), programmingLanguage(programmingLanguage)
	{
	}

	void printDetails()
	{
		Employee::printDetails();
		cout << endl << "Limbajul de programare in care lucreaza este " << programmingLanguage << endl;
	}

	bool isEligibleForSalaryIncrease()
	{
		if (programmingLanguage == "C++") {
			return true;
		}
		else {
			return false;
		}
	}
};

class Accountant : public Employee {
private:
	bool hasCertificate;
public:

	Accountant(string name, string company, double salary, bool hasCertificate) :Employee(name, company, salary), hasCertificate(hasCertificate)
	{

	}

	void printDetails()
	{
		Employee::printDetails();
		if (hasCertificate == true)
		{
			cout << endl << "Are certificat CECCAR" << endl;
		}
		else
		{
			cout << endl << "Nu are certificat CECCAR" << endl;
		}
	}

	bool isEligibleForSalaryIncrease()
	{
		if (hasCertificate == true) {
			return true;
		}
		else {
			return false;
		}
	}
};



int main()
{
	//Employee employee1("Gigel", "Microsoft", 10000);
	//employee1.printDetails();
	/*cout << endl << endl;*/
	SoftwareEngineer georgeEng("George", "Microsoft", 500, "C++");
	SoftwareEngineer ioneEng("Ion", "Microsoft", 12000, "C#");

	Accountant accAndrei("Andrei", "Google", 2000, true);
	Accountant accRodica("Rodica", "Google", 1200, false);

	//Employee emp = georgeEng;

	//Employee employees[4];

	//employees[0] = georgeEng;
	//employees[1] = ioneEng;
	//employees[2] = accAndrei;
	//employees[3] = accRodica;

	Employee* employees[4];

	//upcasting de la SoftwareEnginner* la Employee*
	employees[0] = &georgeEng;
	employees[1] = &ioneEng;
	employees[2] = &accAndrei;
	employees[3] = &accRodica;

	for (int i = 0; i < 4; i++)
	{
		cout << endl;
		employees[i]->printDetails();
		if (employees[i]->isEligibleForSalaryIncrease()) {
			cout << "Angajatul este eligibil pentru crestere salariala" << endl;
		}
		else {
			cout << "Angajatul NU este eligibil pentru crestere salariala" << endl;

		}
	}

	cout << endl << endl;

	try
	{
		SoftwareEngineer eng("Test", "Microsoft", -1, "React");
	}
	catch (argumentInvalidException ex)
	{
		cout << "argumentInvalidException " << ex.what() << endl;
	}
	catch (exception ex)
	{
		cout << "exception" << ex.what() << endl;
	}
	catch (...) {
		cout << "Unknown exception" << endl;
	}

	return 0;
}