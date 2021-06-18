#include <iostream>
#include <windows.h>
#include "lab_2.h"
#include <string.h>
using namespace std;

int main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");

	Cat cat1 ("Richard", 1, 0, "Myaw");
	Cat cat2 ("George", 0, 40, "Mur");

	cat1.SayMaw();

	int food;
	cout << "\nEnter food: ";
	cin >> food;
	string name; 
	cout << endl << "Enter name: ";
	cin >> name;

	if (name == cat1.GetName())
	{
		cat1 = food + cat1;
	}
	else cat2 = food + cat2;
	
	cout << cat1 << endl;
	cout << cat2 << endl;
	
	return 0;
}
