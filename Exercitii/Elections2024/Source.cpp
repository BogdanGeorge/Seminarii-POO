#include<iostream>
#include <string>
using namespace std;

enum Party {
	unknown = 1,
	independent = 2,
	republican = 3,
	democrat = 4,
};

class Candidate {
private:
	const int id;
	char* name; // De preferat ar fi sa initializam cu nullptr toti membrii pointeri ai clasei de la definire ( eg char* name = nullptr ) dar in acest exemplu facem acest lucru explicit in fiecare constructor
	int votes;
	string slogan;
	Party party;
public:
	Candidate() :id(1), votes(0), party(Party::unknown)
	{
		slogan = "N/A";
		name = nullptr;
	}

	Candidate(int id, const char* name, int votes, Party party) : id(id), votes(votes), party(party)
	{
		this->name = nullptr; // Daca membrul pointer nu este initializat cu nullptr poate avea un comportament impredictibil care poate duce la o eroare in executia metodei setName
		setSlogan(party);
		setName(name);
	}

	Candidate(const Candidate& candidate) : id(candidate.id), votes(candidate.votes), party(candidate.party)
	{
		this->name = nullptr; // Daca membrul pointer nu este initializat cu nullptr poate avea un comportament impredictibil care poate duce la o eroare in executia metodei setName
		setSlogan(candidate.party);
		setName(candidate.name);
	}

	Candidate& operator=(const Candidate& candidate)
	{
		if (this == &candidate) // Pentru a evita autoasignarea 
		{
			return *this;
		}

		this->votes = candidate.votes;
		this->party = candidate.party;
		setSlogan(candidate.party);
		setName(candidate.name);

		return *this;
	}

	Candidate& operator--() // Pre
	{
		this->votes = this->votes - 1;
		return *this;
	}

	Candidate operator--(int) // Post
	{
		Candidate copy = *this;
		this->votes = this->votes - 1;
		return copy;
	}

	void setName(const char* name)
	{
		if (this->name != nullptr) // Daca este deja alocata memoria pt this->name
		{
			delete[] this->name; // Evitam memory leaks
			this->name = nullptr; // Setam cu nullptr ca sa evitam dangling pointer
		}

		if (name == nullptr) // Validam ca parametrul primit nu este nullptr.
		{
			return;
		}

		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	char* getName() {
		if (this->name == nullptr) {
			return nullptr;
		}

		char* copy = new char[strlen(this->name) + 1];
		strcpy_s(copy, strlen(this->name) + 1, this->name);

		return copy;
	}

	void setSlogan(Party party) {
		if (party == Party::independent) {
			this->slogan = "Un candidat independent pentru o tara mai buna";
		}
		else if (party == Party::republican) {
			this->slogan = "Un candidat republican pentru o tara mai buna";
		}
		else if (party == Party::democrat) {
			this->slogan = "Un candidat democrat pentru o tara mai buna";
		}
		else {
			this->slogan = "N/A";
		}
	}

	void printCandidateDetails()
	{
		cout << endl;

		if (this->name != nullptr)  // Validam ca name nu este nullptr. Fara aceasta validare in cazul in care name ar fi nullptr si incercam sa-l afisam in consola vom primi o eroare la executia programului
		{
			cout << "Nume candidat: " << this->name << endl;
		}
		else {
			cout << "Nume candidat: N/A" << endl;
		}

		cout << "Numar de voturi: " << this->votes << endl;
		cout << endl;
	}

	string getSlogan() {
		return this->slogan;
	}

	static char* getCandidateWithHighestNumberOfVotes(Candidate* candidates, int nbOfCandidates)
	{
		if (nbOfCandidates == 0) {
			return nullptr;
		}

		Candidate c = candidates[0];
		for (int i = 0; i < nbOfCandidates; i++) {
			if (c.votes < candidates[i].votes)
			{
				c = candidates[i];
			}
		}
		return c.getName();
	}


	~Candidate()
	{
		if (name != nullptr) {
			delete[] name; // Evitam memory leaks
			name = nullptr; // Evitam dangling pointers
		}
	}
};


int main()
{
	Candidate candidate(1, "Bogdan", 100, Party::independent);
	Candidate candidate2(2, "George", 101, Party::independent);
	Candidate candidate3(3, "John", 102, Party::independent);
	Candidate candidate4(4, nullptr, 1, Party::independent);
	candidate4.printCandidateDetails(); // Testam ca nu se va afisa name atata timp cat este nullptr

	Candidate testConstructorCopiere = candidate; // Testam constructorul de copiere

	testConstructorCopiere.printCandidateDetails();

	testConstructorCopiere = candidate; // Testam operatorul = 

	testConstructorCopiere.printCandidateDetails();

	Candidate c1 = candidate--; // Testam operatorul post decrementare
	candidate.printCandidateDetails();
	c1.printCandidateDetails();

	Candidate c2 = --candidate; // Testam operatorul pre decrementare
	candidate.printCandidateDetails();
	c2.printCandidateDetails();

	Candidate candidates[3]{ candidate, candidate2, candidate3 };

	char* candidateWithHighestNumberOfVotes = Candidate::getCandidateWithHighestNumberOfVotes(candidates, 3);
	cout << "Candidatul cu numele: " << candidateWithHighestNumberOfVotes << " are cele mai multe voturi" << endl;

	delete[] candidateWithHighestNumberOfVotes;
	candidateWithHighestNumberOfVotes = nullptr;

	return 0;
}