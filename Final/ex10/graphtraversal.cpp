//
//  graphtraversal.cpp
//
//  Created by KD on 12.04.21.
//  Modified on 06.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graphtraversal.h"
using std::cin;
using std::cout;

/* Only changes to class template graphtraversal are required */

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template <class T>
vertex<T>::vertex(T item, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    next = pt_next;
    previous = pt_prev;
    edgelist = 0;
}

template <class T>
int vertex<T>::numoutedges(void)
{
    if (edgelist != 0)
        return (*edgelist).getlength();
    return 0;
}

template <class T>
T vertex<T>::getitem(void)
{
    return vertexid;
}

template <class T>
vertex<T> *vertex<T>::getnext(void)
{
    return next;
}

template <class T>
vertex<T> *vertex<T>::getprevious(void)
{
    return previous;
}

template <class T>
elist<T> *vertex<T>::getedges(void)
{
    return edgelist;
}

template <class T>
void vertex<T>::setitem(T item)
{
    vertexid = item;
    return;
}

template <class T>
void vertex<T>::setnext(vertex<T> *pt_next)
{
    next = pt_next;
    return;
}

template <class T>
void vertex<T>::setprevious(vertex<T> *pt_prev)
{
    previous = pt_prev;
    return;
}

template <class T>
void vertex<T>::setedges(elist<T> *pt_edges)
{
    edgelist = pt_edges;
    return;
}

/* A vertexlist is a doubly linked list with vertices and a dummy node. */
template <class T>
vertexlist<T>::vertexlist(void)
{
    dummy = new vertex<T>;
    (*dummy).setnext(dummy);
    (*dummy).setprevious(dummy);
    numvertices = 0;
}

template <class T>
int vertexlist<T>::getlength(void)
{
    return numvertices;
}

/* For counting edges we must add up the counts of outgoing edges for each vertex */
template <class T>
int vertexlist<T>::countedges(void)
{
    int count = 0;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        count = count + (*pt).numoutedges();
        pt = (*pt).getnext();
    }
    return count;
}

/* append is analogous to linked lists, i.e. we add a new vertex at the end and adjust pointers. */
template <class T>
void vertexlist<T>::append(T item)
{
    vertex<T> *pt_last = (*dummy).getprevious();
    vertex<T> *pt_new = new vertex<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template <class T>
void vertexlist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template <class T>
bool vertexlist<T>::contains(T item)
{
    bool result = false;
    vertex<T> *pt = (*dummy).getnext();
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

/* In order to remove a vertex we have to find it in the list of vertices. If it has a non-empty list of neighbours, it cannot be deleted. It cannot be deleted, if it appwars in any edgelist. */
template <class T>
bool vertexlist<T>::remove(T item)
{
    bool result = false;
    vertex<T> *location = 0;
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
            /* We may be able to delete the vertex at location pt, but we still have to check other edgelists. Therefore pt is stored in location. */
            location = pt;
            continue;
        }
        elist<T> *edges = (*pt).getedges();
        if (edges != 0 && (*edges).contains(item) == true)
        /* it is appears in an edgelist, there is no delete. */
        {
            cout << "The vertex " << item << " cannot be deleted, as it appears in an edge.\n";
            return result;
        }
        pt = (*pt).getnext();
    }
    /* Finally, we get to the deletion from the veertexlist. */
    if (location != 0)
    {
        result = true;
        vertex<T> *pt_prev = (*location).getprevious();
        vertex<T> *pt_next = (*location).getnext();
        (*pt_prev).setnext(pt_next);
        (*pt_next).setprevious(pt_prev);
        --numvertices;
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template <class T>
void vertexlist<T>::addedge(T first, T second)
{
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> *pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second);
            else
            {
                elist<T> *newlist = new elist<T>(second);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first);
    pt = (*dummy).getprevious();
    elist<T> *newlist = new elist<T>(second);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template <class T>
void vertexlist<T>::removeedge(T first, T second)
{
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first)
        {
            elist<T> *pt_edges = (*pt).getedges();
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

template <class T>
vertex<T> *vertexlist<T>::getdummy(void)
{
    return dummy;
}

template <class T>
elist<T> *vertexlist<T>::edges(T node)
{
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == node)
            return (*pt).getedges();
        pt = (*pt).getnext();
    }
    return 0;
}

/* only for testing */
template <class T>
void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        elist<T> *pte = (*ptv).getedges();
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }
    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no assiciated edgelists. The elements of the list are organised by the neighbour class. */
