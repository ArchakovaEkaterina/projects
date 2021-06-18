#pragma once
#include <string.h>
#include <iostream>
using namespace std;
/*------------------------------------------------------------*/
/*                         � � � �    � � � � � �             */
/*------------------------------------------------------------*/

/*-----------------------  ����� �������������� ---------------*/
class Location
{
protected:		//������������� ����������� �������� (������������ 
				//������) ����� ������ � ������� ������
	int X;		//���������� X
	int Y;		//���������� Y

public:   //��� ������ �������� ����� ���� � ���������

	Location(int InitX, int InitY); //�����������
	~Location();                    //����������
	int GetX();						//�������� X ���������� �����
	int GetY();						//�������� Y ���������� �����
};//end class Location

  /*-----------------------  ����� ����� --------------------------*/
class Point : public Location
{
	// Point - ����������� ����� �� Location
	// ������� public � ���������� ������������ ������ ��������
	// ����������� ������ ������ �� ����� � �������, ��������������
	// �� Location

protected:	//�������, ����������� �� Point, ����������� ������
	bool Visible;					//�������� ����� ��� ���

public:
	Point(int InitX, int InitY);	//����������� ������
	virtual ~Point();	// ����������� ����������
	bool IsVisible();				//������ ��� ���������� �����
	void MoveTo(int NewX, int NewY);//����������� ������
	void Drag(int Step);			//���������� ������

		//����������� �������
	virtual void Show();              //�������� ������ �����
	virtual void Hide();              //�������� ������ �����

};//end class Point



class Animal :public Point
{
protected:
	string Name;
	bool Fed;//����� ��� ���
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
	bool Playful;//������� ��� ���
public:
	Cat(int InitX, int InitY, string name, int fed, string phrase, bool playful);	//����������� ������
	virtual ~Cat();

	virtual	void Show();		//�������� 
	virtual	void Hide();		//������ 
	void Sniff();
	void Play();
	bool IsPlayful();

	virtual void Eat();
	virtual void Hunt();

};


class Mouse : public Animal, virtual public IAnimal
{
public:
	Mouse(int InitX, int InitY, string name, int fed, string phrase);	//����������� ������
	virtual ~Mouse();

	virtual	void Show();		//�������� 
	virtual	void Hide();		//������ 

	virtual void Eat();
	virtual void Hunt();

};

class Mink : public Point
{
protected:
	bool Full;//���� � ����� ���- �� ��� ���
public:
	Mink(int InitX, int InitY);	//����������� ������
	virtual ~Mink();

	virtual	void Show();		//�������� 
	virtual	void Hide();		//������ 
	void Fill();
	bool is_Full();
};


class Ball : public Point
{
public:
	Ball(int InitX, int InitY);	//����������� ������
	virtual ~Ball();

	virtual	void Show();		//�������� 
	virtual	void Hide();		//������ 
};

class Flower : public Point
{
protected:
	bool Opened;//������ ������ ��� ������
public:
	Flower(int InitX, int InitY);	//����������� ������
	virtual ~Flower();

	virtual	void Show();		//�������� 
	virtual	void Hide();		//������ 
	void Turn();//�������� ��������� ������
	bool IsOpened();
};
