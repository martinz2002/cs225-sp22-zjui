//
//  trie.cpp
//  
//
//  Created by KD on 20.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

/* the constructor creates a node with the given value and next and follow pointers */
template<class T> trienode<T>::trienode(T item, bool l, trienode<T> *pt_next, trienode<T> *pt_follow)
{
    data = item;
    last = l;
    next = pt_next;
    follow = pt_follow;
}

/* the get operations */
template<class T> T trienode<T>::getdata(void)
{
    return data;
}

template<class T> bool trienode<T>::getlast(void)
{
    return last;
}

template<class T> trienode<T> *trienode<T>::getnext(void)
{
    return next;
}

template<class T> trienode<T> *trienode<T>::getfollow(void)
{
    return follow;
}

/* the set operations */
template<class T> void trienode<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void trienode<T>::setlast(bool l)
{
    last = l;
    return;
}

template<class T> void trienode<T>::setnext(trienode<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void trienode<T>::setfollow(trienode<T> *pt_follow)
{
    follow = pt_follow;
    return;
}

/* the constructor creates an empty trie containing just a null pointer at the start */
template<class T> trie<T>::trie(void)
{
    start = 0;
}

/* the insert and intrie functions are realised recursively starting from the start using the corresponding auxiliary functions */
template<class T> void trie<T>::insert(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    start = _insert(start, newlist);
    return;
}

template<class T> bool trie<T>::intrie(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    return contains(start, newlist);
}

/* auxiliary function for insertion */
template<class T> trienode<T> *trie<T>::_insert(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return 0;
    T key = list[1];  // take the first element of the new list
    if (pt == 0)  // case of null pointer: create a new trienode
    {
        list.remove(1);
        trienode<T> *newnode = new trienode<T>;
        (*newnode).setdata(key);  // set the value of the new trienode
        /* mark the trienode as final, if the inout list is used up */
        if (list.getlength() == 0)
            (*newnode).setlast(true);
        /* recursively proceed with the next element of the input list */
        (*newnode).setfollow(_insert((*newnode).getfollow(), list));
        return newnode;
    }
    if ((*pt).getdata() == key) // case of a prefix already in the trie
    {
        list.remove(1);
        if (list.getlength() == 0)
        {
            (*pt).setlast(true);
            return pt;
        }
        /* just skip over the prefix */
        (*pt).setfollow(_insert((*pt).getfollow(), list));
    }
    else
        /* otherwise follow the next pointer */
        (*pt).setnext(_insert((*pt).getnext(), list));
    return pt;
}

template<class T> bool trie<T>::contains(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return false;
    if (pt == 0)
        return false;
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
            return (*pt).getlast();
        /* proceed recursively with the follow pointer */
        return contains((*pt).getfollow(), list);
    }
    /* otherwise follow the next pointer */
    return contains((*pt).getnext(), list);
}

template<class T> void trie<T>::display(void)
{
    AList<T> list;
    _display(start, list);
    cout << "\n";
}

template<class T> void trie<T>::_display(trienode<T> * pt, AList<T> list)
{
    if (pt != 0)
    {
        list.append((*pt).getdata());
        if ((*pt).getlast() == true)
        {
            cout << "Trie entry: ";
            for (int i = 1; i <= list.getlength(); i++)
            {
                cout << list[i];
                if (i != list.getlength())
                    cout << " , ";
                else
                    cout << "\n";
            }
            if ((*pt).getfollow() != 0)
                _display((*pt).getfollow(),list);
        }
        else
            _display((*pt).getfollow(), list);
        list.remove(list.getlength());
        if ((*pt).getnext() != 0)
            _display((*pt).getnext(), list);
    }
    return;
}

template<class T> void trie<T>::correct1(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    AList<T> *extlist = new AList<T>(10);   // initialise an empty list
    bool b = contains1(start, newlist, extlist);
    if (b)
    {
        cout << "The word appears in the dictionary.\n";
    }
    else
    {
        cout << "The word does not appear in the dictionary.\n";
        if ((*extlist).getlength() > 0)
        {
            cout << "The dictionary contains words that extend the given input by one of the following characters:\n";
            for (int i = 1; i <= (*extlist).getlength(); i++)
            {
                cout << (*extlist)[i] << "  ";
            }
            cout << "\n\n";
        }
    }
    return;
}

