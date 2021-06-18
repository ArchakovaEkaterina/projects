#include <windows.h>
#include "Point05_07.h"	//объявление классов
#include <string.h>
#include <iostream>
using namespace std;


int func(int x0, int x1, int y1, int x2, int y2)//рассчет координаты объекта на траектории до норки
{
	return int(((x0 - x1) * (y2 - y1)) / (x2 - x1) + y1);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/*            ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ И КОНСТАНТЫ                */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//глобальная переменная видна в двух файлах:
// Point05_04.cpp и Ex05_04_Con_Virt.cpp
//внешнее обявление глобальной переменной
extern HDC hdc;      // объявим  контекст устройства

// Макрос для проверки состояния клавиатуры – из ШАБЛОНА
#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

/*----------------------------------------------------------*/
/*             Р Е А Л И З А Ц И Я    М Е Т О Д О В         */
/*----------------------------------------------------------*/

/*-----------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Location          */
/*----------------------------------------*/
//конструктор
Location::Location(int InitX, int InitY)
{
	//инициализация закрытых переменных своего класса
	X = InitX;
	Y = InitY;
};//end Location::Location()

  //деструктор
Location::~Location(void)  //формально пустое тело
{
};//end Location::~Location()

  //получить X координату точки
int Location::GetX(void)
{
	return X;
};//end Location::GetX()	

  //получить Y координату точки
int Location::GetY(void)
{
	return Y;
}; //end Location::GetY()


/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Point             */
/*----------------------------------------*/
//конструктор
//для инициализации закрытых полей используем конструктор предка
Point::Point(int InitX, int InitY) : Location(InitX, InitY)
{
	//инициализация закрытых переменных своего класса
	Visible = false;
}//end Point::Point()


 //--------------------------------------------------------------
 //деструктор
Point::~Point(void)   //формально пустое тело
{
}//end Point::~Point()

 //--------------------------------------------------------------
 //показать ТОЧКУ
void Point::Show(void)
{
	Visible = true;
	SetPixel(hdc, X, Y, RGB(255, 0, 0));	//рисуем красным цветом
	SetPixel(hdc, X + 1, Y, RGB(255, 0, 0));	// 4 точки для удобства
	SetPixel(hdc, X, Y + 1, RGB(255, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(255, 0, 0));
}//end Point::Show()

 //--------------------------------------------------------------
 //скрыть ТОЧКУ
void Point::Hide(void)
{
	Visible = false;

	SetPixel(hdc, X, Y, RGB(0, 0, 0));//рисуем синим цветом или фона
	SetPixel(hdc, X + 1, Y, RGB(0, 0, 0));
	SetPixel(hdc, X, Y + 1, RGB(0, 0, 0));
	SetPixel(hdc, X + 1, Y + 1, RGB(0, 0, 0));
}//end Point::Hide()

 //--------------------------------------------------------------
 //узнать про светимость ТОЧКИ
bool Point::IsVisible(void)
{
	return Visible;
};//end Point::IsVisible()

//--------------------------------------------------------------
//переместить ТОЧКУ
void Point::MoveTo(int NewX, int NewY)
{
	Hide();		//сделать точку невидимой
	X = NewX;	//поменять координаты ТОЧКИ
	Y = NewY;
	Show();		//показать точку на новом месте
};//end Point::MoveTo()

 //-------------------------------------------------------------------
//буксировка фигуры
void Point::Drag(int Step)
{
	int FigX, FigY;   //новые координаты фигуры

	FigX = GetX();    //получаем начальное положение фигуры
	FigY = GetY();

	while (1)	//бесконечный цикл буксировки фигуры
	{
		if (KEY_DOWN(48))     //конец работы 27
			break;

		//направление движения объекта

		if (KEY_DOWN(VK_LEFT)) //стрелка влево  37
		{
			FigX -= Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_RIGHT)) //стрелка вправо  39
		{
			FigX += Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_DOWN)) //стрелка вниз  40
		{
			FigY += Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if

		if (KEY_DOWN(VK_UP)) //стрелка вверх  38
		{
			FigY -= Step;
			MoveTo(FigX, FigY);
			Sleep(150);
		}//end if
	}   //while
}//end Drag()



/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Animal             */
/*----------------------------------------*/
Animal::Animal(int InitX, int InitY, string name, bool fed, string phrase) :Point(InitX, InitY)//инициализация
{
	this->Name = name;
	this->Fed = fed;
	this->Phrase = phrase;
}


Animal::~Animal(void)//деструктор
{

}

void Animal::Say()//животное издает свой звук
{
	cout << Name << ": " << Phrase << endl;
}

string Animal::GetName()//получить имя животного
{
	return Name;
}

bool Animal::isFed()//состояние животного
{
	return this->Fed;
}

void Animal::Eat()//изменить сытость или голод
{
	Hide();
	this->Fed = !(this->Fed);
	Show();
}



/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Cat                */
/*----------------------------------------*/

//инициализация значениями
Cat::Cat(int InitX, int InitY, string name, int fed, string phrase, bool playful) :Animal(InitX, InitY, name, fed, phrase)
{
	this->Playful = playful;
}

Cat::~Cat(void)
{

}

//показать кошку и шкалу ее сытости
void Cat::Show(void)
{
	Visible = true;

	// Зададим перо и цвет пера - красный
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HPEN BluePen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	HPEN YellowPen = CreatePen(PS_SOLID, 4, RGB(255, 255, 50));
	HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 50));
	SelectObject(hdc, Brush);

	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище
	Ellipse(hdc, X - 50, Y - 50, X, Y);//голова


	//треугольники
	POINT poly[3];

	poly[0].x = X - 20;
	poly[0].y = Y - 50;

	poly[1].x = X;
	poly[1].y = Y - 60;

	poly[2].x = X;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//правое ухо
	SelectObject(hdc, Pen);
	Polygon(hdc, poly, 3);//правое ухо
	SelectObject(hdc, Brush);

	poly[0].x = X - 35;
	poly[0].y = Y - 48;

	poly[1].x = X - 50;
	poly[1].y = Y - 60;

	poly[2].x = X - 50;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//левое ухо

	SelectObject(hdc, Pen);
	Polygon(hdc, poly, 3);//левое ухо
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище
	Ellipse(hdc, X - 50, Y - 50, X, Y);//голова
	//рисование линий
	POINT pt;

	//хвост
	//у игривой кошки хвост трубой(вверх), у неигривой - по диагонали
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

	//правая передняя лапа
	MoveToEx(hdc, X - 20, Y + 15, &pt);
	LineTo(hdc, X - 35, Y + 60);

	//левая передняя лапа
	MoveToEx(hdc, X - 10, Y + 20, &pt);
	LineTo(hdc, X - 25, Y + 80);

	//правая задняя лапа
	MoveToEx(hdc, X + 75, Y + 23, &pt);
	LineTo(hdc, X + 80, Y + 60);

	//левая задняя лапа
	MoveToEx(hdc, X + 90, Y + 20, &pt);
	LineTo(hdc, X + 100, Y + 80);


	//глаза и нос
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

	//рисуем шкалу: если кот сытый, то рисуется закрашенный прямоугольник, нет - незакрашенный
	if (this->Fed == true)
	{
		SelectObject(hdc, YellowBrush);
	}
	else
	{
		SelectObject(hdc, BlackBrush);
	}
	Rectangle(hdc, 900, 40, 950, 60);


	// Уничтожим нами созданные объекты  
	DeleteObject(Pen);
	DeleteObject(BluePen);
	DeleteObject(Brush);
	DeleteObject(YellowPen);
	DeleteObject(YellowBrush);
	DeleteObject(BlackBrush);
}//end  Cat::Show()


