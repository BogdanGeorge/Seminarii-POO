#include <iostream>
#include <cstring>
using namespace std;

void generateStackOverflow() {
	generateStackOverflow();
}

void generateMemoryLeak() {
	for (int i = 0; i < 5000; i++) {
		int* vect = new int[50000];
		delete[] vect; // Fara delete[] va genera memory leak
	}
}

void printVector(int* vector, int n)
{
	for (int i = 0; i < n; i++) {
		cout << vector[i] << " ";
	}

	cout << endl;
}

int* createVector(int size)
{
	int* vect = new int[size];
	for (int i = 0; i < size; i++)
	{
		cout << "Introduceti vector[" << i << "]:";
		cin >> vect[i];
	}
	return vect;
}

int* addNewItemToVector(int* vector, int size, int value)
{
	int* newVector = new int[size + 1];

	for (int i = 0; i < size; i++)
		newVector[i] = vector[i];

	newVector[size] = value;

	return newVector;
}

char* uppercaseText(const char* text)
{
	char* newText = new char[strlen(text) + 1];

	strcpy_s(newText, strlen(text) + 1, text);

	for (int i = 0; i < strlen(text); i++) {
		if (newText[i] >= 97 && newText[i] <= 122)
		{
			newText[i] = newText[i] - 32;
		}
	}

	return newText;
}

void main()
{
	//generateStackOverflow();

	int* vector = createVector(3);
	printVector(vector, 3);

	delete[] vector;
	vector = nullptr;
	//generateMemoryLeak();

	int* vector2 = createVector(2);
	vector = vector2;
	printVector(vector, 2);

	int value;

	cout << "Value: "; 
	cin >> value;

	int* newVector = addNewItemToVector(vector2, 2, value);

	printVector(newVector, 3);
	cin.get();

	char* uppercasedText = uppercaseText("Hello world!"); // Contine \0
	cout << uppercasedText << endl;
}