template <class T>
neighbour<T>::neighbour(T item, neighbour<T> *pt_next, neighbour<T> *pt_prev)
{
    secondvertex = item;
    next = pt_next;
    previous = pt_prev;
}

template <class T>
T neighbour<T>::getitem(void)
{
    return secondvertex;
}

template <class T>
neighbour<T> *neighbour<T>::getnext(void)
{
    return next;
}

template <class T>
neighbour<T> *neighbour<T>::getprevious(void)
{
    return previous;
}

template <class T>
void neighbour<T>::setitem(T item)
{
    secondvertex = item;
    return;
}

template <class T>
void neighbour<T>::setnext(neighbour<T> *pt)
{
    next = pt;
    return;
}

template <class T>
void neighbour<T>::setprevious(neighbour<T> *pt)
{
    previous = pt;
    return;
}

template <class T>
void neighbour<T>::prettyprint(void)
{
    cout << secondvertex << " ; ";
    return;
}

/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template <class T>
elist<T>::elist(T item)
{
    first = new neighbour<T>;
    (*first).setitem(item);
    length = 1;
    (*first).setnext(first);
    (*first).setprevious(first);
}

template <class T>
int elist<T>::getlength(void)
{
    return length;
}

template <class T>
neighbour<T> *elist<T>::getfirst(void)
{
    return first;
}

