//
//  partition.cpp
//  
//
//  Created by KD on 15.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "partition.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

Partition::Partition(int size)
{
    array = new int[size];
    rank = new int[size];
    numitems = size;
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
        rank[i] = 0;
    }
}

int Partition::getsize(void)
{
    return numitems;
}

int Partition::getparent(int index)
{
    return array[index];
}

int Partition::find(int value)
{
    int root = value;
    while (array[root] != root)
    {
        root = array[root];
    }
    int index = value;
    while (index != root)
    {
        array[index] = root;
        index = array[index];
    }
    return root;
}

void Partition::merge(int item1, int item2)
{
    if (item1 == item2)
        return;
    if (rank[item1] == rank[item2])
    {
        rank[item1] = rank[item1] + 1;
        array[find(item2)] = find(item1);
    }
    else
    {
        if (rank[item1] > rank[item2])
            array[find(item2)] = find(item1);
        else
            array[find(item1)] = find(item2);
    }
    return;
}

void Partition::prettyprint(void)
{
    cout << "Union-Find Array:\n";
    for (int i = 0; i < getsize(); i++)
    {
        cout << "     Parent of " << i << " is " << array[i] << ".\n";
    }
    cout << "---------";
    return;
}

int main()
{
    Partition *mypart = new Partition(100);
    srand(time(0));
    for (int i = 0; i < 75; i++)
    {
        int ii = rand() % 100;
        int jj = rand() % 100;
        cout << "Parent of " << ii << " is " << (*mypart).find(ii) << "\n";
        cout << "Parent of " << jj << " is " << (*mypart).find(jj) << "\n";
        cout << "Merge " << ii << " and " << jj << "\n";
        (*mypart).merge(ii, jj);
    }
    (*mypart).prettyprint();
    return 0;
}
