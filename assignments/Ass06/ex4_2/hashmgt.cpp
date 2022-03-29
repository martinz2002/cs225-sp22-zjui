//
//  hashmgt.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.cpp"
#include "hashmap.h"
using std::cout;
using std::cin;
using std::hash;

int main()
{
    int type, size, op;
    hashmap<int,int> myhashtable1;
    hashmap<int,double> myhashtable2;
    bool boolresult;
    do
    {
        cout << "Choose your element type:\n";
        cout << "0: int  1: double\n";
        cin >> type ;
        if ((type != 0) && (type != 1))
            cout << "You must choose 0 or 1\n\n";
    }
    while ((type != 0) && (type != 1));
    cout << "Enter a positive integer for the size of your hashtable:\n";
    cin >> size;
    switch(type)
    {
        case 0:
        {
            myhashtable1 = hashmap<int,int>(size);
            break;
        }
        case 1:
        {
            myhashtable2 = hashmap<int,double>(size);
            break;
        }
    }
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "O: quit\n";
            cout << "1: add\n";
            cout << "2: delete\n";
            cout << "3: member\n";
            cout << "4: display\n";
            cin >> op ;
        }
        while ((op < 0) && (op > 4));
        switch(op)
        {
            case 0: return(0);
            case 1:
            {
                cout << "Enter a value of item:\n";
                if (type == 0)
                {
                    int intitem,intkey1;
                    cin >> intitem;
                    cout << "Enter a value of Key:\n";
                    cin >> intkey1;
                    myhashtable1.add(intkey1,intitem);
                }
                
                break;
            }
            case 2:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    int intitem;
                    cin >> intitem;
                    myhashtable1.remove(intitem);
                }
                
                break;
            }
            case 3:
            {
                cout << "Enter a value:\n";
                if (type == 0)
                {
                    int intitem;
                    int intkey2;
                    cout << "Enter a value of Key:\n";
                    cin >> intkey2;
                    cin >> intitem;
                    boolresult = myhashtable1.member(intkey2,intitem);
                }
                
                if (boolresult == true)
                    cout << "The value is in the hashtable.\n";
                else
                    cout << "The value is not in the hashtable.\n";
                break;
            }
            case 4:
            {
                if (type == 0)
                    myhashtable1.display();
                else
                    myhashtable2.display();
            }
        }
    }
    while (op != 0);
    return(0);
}
