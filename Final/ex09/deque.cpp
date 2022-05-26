//
//  deque.cpp
//
//  Created by KD on 17.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "deque.h"
using std::cout;
using std::cin;

template<class T> node<T>::node(T item, node<T> *pt_n)
{
    dataitem = item;
    pt_next = pt_n;
}

template<class T> T node<T>::getdata(void)
{
    return dataitem;
}

template<class T> node<T> *node<T>::getnext(void)
{
    return pt_next;
}

template<class T> void node<T>::setdata(T item)
{
    dataitem = item;
    return;
}

template<class T> void node<T>::setnext(node<T> *pt)
{
    pt_next = pt;
    return;
}

template<class T> Deque<T>::Deque(void)
{
    first = 0;
    last = 0;
    numitems = 0;
}

template<class T> int Deque<T>::getlength(void)
{
    return numitems;
}

template<class T> void Deque<T>::pushback(T value)
{
    // This member function needs to be implemented.
}

template<class T> void Deque<T>::pushfront(T value)
{
    // This member function needs to be implemented.
}

template<class T> bool Deque<T>::isempty(void)
{
    return (numitems == 0);
}

template<class T> T Deque<T>::popfront(void)
{
    // This member function needs to be implemented.
}

template<class T> T Deque<T>::popback(void)
{
    // This member function needs to be implemented.
}

template<class T> T Deque<T>::front(void)
{
    // This member function needs to be implemented.
}

template<class T> T Deque<T>::back(void)
{
    // This member function needs to be implemented.
}

template<class T> void Deque<T>::printall(void)
{
    cout << "\n" << "Deque elements from front to back:\n";
    node<T> *pt = first;
    for (int i = 0; i < numitems; i++)
    {
        cout << (*pt).getdata() << " + ";
        pt = (*pt).getnext();
    }
    cout << "=========\n";
    return;
}