//скрыть кошку - рисуем кошку цветом фона
void Cat::Hide(void)
{
	Visible = false;

	// Зададим перо и цвет пера - черный
	HPEN Pen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Brush);	//сделаем перо активным

	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище
	SelectObject(hdc, Pen);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище

	Ellipse(hdc, X - 50, Y - 50, X, Y);//голова


	//рисование линий
	POINT pt;

	//хвост
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

	//правая передняя лапа
	MoveToEx(hdc, X - 20, Y + 15, &pt);

	LineTo(hdc, X - 35, Y + 60);

	//левая передняя лапа
	MoveToEx(hdc, X - 10, Y + 20, &pt);
	LineTo(hdc, X - 25, Y + 80);

	//правая задняя лапа
	MoveToEx(hdc, X + 75, Y + 23, &pt);
	LineTo(hdc, X + 80, Y + 60);

	//левая задняя лапа
	MoveToEx(hdc, X + 90, Y + 20, &pt);
	LineTo(hdc, X + 100, Y + 80);


	//треугольники
	POINT poly[3];

	poly[0].x = X - 20;
	poly[0].y = Y - 50;

	poly[1].x = X;
	poly[1].y = Y - 60;

	poly[2].x = X;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//правое ухо

	poly[0].x = X - 35;
	poly[0].y = Y - 48;

	poly[1].x = X - 50;
	poly[1].y = Y - 60;

	poly[2].x = X - 50;
	poly[2].y = Y - 35;

	Polygon(hdc, poly, 3);//левое ухо

	//глаза и нос
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

	SelectObject(hdc, Brush);	//сделаем перо активным
	Rectangle(hdc, 900, 40, 950, 60);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище
	SelectObject(hdc, Pen);	//сделаем перо активным
	Rectangle(hdc, 900, 40, 950, 60);
	Ellipse(hdc, X - 25, Y - 25, X + 100, Y + 30);//туловище


	// Уничтожим нами созданные объекты  
	DeleteObject(Pen);
	DeleteObject(Brush);
}//end Cat::Hide()


