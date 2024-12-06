#include <iostream>
#include<stdexcept>

using namespace std;

#define MAX 500

//tabla de sah
void afisareBoard(int* board, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (board[i] == j)
			{
				cout << "X ";
			}
			else
			{
				cout << ". ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

//verifica daca un anumit rand si o anumita coloana este libera 
//se verifica dupa fiecare plasare a unui turn
bool verificare(int* board, int rand, int coloana)
{
	for (int i = 0; i < rand; i++)
	{
		if (board[i] == coloana)
		{
			return false;
		}
	}
	return true;
}

//dupa ce s a gasit o solutie opreste plasarea de turnuri
bool solutiecompleta(int* board, int n) {
	for (int i = 0; i < n; i++) {
		if (board[i] == -1) {
			return false;
		}
	}
	return true;
}

// functie care genereaza solutiie ramase
void backtrack(int* board, int n, int rand, int** solutii, int& index) {
	if (rand == n)
	{
		for (int i = 0; i < n ; i++)
		{
			solutii[index][i] = board[i];
		}
		index++;
		return;
	}

	for (int coloana = 0; coloana < n; coloana++) {
		if (verificare(board, rand, coloana))
		{
			board[rand] = coloana;
			backtrack(board, n, rand + 1, solutii, index);
			board[rand] = -1;
		}
	}
}

int main() {
	int n;

	//dimensiune tabla de sah
	cout << "dimensiune tabla de sah: ";
	cin >> n;

	if (n <= 2) {
		cout << "dimensiune invalida!" << endl;
		return 1;
	}

	//alocare memorie pentru board
	int* board = new int[n];

	//initializare board
	for (int i = 0; i < n; i++) {
		board[i] = -1;
	}

	//afisare tabla de sah
	cout << "\ntabla se sah\n";
	afisareBoard(board, n);


	bool continua = true;

	while (continua)
	{
		int rand, coloana;

		cout << "introduceti randul: ";
		cin >> rand;

		if (rand == -1) {
			continua = false;
			break;
		}

		cout << "introduceti coloana: ";
		cin >> coloana;

		// verificare rand si coloana
		if (rand < 0 || rand >= n || coloana < 0 || coloana >= n) {
			cout << "rand sau coloana sunt invalide!\n";
			continue;
		}

		// verifica daca pozitia este valida si plaseaza turn
		if (verificare(board, rand, coloana))
		{
			board[rand] = coloana;
			cout << "\ntabla de sah dupa plasarea turnului:\n";
			afisareBoard(board, n);

			// verifica daca s a gasit o solutie 
			if (solutiecompleta(board, n))
			{
				break;
			}
		}
		else {
			cout << "coloana " << (coloana + 1) << " este deja ocupata\n";
		}
	}

	// generare solutii valide ramase
	int** solutii = new int*[MAX];

	for (int i = 0; i < MAX; i++)
	{
		solutii[i] = new int[n];
	}

	int index = 0;
	backtrack(board, n, 0, solutii, index);


	// afisare solutii ramase
	cout << "\nrestul solutiilor posibile\n";
	for (int i = 0; i < index; i++)
	{
		bool identica = true;

		for (int j = 0; j < n; j++)
		{
			if (solutii[i][j] != board[j])
			{
				identica = false;
				break;
			}
		}
		if (!identica) {
			afisareBoard(solutii[i], n);
		}
	}


	// afisare numar total de solutii
	cout << "\nnumarul total de solutii: " << index << endl;


	// eliberam memoria alocata
	for (int i = 0; i < MAX; i++)
	{
		delete[] solutii[i];
	}

	delete[] solutii;
	delete[] board;

	return 0;
}