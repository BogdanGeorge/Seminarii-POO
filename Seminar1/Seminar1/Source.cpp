#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;

namespace MasiniMici {
	int nrLocuri = 2;
}

namespace MasiniMedii {
	int nrLocuri = 5;
}

using namespace MasiniMici;
using namespace MasiniMedii;

int suma(int nr1, int nr2)
{
	int suma = nr1 + nr2;
	return suma;
}

int diferenta(int nr1, int nr2)
{
	int dif = nr1 - nr2;
	return dif;
}

bool suntEgale(float fl, double dl)
{
	double epsilon = 1e-6;
	double dif = fabs(fl - dl);

	if (dif < epsilon)
	{
		return true;
	}
	else {
		return false;
	}
}


void main()
{
	printf("Bye bye C \n");
	std::cout << "Welcome C++" << std::endl;

	cout << "MasiniMici nr de locuri " << MasiniMici::nrLocuri << endl;
	cout << "MasiniMedii nr de locuri " << MasiniMedii::nrLocuri << endl;

	int nr1 = 1;
	int nr2 = 2;
	int sumaNr1Nr2 = suma(nr1, nr2);

	cout << "Suma functiei noastre este " << sumaNr1Nr2 << endl;

	int difNr1Nr2 = diferenta(nr1, nr2);
	cout << "Diferenta functiei noastre este " << difNr1Nr2 << endl;

	cout << "Numar bytes pt int: " << sizeof(int) << " iar pentru nr1 " << sizeof(nr1) << endl;

	// char a = "a"; Contine si \0
	char caracter = 85;

	cout << "Caracter: " << caracter << " nr echivalent caracterului " << (int)caracter << endl;

	caracter = 127;
	caracter++; // caracter = caracter +1;

	cout << "Caracter: " << caracter << " nr echivalent caracterului " << (int)caracter << endl;

	float fl = 0.1; // Ocupa 4 Bytes
	double dl = 0.1; // Ocupa 8 Bytes

	bool suntFlSiDlEgale = suntEgale(fl, dl);
	if (suntFlSiDlEgale) {
		cout << "Variabilele fl si dl sunt egale" << endl;
	}
	else {
		cout << "Variabilele fl si dl NU sunt egale" << endl;
	}
}