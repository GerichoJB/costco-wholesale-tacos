// TempDriver.cpp : Defines the entry point for the console application.
// Gericho Ball U65224655
// TempDriver.cpp takes in sets of values, ints, doubles, strings, and 
// distances, (input as feet, inches) and determines which of the two is
// the greatest and the least

#include "stdafx.h"
#include "FeetInches.h"
#include <iostream>
#include <string>
using namespace std;

//Templates for greater and lesser functions
template <class T>
T greater(T n1, T n2) {
	if (n1 < n2)
	{
		return n2;
	}
	else
	{
		return n1;
	}
}
template <class T>
T lesser(T n1, T n2) {
	if (n1 > n2)
	{
		return n2;
	}
	else
	{
		return n1;
	}
}

int main()
{
	// variable declarations
	int intVal, intVal2;
	double douVal, douVal2;
	string sVal, sVal2;
	int f1i, f2i, f1f, f2f;
	//input and output for the above variables
	cout << "Enter two intigers: ";
	cin >> intVal >> intVal2;
	cout << "The minimum of " << intVal << " and " << intVal2 << " is: " << lesser(intVal, intVal2) <<endl;
	cout << "The maximum of " << intVal << " and " << intVal2 << " is: " << greater(intVal, intVal2) << endl;
	cout << "Enter two doubles: ";
	cin >> douVal >> douVal2;
	cout << "The minimum of " << douVal << " and " << douVal2 << " is: " << lesser(douVal, douVal2) << endl;
	cout << "The maximum of " << douVal << " and " << douVal2 << " is: " << greater(douVal, douVal2) << endl;
	cout << "Enter two strings: ";
	cin >> sVal >> sVal2;
	cout << "The minimum of " << sVal << " and " << sVal2 << " is: " << lesser(sVal, sVal2) << endl;
	cout << "The maximum of " << sVal << " and " << sVal2 << " is: " << greater(sVal, sVal2) << endl;
	//constructs obj with input from user as values
	FeetInches f1{};
	FeetInches f2{};
	cout << "Enter the first distance (in feet, inches format): ";
	cin >> f1;
	cout << "Enter the second distance (in feet, inches format): ";
	cin >> f2;
	//output to state which is greatest, and which is least
	cout << "The minimum of " << f1 << " and " << f2 << " is: " << lesser(f1, f2) << endl;
	cout << "The maximum of " << f1 << " and " << f2 << " is: " << greater(f1, f2) << endl;
	system("pause");
    return 0;
}

