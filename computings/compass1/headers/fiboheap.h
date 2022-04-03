#include <bits/stdc++.h>

template <class dataregionT, class keyT>
class fiboheap
{
public:
    fiboheap();
    ~fiboheap();

public:
    dataregionT min();
    dataregionT popmin();
    bool merge(fiboheap *heap_pointer);
    bool delete_node(heapnodes* nodepointer);
    bool change_value(heapnodes* nodepointer, keyT key);
    heapnodes* insert_nodes(dataregionT data, keyT key);
    bool to_root(heapnodes* nodepointer);

private:
    void maintain_heap();
    heapnodes<dataregionT, keyT> *minnode;
    int64_t maxdegree;
    heapnodes<dataregionT, keyT> *nodes;
};

template <class dataregionT, class keyT>
class heapnodes
{
public:
    heapnodes();
    ~heapnodes();
public:
    void add_brother();
    void add_children();
    void to_root();
    void self_delete();
    void change_value();
private:
    int64_t degree;
    heapnodes *parent;
    heapnodes *children;
    heapnodes *left;
    heapnodes *right;
    bool marked;
    dataregionT dataregion;
    keyT key;
};
