//���������� ������� ������������� �� �����������
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

struct reading_result {
    int status;//������ ���������� ������ ����� - �������� �� ������ � �����
    int n;
    int *mas;//��������� ������ � ���-�� ���������
};


//���������� ������� � ��� ����� �� ������ ����� � ����� ������ � ����������� �� �����
reading_result read_file(int mode);

//���������� ������� �������������
void quicksort(int *mas, int first, int last, int n);

//������ �������
void print_arr(int *mas, int n);

//������������ �� ������ �� �����������
bool arr_is_sorted(int *mas, int n);


//���������� ������� � ��� ����� �� ������ ����� � ����� ������ � ����������� �� �����
reading_result read_file(int mode)
{
    int kol = 0;//���-�� ��������� ��������� �������
    int n;//���-�� ��������� �������
    int i;
    reading_result result = {0, 0, NULL};

    //������������ ����� ����� � ������ � ��������� ��������������� ����
    stringstream ss;
    ss << mode;
    string file_number;
    ss>>file_number;

    string file_name = file_number + ".txt";
    ifstream file(file_name);


    //�������� �����
	if (!(file.is_open()))
	{
	    cout << "������ �������� �����" << endl;
		result.status = -1;
		return result;
	}
	if (file.peek() == EOF)
	{
	    cout << "���� ����" << endl;
		result.status = -2;
		return result;
	}


	//��������� ����� ��������� �������
	if (!(file >> n) || (n <= 0) || (n > 50))
    {
        cout << "������. ������� ���������� ���-�� ��������� �������\n";
        file.close();
        result.status = -3;
        return result;
    }

    int *mas = new int[n];
    //���������� ������� �� �����
    for (i = 0; i < n; i++)
    {
        if (!(file >> mas[i]) && (kol < n))
        {
            cout << "������. ������� "<< n << " ��������� �������\n";
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


//���������� ������� �������������
void quicksort(int *mas, int first, int last, int n)
{
    int x, tmp;
    int f=first, l=last;
    x=mas[(f+l) / 2]; //���������� �������� ��������

    do
    {
        while (mas[f]<x) f++;
        while (mas[l]>x) l--;

        if (f<=l) //������������ ���������
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


//������ �������
void print_arr(int *mas, int n)
{
    for (int i=0; i<n; i++)
    {
        cout<<mas[i]<<" ";
        if (i%10 == 9) cout<<endl;
    }
    cout << endl << endl;
}


//������������ �� ������ �� �����������
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
