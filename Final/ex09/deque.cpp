//
//  deque.cpp
//
//  Created by KD on 17.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "deque.h"
using std::cin;
using std::cout;

template <class T>
node<T>::node(T item, node<T> *pt_n)
{
    dataitem = item;
    pt_next = pt_n;
}

template <class T>
T node<T>::getdata(void)
{
    return dataitem;
}

template <class T>
node<T> *node<T>::getnext(void)
{
    return pt_next;
}

template <class T>
void node<T>::setdata(T item)
{
    dataitem = item;
    return;
}

template <class T>
void node<T>::setnext(node<T> *pt)
{
    pt_next = pt;
    return;
}

template <class T>
Deque<T>::Deque(void)
{
    first = 0;
    last = 0;
    numitems = 0;
}

template <class T>
int Deque<T>::getlength(void)
{
    return numitems;
}

template <class T>
void Deque<T>::pushback(T value)
{
    node<T> *newnode;
    newnode = new node<T>(value, 0);
    numitems++;
    if (numitems == 1)
    {
        first = newnode;
        last = newnode;
    }
    else
    {
        last->setnext(newnode);
        last = newnode;
    }
    return;
    // This member function needs to be implemented.
}

template <class T>
void Deque<T>::pushfront(T value)
{
    node<T> *newnode;
    newnode = new node<T>(value, first);
    first = newnode;
    numitems++;
    if(numitems == 1)
    {
        last = newnode;
    }
    return;
    // This member function needs to be implemented.
}

template <class T>
bool Deque<T>::isempty(void)
{
    return (numitems == 0);
}

template <class T>
T Deque<T>::popfront(void)
{
    if (numitems == 0)
        return 0;
    T temp;
    temp = first->getdata();
    numitems--;
    if (numitems == 0)
    {
        first = 0;
        last = 0;
    }
    else
    {
        first = first->getnext();
    }
    return temp;

    // This member function needs to be implemented.
}

template <class T>
T Deque<T>::popback(void)
{
    if (numitems == 0)
        return 0;
    T temp;
    temp = last->getdata();
    numitems--;
    if (numitems == 0)
    {
        first = 0;
        last = 0;
    }
    else
    {
        node<T> *tempnode;
        tempnode = first;
        while (tempnode->getnext() != last)
        {
            tempnode = tempnode->getnext();
        }
        last = tempnode;
        last->setnext(0);
    }
    return temp;
    // This member function needs to be implemented.
}

template <class T>
T Deque<T>::front(void)
{
    if (numitems == 0)
        return 0;
    return first->getdata();
    // This member function needs to be implemented.
}

template <class T>
T Deque<T>::back(void)
{
    if (numitems == 0)
        return 0;
    return last->getdata();
    // This member function needs to be implemented.
}

template <class T>
void Deque<T>::printall(void)
{
    cout << "\n"
         << "Deque elements from front to back:\n";
    node<T> *pt = first;
    for (int i = 0; i < numitems; i++)
    {
        cout << (*pt).getdata() << " + ";
        pt = (*pt).getnext();
    }
    cout << "=========\n";
    return;
}
