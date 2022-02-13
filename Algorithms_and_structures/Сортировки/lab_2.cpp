#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;

void Insertion_Sort(int* arr, int p, int r, long long int& comp_count, long long int& swap_count, bool isbig);
void Merge_Sort(int* arr, int p, int r, long long int& comp_count, long long int& swap_count, bool isbig);
void Merge(int* arr, int p, int q, int r, long long int& comp_count, long long int& swap_count, bool isbig);
void Time_Analysis(void (*func)(int*, int, int, long long int&, long long int&, bool), int* arr, const char* name, int p, int r, bool isbig);
void Sort(void (*func)(int*, int, int, long long int&, long long int&, bool), int* arr, const char* name, int N, ofstream& output, bool isbig);

int main()
{
	int* arr;
	int N = 50;
	bool isbig = false;
	ofstream output("output.txt", ios_base::binary | ios_base::out | std::ios::trunc);

	setlocale(LC_ALL, "rus");
	srand((unsigned)time(NULL));

	arr = new int[N];

	if (N > 15)
		isbig = true;

	Sort(Insertion_Sort, arr, "Сортировка вставками", N, output, isbig);
	Sort(Merge_Sort, arr, "Сортировка слиянием", N, output, isbig);

	return 0;
}

void Insertion_Sort(int* arr, int p, int r, long long int& comp_count, long long int& swap_count, bool isbig)
{
	int i, j, key;
	for (i = p; i <= r; i++)
	{
		key = arr[i];
		j = i - 1;
		comp_count++;
		while (j >= 0 && arr[j] < key)
		{
			comp_count += 2;
			swap_count++;
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = key;
		swap_count++;

		if (!isbig)
		{
			cout << "n = " << i << " \t";
			for (int k = 0; k < r + 1; k++)
				cout << setw(3) << right << arr[k] << " ";
			cout << endl;
		}
	}
}

void Merge_Sort(int* arr, int p, int r, long long int& comp_count, long long int& swap_count, bool isbig)
{
	if (p < r)
	{
		int	q = (int)floor((p + r) / 2);
		Merge_Sort(arr, p, q, comp_count, swap_count, isbig);
		Merge_Sort(arr, q + 1, r, comp_count, swap_count, isbig);
		Merge(arr, p, q, r, comp_count, swap_count, isbig);
	}
}

void Merge(int* arr, int p, int q, int r, long long int& comp_count, long long int& swap_count, bool isbig)
{
	int* barr, * carr;
	int N1, N2;
	int i, j, k;

	N1 = q - p + 1;
	N2 = r - q;
	barr = new int[N1 + 1];
	carr = new int[N2 + 1];

	for (k = 0; k < N1; k++)
		barr[k] = arr[p + k];
	for (k = 0; k < N2; k++)
		carr[k] = arr[q + 1 + k];

	barr[N1] = carr[N2] = INT_MIN;
	i = j = 0;

	for (k = p; k <= r; k++)
	{
		comp_count++;
		if (barr[i] > carr[j])
		{
			arr[k] = barr[i];
			i++;
			swap_count++;
		}
		else
		{
			arr[k] = carr[j];
			j++;
			swap_count++;
		}
	}

	if (!isbig)
	{
		cout << "элементы " << p + 1 << "-" << r + 1 << "\t";
		for (int i = p; i < r + 1; i++)
			cout << setw(3) << right << arr[i] << " ";
		cout << endl;
	}
}

void Time_Analysis(void (*func)(int*, int, int, long long int&, long long int&, bool), int* arr, const char* name, int p, int r, bool isbig)
{
	long long int comp_count, swap_count;
	DWORD64 start, end;

	comp_count = swap_count = 0;

	start = __rdtsc();
	func(arr, p, r, comp_count, swap_count, isbig);
	end = __rdtsc();
	cout << name << " заняла " << (float)(end - start) / 1000000 << " мс, " << comp_count << " сравнений, " << swap_count << " пересылок " << endl;
}

void Sort(void (*func)(int*, int, int, long long int&, long long int&, bool), int* arr, const char* name, int N, ofstream& output, bool isbig)
{
	output << name << endl;
	output << "Неотсортированный массив: " << endl;
	for (int i = 0; i < N; i++)
	{
		arr[i] = rand() % 10;
		output << arr[i] << " ";
	}
	output << endl;

	if (!isbig)
	{
		cout << "Неотсортированный массив: " << endl;
		for (int i = 0; i < N; i++)
			cout << arr[i] << " ";
		cout << endl;
	}
	Time_Analysis(func, arr, name, 0, N - 1, isbig);

	output << "Отсортированный массив: " << endl;
	if (!isbig)
	{
		cout << "Отсортированный массив: " << endl;
		for (int i = 0; i < N; i++)
			cout << arr[i] << " ";
		cout << endl << endl;
	}
	for (int i = 0; i < N; i++)
		output << arr[i] << " ";
	output << endl << endl;
}