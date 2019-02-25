// Gericho Ball U65224655 
// FeetInches.h is the header file for a class that holds feet & inches
// the file also overloads some of the operators to make working with sets
// of two numbers easier to do

#pragma once
#include <iostream>
using namespace std;
#ifndef FEETINCHES_H
#define FEETINCHES_H
// The FeetInches class holds distances or measurements 
// expressed in feet and inches.
class FeetInches
{
private:
	int feet;        
	// To hold a number of feet
	int inches;      
	// To hold a number of inches
public:
	// Constructor
	FeetInches(int f = 0, int i = 0)
	{ feet = f;
	inches = i;
	}
	// Mutator functions
	void setFeet(int f)
	{ feet = f; }

	void setInches(int i)
	{ inches = i;}
	
	// Accessor functions
	int getFeet() const
	{ return feet; }

	int getInches() const
	{ return inches; }
	
	// Overloaded operator functions
	bool FeetInches::operator > (const FeetInches &right) // Overloaded >
	{
		bool p;
		if (feet > right.feet) {
			p = true;
		}

		else if (feet == right.feet && inches > right.inches)
		{
			p = true;
		}

		else {
			p = false;
		}
		return p;
	}

	bool FeetInches::operator < (const FeetInches &right) // Overloaded <
	{
		bool q;
		if (feet < right.feet) {
			q = true;
		}

		else if (feet == right.feet && inches < right.inches)
		{
			q = true;
		}

		else
		{
			q = false;
		}
		return q;
	}

	//overload the operator <<
	friend ostream &operator <<  (ostream& os, const FeetInches&fraction) {
		os << fraction.feet << " feet , " << fraction.inches << " inches";
		return os;
	}
	//overload the operator >>
	friend istream &operator >> (istream &is, FeetInches&fraction) {
		char ch;
		is >> fraction.feet;
		is >> fraction.inches;
		return is;
	}
};
#endif