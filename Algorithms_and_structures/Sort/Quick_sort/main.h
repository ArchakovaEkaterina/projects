//Сортировка быстрой перестановкой по возрастанию
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct reading_result {
    int status;//статус выполнения чтения файла - возникла ли ошибка и какая
    int n;
    int *mas;//считанный массив и кол-во элементов
};


//считывание массива и его длины по номеру файла и вывод ошибки в зависимости от флага
reading_result read_file(int mode);

//Сортировка быстрой перестановкой
void quicksort(int *mas, int first, int last, int n);

//печать массива
void print_arr(int *mas, int n);

//отсортирован ли массив по возрастанию
bool arr_is_sorted(int *mas, int n);


//считывание массива и его длины по номеру файла и вывод ошибки в зависимости от флага
reading_result read_file(int mode)
{
    int kol = 0;//кол-во считанных элементов матрицы
    int n;//кол-во элементов матрицы
    int i;
    reading_result result = {0, 0, NULL};

    //конвертируем номер файла в строку и открываем соответствующий файл
    stringstream ss;
    ss << mode;
    string file_number;
    ss>>file_number;

    string file_name = file_number + ".txt";
    ifstream file(file_name);


    //проверка файла
	if (!(file.is_open()))
	{
	    cout << "Ошибка открытия файла" << endl;
		result.status = -1;
		return result;
	}
	if (file.peek() == EOF)
	{
	    cout << "Файл пуст" << endl;
		result.status = -2;
		return result;
	}


	//считываем число элементов массива
	if (!(file >> n) || (n <= 0) || (n > 50))
    {
        cout << "Ошибка. Введите корректное кол-во элементов матрицы\n";
        file.close();
        result.status = -3;
        return result;
    }

    int *mas = new int[n];
    //считывание массива из файла
    for (i = 0; i < n; i++)
    {
        if (!(file >> mas[i]) && (kol < n))
        {
            cout << "Ошибка. Введите "<< n << " элементов матрицы\n";
            file.close();
            result.status = -4;
            return result;
        }
        kol++;
    }
    file.close();

    result.mas = mas;
    result.n = n;
    return result;
}


//Сортировка быстрой перестановкой
void quicksort(int *mas, int first, int last, int n)
{
    int x, tmp;
    int f=first, l=last;
    x=mas[(f+l) / 2]; //вычисление опорного элемента

    do
    {
        while (mas[f]<x) f++;
        while (mas[l]>x) l--;

        if (f<=l) //перестановка элементов
        {
            tmp=mas[f];
            mas[f]=mas[l];
            mas[l]=tmp;
            f++;
            l--;
        }

         if (n < 11)
        {
            cout<< "x = "<< x<<endl;
            cout<< "first = "<< first << ", last = "<< last<<endl;
            cout<< "f = "<< f << ", l = "<< l<<endl;
            print_arr(mas, n);
        }
    } while (f<l);


    if (first<l)
        quicksort(mas, first, l, n);
    if (f<last)
        quicksort(mas, f, last, n);
}


//печать массива
void print_arr(int *mas, int n)
{
    for (int i=0; i<n; i++)
    {
        cout<<mas[i]<<" ";
        if (i%10 == 9) cout<<endl;
    }
    cout << endl << endl;
}


//отсортирован ли массив по возрастанию
bool arr_is_sorted(int *mas, int n)
{
    if (n == 1)
        return true;

    int pred = mas[0];
    for (int i=1; i < n; i++)
    {
        if (mas[i] < pred)
            return false;
    }

    return true;
}
