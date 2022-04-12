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
using std::cin;
using std::cout;

template <class T>
AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template <class T>
T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int AList<T>::getlength(void)
{
    return numitems;
}

template <class T>
void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template <class T>
T AList<T>::getitem(int index)
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

template <class T>
void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j + 1] = reprarray[j];
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

template <class T>
void AList<T>::allocate(void)
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

template <class T>
void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j - 1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template <class T>
void AList<T>::deallocate(void)
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
template <class T>
trienode<T>::trienode(T item, bool l, trienode<T> *pt_next, trienode<T> *pt_follow)
{
    data = item;
    last = l;
    next = pt_next;
    follow = pt_follow;
}

/* the get operations */
template <class T>
T trienode<T>::getdata(void)
{
    return data;
}

template <class T>
bool trienode<T>::getlast(void)
{
    return last;
}

template <class T>
trienode<T> *trienode<T>::getnext(void)
{
    return next;
}

template <class T>
trienode<T> *trienode<T>::getfollow(void)
{
    return follow;
}

/* the set operations */
template <class T>
void trienode<T>::setdata(T item)
{
    data = item;
    return;
}

template <class T>
void trienode<T>::setlast(bool l)
{
    last = l;
    return;
}

template <class T>
void trienode<T>::setnext(trienode<T> *pt_next)
{
    next = pt_next;
    return;
}

template <class T>
void trienode<T>::setfollow(trienode<T> *pt_follow)
{
    follow = pt_follow;
    return;
}

/* the constructor creates an empty trie containing just a null pointer at the start */
template <class T>
trie<T>::trie(void)
{
    start = 0;
}

/* the insert and intrie functions are realised recursively starting from the start using the corresponding auxiliary functions */
template <class T>
void trie<T>::insert(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    start = _insert(start, newlist);
    return;
}

template <class T>
bool trie<T>::intrie(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    return contains(start, newlist);
}
/* auxiliary function for insertion */
template <class T>
trienode<T> *trie<T>::_insert(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return 0;
    T key = list[1]; // take the first element of the new list
    if (pt == 0)     // case of null pointer: create a new trienode
    {
        list.remove(1);
        trienode<T> *newnode = new trienode<T>;
        (*newnode).setdata(key); // set the value of the new trienode
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

template <class T>
bool trie<T>::contains(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0 && pt == 0)
        return true;
    T key = list[1];
    if (pt == 0)
        return false;
    if (list.getlength() == 0)
        return false;
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        return contains((*pt).getfollow(), list);
    }
    else
        return contains((*pt).getnext(), list);

    // This function needs to be implemented
}

template <class T>
void trie<T>::display(void)
{
    AList<T> list;
    _display(start, list);
    cout << "\n";
}

template <class T>
void trie<T>::_display(trienode<T> *pt, AList<T> list)
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
                _display((*pt).getfollow(), list);
        }
        else
            _display((*pt).getfollow(), list);
        list.remove(list.getlength());
        if ((*pt).getnext() != 0)
            _display((*pt).getnext(), list);
    }
    return;
}
template <class T>
bool trie<T>::_correct1(trienode<T> *pt, AList<T> list, AList<T> *change_char)
{
    if (pt == 0)
        return false;
    if (list.getlength() == 0 && pt->getlast())
    {
        change_char->append(pt->getdata());
        return true;
    }
    if (list.getlength() == 0)
        return _correct1(pt->getnext(), list, change_char);
    T key = list[1];
    if ((*pt).getdata() == key)
    {
        list.remove(1);
        return _correct1((*pt).getfollow(), list, change_char);
    }
    else
        return _correct1((*pt).getnext(), list, change_char);
}

