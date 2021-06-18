#include <windows.h>
#include "Point05_07.h"	//���������� �������
#include <string.h>
#include <iostream>
using namespace std;


int func(int x0, int x1, int y1, int x2, int y2)//������� ���������� ������� �� ���������� �� �����
{
	return int(((x0 - x1) * (y2 - y1)) / (x2 - x1) + y1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*            ���������� ���������� � ���������                */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//���������� ���������� ����� � ���� ������:
// Point05_04.cpp � Ex05_04_Con_Virt.cpp
//������� ��������� ���������� ����������
extern HDC hdc;      // �������  �������� ����������

// ������ ��� �������� ��������� ���������� � �� �������
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*----------------------------------------------------------*/
/*             � � � � � � � � � �    � � � � � � �         */
/*----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*        ������ ������ Location          */
/*----------------------------------------*/
//�����������
Location::Location(int InitX, int InitY)
{
	//������������� �������� ���������� ������ ������
	X = InitX;
	Y = InitY;
};//end Location::Location()

  //����������
Location::~Location(void)  //��������� ������ ����
{
};//end Location::~Location()

  //�������� X ���������� �����
int Location::GetX(void)
{
	return X;
};//end Location::GetX()	

  //�������� Y ���������� �����
int Location::GetY(void)
{
	return Y;
}; //end Location::GetY()


/*-------------------------------------------------------------*/
/*        ������ ������ Point             */
/*----------------------------------------*/
//�����������
//��� ������������� �������� ����� ���������� ����������� ������
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//������������� �������� ���������� ������ ������
	Visible = false;
}//end Point::Point()


 //--------------------------------------------------------------
 //����������
Point::~Point(void)   //��������� ������ ����
{
}//end Point::~Point()

 //--------------------------------------------------------------
 //�������� �����
void Point::Show(void)
{
	Visible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	//������ ������� ������
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	// 4 ����� ��� ��������
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//end Point::Show()

 //--------------------------------------------------------------
 //������ �����
void Point::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 0));//������ ����� ������ ��� ����
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));
}//end Point::Hide()

 //--------------------------------------------------------------
 //������ ��� ���������� �����
bool Point::IsVisible(void)
{
	return Visible;
};//end Point::IsVisible()

//--------------------------------------------------------------
//����������� �����
void Point::MoveTo(int NewX, int NewY)
{
	Hide();		//������� ����� ���������
	X = NewX;	//�������� ���������� �����
	Y = NewY;
	Show();		//�������� ����� �� ����� �����
};//end Point::MoveTo()

 //-------------------------------------------------------------------
//���������� ������
void Point::Drag(int Step)
{
	int FigX, FigY;   //����� ���������� ������

	FigX = GetX();    //�������� ��������� ��������� ������
	FigY = GetY();

	while (1)	//����������� ���� ���������� ������
	{
		if (KEY_DOWN(48))     //����� ������ 27
			break;

		//����������� �������� �������

		if (KEY_DOWN(VK_LEFT)) //������� �����  37
		{
			FigX -= Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_RIGHT)) //������� ������  39
		{
			FigX += Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_DOWN)) //������� ����  40
		{
			FigY += Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_UP)) //������� �����  38
		{
			FigY -= Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if
	}   //while
}//end Drag()



/*-------------------------------------------------------------*/
/*        ������ ������ Animal             */
/*----------------------------------------*/
Animal::Animal(int InitX, int InitY, string name, bool fed, string phrase) :Point(InitX, InitY)//�������������
{
	this->Name = name;
	this->Fed = fed;
	this->Phrase = phrase;
}


Animal::~Animal(void)//����������
{

}

void Animal::Say()//�������� ������ ���� ����
{
	cout << Name << ": " << Phrase << endl;
}

string Animal::GetName()//�������� ��� ���������
{
	return Name;
}

bool Animal::isFed()//��������� ���������
{
	return this->Fed;
}

