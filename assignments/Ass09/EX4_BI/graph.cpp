//
//  graph.cpp
//
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.h"
#include "id_hash.cpp"
using std::cout;

/* The structure of a vertex is analogous to a node in a doubly linked list. In addition we keep an "edgelist" with each vertex, i.e. the list of neighbour vertices. */
template <class T>
vertex<T>::vertex(T item, bool gender, vertex<T> *pt_next, vertex<T> *pt_prev)
{
    vertexid = item;
    this->gender = gender;
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
bool vertex<T>::getgender()
{
    return gender;
}

template <class T>
elist<T> *vertex<T>::getedges(void)
{
    return edgelist;
}

template <class T>
void vertex<T>::setitem(T item, bool gender)
{
    vertexid = item;
    this->gender = gender;
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
    falsevertices = 0;
    truevertices = 0;
}

template <class T>
int vertexlist<T>::getlength(void)
{
    return numvertices;
}

template <class T>
bool vertexlist<T>::is_balance(void)
{
    return falsevertices == truevertices;
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
void vertexlist<T>::append(T item, bool gender)
{
    vertex<T> *pt_last = (*dummy).getprevious();
    vertex<T> *pt_new = new vertex<T>;
    (*pt_new).setitem(item, gender);
    (*pt_new).setnext(dummy);
    (*pt_new).setprevious(pt_last);
    (*dummy).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++numvertices;
    if (gender)
        ++truevertices;
    else
        ++falsevertices;
    item2ptr->add(item, pt_new);
    return;
}

/* A new vertex is only added, if it is not yet in the list. */
template <class T>
void vertexlist<T>::addvertex(T item, bool gender)
{
    if (contains(item, gender) == false)
        append(item, gender);
    return;
}

/* To check if a vertex is already in the list the list is scanned until the element is found. */
template <class T>
bool vertexlist<T>::contains(T item, bool gender)
{
    bool result = false;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item && (pt->getgender() == gender))
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
bool vertexlist<T>::remove(T item, bool gender)
{
    bool result = false;
    vertex<T> *location = 0;
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == item && pt->getgender() == gender)
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
        if (edges != 0 && (*edges).contains(item, gender) == true)
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
        if (gender)
            --truevertices;
        else
            --falsevertices;
        item2ptr->remove(location->getitem());
    }
    /* The returned Boolean result indicates, if the vertex was deleted or not. */
    return result;
}

/* Adding an edge is done by first locating the origin vertex in the vertex list, then inserting the destination vertex into the associated edgelist. */
template <class T>
void vertexlist<T>::addedge(T first, bool first_gender, T second, bool second_gender)
{
    if (first_gender == second_gender)
    {
        cout << "Same gender!!\n";
        return;
    }
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first && pt->getgender() == first_gender)
        {
            elist<T> *pt_edges = (*pt).getedges();
            if (pt_edges != 0)
                (*pt_edges).addvertex(second, second_gender);
            else
            {
                elist<T> *newlist = new elist<T>(second, second_gender);
                (*pt).setedges(newlist);
            }
            return;
        }
        pt = (*pt).getnext();
    }
    /* If the origin vertex is not yet in the vertex list, it is first appended to the vertex list. The associated edgelist contains a single vertex. */
    append(first, first_gender);
    pt = (*dummy).getprevious();
    elist<T> *newlist = new elist<T>(second, second_gender);
    (*pt).setedges(newlist);
    return;
}

