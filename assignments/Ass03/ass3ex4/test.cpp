//
//  test.cpp
//
//
//  Created by KD on 09.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listext.cpp"
#include "time.h"
using std::cin;
using std::cout;
using std::rand;
using std::srand;

int main()
{
    freopen("test.out", "w", stdout);
    for (int i = 0; i < 10; i++)
    {
        Listext<int> *mylist = new Listext<int>();
        srand(time(0));
        int j;
        cout << std::endl << "Original Data:" << std::endl;
        for (int i = 0; i < 500; i++)
        {
            j = (rand() % 2000) - 1000;
            (*mylist).append(j);
            cout << "ID=" << i << ": " << j << std::endl;
        }
        int result;
        for (int k = 1; k < 251; k++)
        {
            result = (*mylist).select(k);
            cout << k << "'th element: " << result << "\n";
        }
        for (int i = 1; i < 7; i++)
        {
            (*mylist).rotate(3 * i);
            cout << "Rotation by " << 3 * i << " positions:\n";
            (*mylist).prettyprint();
        }
    }
}
