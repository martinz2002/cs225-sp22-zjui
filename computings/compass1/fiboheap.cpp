#include "headers/fiboheap.h";

template <class dataregionT, class keyT>
heapnodes<dataregionT, keyT>::heapnodes()
{
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::add_brother(heapnodes<dataregionT, keyT> *ptr)
{
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::add_children(heapnodes<dataregionT, keyT> *ptr)
{
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::to_root()
{
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::self_delete()
{
}

template <class dataregionT, class keyT>
void heapnodes<dataregionT, keyT>::change_value(keyT new_key)
{
}

template <class dataregionT, class keyT>
fiboheap<dataregionT, keyT>::fiboheap()
{
}

template <class dataregionT, class keyT>
dataregionT fiboheap<dataregionT, keyT>::getmin()
{
}

template <class dataregionT, class keyT>
dataregionT fiboheap<dataregionT, keyT>::popmin()
{
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::merge(fiboheap *heap_pointer)
{
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::delete_node(heapnodes<dataregionT, keyT> *nodepointer)
{
}

template <class dataregionT, class keyT>
bool fiboheap<dataregionT, keyT>::change_value(heapnodes<dataregionT, keyT> *nodepointer, keyT key)
{
}

template <class dataregionT, class keyT>
heapnodes<dataregionT, keyT> *fiboheap<dataregionT, keyT>::insert_nodes(dataregionT data, keyT key)
{
}