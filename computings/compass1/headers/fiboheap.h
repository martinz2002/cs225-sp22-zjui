#include <bits/stdc++.h>



template <class dataregionT, class keyT>
class heapnodes
{
public:
    heapnodes();
    ~heapnodes();

public:
    void add_brother(heapnodes<dataregionT,keyT> *ptr);
    void add_children(heapnodes<dataregionT,keyT> *ptr);
    void to_root();
    void self_delete();
    void change_value(keyT new_key);

private:
    int64_t degree;
    heapnodes<dataregionT,keyT> *parent;
    heapnodes<dataregionT,keyT> *children;
    heapnodes<dataregionT,keyT> *left;
    heapnodes<dataregionT,keyT> *right;
    bool marked;
    dataregionT dataregion;
    keyT key;
};
template <class dataregionT, class keyT>
class fiboheap
{
public:
    fiboheap();
    ~fiboheap();

public:
    dataregionT getmin();
    dataregionT popmin();
    bool merge(fiboheap<dataregionT,keyT> *heap_pointer);
    bool delete_node(heapnodes<dataregionT,keyT> *nodepointer);
    bool change_value(heapnodes<dataregionT,keyT> *nodepointer, keyT new_key);
    heapnodes<dataregionT,keyT>* insert_nodes(dataregionT data, keyT key);

private:
    bool to_root(heapnodes<dataregionT,keyT> *nodepointer);
    void maintain_heap();
    heapnodes<dataregionT, keyT> *minnode;
    int64_t maxdegree;
    heapnodes<dataregionT, keyT> *nodes;
};