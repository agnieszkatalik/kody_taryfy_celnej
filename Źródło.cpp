#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;



void function(string* data_wystawienia, string* dokument, int* pozycja, string* kontrahent, string* nip, string* nazwa, double* ilosc, double* wartosc_netto_pln, string* kraj, string* kod_celny, double* waga, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (dokument[i] == dokument[j] && dokument[i] != "0")
			{
				if (kraj[i] == kraj[j] && kraj[i] != "0")
				{
					if (kod_celny[i] == kod_celny[j] && kod_celny[i] != "0" && kod_celny[i] != "*")
					{

						ilosc[j] += ilosc[i];
						ilosc[i] = 0;

						wartosc_netto_pln[j] += wartosc_netto_pln[i];
						wartosc_netto_pln[i] = 0;

						waga[j] += waga[i];
						waga[i] = 0;

						nazwa[j] = nazwa[i];


						data_wystawienia[i] = "0";
						dokument[i] = "0";
						pozycja[i] = 0;
						kontrahent[i] = "0";
						nip[i] = "0";
						nazwa[i] = "0";
						ilosc[i] = 0;
						wartosc_netto_pln[i] = 0;
						kraj[i] = "0";
						kod_celny[i] = "0";

					}
				}
			}
			//else

		}
	}
}


void names(string* data_wystawienia, string* dokument, int* pozycja, string* kontrahent, string* nip, string* nazwa, double* ilosc, double* wartosc_netto_pln, string* kraj, string* kod_celny, double* waga, int n){

	static int m = 0; // to bêdzie liczba przedmiotów
	string* tmp = new string[10000];
	bool t = false;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if (tmp[j] == nazwa[i])
				t = true;

		}
		if (t == false)
		{
			tmp[m] = nazwa[i];
			m++;
		}
		t = false;
	}
	string* names = new string[m];
	for (int i = 0; i < m; i++)
	{
		names[i] = tmp[i];
		//cout << names[i] << endl;
	}
	//cout << n << " " << m << endl;
	delete[] tmp;

	//function(data_wystawienia, dokument, pozycja, kontrahent, nip, nazwa, ilosc, wartosc_netto_pln, kraj, kod_celny, waga, names, n, m);
}
/*
void codes(string* data_wystawienia, string* dokument, int* pozycja, string* kontrahent, string* nip, string* nazwa, double* ilosc, double* wartosc_netto_pln, string* kraj, string* kod_celny, double* waga, int n) {

	static int m = 0; // to bêdzie liczba kodó
	string* tmp = new string[10000];
	bool t = false;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m + 1; j++)
		{
			if (tmp[j] == kod_celny[i])
				t = true;

		}
		if (t == false)
		{
			tmp[m] = kod_celny[i];
			m++;
		}
		t = false;
	}
	string* code = new string[m];
	for (int i = 0; i < m; i++)
	{
		code[i] = tmp[i];
		//cout << names[i] << endl;
	}
	//cout << n << " " << m << endl;
	delete[] tmp;

	function(data_wystawienia, dokument, pozycja, kontrahent, nip, nazwa, ilosc, wartosc_netto_pln, kraj, kod_celny, waga, code, n, m);
}*/

int main()
{
	static int n = 0;

	ifstream file;
	file.open("kody.txt", std::ios::in | std::ios::out);
	if (file.good() == false)
	{
		cout << "File failed to open" << endl;
		exit(0);
	}
	else
	{
			string line;
			while (getline(file, line))
			{
				n++;
			}
			//cout << n;
			file.close();

			string* data_wystawienia = new string[n];
			string* dokument = new string[n];
			int* pozycja = new int[n];
			string* nazwa = new string[n];
			string* kontrahent = new string[n];
			string* nip = new string[n];
			double* ilosc = new double[n];
			double* wartosc_netto_pln = new double[n];
			string* kraj = new string[n];
			string* kod_celny = new string[n];
			double* waga = new double[n];
			double* suma_wartosci_faktury = new double[n];
			double* suma_wag_faktury = new double[n];

			file.open("kody.txt", std::ios::in | std::ios::out);

		for(int i=0; i<n; i++)
		{
			//file >> nazwa[i] >> dokument[i] >> kraj[i] >> ilosc[i] >> price_unit_euro >> wartosc_netto_pln[i];
			file >> data_wystawienia[i] >> dokument[i] >> pozycja[i] >> kontrahent[i] >> nip[i] >> nazwa[i] >> ilosc[i] >> wartosc_netto_pln[i] >> kraj[i] >> kod_celny[i] >> waga[i];

			//cout << i << " " << data_wystawienia[i] << " " << dokument[i] << " " << pozycja[i] << " " << kontrahent[i] << " " << nip[i] << " " << nazwa[i] << " " << ilosc[i] << " " << wartosc_netto_pln[i] << " " << kraj[i] << " " << kod_celny[i] << " " << waga[i] << endl;
		}
		//cout << kod_celny[104];

		file.close();

		function(data_wystawienia, dokument, pozycja, kontrahent, nip, nazwa, ilosc, wartosc_netto_pln, kraj, kod_celny, waga, n);
		//codes(data_wystawienia, dokument, pozycja, kontrahent, nip, nazwa, ilosc, wartosc_netto_pln, kraj, kod_celny, waga, n);

		ofstream done("gotowe.txt");
		for (int i = 0; i < n; i++)
		{
			//cout << data_wystawienia[i] << "\t" << dokument[i] << "\t" << pozycja[i] << "\t" << kontrahent[i] << "\t" << nip[i] << "\t" << nazwa[i] << "\t" << ilosc[i] << "\t" << wartosc_netto_pln[i] << "\t" << kraj[i] << "\t" << kod_celny[i] << "\t" << waga[i] << endl;
			done << data_wystawienia[i] <<"\t" << dokument[i] << "\t" << pozycja[i] << "\t" << kontrahent[i] << "\t" << nip[i] << "\t" << nazwa[i] << "\t" << ilosc[i] << "\t" << wartosc_netto_pln[i] << "\t" << kraj[i] << "\t" << kod_celny[i] << "\t" << waga[i] << endl;
		}

		
		delete[] data_wystawienia, dokument, pozycja, kontrahent, nip, nazwa, ilosc, wartosc_netto_pln, kraj, kod_celny, waga;

		done.close();

		fstream done_tmp;
		done_tmp.open("gotowe.txt", ios::in | ios::out);

		if (done_tmp.good() == false)
		{
			cout << "File failed to open" << endl;
			exit(0);
		}

		
		else
		{
			ofstream done("kody_gotowe.txt");

			string linia;
			done << "Data_Wystawienia \t Dokument \t Pozycja \t Kontrahent \t	NIP \t	Nazwa \t	Iloœæ \t	Wartoœæ_Netto_PLN \t	Kraj \t	 Kod_celny \t	Waga" <<endl;

			do
			{
				getline(done_tmp, linia);
				if (linia != "0	0	0	0	0	0	0	0	0	0	0")
				{
					done << linia << endl;
					cout << linia << endl;
				}

			} while (linia != "");

			done.close();
			done_tmp.close();

			remove("gotowe.txt");
		
		}
		
	}

		return 0;

}