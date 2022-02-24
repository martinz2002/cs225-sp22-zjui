
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.cpp"
#define MAXLEN 20
using namespace std;

int type, len, data[MAXLEN], k;

int main()
{
    // freopen("list.in.txt", "r", stdin);
    // freopen("list.out.txt", "w", stdout);

    cin >> type;
    cin >> len; // Data Generator will guarentee that len is smaller than maxlen

    for (int i = 0; i < len; i++)
        cin >> data[i];

    cin >> k;

    // Create a new object
    AList<int> myList1;
    AList<double> myList2;
    AList<char> myList3;
    switch (type)
    {
    case 0: // int
        myList1 = AList<int>(len);
        break;

    case 1: // double
        myList2 = AList<double>(len);
        break;

    case 2: // char
        myList3 = AList<char>(len);
        break;
    default:
        cout << "Invalid type. Terminated.";
        return 0;
        break;
    }

    if (type == 0)
    {
        // Append data
        for (int i = 0; i < myList1.getlength(); i++)
        {
            myList1.append(data[i]);
        }

        // Delete the last k data
        myList1.delete_last(k);
        cout << k;
        for (int i = 0; i < myList1.getlength(); i++)
        {
            cout << myList1.getitem(i) << ' ';
        }
        cout << endl;
    }
    else if (type == 1)
    {
        // Append data
        for (int i = 0; i < myList2.getlength(); i++)
        {
            myList2.append(data[i]);
        }

        // Delete the last k data
        myList2.delete_last(k);
        cout << k;
        for (int i = 0; i < myList2.getlength(); i++)
        {
            cout << myList2.getitem(i) << ' ';
        }
        cout << endl;
    }
    else if (type == 3)
    {
        // Append data
        for (int i = 0; i < myList2.getlength(); i++)
        {
            myList3.append(data[i]);
        }

        // Delete the last k data
        myList3.delete_last(k);
        cout << k;
        for (int i = 0; i < myList3.getlength(); i++)
        {
            cout << myList3.getitem(i) << ' ';
        }
        cout << endl;
    }
    return 0;
}