void Animal::Eat()//�������� ������� ��� �����
{
	Hide();
	this->Fed = !(this->Fed);
	Show();
}



/*-------------------------------------------------------------*/
/*        ������ ������ Cat                */
/*----------------------------------------*/

//������������� ����������
Cat::Cat(int InitX, int InitY, string name, int fed, string phrase, bool playful) :Animal(InitX, InitY, name, fed, phrase)
{
	this->Playful = playful;
}

Cat::~Cat(void)
{

}

//�������� ����� � ����� �� �������
void Cat::Show(void)
{
	Visible = true;

	// ������� ���� � ���� ���� - �������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN YellowPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 50));
	HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 50));
	SelectObject(hdc, Brush);

	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������
	Ellipse(hdc, X - 50, Y - 50, X, Y);//������


	//������������
	POINT poly[3];

	poly[0].x = X - 20;
	poly[0].y = Y - 50;

	poly[1].x = X;
	poly[1].y = Y - 60;

	poly[2].x = X;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//������ ���
	SelectObject(hdc, Pen);
	Polygon(hdc, poly, 3);//������ ���
	SelectObject(hdc, Brush);

	poly[0].x = X - 35;
	poly[0].y = Y - 48;

	poly[1].x = X - 50;
	poly[1].y = Y - 60;

	poly[2].x = X - 50;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//����� ���

	SelectObject(hdc, Pen);
	Polygon(hdc, poly, 3);//����� ���
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������
	Ellipse(hdc, X - 50, Y - 50, X, Y);//������
	//��������� �����
	POINT pt;

	//�����
	//� ������� ����� ����� ������(�����), � ��������� - �� ���������
	if (this->Playful == 1)
	{
		MoveToEx(hdc, X + 100, Y, &pt);
		LineTo(hdc, X + 110, Y - 60);
	}
	else
	{
		MoveToEx(hdc, X + 100, Y - 5, &pt);
		LineTo(hdc, X + 170, Y - 30);
	}

	//������ �������� ����
	MoveToEx(hdc, X - 20, Y + 15, &pt);
	LineTo(hdc, X - 35, Y + 60);

	//����� �������� ����
	MoveToEx(hdc, X - 10, Y + 20, &pt);
	LineTo(hdc, X - 25, Y + 80);

	//������ ������ ����
	MoveToEx(hdc, X + 75, Y + 23, &pt);
	LineTo(hdc, X + 80, Y + 60);

	//����� ������ ����
	MoveToEx(hdc, X + 90, Y + 20, &pt);
	LineTo(hdc, X + 100, Y + 80);


	//����� � ���
	SelectObject(hdc, BluePen);
	Ellipse(hdc, X - 15-2, Y - 23-2, X - 18-2, Y - 30-2);
	Ellipse(hdc, X - 33-2, Y - 23-2, X - 30-2, Y - 30-2);


	SetPixel(hdc, X - 25, Y - 23+2, RGB(0, 0, 0));
	SetPixel(hdc, X - 25, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 27, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 27, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 28, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 28, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 23, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 23, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 24, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 24, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 25, Y - 23+2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 25, Y - 22+2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 23+2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 22+2 + 2, RGB(0, 0, 0));

	SelectObject(hdc, YellowPen);
	Rectangle(hdc, 900, 40, 950, 60);

	//������ �����: ���� ��� �����, �� �������� ����������� �������������, ��� - �������������
	if (this->Fed == true)
	{
		SelectObject(hdc, YellowBrush);
	}
	else
	{
		SelectObject(hdc, BlackBrush);
	}
	Rectangle(hdc, 900, 40, 950, 60);


	// ��������� ���� ��������� �������  
	DeleteObject(Pen);
	DeleteObject(BluePen);
	DeleteObject(Brush);
	DeleteObject(YellowPen);
	DeleteObject(YellowBrush);
	DeleteObject(BlackBrush);
}//end  Cat::Show()


