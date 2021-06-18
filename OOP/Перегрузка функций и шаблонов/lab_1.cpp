#include <iostream>
using namespace std;

template <typename xType>
bool IsSquareRoot(xType x);

template <typename XType, typename YType>
void IsSquareRoot(XType x, YType *res);

template <typename XType, typename YType>
void IsSquareRoot(XType x, YType &res);

int main()
{
    setlocale(LC_ALL, "RUSSIAN");
    system("color F0");

    int x1, x2, x3;
    cout << "Введите три натуральных числа\n";
    cin >> x1; cin >> x2; cin >> x3;
    if (x1 < 1 || x2 < 1 || x3 < 1)
    {
        cout << "Ошибка. Введите 3 натуральных числа(>=1)" << endl;
        return -1;
    }

    bool res1, res2, res3;
    res1 = IsSquareRoot(x1);
    IsSquareRoot(x2, &res2);
    IsSquareRoot(x3, res3);

    cout << x1 << " является корнем: " << res1 << endl;
    cout << x2 << " является корнем: " << res2 << endl;
    cout << x3 << " является корнем: " << res3 << endl;

    return 0;
}

template <typename xType>
bool IsSquareRoot(xType x)
{
    for (int i = 1; i <= x / 2; i++)
    {
        if (i * i == x) return true;
    }
    return false;
}

template <typename XType, typename YType>
void IsSquareRoot(XType x, YType* res)
{
    *res = false;
    for (int i = 1; i <= x / 2; i++)
    {
        if (i * i == x) *res = true;
    }
}

template <typename XType, typename YType>
void IsSquareRoot(XType x, YType& res)
{
    res = false;
    for (int i = 1; i <= x / 2; i++)
    {
        if (i * i == x) res = true;
    }
}