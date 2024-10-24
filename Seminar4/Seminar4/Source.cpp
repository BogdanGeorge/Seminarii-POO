#include <iostream>

void setDefaultValues(int** matrix, int nbOfRows, int nbOfColumns) {
	for (int i = 0; i < nbOfRows; i++) {
		for (int j = 0; j < nbOfColumns; j++) {
			matrix[i][j] = i + j;
		}
	}
}

void initializeMatrix(int**& matrix, int nbOfRows, int nbOfColumns) {
	matrix = new int* [nbOfRows];

	for (int i = 0; i < nbOfRows; i++) {
		matrix[i] = new int[nbOfColumns];
	}

	setDefaultValues(matrix, nbOfRows, nbOfColumns);
}

void printMatrix(int** matrix, int nbOfRows, int nbOfColumns) {
	for (int i = 0; i < nbOfRows; i++) {
		std::cout << std::endl;
		for (int j = 0; j < nbOfColumns; j++) {
			std::cout << matrix[i][j] << " ";
		}
	}
}

void releaseMemory(int**& matrix, int& nbOfRows, int& nbOfColumns) {
	for (int i = 0; i < nbOfRows; i++) {
		delete[] matrix[i];
	}

	delete[] matrix;
	matrix = nullptr;
	nbOfRows = 0;
	nbOfColumns = 0;
}

enum RobotColor {
	Black,
	Pink,
	Green
};

struct Robot {
	RobotColor color;
	char* name;
	bool isOperational;
};

Robot initializeRobot(const RobotColor color, const char* name, const bool isOperational)
{
	Robot r;
	r.color = color;
	r.name = new char[strlen(name) + 1];
	strcpy_s(r.name, strlen(name) + 1, name);
	r.isOperational = isOperational;
	return r;
}

void main() {
	int nbOfRows = 0;
	int nbOfColumns = 0;
	std::cout << "Nr de linii: ";
	std::cin >> nbOfRows;
	std::cout << "Nr de coloane: ";
	std::cin >> nbOfColumns;

	int numb = 1;
	int* pointerToNumb = &numb;
	int** pointerToPointerToNumb = &pointerToNumb;

	std::cout << numb << std::endl;
	std::cout << &numb << std::endl;
	std::cout << pointerToNumb << std::endl;
	std::cout << *pointerToNumb << std::endl;
	std::cout << &pointerToNumb << std::endl;
	std::cout << pointerToPointerToNumb << std::endl;
	std::cout << *pointerToPointerToNumb << std::endl;
	std::cout << **pointerToPointerToNumb << std::endl;

	int** matrix = nullptr;
	initializeMatrix(matrix, nbOfRows, nbOfColumns);
	printMatrix(matrix, nbOfRows, nbOfColumns);
	releaseMemory(matrix, nbOfRows, nbOfColumns);

	std::cout << std::endl;
	RobotColor robotColor = RobotColor::Black;
	std::cout << robotColor << std::endl;

	Robot robot = initializeRobot(robotColor, "Nelu Robotelu", true);
	std::cout << robot.name;
}