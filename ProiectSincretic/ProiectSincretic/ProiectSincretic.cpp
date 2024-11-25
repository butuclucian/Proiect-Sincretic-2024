#include<iostream>
#include<stdexcept>

using namespace std;


//tabla de sah
void afisareboard(int *board, int n)
{
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++) {
			if (board[i] == j) {
				cout << "X ";
			}
			else {
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
	for(int i = 0; i < rand; i++)
	{
		if (board[i] == coloana)
		{
			return false; 
		}
	}
	return true;
}

int main()
{
	try {
		int n;
		int rand;
		int coloana;

		//dimensiune tabla de sah
		cout << "dimensiune tabla de sah: ";
		cin >> n;

		if (n <= 0) {
			throw invalid_argument("trebuie sa fie un numar >=2!\n");
		}

		//alocare memorie pentru board
		int* board = new int[n];

		//initializare board
		for (int i = 0; i < n; i++)
		{
			board[i] = -1;
		}

		//afisare tabla de sah
		cout << "\ntabla se sah\n";
		afisareboard(board, n);


		//verificare rand si coloana daca este libera
		cout << "introduceti randul pentru verificare: ";
		cin >> rand;

		cout << "introduceti coloana pentru verificare: ";
		cin >> coloana;


		if (rand < 0 || rand >= n || coloana<0 || coloana>n) {
			throw out_of_range("rand sau coloana gresita!\n");
		}

		if (verificare(board, rand, coloana)) {
			cout << "\nse poate plasa pe randul " << rand << " si coloana " << coloana << "\n";
		}
		else {
			cout << "\nnu se poate plasa pe randul " << rand << " si coloana " << coloana << "\n";
		}

		//eliberare memorie 
		delete[] board;
	}
	catch (const invalid_argument& e) {
		cout << "" << e.what() << endl;
	}
	catch (const out_of_range& e) {
		cout << "" << e.what() << endl;
	}


	return 0;
}