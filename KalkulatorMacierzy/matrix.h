#pragma once
#include <vector>
#include <string>

using namespace std;

//toMatrix dla liczb
vector<vector<char>> toMatrix(int dana)
{
	char text[1000];
	sprintf_s(text, "%d", dana);
	vector<vector<char>> wynik;
	wynik.push_back(vector<char>());
	for (int i = 0; i < strlen(text); i++)
		wynik[0].push_back(text[i]);
	return wynik;
}

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
			for (int elementnr = 0; elementnr < ilosc_kolumn; elementnr++)
			{
				vector<vector<char>> element = toMatrix(dana[wiersz][elementnr]);
				//Dla kazdego znaku elementu
				for (int znak = 0; znak < element[0].size(); znak++)
					wynik[wiersz].push_back(element[0][znak]);
			}
			wynik[wiersz].push_back('|');
		}
		return wynik;
	}
	//toMatrix dla klas klas itd
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
			{
				out.push_back(wynik[i][x]);
			}
			out.push_back('\n');
		}
		return out;
	}
	//operator<<

	//Wymiary macierzy
	int iloscWierszy() { return (*this).size(); }
	int iloscKolumn() { return (*this)[0].size(); }
};

