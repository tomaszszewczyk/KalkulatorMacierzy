#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

string stringer(int dana)
{
	char text[1000];
	sprintf_s(text, "%d", dana);
	return string(text);
}

//toMatrix dla liczb
template<class T>
vector<vector<char>> toMatrix(T& dana)
{
	string text = stringer(dana);
	vector<vector<char>> wynik;
	wynik.push_back(vector<char>());
	for (int i = 0; i < text.size(); i++)
		wynik[0].push_back(text[i]);
	return wynik;
};

template <class TYP>
class matrix : public vector<vector<TYP>>
{
public:
	matrix() : vector<vector<TYP>>(1, vector<TYP>(1)) {}
	matrix(int x, int y, TYP stdelement) : vector<vector<TYP>>(x, vector<TYP>(y, stdelement)) {}
	//Operacje na macierzach

	//Dodawanie
	matrix<TYP>& operator+(matrix<TYP>& dodawana)
	{
		if (iloscWierszy() == dodawana.iloscWierszy() && iloscKolumn() == dodawana.iloscKolumn())
			for (int i = 0; i < iloscWierszy(); i++)
				for (int x = 0; x < iloscKolumn(); x++)
					(*this)[i][x] += dodawana[i][x];
		else
			throw(string error = "Dodawanie macierzy o niezgodnych wymiarach!!!\n");
	}
	//Przeciwienstwo
	matrix<TYP>& operator-() { return (*this)*(-1); }
	//Odejmowanie
	matrix<TYP>& operator-(matrix<TYP>& odejmowana) { return (*this)+(-odejmowana); }
	//Mnozenie przez inny typ
	template<class T>
	matrix<TYP>& operator*(T czynnik)
	{
		for (int i = 0; i < iloscWierszy(); i++)
			for (int x = 0; x < iloscKolumn(); x++)
				(*this)[i][x] *= dodawana[i][x];
		return;
	}
	//Mnozenie przez macierz
	//Odwracanie
	//Wyznacznik
	//Transpozycja

	//Wyœwietlanie macierzy
	//toMatrix dla klas

	template<class T>
	friend vector<vector<char>> toMatrix(matrix<T>& dana)
	{
		const int ilosc_wierszy = dana.iloscWierszy();
		const int ilosc_kolumn = dana.iloscKolumn();
		vector<vector<char>> wynik;
		//Dla kazdego wiersza
		for (int wiersz = 0; wiersz < ilosc_wierszy; wiersz++)
		{
			wynik.push_back(vector<char>());
			wynik[wiersz].push_back('|');
			//Dla kazdego elementu w wierszu
			for (int numer_elementu = 0; numer_elementu < ilosc_kolumn; numer_elementu++)
			{
				vector<vector<char>> element = toMatrix(dana[wiersz][numer_elementu]);
				const int dlugosc_elementu = element[0].size();
				//Dla kazdego znaku elementu
				for (int znak = 0; znak < dlugosc_elementu; znak++)
					wynik[wiersz].push_back(element[0][znak]);
			}
			wynik[wiersz].push_back('|');
		}
		return wynik;
	};
	//toMatrix dla klas klas itd
	template<class T>
	friend vector<vector<char>> toMatrix(matrix<matrix<T>>& dana)
	{
		const int ilosc_wierszy = dana.iloscWierszy();
		const int ilosc_kolumn = dana.iloscKolumn();
		const int ilosc_wierszy_elementu = toMatrix(dana[0][0]).size();
		const int ilosc_kolumn_elementu = toMatrix(dana[0][0])[0].size();

		vector<vector<char>> wynik;
		//Dla kazdego wiersza
		for (int wiersz = 0; wiersz < ilosc_wierszy; wiersz++)
		{
			for (int wiersz_elementu = 0; wiersz_elementu < ilosc_wierszy_elementu+1; wiersz_elementu++)
			{
				wynik.push_back(vector<char>());
				wynik[wiersz*(ilosc_wierszy_elementu+1)+wiersz_elementu].push_back('|');
				wynik[wiersz*(ilosc_wierszy_elementu+1)+wiersz_elementu].push_back(' ');
			}

			//Dla kazdego elementu w wierszu
			for (int numer_elementu = 0; numer_elementu < ilosc_kolumn; numer_elementu++)
			{
				vector<vector<char>> element = toMatrix(dana[wiersz][numer_elementu]);
				const int ilosc_wierszy_elementu = element.size();
				const int ilosc_kolumn_elementu = element[0].size();
				//Dla kazdego wiersza elementu
				for (int wiersz_elementu = 0; wiersz_elementu < ilosc_wierszy_elementu; wiersz_elementu++)
				{
					//Dla kazdej kolumny elementu
					for (int kolumna_elementu = 0; kolumna_elementu < ilosc_kolumn_elementu; kolumna_elementu++)
					{
						wynik[wiersz*(ilosc_wierszy_elementu + 1) + wiersz_elementu].push_back(element[wiersz_elementu][kolumna_elementu]);
					}
					wynik[wiersz*(ilosc_wierszy_elementu + 1) + wiersz_elementu].push_back(' ');
				}
			}
			//Zakonczenia wierszy
			for (int wiersz_elementu = 0; wiersz_elementu < ilosc_wierszy_elementu; wiersz_elementu++)
			{
				wynik.push_back(vector<char>());
				wynik[wiersz*(ilosc_wierszy_elementu + 1) + wiersz_elementu].push_back('|');
			}
			//Pusty wiersz
			const int rozmiar_wiersza = wynik[0].size();
			vector<char>& pusty_wiersz = wynik[(wiersz + 1)*(ilosc_wierszy_elementu + 1)];
			while (pusty_wiersz.size() != rozmiar_wiersza-1)
				pusty_wiersz.push_back(' ');
			pusty_wiersz.push_back('|');
		}
		wynik.pop_back();
		return wynik;
	};

	//toString
	string toString()
	{
		vector<vector<char>> wynik = toMatrix(*this);
		string out;
		//Dla kazdego wiersz
		for (int i = 0; i < wynik.size(); i++)
		{
			//Dla kazdego elementu
			for (int x = 0; x < wynik[i].size(); x++)
				out.push_back(wynik[i][x]);
			out.push_back('\n');
		}
		return out;
	}
	//operator<<
	template <class T>
	friend ostream& operator<<(ostream& output, matrix<T> dane)
	{
		output << dane.toString();
		return output;
	};

	//Wymiary macierzy
	int iloscWierszy() { return (*this).size(); }
	int iloscKolumn() { return (*this)[0].size(); }
};

