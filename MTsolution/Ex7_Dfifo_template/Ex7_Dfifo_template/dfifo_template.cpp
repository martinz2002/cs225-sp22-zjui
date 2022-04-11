//
//  dfifo.cpp
//  
//
//  Created by KD on 16.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "dfifo.h"
using std::cout;
using std::cin;

template<class T> node<T>::node(T item, node<T> *pt_n, node<T> *pt_p)
{
    dataitem = item;
    pt_next = pt_n;
    pt_previous = pt_p;
}

template<class T> T node<T>::getdata(void)
{
    return dataitem;
}

template<class T> node<T> *node<T>::getnext(void)
{
    return pt_next;
}

template<class T> node<T> *node<T>::getprevious(void)
{
    return pt_previous;
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

template<class T> void node<T>::setprevious(node<T> *pt)
{
    pt_previous = pt;
    return;
}

template<class T> Dfifo<T>::Dfifo(void)
{
    dummy = new node<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numitems = 0;
}

template<class T> int Dfifo<T>::getlength(void)
{
    return numitems;
}

template<class T> void Dfifo<T>::pushback(T value)
{
    node<T> *lpt;
    lpt = (*dummy).getprevious();
    node<T> *pt = new node<T>;
    (*pt).setdata(value);
    (*pt).setnext(dummy);
    (*pt).setprevious(lpt);
    (*dummy).setprevious(pt);
    (*lpt).setnext(pt);
    ++numitems;
    return;
}

template<class T> T Dfifo<T>::popfront(void)
{
    node<T> *pt;
    pt = (*dummy).getnext();
    node<T> *pt_i2;
    pt_i2 = (*pt).getnext();
    (*dummy).setnext(pt_i2);
    (*pt_i2).setprevious(dummy);
    numitems -= 1;
    return (*pt).getdata();
}

template<class T> T Dfifo<T>::front(void)
{
    node<T> *pt;
    pt = (*dummy).getnext();
    return (*pt).getdata();
}

template<class T> bool Dfifo<T>::isempty(void)
{
    return (numitems == 0);
}

template<class T> void Dfifo<T>::reverse(void)
{
    // This function needs to be implemented.
}

template<class T> void Dfifo<T>::display(void)
{
    cout << "The queue elements from front to back are:\n";
    node<T> *pt;
    pt = (*dummy).getnext();
    for (int i = 0; i < numitems; i++)
    {
        cout << i << ": " << (*pt).getdata() << "\n";
        pt = (*pt).getnext();
    }
    cout << "\n";
    return;
}
