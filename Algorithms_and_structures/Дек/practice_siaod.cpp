/*	Полянина Екатерина, вариант 14, пз1 стеки_деки_очереди
дек в виде двунаправленного списка
тип элементов - вещественный, кол-во элементов - 17
доп операции:
1. выборка элемента из конца списка
2. добавление элемента в начало списка
3.нахождение элемента дека с заданным номером(не первого и не последнего) с выводом его значения на экран(в файл)
*/
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

int const N = 17;
struct elem
{
	double data;
	elem* next, * prev;
};

void Create(elem** head, elem** rear, double str);
void Print(elem* p);
void Delete(elem** head, elem** rear, int& count);
double Search(elem* head, elem* rear, int pos, int size, int& count);
void Insert(elem** head, elem** rear, double str, int pos);
void Remove(elem** rear);

int main()
{
	int size = 0;//кол-во элементов в деке
	int mode, pos;
	int count;//кол-во просмотренных элементов дека
	double str;
	elem* head = NULL;//указатель на первый элемент дека
	elem* rear = NULL;//указатель на последний элемент дека
	ifstream file("Input.txt");

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");

	if (!(file.is_open()))
	{
		cout << "Ошибка открытия файла." << endl;
		return -1;
	}
	if (file.peek() == EOF)
	{
		cout << "Файл пуст" << endl;
		return -2;
	}
	file >> str;
	Create(&head, &rear, str);
	size++;
	while (file.peek() != EOF && size<N)
	{
		file >> str;
		Insert(&head, &rear, str, size);
		size++;
	}
	

	do
	{
		Print(head);
		count = 0;
		mode = 0;
		cout << "Выберете операцию:\n"
			<< "1.Поиск в деке элемента с заданным номером\n"
			<< "2.Включение нового элемента в начало дека\n"
			<< "3.Удаление элемента из конца дека.\n"
			<< "4.Удалить дек и завершить работу\n";
		cout << "Ваш Выбор: ";
		while (!(cin >> mode) || (mode > 4) || (mode < 1))
		{
			cout << "Неверное значение, попробуйте еще раз: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
		cin.ignore();

		switch (mode)
		{
		case 1:
			cout << "Введите номер элемента дека, который желаете найти: ";
			if (!(cin >> pos) || pos<1 || pos>size)
			{
				cout << "Номер элемента должен быть натуральным и не больше " << size << endl<< endl;
				break;
			}
			str = Search(head,rear, pos, size, count);
			cout << "Было просмотрено " << count << " элементов дека" << endl;
			cout << "Элемент с номером " << pos << ": " << str << endl << endl;
			break;
		case 2:
			if (size == N)
			{
				cout << "Невозможно добавить элемент в дек, поскольку его размер максимален(17)\n" << endl;
				Print(head);
				break;
			}
			else
			{
				cout << "Введите число, которое желаете включить в дек: ";
				if (!(cin >> str))
				{
					cout << "Возможно включить в дек только вещественное число\n\n";
					break;
				}
				Insert(&head, &rear, str, 0);
				size++;
				cout << "Измененный дек:" << endl;
				Print(head);
				cout << endl;
				break;
			}	
		case 3://удаление элемента из конца дека
			if (size ==1)
				cout << "Дек состоит из одного элемента\n" << endl;
			else
			{	
				Remove(&rear);
				size--;
				cout << "Измененный дек:\n";
				Print(head);
			}
			break;
		case 4://удалить дек
			Delete(&head, &rear, count);
			size = 0;
			cout << "Было просмотрено " << count << " элементов дека" << endl;
			break;
		}
	} while (mode != 4);
	file.close();
	return 0;
}

//Функция создания списка
void Create(elem** head, elem** rear, double str)
{
	if ((*head) == NULL)
	{
		elem* ptr = new elem;
		ptr->data = str;
		*head = ptr;
		*rear = ptr;
		(*rear)->next = (*rear)->prev =  NULL;
		(*head)->next = (*head)->prev = NULL;
	}
}//Create

//Функция вставки элемента в список
void Insert(elem** head, elem** rear, double str, int pos)
{
	if ((*head) != NULL)
	{
		elem* ptr = new elem;
		ptr->data = str;
		
		if (pos == 0)
		{
			ptr->next = (*head);
			ptr->prev = (*head)->prev;
			(*head)->prev = ptr;
			(*head) = ptr;
		}
		else
		{
			ptr->prev = (*rear);
			ptr->next = (*rear)->next;
			(*rear)->next = ptr;
			(*rear) = ptr;
		}
	}
}//Insert

//Функция печати списка
void Print(elem* head)
{
	int i = 0;
	elem* temp = head;

	if (head != NULL)
		do
		{
			cout << i + 1 << ". " << temp->data << endl;
			temp = temp->next;
			i++;
		} while (temp != NULL);
	cout << endl;
}//Print

//Функция поиска элемента в списке
double Search(elem* head, elem* rear, int key, int size, int& count)
{
	if (head != NULL)
	{
		int i;//позиция текущего элемента дека
		elem* temp;
		count = 0;
		if (key <= size / 2)
		{
			i = 1;
			temp = head;
			while (i<= size/2)
			{
				count++;
				if (i == key)
					return temp->data;
				temp = temp->next;
				i++;
			} 
		}
		else
		{
			i = size;
			temp = rear;
			while (i > size / 2)
			{
				count++;
				if (i == key)
					return temp->data;
				temp = temp->prev;
				i--;
			}
		}
	}
	return -1;
}//Search

//Функция удаления элемента из конца дека
void Remove(elem** rear)
{
	elem* temp = (*rear);
	temp->prev->next = temp->next;
	*rear = temp->prev;
	delete temp;
}

//Функция удаления дека
void Delete(elem** head, elem** rear, int& count)
{
	if ((*head) != NULL)
	{
		elem* temp = (*rear);
		while (temp != *head)
		{
			temp = temp->prev;
			(*rear) = temp;
			delete temp->next;
			count++;
		}
		delete* head;
	}
	
}//Delete