template <class T>
void elist<T>::append(T item)
{
    neighbour<T> *pt_last = (*first).getprevious();
    neighbour<T> *pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template <class T>
void elist<T>::pushfront(T item)
{
    neighbour<T> *pt_last = (*first).getprevious();
    neighbour<T> *pt_new = new neighbour<T>;
    (*pt_new).setitem(item);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    first = pt_new;
    return;
}

template <class T>
void elist<T>::popback(void)
{
    if (length <= 1)
        return;
    neighbour<T> *pt_last = (*first).getprevious();
    neighbour<T> *pt2 = (*pt_last).getprevious();
    (*pt2).setnext(first);
    (*first).setprevious(pt2);
    --length;
    return;
}

template <class T>
void elist<T>::addvertex(T item)
{
    if (contains(item) == false)
        append(item);
    return;
}

template <class T>
bool elist<T>::contains(T item)
{
    bool result = false;
    neighbour<T> *pt = first;
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

template <class T>
void elist<T>::remove(T item)
{
    neighbour<T> *pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item)
        {
            neighbour<T> *pt_prev = (*pt).getprevious();
            neighbour<T> *pt_next = (*pt).getnext();
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
/* The function addall adds all pairs with the given item and the list members, i.e. all outgoing edges to the list given by the pointer pt. It exploit the function add on edgelists. */
template <class T>
void elist<T>::addall(T item, edgelist<T> *pt)
{
    neighbour<T> *pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, (*pte).getitem());
        pte = (*pte).getnext();
    }
    return;
}

template <class T>
void elist<T>::prettyprint(void)
{
    neighbour<T> *cursor = first;
    for (int i = 0; i < length; i++)
    {
        (*cursor).prettyprint();
        cursor = (*cursor).getnext();
    }
    cout << "\n      --------\n";
    return;
}

/* A dirgraph object just contains a pointer to a vertexlist. */
template <class T>
dirgraph<T>::dirgraph(void)
{
    vertices = new vertexlist<T>;
}

template <class T>
int dirgraph<T>::numvertices(void)
{
    return (*vertices).getlength();
}

template <class T>
int dirgraph<T>::numedges(void)
{
    return (*vertices).countedges();
}

template <class T>
void dirgraph<T>::addedge(T origin, T destination)
{
    (*vertices).addedge(origin, destination);
    return;
}

template <class T>
void dirgraph<T>::addvertex(T item)
{
    (*vertices).addvertex(item);
    return;
}

template <class T>
void dirgraph<T>::deleteedge(T origin, T destination)
{
    (*vertices).removeedge(origin, destination);
    return;
}

template <class T>
void dirgraph<T>::deletevertex(T item)
{
    (*vertices).remove(item);
    return;
}

template <class T>
void dirgraph<T>::prettyprint(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}

/* Marker objects are used to mark vertices when they have been explored in depth-first search. */
template <class T>
marker<T>::marker(T item, marker<T> *pt)
{
    vertex = item;
    next = pt;
}

template <class T>
T marker<T>::getitem(void)
{
    return vertex;
}

template <class T>
marker<T> *marker<T>::getnext(void)
{
    return next;
}

template <class T>
void marker<T>::setitem(T item)
{
    vertex = item;
    return;
}

template <class T>
void marker<T>::setnext(marker<T> *pt)
{
    next = pt;
    return;
}

/* A markerlist contains the marked vertices. */
template <class T>
markerlist<T>::markerlist(void)
{
    first = 0;
    last = 0;
}

template <class T>
void markerlist<T>::mark(T item)
{
    marker<T> *newmarker = new marker<T>(item);
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

template <class T>
bool markerlist<T>::ismarked(T item)
{
    bool result = false;
    if (first == 0)
        return result;
    marker<T> *cursor = first;
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

/* no changres until here */

template <class T>
vertex<T> *vertexlist<T>::getvertex(T item)
{
    vertex<T> *cursor = dummy;
    for (int i = 0; i < numvertices; i++)
    {
        cursor = cursor->getnext();
        if ((*cursor).getitem() == item)
        {
            return cursor;
        }
    }
    return 0;
}

/* depth-first search procedure for topological sorting */
template <class T>
elist<T> *graphtraversal<T>::topol_order(T startnode)
{
    if (suitablestart(startnode) == false)
        return 0;
    elist<T> *result = new elist<T>(startnode);
    markerlist<T> *markers = new markerlist<T>;
    _dfs(startnode, this->vertices, result, markers);
    result->remove(startnode);
    result->pushfront(startnode);
    return result;

    /* This member function needs to be implemented by modifying dfs */
}

/* auxiliary functions for depth-first search */
template <class T>
void graphtraversal<T>::_dfs(T node, vertexlist<T> *vertices, elist<T> *output, markerlist<T> *markedvertices)
{
    if (markedvertices->ismarked(node) == true)
        return;
    markedvertices->mark(node);

    vertex<T> *cursor = (*vertices).getvertex(node);
    if (cursor == 0)
    {
        _traverse_nontreeedge(node, output);
        return;
    }
    elist<T> *temp_edges = (*cursor).getedges();
    neighbour<T> *cursorn = (*temp_edges).getfirst();
    for (int i = 0; i < (*temp_edges).getlength(); i++)
    {
        _dfs(cursorn->getitem(), vertices, output, markedvertices);
        cursorn = (*cursorn).getnext();
    }
    _traverse_nontreeedge(node, output);

    /* This is the key function used by topol_order. Note that backtracking and traversal of tree edges is trivial, so there is no need for an auxiliary function */
}

template <class T>
void graphtraversal<T>::_traverse_nontreeedge(T node, elist<T> *output)
{
    if (!output->contains(node))
        output->pushfront(node);
    /* The traversal of non-tree edges needs to check for cycles */
}

template <class T>
bool graphtraversal<T>::suitablestart(T item)
{
    if (false == this->vertices->contains(item))
        return false;
    vertex<T> *pt = this->vertices->getdummy();
    elist<T> *pt_out;
    for (int i = 0; i < this->vertices->getlength(); i++)
    {
        pt = pt->getnext();
        pt_out = pt->getedges();
        if (pt_out->contains(item))
            return false;
    }
    return true;

    /* check, if the given startnode is suitable */
}
