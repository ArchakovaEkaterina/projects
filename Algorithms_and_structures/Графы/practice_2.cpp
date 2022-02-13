#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

const int N = 12; //кол-во вершин ориентированного ациклического графа
struct elem
{
    int data;
    elem* next;
};
//процедуры работы со стеком
void Create(elem** top, int str);
void Insert(elem** top, int str);//вставка элемента в конец стека
void Remove(elem** top);//удаление элемента из вершины стека
void Print(elem* top);//печать стека


int** CreateMatrix();//функции создания и удаления динамической матрицы(графа)
void MEMCLEAR(int** ptr, int size);

void TopologicalSort(int** graph, int* linearOrder);
void Relax(int u, int v, int** graph, int* shortest, int* pred);
void DagShortestPath(int** graph, int* linearOrder, int s, int* shortest, int* pred);
int main() {
    int** graph = CreateMatrix();
    int kol = 0;//кол-во считанных элементов матрицы
    ifstream file("Input.txt");
    int i, j;//счетчики

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    system("color F0");

    //проверка файла
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

    //считывание графа из файла
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (!(file >> graph[i][j]) && (kol < N * N))
            {
                cout << "Ошибка. Введите "<< N*N << " элементов матрицы\n";
                file.close();
                return -3;
            }
            if (graph[i][j] != 0 && i == j)
            {
                cout << "Ошибка. В графе не может быть петель\n";
                file.close();
                return -4;
            }
            kol++;
        }
    }
    file.close();

    int s; //вершина, от которых будут искаться кратчайшие пути
    cout << "Введите номер вершины графа: ";
    cin >> s;
    if (s<1 || s>N)
    {
        cout << "Вы ввели некорректный номер вершины графа" << endl;
        return -5;
    }
    s = s - 1;
    cout << endl;

    
    int* linearOrder;//Линейное упорядочение графа
    linearOrder = new int[N];
    TopologicalSort(graph, linearOrder);

    cout << "Линейное упорядочение:" << endl;
    for (i = 0; i < N; i++)
    {
        cout << linearOrder[i]+1 << " ";
    }
    cout << endl<<endl;


    int* shortest;//вес кратчайшего пути от заданной вершины к каждой
    int* pred;//предыдущая вершина в кратчайшем пути от заданной вершины к каждой

    shortest = new int[N];
    pred = new int[N];
    
    DagShortestPath(graph, linearOrder, s, shortest,  pred);
    for (i = 0; i < N; i++)
    {
        if (shortest[i] == 32000)
        {
            cout << "Из вершины " << s+1 << " к " << i+1 << " нет пути "<<endl;
        }
        else
        {
            cout << "Кратчайший путь от " << s+1 << " к " << i+1 << " равен " << shortest[i] << endl;
            cout << "    предыдущая вершина - " << pred[i]+1 << endl;
        }
    }
 
    MEMCLEAR(graph, N);
    delete[] linearOrder;
    delete[] shortest;
    delete[] pred;

    return 0;
}

int** CreateMatrix()
{
    int** matrix;//указатель на динамическую матрицу

    matrix = new int* [N];
    for (int i = 0; i < N; i++)
        matrix[i] = new int[N];

    return matrix;
}

void MEMCLEAR(int** ptr, int size)
{
    for (int i = 0; i < size; i++)
        delete[] ptr[i];
    delete[] ptr;
}

//Функция создания стека
void Create(elem** top, int str)
{
    if ((*top) == NULL)
    {
        elem* ptr = new elem;
        ptr->data = str;
        *top = ptr;
        (*top)->next = NULL;
    }
}//Create

//Функция вставки элемента в стек
void Insert(elem** top, int str)
{
    if ((*top) != NULL)
    {
        elem* ptr = new elem;
        ptr->data = str;
        ptr->next = (*top);
        (*top) = ptr;
    }
    else  Create(top, str);
    
}//Insert

//Функция удаления элемента из стека
void Remove(elem** top)
{
    elem* temp = (*top);
    if ((*top)->next != NULL)
    {
        (*top) = (*top)->next;
        (*top)->next = temp->next->next;
        (temp)->next = NULL;
        temp->data = NULL;
        (temp) = NULL;
        delete temp;

    }
    else
    {
        (*top) = NULL;
        delete temp;
    }
}


//Функция печати списка
void Print(elem* top)
{
    int i = 0;
    elem* temp = top;

    if (top != NULL)
    do
    {
        cout << i + 1 << ". " << temp->data+1 << endl;
        temp = temp->next;
        i++;
    } while (temp != NULL);
}//Print


//топологическая сортировка
void TopologicalSort(int** graph, int* linearOrder)
{
    int inDegree[12];//массив входящих степеней вершин
    elem* top = NULL;//указатель на вершину стека(списка вершин с 0й входящей степенью)
    int count = 0;//кол-во вершин в линейном упорядочении
    int i,j;

    for (i = 0; i < N; i++)
    {
        inDegree[i] = 0;
    }
    
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (graph[i][j] != 0)
            {
                inDegree[j]++;
            }
        }
    }


    //добавляем элементы в список next(стек)
    for (int i = 0; i < N; i++)
    {
        if (inDegree[i] == 0)
        {
            if ((top) == NULL)
            {
                Create(&top, i);
            }
            else
            {
                Insert(&top, i);
            }
            inDegree[i] = -1;
        }
    }
    
    if (count == N)//все вершины имеют 0ю степень
    {
        cout << "Граф должен быть ациклическим" << endl;
    }
    while (count < N)
    {
        cout << "Стек:\n";
        Print(top);
        cout << "Степени вершин:" << endl;
        for (i = 0; i < N; i++)
            cout << inDegree[i] << ' ';
        cout << endl;
        cout << "Линейное упорядочение:" << endl;
        for (i = 0; i < count; i++)
        {
            cout << linearOrder[i]+1 << " ";
        }
        cout << endl;

        int u = top->data;
        Remove(&top);
        cout << "u = " << u+1 << endl;
        linearOrder[count] = u;//добавляем вершину u в конец линейного упорядочения
        count++;
        cout << "count = " << count << endl<<endl;
        for (int v = 0; v < N; v++)
        {
            if (graph[u][v]!= 0)
                inDegree[v]--;
            if (inDegree[v] == 0)
            {
                Insert(&top, v);//помещаем вершину в конец стека (списка next)
                inDegree[v] = -1;
            }
        }
    }
    cout << endl;
}

void Relax(int u, int v, int** graph, int* shortest, int* pred)
{
    if (shortest[u] + graph[u][v] < shortest[v])
    {
        shortest[v] = shortest[u] + graph[u][v];
        pred[v] = u;
    }
}

void DagShortestPath(int** graph, int* linearOrder, int s, int* shortest, int* pred)
{
    int v, u;

    for (v = 0; v < N; v++)
    {
        if (v == s)
        {
            shortest[v] = 0;
        }
        else
        {
           shortest[v] = 32000;
        }
        pred[v] = NULL;
    }

    for (u = 0; u < N; u++)
    {
        for (v = 0; v < N; v++)
        {
            if (graph[linearOrder[u]][v] != 0)
            {
                Relax(linearOrder[u], v, graph, shortest, pred);
            }
        }
    }

}