/* Removing an edge is done by first locating the origin vertex in the vertex list, then searching for the destination vertex into the associated edgelist. In this case the edge is always deleted, if it is found. */
template <class T>
void vertexlist<T>::removeedge(T first, bool first_gender, T second, bool second_gender)
{
    if (first_gender == second_gender)
    {
        cout << "Same gender!!\n";
        return;
    }
    vertex<T> *pt = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*pt).getitem() == first && pt->getgender() == first_gender)
        {
            elist<T> *pt_edges = (*pt).getedges();
            if (pt_edges != 0)
            {
                (*pt_edges).remove(second, second_gender);
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
bool vertexlist<T>::find_pair(vertex<T> *pt, edgelist<T> *edges)
{
    bool result = false;
    elist<T> *pt_edges = (*pt).getedges();
    int length = (*pt_edges).getlength();
    neighbour<T> *pt_neighbour = (*pt_edges).get_first();
    for (int i = 0; i < length; i++)
    {
        if (!vertexmap->retrieve(pt_neighbour->getitem()))
        {
            vertexmap->modify(pt_neighbour->getitem(), true);
            T *item = edges->contain(pt_neighbour->getitem(), pt_neighbour->getgender());
            if (!item || find_pair(item2ptr->retrieve(*item), edges))
            {
                result = true;
                edges->add(pt->getitem(), pt->getgender(), pt_neighbour->getitem(), pt_neighbour->getgender());
                return result;
            }
        }
        pt_neighbour = (*pt_neighbour).getnext();
    }
    return result;
}

template <class T>
edgelist<T> *vertexlist<T>::perfectly_match()
{
    vertex<T> *pt1 = (*dummy).getnext();

    vertexmap = new hashmap<T, bool>;
    for (int i = 0; i < numvertices; ++i)
    {
        if (!pt1->getgender())
        {
            pt1 = pt1->getnext();
            continue;
        }
        vertexmap->add(pt1->getitem(), false);
        pt1 = pt1->getnext();
    }
    pt1 = dummy->getnext();
    edgelist<T> *result = new edgelist<T>();
    for (int i1 = 0; i1 < numvertices; i1++)
    {
        if (pt1->getgender())
        {
            pt1 = pt1->getnext();
            continue;
        }
        if (!find_pair(pt1, result))
            return 0;
        vertex<T> *pt2 = (*dummy).getnext();
        for (int i2 = 0; i2 < numvertices; ++i2)
        {
            if (!pt2->getgender())
            {
                pt2 = pt2->getnext();
                continue;
            }
            vertexmap->modify(pt2->getitem(), false);
            pt2 = pt2->getnext();
        }
        pt1 = pt1->getnext();
    }
    return result;
}

/* To build list of outgoing edges for a given vertex, a new edge sequence is created for the output, then by scanning the associated edgelist edges (pairs of vertices) are added one by one. */
template <class T>
edgelist<T> *vertexlist<T>::outgoingedges(T item, bool gender)
{
    edgelist<T> *result = new edgelist<T>;
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if ((*ptv).getitem() == item && ptv->getgender() == gender)
        {
            elist<T> *edges = (*ptv).getedges();
            if (edges != 0)
                (*edges).addall(item, gender, result);
            return result;
        }
        ptv = (*ptv).getnext();
    }
    return result;
}

/* only for testing */
template <class T>
void vertexlist<T>::prettyprint(void)
{
    vertex<T> *ptv = (*dummy).getnext();
    for (int i = 0; i < numvertices; i++)
    {
        if (ptv->getgender())
            cout << "True: \n";
        else
            cout << "False: \n";
        cout << "Edges with origin " << (*ptv).getitem() << " :\n";
        edgelist<T> *pte = outgoingedges((*ptv).getitem(), ptv->getgender());
        (*pte).prettyprint();
        ptv = (*ptv).getnext();
    }

    return;
}

/* The edge list for each vertex is organised analogous to the vertexlist, but the are no assiciated edgelists. The elements of the list are organised by the neighbour class. */
template <class T>
neighbour<T>::neighbour(T item, bool gender, neighbour<T> *pt_next, neighbour<T> *pt_prev)
{
    secondvertex = item;
    next = pt_next;
    previous = pt_prev;
    this->gender = gender;
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
bool neighbour<T>::getgender(void)
{
    return gender;
}
template <class T>
void neighbour<T>::setitem(T item, bool gender)
{
    secondvertex = item;
    this->gender = gender;
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
void neighbour<T>::setgender(bool gender)
{
    this->gender = gender;
    return;
}
/* elist is the class used for the representation of doubly linked lists of vertices (no dummy node) associated with the vertices in the vertexlist. All functions are analogous to those defined for vertexlist. */
template <class T>
elist<T>::elist(T item, bool gender)
{
    first = new neighbour<T>;
    (*first).setitem(item, gender);
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
void elist<T>::append(T item, bool gender)
{
    neighbour<T> *pt_last = (*first).getprevious();
    neighbour<T> *pt_new = new neighbour<T>;
    (*pt_new).setitem(item, gender);
    (*pt_new).setnext(first);
    (*pt_new).setprevious(pt_last);
    (*first).setprevious(pt_new);
    (*pt_last).setnext(pt_new);
    ++length;
    return;
}

template <class T>
neighbour<T> *elist<T>::get_first()
{
    return first;
}

template <class T>
void elist<T>::addvertex(T item, bool gender)
{
    if (contains(item, gender) == false)
        append(item, gender);
    return;
}

template <class T>
bool elist<T>::contains(T item, bool gender)
{
    bool result = false;
    neighbour<T> *pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item && pt->getgender() == gender)
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
void elist<T>::remove(T item, bool gender)
{
    neighbour<T> *pt = first;
    for (int i = 0; i < length; i++)
    {
        if ((*pt).getitem() == item && pt->getgender() == gender)
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
void elist<T>::addall(T item, bool gender, edgelist<T> *pt)
{
    neighbour<T> *pte = first;
    for (int i = 0; i < length; i++)
    {
        (*pt).add(item, gender, (*pte).getitem(), pte->getgender());
        pte = (*pte).getnext();
    }
    return;
}

/* Edges are simply pairs of vertices with obvious get and set functions. */
template <class T>
edge<T>::edge(T first, bool first_gender, T second, bool second_gender)
{
    firstitem = first;
    this->first_gender = first_gender;
    this->second_gender = second_gender;
    seconditem = second;
}

template <class T>
T edge<T>::origin(void)
{
    return firstitem;
}

template <class T>
T edge<T>::destination(void)
{
    return seconditem;
}

template <class T>
void edge<T>::setorigin(T item, bool gender)
{
    firstitem = item;
    first_gender = gender;
    return;
}

template <class T>
void edge<T>::setdestination(T item, bool gender)
{
    seconditem = item;
    second_gender = gender;
    return;
}

/* only for testing */
template <class T>
void edge<T>::prettyprint(void)
{
    cout << "(origin: " << origin() << ", destination: " << destination() << ") + ";
    return;
}

/* edgelists, i.e. sequences of pairs of vertices are only used for output purposes. */
template <class T>
edgelist<T>::edgelist(void)
{
    reprarray = new edge<T> *[100];
    numedges = 0;
}

template <class T>
T *edgelist<T>::contain(T item, bool gender)
{
    T *result = new T;
    for (int i = 0; i < numedges; i++)
    {
        if (reprarray[i]->origin() == item)
        {
            *result = reprarray[i]->destination();
            return result;
        }
        if (reprarray[i]->destination() == item)
        {
            *result = reprarray[i]->origin();
            return result;
        }
    }
    delete result;
    return NULL;
}

template <class T>
int edgelist<T>::getnumedges(void)
{
    return numedges;
}

template <class T>
void edgelist<T>::add(T item1, bool item1_gender, T item2, bool item2_gender)
{
    delete_edge(item1);
    edge<T> *newedge = new edge<T>(item1, item1_gender, item2, item2_gender);
    reprarray[numedges] = newedge;
    ++numedges;
    return;
}

template <class T>
void edgelist<T>::prettyprint(void)
{
    for (int i = 0; i < numedges; i++)
    {
        edge<T> *pte = reprarray[i];
        (*pte).prettyprint();
    }
    cout << "\n      --------\n";
    return;
}

template <class T>
void edgelist<T>::delete_edge(T item1)
{
    for (int i = 0; i < numedges; i++)
    {
        if (reprarray[i]->origin() == item1)
        {
            delete reprarray[i];
            for (int j = i; j < numedges - 1; j++)
            {
                reprarray[j] = reprarray[j + 1];
            }
            numedges--;
            i--;
        }
    }
}

/* A graph object just contains a pointer to a vertexlist. */
template <class T>
BiPartite<T>::BiPartite(void)
{
    vertices = new vertexlist<T>;
}

template <class T>
int BiPartite<T>::numvertices(void)
{
    return (*vertices).getlength();
}

template <class T>
int BiPartite<T>::numedges(void)
{
    return (*vertices).countedges();
}

template <class T>
void BiPartite<T>::addedge(T origin, T destination, bool o_gender, bool d_gender)
{
    if (o_gender == d_gender)
    {
        cout << "Same gender!!";
        return;
    }
    (*vertices).addedge(origin, o_gender, destination, d_gender);
    (*vertices).addedge(destination, d_gender, origin, o_gender);
    return;
}

template <class T>
void BiPartite<T>::addvertex(T item, bool gender)
{
    (*vertices).addvertex(item, gender);
    return;
}

template <class T>
void BiPartite<T>::deleteedge(T origin, T destination, bool o_gender, bool d_gender)
{
    if (o_gender == d_gender)
    {
        cout << "Same gender!!";
        return;
    }
    (*vertices).removeedge(origin, o_gender, destination, d_gender);
    (*vertices).removeedge(destination, d_gender, origin, o_gender);
    return;
}

template <class T>
void BiPartite<T>::deletevertex(T item, bool gender)
{
    (*vertices).remove(item, gender);
    return;
}

template <class T>
edgelist<T> *BiPartite<T>::outgoingedges(T item, bool gender)
{
    return (*vertices).outgoingedges(item, gender);
}

template <class T>
void BiPartite<T>::prettyprint(void)
{
    cout << "\n\n====== Graph ======\n\n";
    (*vertices).prettyprint();
    cout << "=================\n\n";
    return;
}

template <class T>
edgelist<T> *BiPartite<T>::perfectly_match()
{
    if (!vertices->is_balance())
        return 0;
    edgelist<T> *result = vertices->perfectly_match();
    if (result != 0)
        return result;
    result = new edgelist<T>;
    return result;
}