template <class T>
void trie<T>::correct1(AList<T> list)
{
    cout << "The word ";
    for (int i = 1; i <= list.getlength(); i++)
    {
        cout << list[i];
    }
    if (intrie(list))
    {
        cout << " is in the trie\n";
        return;
    }
    cout << " is not in the trie\n";
    AList<T> *change_char = new AList<T>;
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    if (_correct1(start, newlist, change_char))
    {
        cout << "However, the word ";
        for (int i = 1; i <= list.getlength(); i++)
        {
            cout << list[i];
        }
        cout << (*change_char)[1];
        cout << " is in the trie\n";
        return;
    }
    cout << "The word extend the given word by one symbol is also not in the trie\n";
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that extend the given word (not found in the dictionary) by one symbol. */
}
// template <class T>
// bool trie<T>::_correct2(trienode<T> *pt, AList<T> list, int chance, AList<T> *prefix_list)
// {
//     if (chance < 2)
//     {
//         if (chance == 0 || pt == 0)
//             return false;
//         if (pt->getlast())
//         {
//             prefix_list->append(pt->getdata());
//             return true;
//         }
//         else
//         {
//             bool itself = _correct2(pt->getfollow(), list, chance - 1, prefix_list);
//             if (itself)
//             {
//                 prefix_list->append(pt->getdata());
//                 return true;
//             }
//             else
//                 return _correct2(pt->getnext(), list, chance, prefix_list);
//         }
//     }
//     if (pt == 0 && list.getlength() == 0)
//         return true;
//     if (pt == 0)
//         return false;
//     if (list.getlength() == 0)
//     {
//         if (pt->getlast())
//         {
//             prefix_list->append(pt->getdata());
//             return true;
//         }
//         else
//         {
//             bool itself = _correct2(pt->getfollow(), list, chance - 1, prefix_list);
//             if (itself)
//             {
//                 prefix_list->append(pt->getdata());
//                 return true;
//             }
//             else
//                 return _correct2(pt->getnext(), list, chance, prefix_list);
//         }
//     }
//     T key = list[1];
//     if ((*pt).getdata() == key)
//     {
//         list.remove(1);
//         return _correct2((*pt).getfollow(), list, chance, prefix_list);
//     }
//     else
//         return _correct2((*pt).getnext(), list, chance, prefix_list);
// }

template <class T>
void trie<T>::correct2(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    cout << "The word ";
    for (int i = 1; i <= list.getlength(); i++)
    {
        cout << list[i];
    }
    if (intrie(newlist))
    {
        cout << " is in the trie\n";
        return;
    }
    cout << " is not in the trie";
    newlist.remove(newlist.getlength());
    if (intrie(newlist))
    {
        cout << "\nHowever, the word ";
        for (int i = 1; i <= newlist.getlength(); i++)
        {
            cout << newlist[i];
        }
        cout << " is in the trie\n";
        return;
    }

    newlist.remove(newlist.getlength());
    if (intrie(newlist))
    {
        cout << "\nHowever, the word ";
        for (int i = 1; i <= newlist.getlength(); i++)
        {
            cout << newlist[i];
        }
        cout << " is in the trie\n";
        return;
    }
    cout << ", and word that prefixes of the given word with one or two symbols less is also not in the trie.\n";
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that are prefixes of the given word (not found in the dictionary) with one or two symbols less. */
}

template <class T>
bool trie<T>::_correct3(trienode<T> *pt, AList<T> list, AList<T> *change_char, int *change_char_index)
{
    if (change_char->getlength() >= 1 || pt == 0)
        return contains(pt, list);
    if (pt == 0)
        return false;

    if (pt->getdata() == list[1])
    {
        T key = list[1];
        list.remove(1);
        ++(*change_char_index);
        bool itself = _correct3(pt->getfollow(), list, change_char, change_char_index);
        if (itself)
            return true;
        list.insert(1, key);
        (*change_char_index)--;
    }

    bool flag_next = _correct3(pt->getnext(), list, change_char, change_char_index);

    if (flag_next)
        return true;
    if (pt->getdata() == list[1])
        return false;

    change_char->append(pt->getdata());
    list.remove(1);
    bool flag_follow = _correct3(pt->getfollow(), list, change_char, change_char_index);
    if (flag_follow)
        return true;
    else
        change_char->remove(1);
    return false;
}

template <class T>
void trie<T>::correct3(AList<T> list)
{
    cout << "The word ";
    for (int i = 1; i <= list.getlength(); i++)
    {
        cout << list[i];
    }
    if (!intrie(list))
    {
        cout << " is not in the trie\n";
    }
    else
    {
        cout << " is in the trie\n";
        return;
    }

    AList<T> *change_char = new AList<T>;
    AList<T> newlist;
    int *newint = new int;
    (*newint) = 1;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    if (_correct3(start, newlist, change_char, newint))
    {
        cout << "However, the word ";
        for (int i = 1; i <= list.getlength(); i++)
        {
            if (i == *newint)
                cout << (*change_char)[1];
            else
                cout << list[i];
        }
        cout << " is in the trie\n";
        return;
    }
    cout << "And word from the dictionary that differ from the given word by exactly one symbol is also not in the trie.\n";
    /* This function needs to be implemented. It should try to find the input word in the TRIE. If unsussessful, it should output words from the dictionary that differ from the given word (not found in the dictionary) by exactly one symbol. */
}
