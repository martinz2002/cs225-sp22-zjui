//
//  bpgraph.cpp
//  
//
//  Created by KD on 12.04.21.
//  Modified on 07.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bpgraph.h"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

template<class T> fifo<T>::fifo(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    first = 0;
    last = -1;
    reprarray = new T[maxsize];
}

template<class T> T &fifo<T>::operator[](int index)
{
    if ((1 <= index) && (index <= numitems))
    {
        int relindex = (index + first -1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "Error: index " << index << " out of range.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> int fifo<T>::getlength(void)
{
    return numitems;
}

template<class T> bool fifo<T>::isempty(void)
{
    if (numitems == 0)
        return true;
    else
        return false;
}

template<class T> T fifo<T>::front(void)
{
    if (isempty() == false)
        return reprarray[first];
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> T fifo<T>::back(void)
{
    if (isempty() == false)
    {
        int relindex = (first + numitems - 1) % maxsize;
        return reprarray[relindex];
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::pushback(T value)
{
    if (numitems == maxsize)
        allocate();
    last = ++last % maxsize;
    reprarray[last] = value;
    ++numitems;
    return;
}

template<class T> T fifo<T>::popfront(void)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (isempty() == false)
    {
        T frontelement = reprarray[first];
        first = ++first % maxsize;
        --numitems;
        return frontelement;
    }
    else
    {
        cout << "The queue is empty.\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void fifo<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

template<class T> void fifo<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        int pos = (i + first) % maxsize;
        newarray[i] = reprarray[pos];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    first = 0;
    last = numitems -1;
    return;
}

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

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool AList<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template<class T> bool AList<T>::equal(AList<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void AListsort<T>::bsort(void)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    for (int i = 0; i < numitems - 1; ++i)
    {
        for (int j = i+1; j < numitems; ++j)
        {
            if (reprarray[i] > reprarray[j])
            {
                T temp;
                temp = reprarray[i];
                reprarray[i] = reprarray[j];
                reprarray[j] = temp;
            }
        }
    }
    return;
}

template<class T> void AListsort<T>::qsort(int thr)
{
    int numitems = AList<T>::numitems;
    T *reprarray;
    reprarray = AList<T>:: reprarray;
    if (thr < 20)
        thr = 20;
    if (thr > 100)
        thr = 100;
    if (numitems <= thr)
    {
        bsort();
        return;
    }
    else
    {
        srand(time(0));
        int index = rand() % numitems;
        T pivot = reprarray[index];
        AListsort<T> lsmall = AListsort<T>(10);
        AListsort<T> lpivot = AListsort<T>(5);
        AListsort<T> llarge = AListsort<T>(10);
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] < pivot)
                lsmall.append(reprarray[i]);
            else if (reprarray[i] == pivot)
                lpivot.append(reprarray[i]);
            else
                llarge.append(reprarray[i]);
        }
        lsmall.qsort(thr);
        llarge.qsort(thr);
        for (int i = 0; i < numitems; ++i)
        {
            if (i < lsmall.getlength())
                reprarray[i] = lsmall.getitem(i+1);
            else if (i < (lsmall.getlength() + lpivot.getlength()))
                reprarray[i] = lpivot.getitem(i - lsmall.getlength() + 1);
            else
                reprarray[i] = llarge.getitem(i - lsmall.getlength() - lpivot.getlength() + 1);
        }
        return;
    }
}

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template<class T> vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
}

template<class T> int vertex<T>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template<class T> T vertex<T>::getitem(void)
{
    return vertexid;
}

template<class T> vertex<T> * vertex<T>::getnext(void)
{
    return next;
}

template<class T> vertex<T> * vertex<T>::getprevious(void)
{
    return previous;
}

template<class T> elist<T> * vertex<T>::getedges(void)
{
    return edgelist;
}

template<class T> void vertex<T>::setitem(T item)
{
    vertexid = item;
    return;
}

template<class T> void vertex<T>::setnext(vertex<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void vertex<T>::setprevious(vertex<T> *pt_prev)
{
    previous = pt_prev;
    return;
}

template<class T> void vertex<T>::setedges(elist<T> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template<class T> vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template<class T> int vertexlist<T>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template<class T> int vertexlist<T>::countedges(void)
{
    int count = 0;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template<class T> void vertexlist<T>::append(T item)
{
    vertex<T> * pt_last = (*dummy).getprevious();
    vertex<T> * pt_new = new vertex<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template<class T> void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template<class T> bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. */
template<class T> bool vertexlist<T>::remove(T item)
{
    bool result = false;
    vertex<T> * location = 0;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item)
        {
            if ((*pt).getedges() != 0)
            {
                cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
                return result;
            }
            result = true;
            vertex<T> * pt_prev = (*location).getprevious();
            vertex<T> * pt_next = (*location).getnext();
            (*pt_prev).setnext(pt_next);
            (*pt_next).setprevious(pt_prev);
            --numvertices;
        }
        pt = (*pt).getnext();
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template<class T> void vertexlist<T>::addedge(T first, T second, bool m)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second, m);
            else
            {
                elist<T> * newlist = new elist<T>(second, m);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T> * newlist = new elist<T>(second, m);
    (*pt).setedges(newlist);
    return;
}

/* Marking and unmarking an edge as matched is done by first locating the origin vertex in the vertex list, then locating the destination vertex in the associated edgelist. */
template<class T> void vertexlist<T>::matchedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).match(second);
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> void vertexlist<T>::unmatchedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).unmatch(second);
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template<class T> void vertexlist<T>::removeedge(T first, T second)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> * pt_edges = (*pt).getedges();
            if (pt_edges != 0)
            {
                (*pt_edges).remove(second);
                if ((*pt_edges).getlength() == 0)
                    (*pt).setedges(0);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> bool vertexlist<T>::ismatched(T node1, T node2)
{
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node1)
        {
            elist<T> *edges = (*pt).getedges();
            return (*edges).ismatched(node2);
        }
        pt = (*pt).getnext();
    }
    return 0;
}

template<class T> elist<T> * vertexlist<T>::edges(T node)
{
    vertex<T> * pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            return (*pt).getedges();
        pt = (*pt).getnext();
    }
    return 0;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template<class T> edgelist<T> * vertexlist<T>::outgoingedges(T item)
{
    edgelist<T> * result = new edgelist<T>;
    vertex<T> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item)
        {
            elist<T> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

/* Analogously for the list of all matched outgoing edges. */
template<class T> edgelist<T> * vertexlist<T>::matchededges(T item)
{
    edgelist<T> * result = new edgelist<T>;
    vertex<T> * ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item)
        {
            elist<T> * edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addallmatched(item, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

template<class T> AList<T> *vertexlist<T>:: getlist(void)
{
    AList<T> *result = new AList<T>(); // create an empty output list
    vertex<T> * pt = (*dummy).getnext();
    // scan the vertex list
    for (int i = 0; i < numvertices; i++)
    {
        (*result).append((*pt).getitem());
        pt = (*pt).getnext();
    }
    return result;
}

/* for the perfect matching */
template<class T> void vertexlist<T>::adjustmatching1(edgelist<T> *path)
{
    /* Adjust matching of (b,g) edges. The edgelist contains an odd-length alternating sequence of (b,g) and (g,b) edges. */
    bool b = true;  // used for the alternation
    for (int i = 0; i < (*path).getnumedges(); i++)
    {
        if (b)
            matchedge((*path).getitem1(i), (*path).getitem2(i));
        else
            unmatchedge((*path).getitem2(i), (*path).getitem1(i));
        b = !b; // swap orientation for the next edge
    }
    return;
}

template<class T> void vertexlist<T>::adjustmatching2(edgelist<T> *path)
{
    /* Analogous adjustment of matching of (g,b) edges. */
    bool b = true;
    for (int i = 0; i < (*path).getnumedges(); i++)
    {
        if (b)
            matchedge((*path).getitem2(i), (*path).getitem1(i));
        else
            unmatchedge((*path).getitem1(i), (*path).getitem2(i));
        b = !b;
    }
    return;
}

/* only for testing */
template<class T> void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> * pte = outgoingedges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

template<class T> void vertexlist<T>::prettyprintmatching(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Matching edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> * pte = matchededges((*ptv).getitem());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no associated edgelists. The elements of the list are organised by the neighbour class. */
template<class T> neighbour<T>::neighbour(T item, neighbour<T> *pt_next, neighbour<T> *pt_prev, bool m)
{
    secondvertex = item;
    matched = m;
    next = pt_next;
    previous = pt_prev;
}

template<class T> T neighbour<T>::getitem(void)
{
    return secondvertex;
}

template<class T> bool neighbour<T>::ismatched(void)
{
    return matched;
}

template<class T> neighbour<T> * neighbour<T>::getnext(void)
{
    return next;
}

template<class T> neighbour<T> * neighbour<T>::getprevious(void)
{
    return previous;
}

template<class T> void neighbour<T>::setitem(T item)
{
    secondvertex = item;
    return;
}

template<class T> void neighbour<T>::match(void)
{
    matched = true;
    return;
}

template<class T> void neighbour<T>::unmatch(void)
{
    matched = false;
    return;
}

template<class T> void neighbour<T>::setnext(neighbour<T> * pt)
{
    next = pt;
    return;
}

template<class T> void neighbour<T>::setprevious(neighbour<T> * pt)
{
    previous = pt;
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template<class T> elist<T>::elist(T item, bool m)
{
    first = new neighbour<T>;
    (*first).setitem(item);
    if (m)
        (*first).match();
    length = 1;
    (*first).setnext(first);
    (*first).setprevious(first);
}

template<class T> int elist<T>::getlength(void)
{
    return length;
}

template<class T> neighbour<T> * elist<T>::getfirst(void)
{
    return first;
}

template<class T> void elist<T>::append(T item, bool m)
{
    neighbour<T> * pt_last = (*first).getprevious();
    neighbour<T> * pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    if (m)
        (*pt_new).match();
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template<class T> void elist<T>::addvertex(T item, bool m)
{
    if (contains(item) == false)
        append(item, m);
    else
        if (m)
        {
            neighbour<T> * pt_last = (*first).getprevious();
            (*pt_last).match();
        }
    return;
}

template<class T> bool elist<T>::contains(T item)
{
    bool result = false;
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            result = true;
            break;
        }
        else
            pt = (*pt).getnext();
    }
    return result;
}

template<class T> void elist<T>::remove(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T> * pt_prev = (*pt).getprevious();
            neighbour<T> * pt_next = (*pt).getnext();
            (*pt_prev).setnext(pt_next);
            (*pt_next).setprevious(pt_prev);
            if (i == 0)
                first = pt_next;
            --length;
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> void elist<T>::match(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            (*pt).match();
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> void elist<T>::unmatch(T item)
{
    neighbour<T> * pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            (*pt).unmatch();
            return;
        }
        pt = (*pt).getnext();
    }
    return;
}

template<class T> bool elist<T>::ismatched(T node)
{
    neighbour<T> * neighb = getfirst();
    for (int j = 0; j < length; j++)
    {
        if ((*neighb).getitem() == node)
            return ((*neighb).ismatched());
        neighb = (*neighb).getnext();
    }
    return 0;
}

/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploits the function add on edgelists. */
template<class T> void elist<T>::addall(T item, edgelist<T> *pt)
{
    neighbour<T> * pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem());
        pte = (*pte).getnext();
    }
    return;
}

/* The function addallmatched is analogous, but adds only pairs with the given item and the list members, if they are matched, i.e. all matched outgoing edges to the list given by the pointer pt. */
template<class T> void elist<T>::addallmatched(T item, edgelist<T> *pt)
{
    neighbour<T> * pte = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pte).ismatched())
        {
            (*pt).add(item, (*pte).getitem());
        }
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template<class T> edge<T>::edge(T first, T second)
{
    firstitem = first;
    seconditem = second;
}

template<class T> T edge<T>::origin(void)
{
    return firstitem;
}

template<class T> T edge<T>::destination(void)
{
    return seconditem;
}

template<class T> void edge<T>::setorigin(T item)
{
    firstitem = item;
    return;
}

template<class T> void edge<T>::setdestination(T item)
{
    seconditem = item;
    return;
}

/* only for testing */
template<class T> void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ") + ";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template<class T> edgelist<T>::edgelist(void)
{
    reprarray = new edge<T>*[10000];
    numedges = 0;
}

template<class T> int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template<class T> void edgelist<T>::add(T item1, T item2)
{
    edge<T> * newedge = new edge<T>(item1,item2);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template<class T> T edgelist<T>::getitem1(int pos)
{
    if (0 <= pos && pos < getnumedges())
    {
        edge<T> * pt = reprarray[pos];
        return (*pt).origin();
    }
    cout << "Index error: index " << pos << "out of range\n";
    exit(EXIT_FAILURE);
}

template<class T> T edgelist<T>::getitem2(int pos)
{
    if (0 <= pos && pos < getnumedges())
    {
        edge<T> * pt = reprarray[pos];
        return (*pt).destination();
    }
    cout << "Index error: index " << pos << "out of range\n";
    exit(EXIT_FAILURE);
}

template<class T> void edgelist<T>::removelast(void)
{
    --numedges;
    return;
}

template<class T> void edgelist<T>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T> * pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "\n      --------\n";
    return;
}

/* Until here there was no change to the corresponding classes used for undirected graphs. Now define directed graphs. The only change is that for insertion of an edge (v,w) there is no insertion of (w,v). Analogous for edge deletion. */

/* A bpgraph object just contains pointers to two vertexlists. */
template<class T> bpgraph<T>::bpgraph(void)
{
    vertices1 = new vertexlist<T>;
    vertices2 = new vertexlist<T>;
}

template<class T> int bpgraph<T>::numvertices(void)
{
    return (*vertices1).getlength() + (*vertices2).getlength();
}

template<class T> int bpgraph<T>::numedges(void)
{
    return (*vertices1).countedges();
}

template<class T> void bpgraph<T>::addedge(T origin, T destination, bool m)
{
    if (!(*vertices1).contains(destination) && !(*vertices2).contains(origin))
    {
        (*vertices1).addedge(origin, destination, m);
        (*vertices2).addedge(destination, origin, m);
    }
    return;
}

template<class T> void bpgraph<T>::matchedge(T origin, T destination)
{
    (*vertices1).matchedge(origin, destination);
    (*vertices2).matchedge(destination, origin);
    return;
}

template<class T> void bpgraph<T>::unmatchedge(T origin, T destination)
{
    (*vertices1).unmatchedge(origin, destination);
    (*vertices2).unmatchedge(destination, origin);
    return;
}

template<class T> void bpgraph<T>::addvertex1(T item)
{
    if (!(*vertices2).contains(item))
    (*vertices1).addvertex(item);
    return;
}

template<class T> void bpgraph<T>::addvertex2(T item)
{
    if (!(*vertices1).contains(item))
    (*vertices2).addvertex(item);
    return;
}

template<class T> void bpgraph<T>::deleteedge(T origin, T destination)
{
    (*vertices1).removeedge(origin, destination);
    (*vertices2).removeedge(destination, origin);
    return;
}

template<class T> void bpgraph<T>::deletevertex1(T item)
{
    bool success = (*vertices1).remove(item);
    if (!success)
        cout << "The vertex was not deleted.\n";
    return;
}

template<class T> void bpgraph<T>::deletevertex2(T item)
{
    bool success = (*vertices2).remove(item);
    if (!success)
        cout << "The vertex was not deleted.\n";
    return;
}

template<class T> edgelist<T> * bpgraph<T>::edges(T item)
{
    edgelist<T> * result = 0;
    if ((*vertices1).contains(item))
        result = (*vertices1).outgoingedges(item);
    if ((*vertices2).contains(item))
        result = (*vertices2).outgoingedges(item);
    return result;
}

// for testing
template<class T> void bpgraph<T>::prettyprint(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices1).prettyprint();
    cout << "===================\n\n";
    (*vertices2).prettyprint();
    cout << "=================\n\n";
    return;
}

template<class T> void bpgraph<T>::prettyprintmatching(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices1).prettyprintmatching();
    (*vertices2).prettyprintmatching();
    cout << "=================\n\n";
    return;
}

/* Deeptreenodes are to store the output, i.e. triples of a vertex, its position in the dfs processing, and its finishing time. The get and set functions are obvious. */
template<class T> deeptreenode<T>::deeptreenode(T node, int pos, int finish, deeptreenode<T> *pt)
{
    nodelabel = node;
    dfspos = pos;
    finishingtime = finish;
    next = pt;
}

template<class T> T deeptreenode<T>::label(void)
{
    return nodelabel;
}

template<class T> int deeptreenode<T>::dfsnum(void)
{
    return dfspos;
}

template<class T> int deeptreenode<T>::finishtime(void)
{
    return finishingtime;
}

template<class T> deeptreenode<T> * deeptreenode<T>::getnext(void)
{
    return next;
}

template<class T> void deeptreenode<T>::setlabel(T node)
{
    nodelabel = node;
    return;
}

template<class T> void deeptreenode<T>::setdfsnum(int pos)
{
    dfspos = pos;
    return;
}

template<class T> void deeptreenode<T>::setfinishtime(int finish)
{
    finishingtime = finish;
    return;
}

template<class T> void deeptreenode<T>::setnext(deeptreenode<T> * pt)
{
    next = pt;
    return;
}

/* only for testing */
template<class T> void deeptreenode<T>::prettyprint(void)
{
    cout << "Node " << label() << " has dfs number " << dfsnum() << " and finishing time " << finishtime() << ".\n";
    return;
}

/* A deepsearchtree contains the output of a depth-first search. */
template<class T> deepsearchtree<T>::deepsearchtree(void)
{
    first = 0;
    last = 0;
}

template<class T> void deepsearchtree<T>::add(T node, int pos, int finish)
{
    deeptreenode<T> * newnode = new deeptreenode<T>(node, pos, finish);
    if (first == 0)
    {
        first = newnode;
        last = newnode;
        return;
    }
    (*last).setnext(newnode);
    last = newnode;
    return;
}

template<class T> void deepsearchtree<T>::setfinishtime(T node, int finish)
{
    deeptreenode<T> * cursor = first;
    while (cursor != 0)
    {
        if ((*cursor).label() == node)
        {
            (*cursor).setfinishtime(finish);
            return;
        }
        cursor = (*cursor).getnext();
    }
    return;
}

template<class T> bool deepsearchtree<T>::occurs(T node)
{
    bool result = false;
    if (first == 0)
        return result;
    deeptreenode<T> * cursor = first;
    while (cursor != last)
    {
        if ((*cursor).label() == node)
        {
            result = true;
            break;
        }
        cursor = (*cursor).getnext();
    }
    if ((*last).label() == node)
        result = true;
    return result;
}

template<class T> void deepsearchtree<T>::prettyprint(void)
{
    if (first == 0)
    {
        cout << "The graph is empty.\n";
        return;
    }
    deeptreenode<T> * cursor = first;
    while (cursor != last)
    {
        (*cursor).prettyprint();
        cursor = (*cursor).getnext();
    }
    (*cursor).prettyprint();
    return;
}

/* Marker objects are used to mark vertices when they have been explored in depth-first search. */
template<class T> marker<T>::marker(T item, marker<T> *pt)
{
    vertex = item;
    next = pt;
}

template<class T> T marker<T>::getitem(void)
{
    return vertex;
}

template<class T> marker<T> * marker<T>::getnext(void)
{
    return next;
}

template<class T> void marker<T>::setitem(T item)
{
    vertex = item;
    return;
}

template<class T> void marker<T>::setnext(marker<T> * pt)
{
    next = pt;
    return;
}

/* A markerlist contains the marked vertices. */
template<class T> markerlist<T>::markerlist(void)
{
    first = 0;
    last = 0;
}

template<class T> void markerlist<T>::mark(T item)
{
    marker<T> * newmarker = new marker<T>(item);
    if (first == 0)
    {
        first = newmarker;
        last = newmarker;
        return;
    }
    (*last).setnext(newmarker);
    last = newmarker;
    return;
}

template<class T> bool markerlist<T>::ismarked(T item)
{
    bool result = false;
    if (first == 0)
        return result;
    marker<T> * cursor = first;
    while (cursor != last)
    {
        if ((*cursor).getitem() == item)
        {
            result = true;
            break;
        }
        cursor = (*cursor).getnext();
    }
    if ((*last).getitem() == item)
        result = true;
    return result;
}

/* matching function: Hungarian algorithm */
template<class T> void bpgraphtraversal<T>::findmatch(void)
{
    vertexlist<T> *vertices1 = bpgraph<T>::vertices1;
    vertexlist<T> *vertices2 = bpgraph<T>::vertices2;
    int num1 = (*vertices1).getlength();
    int num2 = (*vertices2).getlength();
    // A perfect matching can only exist, if the number of boys and girls is equal.
    if (num1 < num2)
    {
        cout << "No perfect matching exists. We determine a complete matching for boys, if it exists.\n";
    }
    else
    {
        if (num1 > num2)
        {
            cout << "No perfect matching exists. We determine a complete matching for girls, if it exists.\n";
            // Simply swap the pointers to boys and girls.
            vertexlist<T> * temp = vertices1;
            vertices1 = vertices2;
            vertices2 = temp;
        }
    }
    AList<T> *boys = (*vertices1).getlist();
    for (int i = 1; i <= (*boys).getlength(); i++)
    {
        T startnode = (*boys)[i];
        // find path in digraph using the current partial matching
        edgelist<T> *path = dfsmatch(startnode);
        if ((*path).getnumedges() == 0)  /* No path in digraph was found. dfsmatch is implemented such that the returned edgelist will be empty. */
            cout << "There is no perfect/complete matching.\n";
        (*vertices1).adjustmatching1(path);  // adjust (b,g) edges
        (*vertices2).adjustmatching2(path);  // adjust (g,b) edges
    }
    return;
}

template<class T> edgelist<T> * bpgraphtraversal<T>::dfsmatch(T startnode)
{
    edgelist<T> * path = new edgelist<T>();
    vertexlist<T> * vertices1 = bpgraph<T>::vertices1;
    vertexlist<T> * vertices2 = bpgraph<T>::vertices2;
    bool complete = false;
    bool boy = true;
    markerlist<T> * markedvertices = new markerlist<T>;
    (*markedvertices).mark(startnode);
    _dfs(boy, startnode, startnode, vertices1, vertices2, path, markedvertices, complete);
    return path;
}

/* auxiliary functions for depth-first search */
template<class T> void bpgraphtraversal<T>::_dfs(bool &boy, T node1, T node2, vertexlist<T> * vertices1, vertexlist<T> * vertices2, edgelist<T> * path, markerlist<T> * markedvertices, bool &complete)
{
    elist<T> * neighbours;
    if (boy)
        neighbours = (*vertices1).edges(node2);
    else
        neighbours = (*vertices2).edges(node2);
    if (neighbours != 0)
    {
        neighbour<T> * cursor = (*neighbours).getfirst();
        bool unmatched = true;
        for (int i = 0; i < (*neighbours).getlength(); i++)
        {
            T nextnode = (*cursor).getitem();
            if (!(*markedvertices).ismarked(nextnode))
            {
                bool success = _traverse_treeedge(boy, node2, nextnode, vertices1, vertices2, path);
                if (success)
                {
                    unmatched = false;
                    (*markedvertices).mark(nextnode);
                    boy = !boy;
                    _dfs(boy, node2, nextnode, vertices1, vertices2, path, markedvertices, complete);
                    if (complete)
                        return;
                }
            }
            cursor = (*cursor).getnext();
        }
        if (!boy && unmatched)
            complete = true;
    }
    if (!complete)
    {
        boy = !boy;
        if ((*path).getnumedges() > 0)
            (*path).removelast();
    }
    return;
}

template<class T> bool bpgraphtraversal<T>::_traverse_treeedge(bool &boy, T first, T second, vertexlist<T> * vertices1, vertexlist<T> * vertices2, edgelist<T> * path)
{
    if (boy)
    {
        if (!(*vertices1).ismatched(first, second))
        {
            (*path).add(first,second);
            return true;
        }
        else
            return false;
    }
    else
    {
        if ((*vertices2).ismatched(first,second))
        {
            (*path).add(first,second);
            return true;
        }
        else
            return false;
    }
}

// only for testing
template<class T> void bpgraphtraversal<T>::prettyprintmatching(void)
{
    vertexlist<T> * vertices1 = bpgraph<T>::vertices1;
    vertexlist<T> * vertices2 = bpgraph<T>::vertices2;
    cout << "\n\n====== Matching ======\n\n";
    (*vertices1).prettyprintmatching();
    cout << "========================\n\n";
    (*vertices2).prettyprintmatching();
    cout << "=================\n\n";
    return;
}