template<class T> bool trie<T>::contains1(trienode<T> *pt, AList<T> list, AList<T> *extlist)
{
    if (pt == 0)
        return false;
    if (list.getlength() == 0)
    {
        T nextkey;
        while (pt != 0)
        {
            T nextkey = (*pt).getdata();
            if ((*pt).getlast())
                (*extlist).append(nextkey);
        }
        return false;
    }
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
        {
            pt = (*pt).getfollow();
            if (pt != 0)
            {
                T nextkey = (*pt).getdata();
                if ((*pt).getlast())
                    (*extlist).append(nextkey);
            }
            return false;
        }
        /* proceed recursively with the follow pointer */
        return contains1((*pt).getfollow(), list, extlist);
    }
    /* otherwise follow the next pointer */
    return contains1((*pt).getnext(), list, extlist);
}

template<class T> void trie<T>::correct2(AList<T> list)
{
    AList<T> newlist, newlist1, newlist2;
    int num = list.getlength();
    for (int i = 1; i <= num; i++)
    {
        newlist.append(list[i]);
        if (i < num)
            newlist1.append(list[i]);
        if (i < num - 1)
            newlist2.append(list[i]);
    }
    bool b = contains(start, newlist);
    bool b1 = contains(start, newlist1);
    bool b2 = contains(start, newlist2);
    if (b)
    {
        cout << "The word appears in the dictionary.\n";
    }
    if (b1)
    {
        cout << "The prefix with one character less appears in the dictionary.\n";
    }
    if (b2)
    {
        cout << "The prefix with two characters less appears in the dictionary.\n";
    }
    if (!b && !b1 && !b2)
    {
        cout << "Neither the word nor the prefixes with one or two characters less appear in the dictionary.\n";
    }
    return;
}

template<class T> void trie<T>::correct3(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    AList<T> outlist = AList<T>();   // initialise an empty list
    contains3(start, newlist, outlist);
    return;
}

template<class T> void trie<T>::contains2(trienode<T> *pt, AList<T> list, AList<T> outlist)
/* The function contains2 is used when the exact list has to be found in the dictionary, while outlist already contains a modified character. */
{
    if (list.getlength() == 0)
        return;
    if (pt == 0)
        return;
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        outlist.append(key);
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
        {
            if ((*pt).getlast())
            {
                cout << "The list with the following elements is in the dictionary:\n";
                for (int i = 1; i <= outlist.getlength(); i++)
                {
                    cout << outlist[i] << "  ";
                }
                cout << "\n";
            }
        }
        else
        {
            /* proceed recursively with the follow pointer */
            contains2((*pt).getfollow(), list, outlist);
        }
    }
    else
    {
        /* otherwise follow the next pointer */
        contains2((*pt).getnext(), list, outlist);
    }
    return;
}

template<class T> void trie<T>::contains3(trienode<T> *pt, AList<T> list, AList<T> outlist)
/* The function contains3 is used when list can be modified in one position and the modified list has to be found in the dictionary. */
{
    if (list.getlength() == 0)
        return;
    if (pt == 0)
        return;
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.insert(i, list[i]);
    }
    T key = list[1];  // examine the first element of the input list
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        outlist.append(key);
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
        {
            if ((*pt).getlast())
            {
                cout << "The list with the following elements is in the dictionary:\n";
                for (int i = 1; i <= outlist.getlength(); i++)
                {
                    cout << outlist[i] << "  ";
                }
                cout << "\n";
            }
        }
        else /* proceed recursively with the follow pointer */
            contains3((*pt).getfollow(), list, outlist);
    }
    else
    {
        list.remove(1);
        outlist.append((*pt).getdata());
        /* if the input list is used up, check if the last element was marked as terminal in the trie */
        if (list.getlength() == 0)
        {
            if ((*pt).getlast())
            {
                cout << "The list with the following elements is in the dictionary:\n";
                for (int i = 1; i <= outlist.getlength(); i++)
                {
                    cout << outlist[i] << "  ";
                }
                cout << "\n";
            }
        }
        else /* proceed recursively with the follow pointer */
            contains2((*pt).getfollow(), list, outlist);
    }
    /* In addition follow the next pointer */
    outlist.remove(outlist.getlength());
    contains3((*pt).getnext(), newlist, outlist);
    return;
}
