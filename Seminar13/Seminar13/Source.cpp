#include<iostream>
#include<vector>
#include<list>
#include<deque>
using namespace std;

// Recapitulare clase abstracte dupa vacanta :)
class Sarma {
public:
	virtual void pregatesteIngrediente() = 0;

	void prepara() {
		cout << "Cauta oala" << endl;
		pregatesteIngrediente();
		cout << "Pune incredientele in oala" << endl;
	}

};

class SarmaCuCarne : public Sarma {
public:
	void pregatesteIngrediente()
	{
		cout << "Adauga Orez 10Grame" << endl << "Adauga carne de porc tocata 100G " << endl;
	}
};

class SarmaDePost : public Sarma {
public:
	void pregatesteIngrediente()
	{
		cout << "Adauga Orez 10G" << endl << "Adauga ciuperci 20G " << endl;
	}
};


class IntVector
{
	int* vector;
	int maxSize;
	int currentSize;
public:
	IntVector(int maxSize)
	{
		this->maxSize = maxSize;
		this->currentSize = 0;
		this->vector = new int[maxSize];
	}

	void push(int value)
	{
		if (currentSize == maxSize)
		{
			throw exception("Max size reached.");
		}
		vector[currentSize] = value;
		currentSize++;
	}

	int pop()
	{
		currentSize--;

		int temp = vector[currentSize];
		vector[currentSize] = 0;
		return temp;
	}

	int* getVector()
	{
		int* copy = new int[currentSize];
		for (int i = 0; i < currentSize; i++)
		{
			copy[i] = vector[i];
		}

		return copy;
	}

	int getSize()
	{
		return currentSize;
	}

	// Intrucat lucram cu pointeri in clasa ar trebui sa adaugam:
	// Constructor de copiere
	// Operatorul de atribuire
	// Destructor
};

template <typename T>
class GenericVector
{
	T* vector;
	int maxSize;
	int currentSize;
public:
	GenericVector(int maxSize)
	{
		this->maxSize = maxSize;
		this->currentSize = 0;
		this->vector = new T[maxSize];
	}

	void push(T value)
	{
		if (currentSize == maxSize)
		{
			throw exception("Max size reached.");
		}
		vector[currentSize] = value;
		currentSize++;
	}

	T pop()
	{
		currentSize--;

		T temp = vector[currentSize];
		vector[currentSize] = T();
		return temp;
	}

	T* getVector()
	{
		T* copy = new T[currentSize];
		for (int i = 0; i < currentSize; i++)
		{
			copy[i] = vector[i];
		}

		return copy;
	}

	int getSize()
	{
		return currentSize;
	}

	// Intrucat lucram cu pointeri in clasa ar trebui sa adaugam:
	// Constructor de copiere
	// Operatorul de atribuire
	// Destructor
};

template <typename T>
void displayAll(T* vector, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << vector[i] << " ";
	}
	cout << endl;
}

int main()
{
	SarmaDePost sarmaDePost;
	SarmaCuCarne sarmaCuCarne;

	// Nu functioneaza pentru ca o clasa abstracta ( Sarma ) nu poate fi instantiata
	//Sarma sarma;
	//Sarma* farfurie = new Sarma[2]{ sarmaDePost , sarmaCuCarne }; 
	Sarma** farfurie2 = new Sarma * [2] {&sarmaDePost, & sarmaCuCarne};
	farfurie2[0]->prepara();
	farfurie2[1]->prepara();

	IntVector vint(2);
	try {
		vint.push(1);
		vint.push(2);
		vint.pop();
		vint.push(3);
		vint.push(4);
	}
	catch (exception ex)
	{
		cout << "Exception catched with message: " << ex.what() << endl;
	}


	cout << "============CLASE TEMPLATE============" << endl;

	GenericVector<int> vector1(5);
	vector1.push(1);
	vector1.push(2);
	vector1.push(3);
	cout << vector1.pop() << endl;
	displayAll(vector1.getVector(), vector1.getSize());

	GenericVector<string> vector2(5);
	vector2.push("Bogdan");
	vector2.push("Andreea");
	vector2.push("Vasile");
	cout << vector2.pop() << endl;

	displayAll(vector2.getVector(), vector2.getSize());

	cout << "============CLASE STL============" << endl;
	cout << "============VECTOR============" << endl;

	vector<int> vector3 = { 1,2 };
	cout << "Current size: " << vector3.size() << " Current Capacity: " << vector3.capacity() << endl;
	vector3.push_back(3);
	cout << "Current size: " << vector3.size() << " Current Capacity: " << vector3.capacity() << endl;
	vector3.push_back(4);
	cout << "Current size: " << vector3.size() << " Current Capacity: " << vector3.capacity() << endl;
	vector3.push_back(5);
	cout << "Current size: " << vector3.size() << " Current Capacity: " << vector3.capacity() << endl;
	vector3.pop_back();
	cout << "Current size: " << vector3.size() << " Current Capacity: " << vector3.capacity() << endl;

	vector3.insert(vector3.begin() + 1, 5);

	for (int i = 0; i < vector3.size(); i++)
	{
		cout << vector3[i] << " ";
	}


	cout << endl << "============LIST============" << endl;

	list<int> list1 = { 1,2 };
	cout << "Current size: " << list1.size() << endl;
	list1.push_back(3);
	list1.push_front(4);
	list1.pop_back();
	list1.pop_front();

	list<int>::iterator it = list1.begin(); // 	auto it2 = list1.begin();
	advance(it, 1);
	list1.insert(it, 5);

	list1.sort();

	for (auto it3 = list1.begin(); it3 != list1.end(); it3++)
	{
		cout << *it3 << " ";
	}


	cout << endl << "============DEQUE============" << endl;

	deque<int> d1 = { 1,2 };
	cout << "Current size: " << d1.size() << endl;
	d1.push_back(3);
	d1.push_front(4);
	d1.pop_back();
	d1.pop_front();

	for (int i = 0; i < d1.size(); i++)
	{
		cout << d1[i] << " ";
	}

	return 0;
}