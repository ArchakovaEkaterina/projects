#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;

struct Node {
    char key;
    Node* left;
    Node* right;
};

void Create(Node** p, char s);//создание корня дерева

Node* insert(Node* p, char k);//классическаяя вставка нового узла с ключом k в дерево p, для бинарного дерева поиска


void print_tree(Node* p, int level);//печать дерева

Node* find(Node* p, char k);//поиск ключа k в дереве p

void countOfSigns(Node* p, int* count, char* array, int sizeOfArray);//подсчет кол-ва листьев с гласными ключами

int Height(Node* p);//высота дерева

int remove(Node** root, int k);//удаление из дерева p найденного узла с ключом k




int main()
{
    int mode;//выбор операции
    char s;
    int size = 0; //кол-во вершин в дереве
    int height = 0;//высота дерева
    int count = 0;//кол-во листьев в дереве с гласными ключами
    Node* p = NULL;//указатель на корень дерева
    ifstream file("Input.txt");
    char array[] = { 'А', 'а', 'е', 'Е', 
                    'О', 'о', 'И', 'и', 'Ы', 'ы', 
                    'Ю','ю', 'У', 'у', 'э', 'Э' };//массив гласных букв
    int sizeOfArray = sizeof(array);
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
        file.close();
        return -2;
    }


    while (file.peek() != EOF)
    {
        file >> s;
        if ((s >= 'а' && s <= 'я') || (s >= 'А' && s <= 'Я'))
        {
            if (size == 0)
            {
                Create(&p, s);
            }
            else
            {
                insert(p, s);
            }
            size++;
        }
    }

    file.close();
    if (size == 0)
    {
        cout << "Введите в файл значение хотя бы одного узла" << endl;
        return -3;
    }

    do
    {
        print_tree(p, 0);
        mode = 0;
        cout << "Выберете операцию:\n"
            << "1.Поиск в дереве узла с заданным ключом\n"
            << "2.Вставка узла в дерево\n"
            << "3.Удаление узла из дерева.\n"
            << "4.Узнать высоту дерева и кол-во узлов\n"
            << "5.Подсчет кол-ва гласных в листьях\n"
            << "6.Завершить работу\n";
        cout << "Ваш Выбор: ";
        while (!(cin >> mode) || (mode > 6) || (mode < 1))
        {
            cout << "Неверное значение, попробуйте еще раз: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
        }
        cin.ignore();


        switch (mode)
        {
        case 1://Поиск в дереве узла с заданным ключом
        {
            cout << "Введите ключ узла, который хотите найти: ";
            if (!(cin >> s) || !( (s >= 'а' && s <= 'я') || (s >= 'А' && s <= 'Я')))
            {
                cout << "Ключ должен быть буквой русского алфавита" << endl << endl;
                break;
            }
            if (find(p, s) != NULL)
                cout << "Узел с ключом " << s << " находится в дереве\n\n";
            else
                cout << "Узла с ключом " << s << " нет в дереве\n\n";
            break;
        }
        case 2://вставка узла в дерево
        {
            cout << "Введите ключ нового узла: ";
            if (!(cin >> s) || !( (s >= 'а' && s <= 'я') || (s >= 'А' && s <= 'Я')))
            {
                cout << "Ключ должен быть буквой русского алфавита\n\n";
                break;
            }
            insert(p, s);
            size++;
            cout << "Измененное дерево:" << endl;
            print_tree(p, 0);
            cout << endl;
            break;
        }
        case 3://Удаление узла из дерева
        {
            cout << "Введите ключ удаляемого узла: ";
            if (!(cin >> s) || !( (s >= 'а' && s <= 'я') || (s >= 'А' && s <= 'Я')))
            {
                cout << "Ключ должен быть буквой русского алфавита\n\n";
                break;
            }
            int found = remove(&p, s);
            if (found != 0)
                size--;
            if (size == 0)
                cout << "Удален корень дерева" << endl;
            else
            {
                cout << "Измененное дерево:\n";
                print_tree(p, 0); cout << endl;
            }
           
            break;
        }
        case 4://Узнать высоту дерева и кол-во узлов
        {
            height = Height(p);
            cout << "Количество узлов дерева: " << size << endl;
            cout << "Высота дерева: " << height << endl << endl;
            break;
        }
        case 5://Подсчет кол-ва гласных в листьях
        {
            count = 0;
            countOfSigns(p, &count, array, sizeOfArray);
            cout << "Кол-во гласных в листьях = " << count << endl << endl;
            break;
        }
        case 6://Завершить работу
        {
            break;
        }
        }
    } while (mode != 6);
    

    return 0;
}


