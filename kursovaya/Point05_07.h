#pragma once
#include <string.h>
#include <iostream>
using namespace std;
/*------------------------------------------------------------*/
/*                         Т И П Ы    Д А Н Н Ы Х             */
/*------------------------------------------------------------*/

/*-----------------------  Класс МЕСТОПОЛОЖЕНИЕ ---------------*/
class Location
{
protected:		//предоставляет возможность потомкам (производному 
				//классу) иметь доступ к частным данным
	int X;		//координата X
	int Y;		//координата Y

public:   //эти методы доступны извне всем в программе

	Location(int InitX, int InitY); //конструктор
	~Location();                    //деструктор
	int GetX();						//получить X координату точки
	int GetY();						//получить Y координату точки
};//end class Location

  /*-----------------------  Класс ТОЧКА --------------------------*/
class Point : public Location
{
	// Point - производный класс от Location
	// атрибут public в объявлении производного класса означает
	// возможность вызова любого из полей и методов, унаследованных
	// от Location

protected:	//классам, производным от Point, потребуется доступ
	bool Visible;					//светится точка или нет

public:
	Point(int InitX, int InitY);	//конструктор класса
	virtual ~Point();	// виртуальный деструктор
	bool IsVisible();				//узнать про светимость точки
	void MoveTo(int NewX, int NewY);//переместить фигуру
	void Drag(int Step);			//буксировка фигуры

		//виртуальные функции
	virtual void Show();              //показать фигуру ТОЧКА
	virtual void Hide();              //спрятать фигуру ТОЧКА

};//end class Point



class Animal :public Point
{
protected:
	string Name;
	bool Fed;//сытый или нет
	string Phrase;
public:
	Animal(int InitX, int InitY, string name, bool fed, string phrase);
	virtual ~Animal();

	bool isFed();
	string GetName();
	void Say();
	virtual void Eat();
};

class IAnimal
{
public:
	virtual void Show() = 0;
	virtual void Hide() = 0;

	virtual void Eat() = 0;
	virtual void Hunt() = 0;
};


class Cat : public Animal, virtual public IAnimal
{
protected:
	bool Playful;//игривый или нет
public:
	Cat(int InitX, int InitY, string name, int fed, string phrase, bool playful);	//конструктор класса
	virtual ~Cat();

	virtual	void Show();		//показать 
	virtual	void Hide();		//скрыть 
	void Sniff();
	void Play();
	bool IsPlayful();

	virtual void Eat();
	virtual void Hunt();

};


class Mouse : public Animal, virtual public IAnimal
{
public:
	Mouse(int InitX, int InitY, string name, int fed, string phrase);	//конструктор класса
	virtual ~Mouse();

	virtual	void Show();		//показать 
	virtual	void Hide();		//скрыть 

	virtual void Eat();
	virtual void Hunt();

};

class Mink : public Point
{
protected:
	bool Full;//есть в норке кто- то или нет
public:
	Mink(int InitX, int InitY);	//конструктор класса
	virtual ~Mink();

	virtual	void Show();		//показать 
	virtual	void Hide();		//скрыть 
	void Fill();
	bool is_Full();
};


class Ball : public Point
{
public:
	Ball(int InitX, int InitY);	//конструктор класса
	virtual ~Ball();

	virtual	void Show();		//показать 
	virtual	void Hide();		//скрыть 
};

class Flower : public Point
{
protected:
	bool Opened;//цветок открыт или закрыт
public:
	Flower(int InitX, int InitY);	//конструктор класса
	virtual ~Flower();

	virtual	void Show();		//показать 
	virtual	void Hide();		//скрыть 
	void Turn();//изменить состояние цветка
	bool IsOpened();
};