//������ ����� - ������ ����� ������ ����
void Cat::Hide(void)
{
	Visible = false;

	// ������� ���� � ���� ���� - ������
	HPEN Pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Brush);	//������� ���� ��������

	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������
	SelectObject(hdc, Pen);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������

	Ellipse(hdc, X - 50, Y - 50, X, Y);//������


	//��������� �����
	POINT pt;

	//�����
	if (this->Playful == 1)
	{
		MoveToEx(hdc, X + 100, Y, &pt);
		LineTo(hdc, X + 110, Y - 60);
	}
	else
	{
		MoveToEx(hdc, X + 100, Y - 5, &pt);
		LineTo(hdc, X + 170, Y - 30);
	}

	//������ �������� ����
	MoveToEx(hdc, X - 20, Y + 15, &pt);

	LineTo(hdc, X - 35, Y + 60);

	//����� �������� ����
	MoveToEx(hdc, X - 10, Y + 20, &pt);
	LineTo(hdc, X - 25, Y + 80);

	//������ ������ ����
	MoveToEx(hdc, X + 75, Y + 23, &pt);
	LineTo(hdc, X + 80, Y + 60);

	//����� ������ ����
	MoveToEx(hdc, X + 90, Y + 20, &pt);
	LineTo(hdc, X + 100, Y + 80);


	//������������
	POINT poly[3];

	poly[0].x = X - 20;
	poly[0].y = Y - 50;

	poly[1].x = X;
	poly[1].y = Y - 60;

	poly[2].x = X;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//������ ���

	poly[0].x = X - 35;
	poly[0].y = Y - 48;

	poly[1].x = X - 50;
	poly[1].y = Y - 60;

	poly[2].x = X - 50;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//����� ���

	//����� � ���
	Ellipse(hdc, X - 15 - 2, Y - 23 - 2, X - 18 - 2, Y - 30 - 2);
	Ellipse(hdc, X - 33 - 2, Y - 23 - 2, X - 30 - 2, Y - 30 - 2);


	SetPixel(hdc, X - 25, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 25, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 27, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 27, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 28, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 28, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 23, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 23, Y - 22 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 24, Y - 23 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 24, Y - 22 + 2, RGB(0, 0, 0));

	SetPixel(hdc, X - 25, Y - 23 + 2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 25, Y - 22 + 2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 23 + 2 + 2, RGB(0, 0, 0));
	SetPixel(hdc, X - 26, Y - 22 + 2 + 2, RGB(0, 0, 0));

	SelectObject(hdc, Brush);	//������� ���� ��������
	Rectangle(hdc, 900, 40, 950, 60);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������
	SelectObject(hdc, Pen);	//������� ���� ��������
	Rectangle(hdc, 900, 40, 950, 60);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//��������


	// ��������� ���� ��������� �������  
	DeleteObject(Pen);
	DeleteObject(Brush);
}//end Cat::Hide()


//��� ������� ������ ������ � ���� �������
void Cat::Sniff()
{
	this->Hide();
	this->Playful = 1;
	this->Show();
};

//������ ���� ��������� ����
bool Cat::IsPlayful()
{
	return this->Playful;
}

//��� ������ - ������ ���������
void Cat::Play()
{
	Hide();
	this->Playful = !(this->Playful);
	Show();
};

