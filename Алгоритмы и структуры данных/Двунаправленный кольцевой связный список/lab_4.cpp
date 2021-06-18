#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

struct elem
{
	string data;
	elem* next, * prev;
};

void Create(elem** head, string str);
void Print(elem* p);
void Delete(elem** head, int& count);
int Search(elem* head, string str, int& count);
void Insert(elem** head, string str, int pos, int& count);
void Removeb(elem** head);

int main()
{
	int size, mode, pos, count;
	string str;
	elem* head = NULL;
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
	Create(&head, str);
	size = 1;
	while (file.peek() != EOF)
	{
		file >> str;
		file.ignore(1024, '\n');
		Insert(&head, str, size, count);
		size++;
	}
	Print(head);

	do
	{
		count = 0;
		cout << "Выберете операцию:\n"
			<< "1.Поиск в списке наличия элемента с заданным значением\n"
			<< "2.Включение нового элемента в позицию списка\n"
			<< "3.Удаление элемента из начала списка.\n"
			<< "4.Удалить список и завершить работу\n";
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
			cout << "Введите строку, которую желаете найти: ";
			getline(cin, str);
			pos = Search(head, str, count);
			cout << "Было просмотрено " << count << " элементов списка" << endl;
			if (pos == -1)
				cout << "Данной строки нет в списке" << endl;
			else
				cout << "Строка находится на " << pos + 1 << "-й позиции" << endl;
			break;
		case 2:
			cout << "Введите строку, которую желаете включить в список: ";
			getline(cin, str);
			cout << "Введите позицию: ";
			while (!(cin >> pos))
			{
				cout << "Неверное значение, попробуйте еще раз: ";
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			Insert(&head, str, pos - 1, count);
			cout << "Было просмотрено " << count << " элементов списка" << endl;
			Print(head);
			break;
		case 3:
			Removeb(&head);
			Print(head);
			break;
		case 4:
			Delete(&head, count);
			cout << "Было просмотрено " << count << " элементов списка" << endl;
			break;
		}
	} while (mode != 4);

	file.close();
	return 0;
}
//Функция создания списка
void Create(elem** head, string str)
{
	if ((*head) == NULL)
	{
		(*head) = new elem;
		(*head)->data = str;
		(*head)->next = (*head)->prev = (*head);
	}
}
//Функция печати списка
void Print(elem* head)
{
	int i = 0;;
	elem* temp = head;

	if (head != NULL)
		do
		{
			cout << i + 1 << ". " << temp->data << endl;
			temp = temp->next;
			i++;
		} while (temp != head);
}
//Функция удаления списка
void Delete(elem** head, int& count)
{
	if ((*head) != NULL)
	{
		elem* temp = (*head)->prev;
		while (temp != *head)
		{
			temp = temp->prev;
			delete temp->next;
			count++;
		}
		delete* head;
	}
}
//Функция поиска элемента в списке
int Search(elem* head, string key, int& count)
{
	if (head != NULL)
	{
		int i = 0;
		elem* temp = head;
		do
		{
			count++;
			if (temp->data == key)
				return i;
			temp = temp->next;
			i++;
		} while (temp != head);
	}
	return -1;
}
//Функция вставки элемента в список
void Insert(elem** head, string str, int pos, int& count)
{
	if ((*head) != NULL)
	{
		int i = 0;
		elem* temp = (*head);
		elem* ptr = new elem;
		ptr->data = str;

		if (pos < 0)
			return;
		if (pos > 0)
		{
			do
			{
				count++;
				temp = temp->next;
				i++;
			} while (i != pos && temp != (*head));
		}
		if (i == pos)
		{
			ptr->next = temp;
			ptr->prev = temp->prev;
			temp->prev->next = ptr;
			temp->prev = ptr;
		}
		if (pos == 0)
			(*head) = ptr;
	}
}
//Функция удаления элемента из начала списка
void Removeb(elem** head)
{
	elem* temp = *head;
	if ((*head)->next != (*head))
	{
		(*head)->prev->next = (*head)->next;
		(*head)->next->prev = (*head)->prev;
		(*head) = (*head)->next;
		delete temp;
	}
}