void print_tree(Node* p, int level)
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

void Create(Node** p, char s)
{
    if ((*p) == NULL)
    {
        Node* elem = new Node;
        elem->key = s;
        (*p) = elem;
        (*p)->left = (*p)->right = 0;
    }
}


Node* insert(Node* p, char k)//классическая вставка нового узла с ключом k в дерево p, для бинарного дерева поиска
{
    if (p==NULL)
    {
        (p)= new Node;
        p->left = (p)->right = 0;
        p->key = k;
        
        return p;
    }

    if (p->key > k)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);

    return p;
}


Node* find(Node* p, char k)//поиск ключа k в дереве p
{
    if (!p)
        return p;
    if (k == p->key)
        return p;
    if (k < p->key)
        return find(p->left, k);
    else
        return find(p->right, k);
}


void countOfSigns(Node* p, int* count, char* array, int sizeOfArray)//подсчет кол-ва листьев с гласными ключами
{
    if (p)
    {
        countOfSigns(p->left, count, array, sizeOfArray);
        if ((p->right == NULL) && (p->left == NULL))
        {
            for (int i = 0; i < sizeOfArray; i++)
            {
                if (p->key == array[i])
                {
                    (*count)++;
                    break;
                }
                    
            }
        }
        countOfSigns(p->right, count, array, sizeOfArray);
    }
    
}//countOfSigns

int Height(Node* p)//высота дерева
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


int remove(Node** root, int k)//удаление из дерева p найденного узла с ключом k
{
    Node* p = *root;//запоминаем корень
    Node* parent = NULL;//предок удаляемого узла

    //поиск узла по ключу
    int found = 0;//нашли узел с данным ключом
    while (p && !found)
    {
        if (k == p->key) found = 1;
        else if (k < p->key)
        {
            parent = p;// запоминаем предыдущий
            p = p->left;
        }   
        else
        {
            parent = p;// запоминаем предыдущий
            p = p->right;
        }
            
    }
    if (!found)
    {
        cout << "Узла с таким ключом нет в дереве" << endl<<endl;
        return 0;
    }
    
    //у узла нет потомков
    if ((p->left == 0) && (p->right == 0))
    {
        if (parent == NULL)
        {
            *root = NULL;

            p = NULL;
        }
        else
        {
            if (p == parent->right)
                parent->right = NULL;
            else
                parent->left = NULL;
        }
       
        delete p;
    }else
    //у узла есть поддерево справа
    if ((p->left == NULL) && (p->right != NULL))
    {
        if (parent == 0)//удаляем корень
        {
            *root = p->right;
        }else
        if (p == parent->right)
            parent->right = p->right;
        else
            parent->left = p->right;
        delete p;
    }else
    //у узла есть поддерево слева
    if ((p->left != NULL) && (p->right == NULL))
    {
        if (parent == 0)//удаляем корень
        {
            *root = p->left;
        }else
        if (p == parent->right)
            parent->right = p->left;
        else
            parent->left = p->left;
        delete p;
    }else
    //у узла есть оба потомка
    if ((p->left != NULL) && (p->right != NULL))
    {
        Node* parent1 = p;//предок у преемника
        Node* pNext = p->right;//преемник узла
        while (pNext->left != NULL)//минимальный элемент в правом поддереве - самый левый
        {
            parent1 = pNext;
            pNext = pNext->left;
        }
        
        p->key = pNext->key;//заменяем значение нужного узла
        if (parent1 == p)//удаляем правую вершину, если она является преемником
        {
            if (pNext->right != NULL)
            {
                p->right = pNext->right;
            }
            else
            {
                p->right = NULL;
            }
        }else
        if (pNext->right == NULL)
        {
            parent1->left = NULL;//изменяем указатели родителя преемника
        }
        else
        {
            parent1->left = pNext->right;//изменяем указатели родителя преемника
        }
        
    }
    
    return 1;
}
