#pragma once
#include <vector>

using namespace std;

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
		{
			for (int i = 0; i < iloscWierszy(); i++)
				for (int x = 0; x < iloscKolumn(); x++)
					(*this)[i][x] = dodawana[i][x];
			return;
		}
		else
		{
			string error = "Dodawanie macierzy o niezgodnych wymiarach!!!\n";
			throw(error);
		}
	}
	//Przeciwienstwo
	matrix<TYP>& operator-() { return (*this)*-1; }
	//Odejmowanie
	matrix<TYP>& operator-(matrix<TYP>& odejmowana) { return (*this)+(-odejmowana); }
	//Mnozenie przez inny typ
	template<class T>
	matrix<TYP>& operator*(T czynnik)
	{
		for (int i = 0; i < iloscWierszy(); i++)
			for (int x = 0; x < iloscKolumn(); x++)
				(*this)[i][x] = dodawana[i][x];
		return;
	}
	//Odwracanie
	//Wyznacznik
	//Transpozycja

	//Przypisanie macierzy

	//Wyœwietlanie macierzy

	//Wymiary macierzy
	int iloscWierszy() { return (*this).size(); }
	int iloscKolumn() { return (*this)[0].size(); }
};

