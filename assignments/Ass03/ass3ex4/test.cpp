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
        int data[15] = {13,21,7,8,5,1,3,2,6,11,10,9,4,17,18};
        for (j = 0; j < 15; j++)
        {
            mylist->append(data[j]);
            cout << data[j] << " ";
        }
        // for (int i = 0; i < 50; i++)
        // {
        //     j = (rand() % 2000) - 1000;
        //     (*mylist).append(j);
        //     cout << "ID=" << i << ": " << j << std::endl;
        // }
        // int result;
        // for (int k = 1; k < 45; k++)
        // {
        //     result = (*mylist).select(k);
        //     cout << k << "'th element: " << result << "\n";
        // }

        (*mylist).rotate(4);
        mylist->prettyprint();
        // for (int i = 1; i < 7; i++)
        // {
        //     (*mylist).rotate(3 * i);
        //     cout << "Rotation by " << 3 * i << " positions:\n";
        //     (*mylist).prettyprint();
        // }
    }
}
