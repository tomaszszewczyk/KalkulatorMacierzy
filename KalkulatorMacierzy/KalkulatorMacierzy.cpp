// KalkulatorMacierzy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

int main()
{
	//Zapisanie czasu startu
	time_t start = time(NULL);
	
	matrix<matrix<matrix<int>>> A(3, 3, matrix<matrix<int>>(3,3,matrix<int>(3,3,2))), B, C;
	//matrix<matrix<int>> A(3, 3, matrix<int>(3,3,2)), B, C;
	//matrix<int> A(3, 3, 2), B, C;
	try
	{
		A[0][0] = matrix<matrix<int>>(3, 3, matrix<int>(3, 3, 3));
		A[1][1] = matrix<matrix<int>>(3, 3, matrix<int>(3, 3, 3));
		A[2][2] = matrix<matrix<int>>(3, 3, matrix<int>(3, 3, 3));

		B = A * 2;
		C = A + B;
		A = B * C;

		cout << "DetA = " << endl << A.det();
	}
	catch (string error)
	{
		cout << error;
	}

	//Raport zako�czenia
	time_t czastrwania = time(NULL) - start;
	cout << endl << endl << "Wykonanie programu zajelo: " << czastrwania << "s" << endl;
	system("PAUSE");
    return 0;
}

