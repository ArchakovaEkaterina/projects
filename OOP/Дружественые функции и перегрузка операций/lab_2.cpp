#include "lab_2.h"
#include <string.h>
//нулева€ иницализаци€
Cat::Cat()
{
    name = "Cat";
	playful = 1;
	fed = 0;
	maw="Maw";
}
//--------------------------------------------------------------

//инициализаци€ значени€ми
Cat::Cat(string name, bool playful, int fed, string maw)
{
	this->name = name;
	this->playful = playful;
	this->fed = fed;
	this->maw = maw;
}

Cat operator + (int food, const Cat c)
{
	Cat newCat;
	int newFed;

	if (c.fed == 100)
	{
		cout << "ѕокормить " << c.name << "не удалось" << endl;
		return c;
	}
	newFed = food + c.fed;
	if (newFed > 100) newFed = 100;
	newCat.fed = newFed;

	return newCat;
}

ostream& operator << (ostream& os, const Cat& c)
{
	os << "»м€: " << c.name << ", игрива€" << c.playful << ", накормленна€(в процентах): " << c.fed << ", голос: " << c.maw << endl;
	return os;
}

void Cat::SayMaw() const
{
	cout << name<< ": "<<maw << endl;
}

string Cat::GetName() const
{
	return name;
}
	

