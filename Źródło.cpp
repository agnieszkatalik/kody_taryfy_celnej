#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

#define n 12749 // iloœæ linii fileu

void function(int *custom_code, int *qnt, string *item_name, string *country_of_origin, double *value_eur, string *name)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (custom_code[i] == custom_code[j] && custom_code[i] != 0)
			{
				if (country_of_origin[i] == country_of_origin[j] && country_of_origin[i] != "0")
				{
					if (item_name[i] == item_name[j] && item_name[i] != "0")
					{
						qnt[j] += qnt[i];
						qnt[i] = 0;

						value_eur[j] += value_eur[i];
						value_eur[i] = 0;

						custom_code[i] = 0;
						item_name[i] = "0";
						country_of_origin[i] = "0";
					}
					else if (item_name[i] != "0")
					{
						qnt[j] += qnt[i];
						qnt[i] = 0;

						value_eur[j] += value_eur[i];
						value_eur[i] = 0;

						custom_code[i] = 0;
						for (int l = 0; l < 38; l++)
						{
							size_t found_j = item_name[j].find(name[l]);
							size_t found_i = item_name[i].find(name[l]);
							if (found_i != string::npos && found_j != string::npos)
							{
							}

							else if (found_i != string::npos)
							{
								item_name[j] += ", " + name[l];

							}

						}
						item_name[i] = "0";

						country_of_origin[i] = "0";
					}
				}
			}
		}
	}
}

int main()
{

	int* custom_code = new int[n];
	int* qnt = new int[n];
	string* item_name = new string[n];
	string* country_of_origin = new string[n];
	double* value_eur = new double[n];
	double price_unit_euro;
	string name[38] = { "NIGHTWEAR","UNDERWEAR", "JACKET", "LEGGINGS", "T-SHIRT", "PANTS", "SET", "SORTS", "BEACHWEAR", "CARDIGAN", "SHIRT", "SKIRT", "SWEATSHIRT", "0", "VEST", "SWEATER", "DRESS", "BODY", "TRACKSUIT", "BABY_BIB", "TOP", "CAP", "SOCKS", "SHOES", "BAG", "BELT", "SCARF", "TIE", "ACCESSORIES", "OVERAL", "MAJICA", "BATHROBE", "SUIT", "COAT", "WALLET", "BLAZER", "A", "BABY_SUIT" };

	int i = 0;

	ifstream file;
	file.open("kody.txt", std::ios::in | std::ios::out);
	if (file.good() == false)
	{
		cout << "File failed to open" << endl;
		exit(0);
	}
	else
	{

		for(int i=0; i<n; i++)
		{
			file >> item_name[i] >> custom_code[i] >> country_of_origin[i] >> qnt[i] >> price_unit_euro >> value_eur[i];
		}
		price_unit_euro = 0;

		file.close();

	}

	function(custom_code, qnt, item_name, country_of_origin, value_eur, name);

	ofstream done("gotowe.txt");
	for (int i = 0; i < n; i++)
	{
		//cout << i << ": " << item_name[i] << " " << custom_code[i] << " " << country_of_origin[i] << " " << qnt[i] << " " << value_eur[i] << endl;
		done << item_name[i] << "\t" << custom_code[i] << "\t" << country_of_origin[i] << "\t" << qnt[i] << "\t" << value_eur[i] << endl;
	}
	
	delete [] custom_code, qnt, item_name, country_of_origin, value_eur, name;

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
			do
			{
				getline(done_tmp, linia);
				if (linia != "0	0	0	0	0")
				{
					done << linia << endl;
					cout << linia << endl;
				}

			} while (linia != "");

			done.close();
			done_tmp.close();

			remove("gotowe.txt");
	}
	
	return 0;

}