//��� �������� - ���� � �����
void Cat::Hunt(void)
{
	if (GetX() != 50 && GetY() != 90)
	{
		if (GetX() > 50 + 200)// � ����� � �������� ������ ���� ��� ����, ����� ���������� ����� �� �������� � ����������� �� �� ��������������
		{
			if ((this->Playful == 1) && (this->Fed == 0))//���� ��� ������� � ��������, �� � ���� ��� ������
			{
				MoveTo(GetX() - 15, func(GetX() - 15, GetX(), GetY(), 50, 90));
			}
			else
			{
				MoveTo(GetX() - 10, func(GetX() - 10, GetX(), GetY(), 50, 90));
			}
		}
		else
		{
			if ((this->Playful == 1) && (this->Fed == 0))//���� ��� ������� � ��������, �� � ���� ��� ������
			{
				MoveTo(GetX() - 10, func(GetX() - 10, GetX(), GetY(), 50, 90));
			}
			else
			{
				MoveTo(GetX() - 7, func(GetX() - 7, GetX(), GetY(), 50, 90));
			}
		}

		Sleep(100);
	}

};

//��� ��� - ������ ������� � ���������
void Cat::Eat()
{
	Hide();
	this->Fed = !(this->Fed);
	this->Playful = !(this->Playful);
	Show();
}

/*-------------------------------------------------------------*/
/*        ������ ������ Mouse             */
/*----------------------------------------*/
Mouse::Mouse(int InitX, int InitY, string name, int fed, string phrase) :Animal(InitX, InitY, name, fed, phrase)
{

}

Mouse::~Mouse(void)
{

}


void Mouse::Show()
{
	Visible = true;

	// ������� ���� � ���� ����
	HPEN GreyPen = CreatePen(PS_SOLID, 2, RGB(206, 206, 206));
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH GreyBrush = CreateSolidBrush(RGB(187, 187, 187));
	HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, BlackPen);	//������� ���� ��������

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//��������
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//����� ���
	//Ellipse(hdc, X -5 , Y-5 , X+8 , Y-17 );//������ ���

	//����� � ���
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//����� ����
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//���
	//Ellipse(hdc, X + 5 , Y+2 , X + 10 , Y-3 );//������ ����
	//Ellipse(hdc, X + 12, Y +3, X + 17 , Y-3 );//���

	SelectObject(hdc, GreyBrush);	//������� ���� ��������

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//��������
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//����� ���
	//Ellipse(hdc, X -5 , Y-5 , X+8 , Y-17 );//������ ���

	//����� � ���
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//����� ����
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//���
	//Ellipse(hdc, X + 5 , Y+2 , X + 10 , Y-3 );//������ ����
	//Ellipse(hdc, X + 12, Y +3, X + 17 , Y-3 );//���

	SelectObject(hdc, GreyPen);
	//��������� �����
	POINT pt;

	//�����
	//���� ���� ��������, �� � ��� ����� ������, ����� - �������������
	if (this->Fed == 0)
	{
		MoveToEx(hdc, X + 10, Y, &pt);
		LineTo(hdc, X + 20, Y - 10);
	}
	else
	{
		MoveToEx(hdc, X + 10, Y, &pt);
		LineTo(hdc, X + 25, Y);
	}
	//MoveToEx(hdc, X - 25 , Y , &pt);
	//LineTo(hdc, X - 40 , Y );

	// ��������� ���� ��������� �������  
	DeleteObject(GreyPen);
	DeleteObject(BlackPen);
	DeleteObject(BlackBrush);
	DeleteObject(GreyBrush);
	DeleteObject(WhiteBrush);
};


