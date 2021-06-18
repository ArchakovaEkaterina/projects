#pragma once
#include <string.h>
#include <iostream>
#include <windows.h>

using namespace std;
class Cat
{
protected:	
	string name;
	bool playful;
	int fed;//насколько накормленная(в процентах)
	string maw;
public:
	Cat();
	Cat(string name, bool playful, int fed, string maw);	//конструктор класса
	
	string GetName() const;
	void SayMaw() const;
	friend Cat operator + (int food, const Cat c);
	friend ostream& operator << (ostream& os, const Cat& c);

};


