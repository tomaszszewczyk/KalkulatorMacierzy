#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

//Zamiana int na string
string stringer(int dana)
{
	char text[1000];
	sprintf_s(text, "%d", dana);
	return string(text);
}

//Zamiana float na string
string stringer(float dana)
{
	char text[1000];
	sprintf_s(text, "%f", dana);
	return string(text);
}

//Zamiana double na string
string stringer(double dana)
{
	char text[1000];
	sprintf_s(text, "%f", dana);
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
	//Kontruktory
	matrix() : vector<vector<TYP>>(1, vector<TYP>(1)) {}
	matrix(int x, int y) : vector<vector<TYP>>(x, vector<TYP>(y)) {}
	matrix(int x, int y, TYP stdelement) : vector<vector<TYP>>(x, vector<TYP>(y, stdelement)) {}
	
	//Operacje na macierzach
	//Dodawanie
	matrix<TYP> operator+(matrix<TYP> dodawana)
	{
		matrix<TYP> wynik = (*this);
		if (iloscWierszy() == dodawana.iloscWierszy() && iloscKolumn() == dodawana.iloscKolumn())
			for (int i = 0; i < iloscWierszy(); i++)
				for (int x = 0; x < iloscKolumn(); x++)
					wynik[i][x] += dodawana[i][x];
		else
			throw(string("Dodawanie macierzy o niezgodnych wymiarach!!!\n"));
		return wynik;
	}
	matrix<TYP> operator+= (matrix<TYP> dodawana)
	{
		return (*this) + dodawana;
	}

	//Przeciwienstwo
	matrix<TYP> operator-() { return (*this)*(-1); }
	//Odejmowanie
	matrix<TYP> operator-(matrix<TYP>& odejmowana) { return (*this)+(-odejmowana); }

	//Mnozenie przez inny typ (przez skalar)
	template<class T>
	matrix<TYP> operator*(T czynnik)
	{
		matrix<TYP> wynik = (*this);
		for (int i = 0; i < iloscWierszy(); i++)
			for (int x = 0; x < iloscKolumn(); x++)
				wynik[i][x] *= czynnik;
		return wynik;
	}
	template<class T>
	matrix<TYP> operator*=(T czynnik) { return (*this)*czynnik; }

	//Mnozenie przez macierz
	matrix<TYP> operator*(matrix<TYP> czynnik)
	{
		if (czynnik.iloscWierszy() != iloscKolumn() || czynnik.iloscKolumn() != iloscWierszy())
		{
			string error = "Niezgodnoœæ wymiarow mnozonych macierzy.";
			throw(error);
		}
		
		matrix<TYP> wynik(iloscWierszy(), czynnik.iloscKolumn(), TYP());
		TYP tmp;
		for (int i = 0; i < wynik.iloscWierszy(); i++) //Dla ka¿dego wiersza wyniku
			for (int x = 0; x < wynik.iloscKolumn(); x++)	//Dla ka¿dej komórki wyniku
			{
				int y = 0;
				wynik[i][x] = (*this)[i][y] * czynnik[y][x];
				y++;
				for (; y < iloscKolumn(); y++) //Dla kazdej kolumny this lub wiersza czynnik
					wynik[i][x] += (*this)[i][y] * czynnik[y][x];
			}
		return wynik;
	}

	//Odwracanie
	//Wyznacznik
	TYP det()
	{
		if (iloscWierszy() != iloscKolumn())
			throw("Nie mozna obliczyc wyznacznika macierzy niekwadratowej!");

		const int n = iloscKolumn();
		if (n == 1)
			return (*this)[0][0];
		else
		{
			matrix<TYP> tmp = (*this);
			tmp.erase(tmp.begin());
			for (int x = 0; x < tmp.size(); x++)
				tmp[x].erase(tmp[x].begin());
			TYP wynik = (*this)[0][0] * tmp.det();

			for (int i = 1; i < n; i++)
			{
				tmp = (*this);
				tmp.erase(tmp.begin()+i);
				for (int x = 0; x < tmp.size(); x++)
					tmp[x].erase(tmp[x].begin());
				wynik += (*this)[i][0] * tmp.det() * static_cast<int>(pow(-1, i));
			}
			return wynik;
		}

	}

	//Transpozycja
	matrix<TYP> transp()
	{
		matrix<TYP> wynik(iloscKolumn(), iloscWierszy());
		for (int i = 0; i < iloscWierszy(); i++)
			for (int x = 0; x < iloscKolumn(); x++)
				wynik[x][i] = (*this)[i][x];
		return wynik;
	}

	//Wyœwietlanie macierzy
	//toMatrix dla klas
	template<class T>
	friend vector<vector<char>> toMatrix(matrix<T>& dana);
	//toMatrix dla klas klas itd
	template<class T>
	friend vector<vector<char>> toMatrix(matrix<matrix<T>>& dana);

	//Wygodne wyswietlanie macierzy
	//Zamiana macierzy na string
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
	friend ostream& operator<<(ostream& output, matrix<T> dane);

	//Wymiary macierzy
	size_t iloscWierszy() { return (*this).size(); }
	size_t iloscKolumn() { return (*this)[0].size(); }
};

