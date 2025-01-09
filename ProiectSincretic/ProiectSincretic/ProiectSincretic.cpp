#include <iostream>
#include<stdexcept>

using namespace std;

#define MAX 50000

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


bool solutiecompleta(int* board, int n) {
	for (int i = 0; i < n; i++) {
		if (board[i] == -1) {
			return false;
		}
	}
	return true;
}


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
	cout << "dimensiune tabla de sah: ";
	cin >> n;

	if (n <= 2) {
		cout << "dimensiune invalida!" << endl;
		return 1;
	}

	int* board = new int[n];

	for (int i = 0; i < n; i++) {
		board[i] = -1;
	}


	cout << "\ntabla se sah\n";
	afisareBoard(board, n);

	bool continua = true;

	while (continua)
	{
		int rand, coloana;

		cout << "introduceti randul: ";
		cin >> rand;

		if (rand == -1) 
		{
			continua = false;
			break;
		}

		cout << "introduceti coloana: ";
		cin >> coloana;

		if (rand < 0 || rand >= n || coloana < 0 || coloana >= n) 
		{
			cout << "rand sau coloana sunt invalide!\n";
			continue;
		}


		if (verificare(board, rand, coloana))
		{
			board[rand] = coloana;
			cout << "\ntabla de sah dupa plasarea turnului:\n";
			afisareBoard(board, n);

			if (solutiecompleta(board, n))
			{
				break;
			}
		}
		else 
		{
			cout << "coloana " << (coloana + 1) << " este deja ocupata\n";
		}
	}


	int** solutii = new int*[MAX];
	for (int i = 0; i < MAX; i++)
	{
		solutii[i] = new int[n];
	}


	int index = 0;
	backtrack(board, n, 0, solutii, index);


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

	cout << "\nnumarul total de solutii: " << index << endl;


	for (int i = 0; i < MAX; i++)
	{
		delete[] solutii[i];
	}

	delete[] solutii;
	delete[] board;

	return 0;
}