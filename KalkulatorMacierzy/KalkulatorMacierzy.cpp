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
	time_t start = time(NULL);
	
	matrix<matrix<matrix<int>>> A(3, 3, matrix<matrix<int>>(3,3,matrix<int>(3,3,2))), B, C;
	//matrix<matrix<int>> A(3, 3, matrix<int>(3,3,2)), B, C;
	//matrix<int> A(3, 3, 2), B, C;
	try
	{
		B = A * 2;
		B = A * B;
		cout << B;
	}
	catch (string error)
	{
		cout << error;
	}
	time_t czastrwania = time(NULL) - start;
	cout << endl << endl << "Wykonanie programu zajelo: " << czastrwania << "s" << endl;
	system("PAUSE");
    return 0;
}

