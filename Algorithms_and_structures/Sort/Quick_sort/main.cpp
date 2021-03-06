//?????????? ??????? ????????????? ?? ???????????

#include <iostream>
#include "main.h"

using namespace std;


int main()
{
    setlocale(LC_ALL,"Rus");

    int n;//???-?? ????????? ???????


    //????? ????? ??? ??????
    int mode; //????? ????? ??? ??????
    cout << "???????? ????? ????? ??? ??????(1-12), ? ??????? ?????:\n"
            << "1.??? ????????????? ?????\n"
            << "2.??? ????????????? ?????\n"
            << "3.????????????? ? ????????????? ?????\n"
            << "4.?????? ???-?? ?????, ?????? ???-?? ????????? ? ????? ?????? ?????????? ? ?????? ?????\n"
            << "5.???????? ???-?? ?????\n"
            << "6.????? ????????????? ? ???????? ???????(?? ????????)\n"
            << "7.????? ???-?? ????? ? ?? ?????????????? ???????\n"
            << "8.????? ?? ??????????\n"
            << "9.???? ??????\n"
            << "10.???? ? ???????????? ?????? ?????????\n"
            << "11.???? ? ??????????? ?????????\n"
            << "12.???? ? ????????????? ?????????? ?????????\n";
    cout << "??? ?????: ";
    while (!(cin >> mode) || (mode > 12) || (mode < 1))
    {
        cout << "???????? ????????, ?????????? ??? ???: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    cin.ignore();

    //?????????? ??????? ? ??? ????? ?? ?????? ?????
    reading_result file_result = read_file(mode);
    if (file_result.status != 0)
        return file_result.status;

    int *mas = file_result.mas;
    n = file_result.n;


    cout<<endl<<"???????? ??????:"<< endl;
    print_arr(mas, n);

    //????????? ?????? ?? ???????????
    quicksort(mas, 0, n-1, n);

    //?????????, ???????????? ?? ??????
    bool sorted = arr_is_sorted(mas, n);
    if (sorted == false) {
        cout << "??????. ?? ??????? ????????????? ??????\n";
        return -5;
    }

    cout<<endl<<"??????????????? ??????:"<< endl;
    print_arr(mas, n);


    delete []mas;

    return 0;
}
