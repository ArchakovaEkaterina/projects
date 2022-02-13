#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

void Merge_Sort(int* arr, int p, int r);//сортировка слиянием(по возрастанию)
void Merge(int* arr, int p, int q, int r);

//обычное бинарное дерево
struct Node {
	int key;
	Node* left;
	Node* right;
};


//рандомизированное бинарное дерево
struct NodeRand {
	int key;
	int size;
	NodeRand* left;
	NodeRand* right;
	
};

template <typename Type1>//объявление параметра шаблона функции
void Create(Type1** p, int k);//создание дерева

Node* insert(Node* p, int k);//классическая вставка нового узла с ключом k в дерево p, для бинарного дерева поиска

int getsize(NodeRand* p);
void fixsize(NodeRand* p);
NodeRand* rotateright(NodeRand* p);//правый поворот вокруг узла p
NodeRand* rotateleft(NodeRand* q);//левый поворот вокруг узла q
NodeRand* insertroot(NodeRand* p, int k);//вставка нового узла с ключом k в корень дерева p
NodeRand* insertRand(NodeRand* p, int k);//рандомизированная вставка нового узла с ключом k в дерево p

template <typename T>//объявление параметра шаблона функции
void print_tree(T* p, int level);//печать дерева

template <typename Type>//объявление параметра шаблона функции
int Height(Type* p);//подсчет высоты дерева

int main()
{
	setlocale(LC_ALL, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("color F0");

	
	int length;//длина случайной последовательности ключей
	int* arr1;//случайная последовательность ключей
	int* arr2;//отсортированная случайная последовательность ключей

	Node* p1 = NULL;//указатель на корень обычного бинарного дерева для неотсортированной посл-ти
	NodeRand* p2 = NULL;//указатель на корень рандомизированного дерева для неотсортированной посл-ти
	Node* p3 = NULL;//указатель на корень обычного бинарного дерева для отсортированной посл-ти
	NodeRand* p4 = NULL;//указатель на корень рандомизированного дерева для отсортированной посл-ти

	int height1 = 0;//высота обычного бинарного дерева для неотсортированной посл-ти
	int height2 = 0;//высота рандомизированного дерева для неотсортированной посл-ти
	int height3 = 0;//высота обычного бинарного дерева для отсортированной посл-ти
	int height4 = 0;//высота рандомизированного дерева для отсортированной посл-ти
	int min = 301;//минимальная высота дерева для каждого ключа
	int max = 0;//максимальная высота дерева для каждого ключа
	int i,j; 

	srand(time(NULL));
	//for (length = 25; length <= 300; length = length + 25)
	//{
		
		//cout << "Кол-во ключей = " << length << endl;
		
		cout << "Введите кол-во элементов последовательности: ";
		cin >> length;
		if (length <= 0)
		{
			cout << "Введите натуральное число(больше нуля)" << endl;
			return -1;
		}
		arr1 = new int[length];
		arr2 = new int[length];

		//формируем последовательность ключей
		i = 0;
		while (i < length)
		{
			int flag = 0;//есть ли сгенерированный элемент в последовательности
			int temp = rand() % 1000;
			for (j = 0; j < i; j++)
			{
				if (arr1[j] == temp)
				{
					flag++;
				}
			}
			if (flag == 0)
			{
				arr1[i] = temp;
				arr2[i] = temp;
				i++;
			}
		}

		if (length <= 25)
		{
			cout << endl << "Неотсортированная последовательность:" << endl;
			for (i = 0; i < length; i++)
				cout << arr1[i] << " ";
			cout << endl << endl;
		}

		//сортировка второй последовательности слиянием
		Merge_Sort(arr2, 0, length - 1);

		if (length <= 25)
		{
			cout << "Отсортированная последовательность:" << endl;
			for (i = 0; i < length; i++)
				cout << arr2[i] << " ";
			cout << endl << endl;
		}

		for (i = 0; i < length; i++)
		{
			if (i == 0)
			{
				Create(&p1, arr1[i]);
				Create(&p2, arr1[i]);
				p2->size = 1;
			}
			else
			{
				insert(p1, arr1[i]);
				p2 = insertRand(p2, arr1[i]);
			}
		}
		if (length <= 25)
		{
			cout << "Обычное бинарное дерево для неотсортированной последовательности:" << endl;
			print_tree(p1, 0);
		}
		height1 = Height(p1);//подсчет высоты дерева
		cout << "Высота обычного бинарного дерева равна " << height1 << endl << endl;

		if (length <= 25)
		{
			cout << "Рандомизированное дерево для неотсортированной последовательности:" << endl;
			print_tree(p2, 0);
		}
		height2 = Height(p2);//подсчет высоты дерева
		cout << "Высота рандомизированного дерева равна " << height2 << endl << endl;

		for (i = 0; i < length; i++)
		{
			if (i == 0)
			{
				Create(&p3, arr2[i]);
				Create(&p4, arr2[i]);
				p4->size = 1;
			}
			else
			{
				insert(p3, arr2[i]);
				p4 = insertRand(p4, arr2[i]);
			}
		}

		if (length <= 25)
		{
			cout << "Обычное бинарное дерево для отсортированной последовательности:" << endl;
			print_tree(p3, 0);
		}

		height3 = Height(p3);//подсчет высоты дерева
		cout << "Высота обычного бинарного дерева равна " << height3 << endl << endl;

		if (length <= 25)
		{
			cout << "Рандомизированное дерево для отсортированной последовательности:" << endl;
			print_tree(p4, 0);
		}
		height4 = Height(p4);//подсчет высоты дерева
		cout << "Высота рандомизированного дерева равна " << height4  << endl;

		//миннимальная и максимальная высоты
		if (height1 < min)
			min = height1;
		if (height2 < min)
			min = height2;
		if (height3 < min)
			min = height3;
		if (height4 < min)
			min = height4;

		if (height1 > max)
			max = height1;
		if (height2 > max)
			max = height2;
		if (height3 > max)
			max = height3;
		if (height4 > max)
			max = height4;
		cout << "Минимальная высота = " << min << endl;
		cout << "Максимальная высота = " << max << endl << endl;

		min = 301; max = 0;
		delete[] arr1;
		delete[] arr2;
		p1 = NULL;
		p2 = NULL;
		p3 = NULL;
		p4 = NULL;
	//}

	return 0;
}



void Merge_Sort(int* arr, int p, int r)
{
	if (p < r)
	{
		int	q = (int)floor((p + r) / 2);
		Merge_Sort(arr, p, q);
		Merge_Sort(arr, q + 1, r);
		Merge(arr, p, q, r);
	}
}

void Merge(int* arr, int p, int q, int r)
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

	barr[N1] = carr[N2] = INT_MAX;
	i = j = 0;

	for (k = p; k <= r; k++)
	{
		if (barr[i] < carr[j])
		{
			arr[k] = barr[i];
			i++;
		}
		else
		{
			arr[k] = carr[j];
			j++;
		}
	}

}