template <class T>
ostream& operator<<(ostream& output, matrix<T> dane)
{
	output << dane.toString();
	return output;
};

template<class T>
vector<vector<char>> toMatrix(matrix<T>& dana)
{
	const size_t ilosc_wierszy = dana.iloscWierszy();
	const size_t ilosc_kolumn = dana.iloscKolumn();
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
			const size_t dlugosc_elementu = element[0].size();
			//Dla kazdego znaku elementu
			for (int znak = 0; znak < dlugosc_elementu; znak++)
				wynik[wiersz].push_back(element[0][znak]);
			wynik[wiersz].push_back(' ');
		}
		wynik[wiersz].pop_back();
		wynik[wiersz].push_back('|');
	}
	return wynik;
}

template<class T>
vector<vector<char>> toMatrix(matrix<matrix<T>>& dana)
{
	const size_t ilosc_wierszy = dana.iloscWierszy();
	const size_t ilosc_kolumn = dana.iloscKolumn();
	const size_t ilosc_wierszy_elementu = toMatrix(dana[0][0]).size();
	const size_t ilosc_kolumn_elementu = toMatrix(dana[0][0])[0].size();

	vector<vector<char>> wynik;
	//Dla kazdego wiersza
	for (int wiersz = 0; wiersz < ilosc_wierszy; wiersz++)
	{
		for (int wiersz_elementu = 0; wiersz_elementu < ilosc_wierszy_elementu + 1; wiersz_elementu++)
		{
			wynik.push_back(vector<char>());
			wynik[wiersz*(ilosc_wierszy_elementu + 1) + wiersz_elementu].push_back('|');
			wynik[wiersz*(ilosc_wierszy_elementu + 1) + wiersz_elementu].push_back(' ');
		}

		//Dla kazdego elementu w wierszu
		for (int numer_elementu = 0; numer_elementu < ilosc_kolumn; numer_elementu++)
		{
			vector<vector<char>> element = toMatrix(dana[wiersz][numer_elementu]);
			const size_t ilosc_wierszy_elementu = element.size();
			const size_t ilosc_kolumn_elementu = element[0].size();
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
		const size_t rozmiar_wiersza = wynik[0].size();
		vector<char>& pusty_wiersz = wynik[(wiersz + 1)*(ilosc_wierszy_elementu + 1) - 1];
		while (pusty_wiersz.size() != rozmiar_wiersza - 1)
			pusty_wiersz.push_back(' ');
		pusty_wiersz.push_back('|');
	}
	wynik.resize(ilosc_wierszy*(ilosc_wierszy_elementu+1)-1);
	return wynik;
};