void Mouse::Hide()
{
	Visible = false;

	// ������� ���� � ���� ����
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, BlackBrush);	//������� ���� ��������

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//��������
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//����� ���
	//Ellipse(hdc, X - 25 , Y - 10, X + 15, Y + 10);//��������
	//Ellipse(hdc, X - 5 , Y - 5 , X + 8 , Y - 17 );//������ ���


	//����� � ���
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//����� ����
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//���
	//Ellipse(hdc, X + 5, Y + 2 , X + 10, Y - 3);//������ ����
	//Ellipse(hdc, X + 12, Y + 3, X + 17, Y - 3);//���

	SelectObject(hdc, BlackPen);

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//��������
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//����� ���
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//����� ����
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//���

	//Ellipse(hdc, X - 25 , Y - 10, X + 15 , Y + 10);//��������
	//Ellipse(hdc, X - 5 , Y - 5 , X + 8 , Y - 17 );//������ ���
	//Ellipse(hdc, X + 5 , Y + 2 , X + 10 , Y - 3 );//������ ����
	//Ellipse(hdc, X + 12, Y + 3 , X + 17 , Y - 3 );//���

	//��������� �����
	POINT pt;

	//�����
	if (this->Fed == 0)
	{
		MoveToEx(hdc, X + 10, Y, &pt);
		LineTo(hdc, X + 20, Y - 10);
	}
	else
	{
		MoveToEx(hdc, X + 10, Y, &pt);
		LineTo(hdc, X + 25, Y);
	}
	//MoveToEx(hdc, X - 25, Y , &pt);
	//LineTo(hdc, X - 40 , Y);

	// ��������� ���� ��������� �������  
	DeleteObject(BlackPen);
	DeleteObject(BlackBrush);
};

//���� ������� �� �����
void Mouse::Hunt()
{
	Show();
	//��� ���������� ��������, ����� ��������� x
	if (GetX() > 50 && GetY() > 90)
	{
		if (GetX() > 50 + 200)
		{
			MoveTo(GetX() - 13, func(GetX() - 13, GetX(), GetY(), 50, 90));
		}
		else
		{
			MoveTo(GetX() - 10, func(GetX() - 10, GetX(), GetY(), 50, 90));
		}
		Sleep(80);
	}
	else
	{
		//���� ��������� ����� ��� �� ������ � ������ - ��������� ����� �����
		if (GetX() > 50 && GetY() <= 90)
		{
			MoveTo(GetX() - 10, 90);
		}
		if (GetX() <= 50 && GetY() <= 90)
		{
			MoveTo(50, 90);
		}
		if (GetX() < 50 && GetY() >= 90)
		{
			MoveTo(50, func(GetX() - 13, GetX(), GetY(), 50, 90));
		}
	}
};

//���� ��� - ������ �������
void Mouse::Eat()
{
	Hide();
	this->Fed = !(this->Fed);
	Show();
}
/*-------------------------------------------------------------*/
/*        ������ ������	Mink               */
/*----------------------------------------*/
//� ���� �� ��������� ������ ���
Mink::Mink(int InitX, int InitY) :Point(InitX, InitY)
{
	this->Full = false;
};


Mink::~Mink(void)
{

};


void Mink::Show()
{
	Visible = true;

	// ������� ���� � ���� ����
	HPEN LightPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 150));
	HPEN DarkPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH LightBrush = CreateSolidBrush(RGB(0, 0, 255));

	//���� ������ ��� � ����� - ���� ������ ����� �����, ����� �������
	if (this->is_Full() == false)
	{
		SelectObject(hdc, LightPen);	//������� ���� ��������
	}
	else
	{
		SelectObject(hdc, RedPen);	//������� ���� ��������
	}
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, LightBrush);	//������� ���� ��������
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, Brush);	//������� ���� ��������
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);
	SelectObject(hdc, DarkPen);	//������� ���� ��������
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);

	DeleteObject(LightPen);
	DeleteObject(RedPen);
	DeleteObject(DarkPen);
	DeleteObject(Brush);
	DeleteObject(LightBrush);
};


void Mink::Hide()
{
	Visible = false;

	// ������� ���� � ���� ����
	HPEN DarkPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, DarkPen);	//������� ���� ��������
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, Brush);	//������� ���� ��������
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);
	SelectObject(hdc, DarkPen);	//������� ���� ��������
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);

	DeleteObject(DarkPen);
	DeleteObject(Brush);
};

//������ ������������� �����
void Mink::Fill()
{
	this->Full = !this->Full;
};


bool Mink::is_Full()
{
	return this->Full;
}