template <typename T>//объявление параметра шаблона функции
void print_tree(T* p, int level)//печать дерева
{
	if (p != NULL)
	{
		print_tree(p->right, level + 1);//вывод левого поддерева
		for (int i = 0; i < level; i++)
		{
			cout << " ";
		}
		cout << p->key << endl;
		print_tree(p->left, level + 1);//вывод правого поддерева

	}
}

template <typename Type1>//объявление параметра шаблона функции
void Create(Type1** p, int k)//создание дерева
{
	if ((*p) == NULL)
	{
		Type1* elem = new Type1;
		elem->key = k;
		(*p) = elem;
		(*p)->left = (*p)->right = 0;
	}
}


Node* insert(Node* p, int k)//классическая вставка нового узла с ключом k в дерево p, для бинарного дерева поиска
{
	if (p == NULL)
	{
		(p) = new Node;
		if (p != NULL)
		{
			p->left = (p)->right = 0;
			p->key = k;
		}
		return p;
	}

	if (p->key > k)
	{
		p->left = insert(p->left, k);
	}
	else
	{
		p->right = insert(p->right, k);
	}

	return p;
}

template <typename Type>//объявление параметра шаблона функции
int Height(Type* p)//подсчет высоты дерева
{
	int l, r, h = 0;
	if (p != NULL)
	{
		l = Height(p->left);//высота левого дерева
		r = Height(p->right);//высота правого дерева
		h = ((l > r) ? l : r) + 1;//выбираем большую высоту и прибавляем к ней 1 корневой уровень
	}
	return h;
}


int getsize(NodeRand* p)//узнать размер дерева
{
	if (!p)return 0;
	return p->size;
}

void fixsize(NodeRand* p)//задать размер дерева
{
	p->size = getsize(p->left) + getsize(p->right) + 1;
}

NodeRand* rotateright(NodeRand* p)//правый поворот вокруг узла p
{
	NodeRand* q = p->left;
	if (!q)
	{
		return p;

	}
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}


NodeRand* rotateleft(NodeRand* q)//левый поворот вокруг узла q
{
	NodeRand* p = q->right;
	if (!p)
		return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

NodeRand* insertroot(NodeRand* p, int k)//вставка нового узла с ключом k в корень дерева p
{
	if (p == NULL)
	{
		NodeRand* elem = new NodeRand;
		elem->key = k;
		p = elem;
		p->left = p->right = 0;
		p->size = 1;
		return p;
	}
	if (k < p->key)
	{
		p->left = insertroot(p->left, k);
		fixsize(p);
		NodeRand* elem = new NodeRand;
		elem = rotateright(p);
		return elem;
	}
	else
	{
		p->right = insertroot(p->right, k);
		fixsize(p);
		NodeRand* elem = new NodeRand;
		elem = rotateleft(p);
		return elem;
	}
}

NodeRand* insertRand(NodeRand* p, int k)//рандомизированная вставка нового узла с ключом k в дерево p
{
	if (p == NULL)
	{
		NodeRand* elem = new NodeRand;
		elem->key = k;
		p = elem;
		p->left = p->right = 0;
		p->size = 1;
		return p;
	}
	if (rand() % (p->size + 1) == 0)
	{
		NodeRand* elem = new NodeRand;
		elem = insertroot(p, k);
		return elem;//вставка в корень
	}
	else
	{
		if (p->key > k)
		{
			p->left = insertRand(p->left, k);
		}
		else
		{
			p->right = insertRand(p->right, k);
		}
	}
		
	fixsize(p);
	return p;
}