//кот вдохнул аромат цветом и стал игривым
void Cat::Sniff()
{
	this->Hide();
	this->Playful = 1;
	this->Show();
};

//геттер ддля игривости кота
bool Cat::IsPlayful()
{
	return this->Playful;
}

//кот играет - меняет игривость
void Cat::Play()
{
	Hide();
	this->Playful = !(this->Playful);
	Show();
};

//кот охотится - идет к норке
void Cat::Hunt(void)
{
	if (GetX() != 50 && GetY() != 90)
	{
		if (GetX() > 50 + 200)// в охоте у объектов разные шаги для того, чтобы координаты резко не менялись в зависимости от их местоположения
		{
			if ((this->Playful == 1) && (this->Fed == 0))//если кот игривый и голодный, то у него шаг больше
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
			if ((this->Playful == 1) && (this->Fed == 0))//если кот игривый и голодный, то у него шаг больше
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

//кот ест - меняет сытость и игривость
void Cat::Eat()
{
	Hide();
	this->Fed = !(this->Fed);
	this->Playful = !(this->Playful);
	Show();
}

/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Mouse             */
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

	// Зададим перо и цвет пера
	HPEN GreyPen = CreatePen(PS_SOLID, 2, RGB(206, 206, 206));
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH GreyBrush = CreateSolidBrush(RGB(187, 187, 187));
	HBRUSH WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, BlackPen);	//сделаем перо активным

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//туловище
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//левое ухо
	//Ellipse(hdc, X -5 , Y-5 , X+8 , Y-17 );//правое ухо

	//глаза и нос
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//левый глаз
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//нос
	//Ellipse(hdc, X + 5 , Y+2 , X + 10 , Y-3 );//правый глаз
	//Ellipse(hdc, X + 12, Y +3, X + 17 , Y-3 );//нос

	SelectObject(hdc, GreyBrush);	//сделаем перо активным

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//туловище
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//левое ухо
	//Ellipse(hdc, X -5 , Y-5 , X+8 , Y-17 );//правое ухо

	//глаза и нос
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//левый глаз
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//нос
	//Ellipse(hdc, X + 5 , Y+2 , X + 10 , Y-3 );//правый глаз
	//Ellipse(hdc, X + 12, Y +3, X + 17 , Y-3 );//нос

	SelectObject(hdc, GreyPen);
	//рисование линий
	POINT pt;

	//хвост
	//если мышь голодная, то у нее хвост трубой, иначе - расслабленный
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

	// Уничтожим нами созданные объекты  
	DeleteObject(GreyPen);
	DeleteObject(BlackPen);
	DeleteObject(BlackBrush);
	DeleteObject(GreyBrush);
	DeleteObject(WhiteBrush);
};


void Mouse::Hide()
{
	Visible = false;

	// Зададим перо и цвет пера
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, BlackBrush);	//сделаем перо активным

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//туловище
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//левое ухо
	//Ellipse(hdc, X - 25 , Y - 10, X + 15, Y + 10);//туловище
	//Ellipse(hdc, X - 5 , Y - 5 , X + 8 , Y - 17 );//правое ухо


	//глаза и нос
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//левый глаз
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//нос
	//Ellipse(hdc, X + 5, Y + 2 , X + 10, Y - 3);//правый глаз
	//Ellipse(hdc, X + 12, Y + 3, X + 17, Y - 3);//нос

	SelectObject(hdc, BlackPen);

	Ellipse(hdc, X - 25, Y - 10, X + 15, Y + 10);//туловище
	Ellipse(hdc, X - 18, Y - 5, X - 5, Y - 17);//левое ухо
	Ellipse(hdc, X - 20, Y + 2, X - 15, Y - 3);//левый глаз
	Ellipse(hdc, X - 27, Y + 3, X - 22, Y - 3);//нос

	//Ellipse(hdc, X - 25 , Y - 10, X + 15 , Y + 10);//туловище
	//Ellipse(hdc, X - 5 , Y - 5 , X + 8 , Y - 17 );//правое ухо
	//Ellipse(hdc, X + 5 , Y + 2 , X + 10 , Y - 3 );//правый глаз
	//Ellipse(hdc, X + 12, Y + 3 , X + 17 , Y - 3 );//нос

	//рисование линий
	POINT pt;

	//хвост
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

	// Уничтожим нами созданные объекты  
	DeleteObject(BlackPen);
	DeleteObject(BlackBrush);
};

