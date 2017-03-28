// KalkulatorMacierzy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	matrix<matrix<int>> A(3, 3, matrix<int>(3,3,0)), B;
	B = A;
	cout << A;
	system("PAUSE");
    return 0;
}

