#include <iostream>

using namespace std;

void interschimbarePrinValori(int a, int b) {
	int aux = a;
	a = b;
	b = aux;
}

void interschimbarePrinReferinta(int& a, int& b) {
	int aux = a;
	a = b;
	b = aux;
}

void interschimbarePrinPointeri(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

// Inversarea functioenaza dar valorile returnate nu pot fi folosite si in main intrucat newVector este alocat static in stack-ul functiei inverseazaVectorPrinAlocareStatica
// Dupa executie stack-ul functiei este eliberat automat
int* inverseazaVectorPrinAlocareStatica(int vector[3]) {
	int newVector[3];

	for (int i = 0; i < 3; i++) {
		newVector[i] = vector[3 - i - 1];
	}

	return newVector;
}

// Inversarea functioneaza si persista si in main dar daca parametrul primit de catre aceasta functie devine constant , valorile vectorului nu vor mai putea fi modificate
// de exemplu daca modificam functia in: void inverseazaVectorPrinModificareaParametrului(const int vector[3])
// vom avea erori de compilare
void inverseazaVectorPrinModificareaParametrului(int vector[3]) {
	int newVector[3];

	for (int i = 0; i < 3; i++) {
		newVector[i] = vector[3 - i - 1];
	}

	for (int i = 0; i < 3; i++) {
		vector[i] = newVector[i];
	}
}
int* inverseazaVectorPrinAlocareDinamica(int* vector) {
	int* vNou;
	// Variabila vNou este un pointer la un bloc de memorie ( cu dimensiunea 4 * 3 = 12 Bytes ) alocat dinamic folosind funcția malloc
	// In acest fel aceasta variabila va fi alocata in heap iar durata de viata a acesteia va fi pana cand va fi eliberata explicit ( free ) sau pana cand programul isi incheie executia
	vNou = (int*)malloc(sizeof(int) * 3);

	for (int i = 0; i < 3; i++) {
		vNou[i] = vector[3 - i - 1];
	}

	return vNou;
}

void printeazaVector(int* vector, int nrLinii) {
	for (int i = 0; i < nrLinii; i++) {
		cout << vector[i] << " ";
	}
	cout << endl;
}

int main() {
	std::cout << "Seminar 2 - Recapitulare Pointeri" << std::endl;

	int a = 1;
	int b = 2;
	interschimbarePrinValori(a, b);
	cout << "interschimbarePrinValori: " << "a = " << a << " b = " << b << endl;

	int* pointerA = nullptr; // NULL
	pointerA++; // pointerA = pointerA +1;
	// NU putem accesa valoarea adresei intrucat apartine unei zone de memorie protejata
	// cout << *pointerA << endl; 
	cout << pointerA << endl;
	pointerA = pointerA + 2;
	cout << pointerA << endl;
	cout << sizeof(pointerA) << endl;

	pointerA = &a;
	cout << "Adresa lui a: " << &a << endl;
	cout << "Adresa salvata de pointerA: " << pointerA << endl;
	cout << "Adresa lui pointerA: " << &pointerA << endl;
	cout << "Valoarea de la adresa lui a: " << *pointerA << endl;

	interschimbarePrinReferinta(a, b);
	cout << "interschimbarePrinReferinta: " << "a = " << a << " b = " << b << endl;

	int* pointerB = &b;
	interschimbarePrinPointeri(pointerA, pointerB);
	cout << "interschimbarePrinPointeri: " << "a = " << a << " b = " << b << endl;

	int v[3];
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;

	printeazaVector(v, 3);

	int* vInversat = inverseazaVectorPrinAlocareStatica(v);
	cout << "Rezultatul functiei inverseazaVectorPrinAlocareStatica: " << endl;
	printeazaVector(vInversat, 3);

	inverseazaVectorPrinModificareaParametrului(v);
	cout << "Rezultatul functiei inverseazaVectorPrinModificareaParametrului: " << endl;
	printeazaVector(v, 3);

	int* vnou = inverseazaVectorPrinAlocareDinamica(v);
	cout << "Rezultatul functiei inverseazaVectorPrinAlocareDinamica: " << endl;
	printeazaVector(vnou, 3);

	return 0;
}