//мышь убегает от кошки
void Mouse::Hunt()
{
	Show();
	//обе координаты подходят, чтобы уменьхать x
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
		//мышь находится левее или на линиии с норкой - двигаться вдоль линии
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

//мышь ест - меняем сытость
void Mouse::Eat()
{
	Hide();
	this->Fed = !(this->Fed);
	Show();
}
/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА	Mink               */
/*----------------------------------------*/
//в норе по умолчанию никого нет
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

	// Зададим перо и цвет пера
	HPEN LightPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 150));
	HPEN DarkPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HPEN RedPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH LightBrush = CreateSolidBrush(RGB(0, 0, 255));

	//если никого нет в норке - цвет ободка норки синий, иначе красный
	if (this->is_Full() == false)
	{
		SelectObject(hdc, LightPen);	//сделаем перо активным
	}
	else
	{
		SelectObject(hdc, RedPen);	//сделаем перо активным
	}
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, LightBrush);	//сделаем перо активным
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, Brush);	//сделаем перо активным
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);
	SelectObject(hdc, DarkPen);	//сделаем перо активным
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

	// Зададим перо и цвет пера
	HPEN DarkPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));

	SelectObject(hdc, DarkPen);	//сделаем перо активным
	Ellipse(hdc, X - 20, Y + 50, X + 20, Y + 130);

	SelectObject(hdc, Brush);	//сделаем перо активным
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);
	SelectObject(hdc, DarkPen);	//сделаем перо активным
	Rectangle(hdc, X - 20, Y + 85, X + 20, Y + 130);

	DeleteObject(DarkPen);
	DeleteObject(Brush);
};

//меняем заполненность норки
void Mink::Fill()
{
	this->Full = !this->Full;
};


bool Mink::is_Full()
{
	return this->Full;
}

/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Ball              */
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

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(100, 255, 100));
	HPEN BlackPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH BlackBrush = CreateSolidBrush(RGB(0, 0, 0));


	SelectObject(hdc, BlackPen);	//сделаем перо активным
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Brush);	//сделаем перо активным
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Pen);	//сделаем перо активным
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	DeleteObject(Pen);
	DeleteObject(BlackPen);
	DeleteObject(Brush);
	DeleteObject(BlackBrush);
};


void Ball::Hide()
{
	Visible = false;

	// Зададим перо и цвет пера - черный
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));


	SelectObject(hdc, Brush);	//сделаем перо активным
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	SelectObject(hdc, Pen);	//сделаем перо активным
	Ellipse(hdc, X, Y, X + 20, Y + 20);

	DeleteObject(Pen);
	DeleteObject(Brush);
};

/*-------------------------------------------------------------*/
/*        МЕТОДЫ КЛАССА Flower             */
/*----------------------------------------*/
//цветок по умолчанию открыт
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

	// Зададим перо и цвет пера
	HPEN GreenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN YellowPen = CreatePen(PS_SOLID, 2, RGB(255, 255, 50));
	HBRUSH YellowBrush = CreateSolidBrush(RGB(255, 255, 50));
	HBRUSH Brush = CreateSolidBrush(RGB(255, 255, 255));
	SelectObject(hdc, GreenPen);	//сделаем перо активным

	//рисование линий
	POINT pt;

	//Cтебель
	MoveToEx(hdc, X, Y + 140, &pt);
	LineTo(hdc, X, Y + 110);

	//Листок
	MoveToEx(hdc, X, Y + 130, &pt);
	LineTo(hdc, X + 10, Y + 120);

	SelectObject(hdc, YellowPen);

	//в зависимости от того, открыт лии цветок, рисуем его
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

	// Зададим перо и цвет пера
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, Pen);	//сделаем перо активным

	//рисование линий
	POINT pt;

	//Cтебель
	MoveToEx(hdc, X, Y + 140, &pt);
	LineTo(hdc, X, Y + 110);

	//Листок
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

//если цветок закрыт, окрыть его, если открыт  - закрыть
void Flower::Turn()
{
	Hide();
	this->Opened = !(this->Opened);
	Show();

};