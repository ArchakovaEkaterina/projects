#include<iostream>
#include<iomanip>
#include<fstream>
#include<ctype.h>
#include<windows.h>
usingnamespace std;

constexprauto NOT_FOUND = -1;

intLinear_Search(char* arr, intN, charx, int&comp_count);
intBetter_Linear_Search(char* arr, intN, charx, int&comp_count);
intConsecutive_Search(char* arr, intN, charx, int&comp_count);
intBinary_Search(char* arr, intN, charx, int&comp_count);
voidTime_Analysis(int (*func)(char*, int, char, int&), char* arr, intN, charkey);

int main()
{
	inti, N, mode;
	char* arr;
	char key;
	int (*func)(char*, int, char, int&);

	setlocale(LC_ALL, "rus");
	
	ifstream file("Input.txt");
	if (file.is_open())
	{
		file.seekg(0, file.end);
		N = (int)file.tellg();
		file.seekg(0, file.beg);
		arr = newchar[N];
		for (i = 0; i< N; i++)
			file >>arr[i];
	}
	else
	{
		cout<<"Ошибкаоткрытияфайла."<<endl;
		return -1;
	}

	cout<<"Количество элементов в массиве равно "<< N <<endl;

	cout<<"Введите элемент, который нужно найти: ";
	cin>>key;


	cout<<"Выберете способ поиска: (1)Линейный, (2)Улучш.Линейный, (3)Последовательный, (4)Бинарный: ";
	cin>> mode;
	switch (mode)
	{
		case 1: func = Linear_Search; break;
		case 2: func = Better_Linear_Search; break;
		case 3: func = Consecutive_Search; break;
		case 4: func = Binary_Search; break;
		default: func = Linear_Search; break;
	}

	Time_Analysis(func, arr, N, key);
	delete []arr;

	return 0;
}



intLinear_Search(char*arr, intN, char x, int&comp_count)
{
	int answer = NOT_FOUND;
	inti;
	for (i = 0; i<N; i++)
		if (arr[i] == x)
		{
			answer = i;
			break;
		}
	comp_count = 2 * (i+1);
	return answer;
}




intBetter_Linear_Search(char* arr, intN, charx, int&comp_count)
{
	int last;
	inti;
	int answer = NOT_FOUND;

	i = 0;
	last = arr[N-1];
	arr[N - 1] = x;
	while (arr[i] != x)
		i++;
	arr[N-1] = last;
	if (i<N - 1 || arr[N - 1] == x)
		answer = i;
	comp_count = i + 3;
	return answer;
}




intConsecutive_Search(char* arr, intN, charx, int&comp_count)
{
	inti = 0;
	int answer = NOT_FOUND;

	while (arr[i] <x)
		i++;
	if (arr[i] == x)
		answer = i;
	comp_count = i + 2;
	return answer;
}



intBinary_Search(char* arr, intN, char x, int&comp_count)
{
	int p, q, r;
	int answer=NOT_FOUND;

	p = 0;
	r = N-1;

	while (p <= r)
	{
		comp_count += 2;
		q = (int)floor((p + r) / 2);
		if (arr[q] == x)
		{
			answer = q;
			break;
		}
		elseif (arr[q] >x)
			r = q - 1;
		else
			p = q + 1;
		comp_count++;
	}
	return answer;
}

voidTime_Analysis(int (*func)(char*, int, char, int&), char* arr, intN, charkey)
{
	DWORD64 start, end;
	int pos;
	intcomp_count = 0;

	start = __rdtsc();
	pos = (*func)(arr, N, key, comp_count) + 1;
	end = __rdtsc();

	if (pos != 0)
		cout<<"Элемент находится на "<<pos<<"-й позиции"<<endl;
	else
		cout<<"Элемент не найден"<<endl;

	cout<<"Поиск выполнен за ";
	if (N> 20)
		cout<< (end - start) / 1000000 <<" мс";
	else
		cout<<comp_count<<" сравнений"<<endl;

} 