/*-------------------------------------------------------------*/
/*        ������ ������ Ball              */
/*----------------------------------------*/
Ball::Ball(int InitX, int InitY) :Point(InitX, InitY)
{

};


Ball::~Ball(void)
{

};


void Ball::Show()
{
	Visible = true;

	// ������� ���� � ���� ����
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(100, 255, 100));
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));


	SelectObject(hdc, BlackPen);	//������� ���� ��������
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Brush);	//������� ���� ��������
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Pen);	//������� ���� ��������
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	DeleteObject(Pen);
	DeleteObject(BlackPen);
	DeleteObject(Brush);
	DeleteObject(BlackBrush);
};


void Ball::Hide()
{
	Visible = false;

	// ������� ���� � ���� ���� - ������
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));


	SelectObject(hdc, Brush);	//������� ���� ��������
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Pen);	//������� ���� ��������
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	DeleteObject(Pen);
	DeleteObject(Brush);
};

/*-------------------------------------------------------------*/
/*        ������ ������ Flower             */
/*----------------------------------------*/
//������ �� ��������� ������
Flower::Flower(int InitX, int InitY) :Point(InitX, InitY)
{
	this->Opened = true;
};


Flower::~Flower(void)
{

};


void Flower::Show()
{
	Visible = true;

	// ������� ���� � ���� ����
	HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN YellowPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 50));
	HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 50));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, GreenPen);	//������� ���� ��������

	//��������� �����
	POINT pt;

	//C������
	MoveToEx(hdc, X, Y + 140, &pt);
	LineTo(hdc, X, Y + 110);

	//������
	MoveToEx(hdc, X, Y + 130, &pt);
	LineTo(hdc, X + 10, Y + 120);

	SelectObject(hdc, YellowPen);

	//� ����������� �� ����, ������ ��� ������, ������ ���
	if (Opened == false)
	{
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		SelectObject(hdc, YellowBrush);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
	}
	else
	{
		Ellipse(hdc, X + 3 - 15, Y + 110, X + 4 - 5, Y + 95);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		Ellipse(hdc, X - 3 + 5, Y + 110, X - 4 + 15, Y + 95);

		SelectObject(hdc, YellowBrush);
		Ellipse(hdc, X + 3 - 15, Y + 110, X + 4 - 5, Y + 95);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		Ellipse(hdc, X - 3 + 5, Y + 110, X - 4 + 15, Y + 95);
	}

	DeleteObject(GreenPen);
	DeleteObject(YellowPen);
	DeleteObject(Brush);
	DeleteObject(YellowBrush);
};


void Flower::Hide()
{
	Visible = false;

	// ������� ���� � ���� ����
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Pen);	//������� ���� ��������

	//��������� �����
	POINT pt;

	//C������
	MoveToEx(hdc, X, Y + 140, &pt);
	LineTo(hdc, X, Y + 110);

	//������
	MoveToEx(hdc, X, Y + 130, &pt);
	LineTo(hdc, X + 10, Y + 120);

	if (this->Opened == false)
	{
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		SelectObject(hdc, Brush);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
	}
	else
	{
		Ellipse(hdc, X + 3 - 15, Y + 110, X + 4 - 5, Y + 95);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		Ellipse(hdc, X - 3 + 5, Y + 110, X - 4 + 15, Y + 95);

		SelectObject(hdc, Brush);
		Ellipse(hdc, X + 3 - 15, Y + 110, X + 4 - 5, Y + 95);
		Ellipse(hdc, X - 5, Y + 110, X + 5, Y + 90);
		Ellipse(hdc, X - 3 + 5, Y + 110, X - 4 + 15, Y + 95);
	}

	DeleteObject(Pen);
	DeleteObject(Brush);
};

bool Flower::IsOpened()
{
	return Opened;
};

//���� ������ ������, ������ ���, ���� ������  - �������
void Flower::Turn()
{
	Hide();
	this->Opened = !(this->Opened);
	Show();

};