#include "headers/fiboheap.h"

template <class dataregionT, class keyT>
heapnodes<dataregionT, keyT>::heapnodes()
{
    degree = 0;
    parent = 0;
    children = 0;
    left = &this;
    right = &this;
    dataregion = 0;
    key = 0;
    marked = false;
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::add_brother(heapnodes<dataregionT, keyT> *ptr)
{
    ptr->left = &this;
    ptr->right = right;
    right->left = ptr;
    right = ptr;
    ptr->parent = parent;
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::add_children(heapnodes<dataregionT, keyT> *ptr)
{
    if (children)
        children->add_brother(ptr);
    else
        children = ptr;
    if (marked)
        marked = false;
    else
        degree++;
}

template <class dataregionT, class keyT>
fiboheap<dataregionT, keyT>::fiboheap()
{
    minnode = 0;
    maxdegree = 0;
    nodes = 0;
    nodes_num = 0;
}

template <class dataregionT, class keyT>
dataregionT fiboheap<dataregionT, keyT>::getmin()
{
    if (minnode)
        return minnode;
    else
        return NULL;
}
template <class dataregionT, class keyT>
void fiboheap<dataregionT, keyT>::maintain_heap()
{
}

template <class dataregionT, class keyT>
dataregionT fiboheap<dataregionT, keyT>::popmin()
{
    dataregionT minptr;
    if (minnode)
        minptr = minnode->dataregion;
    else
    {
        return NULL;
    }
    int64_t degree = minnode->degree;
    return NULL;
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::merge(fiboheap *heap_pointer)
{
    return NULL;
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::delete_node(heapnodes<dataregionT, keyT> *nodepointer)
{
    return NULL;
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::change_value(heapnodes<dataregionT, keyT> *nodepointer, keyT key)
{
    return NULL;
}

template <class dataregionT, class keyT>
heapnodes<dataregionT, keyT> *fiboheap<dataregionT, keyT>::insert_nodes(dataregionT data, keyT key)
{
    heapnodes<dataregionT, keyT> *newnode = new heapnodes<dataregionT, keyT>;
    newnode->dataregion = data;
    newnode->key = key;
    if (nodes_num)
    {
        minnode = newnode;
    }
    else
    {
        newnode->left = minnode;
        newnode->right = minnode->right;
        minnode->right->left = newnode;
        minnode->right = newnode;
        if (minnode->key > key)
            minnode = newnode;
    }
    nodes_num++;
    return newnode;
}
