//
//  graph.h
//  
//
//  Created by KD on 11.04.21.
//  Modified for Kruskal on 16.05.22.
//

#ifndef graph_h
#define graph_h

template<class T> class vertexlist;

template<class T> class Partition
{
public:
    Partition(int size);
    Partition(vertexlist<T> *nodes);
    int getsize(void);
    int getparent(int index);
    int getnode(int index);
    int getposition(T node);
    int find(int value);
    void merge(int item1, int item2);
    // for testing
    void prettyprint(void);
private:
    int numitems;
    int *array;
    T *labels;
    int *rank;
};

template<class T> class edgelist;

template<class T> class edge;

template<class T> class elist;

template<class T> class vertex
{
    friend class vertexlist<T>;
public:
    vertex(T item = 0, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    int numoutedges(void);
    T getitem(void);
    vertex<T> * getnext(void);
    vertex<T> * getprevious(void);
    elist<T> * getedges(void);
    void setitem(T item);
    void setnext(vertex<T> * pt_next);
    void setprevious(vertex<T> * pt_prev);
    void setedges(elist<T> * pt_edges);
private:
    T vertexid;
    vertex<T> * next;
    vertex<T> * previous;
    elist<T> * edgelist;
};

template<class T> class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    void append(T item);
    void addvertex(T item);
    bool contains(T item);
    bool remove(T item);
    void addedge(T first, T second, double value = 0);
    void removeedge(T first, T second);
    edgelist<T> * outgoingedges(T item);
    void getlabels(T *labels);
    edgelist<T> * getsortededgelist(void);
    void prettyprint(void); // only for testing
private:
    vertex<T> * dummy;
    int numvertices;
};

template<class T> class neighbour
{
    friend class elist<T>;
public:
    neighbour(T item = 0, double lab = 0, neighbour<T> * pt_next = 0, neighbour<T> * pt_prev = 0);
    T getitem(void);
    double getcost(void);
    neighbour<T> * getnext(void);
    neighbour<T> * getprevious(void);
    void setitem(T item);
    void setcost(double value);
    void setnext(neighbour<T> * pt);
    void setprevious(neighbour<T> * pt);
private:
    T secondvertex;
    double cost;
    neighbour<T> * next;
    neighbour<T> * previous;
};

template<class T> class elist
{
public:
    elist(T item, double lab = 0);
    int getlength(void);
    void append(T item, double lab = 0);
    void addvertex(T item, double lab = 0);
    bool contains(T item);
    double getcost(T item);
    void remove(T item);
    void addall(T item, edgelist<T> * pt);
    void checkandadd(T item, edgelist<T> * edges);
private:
    neighbour<T> * first;
    int length;
};

template<class T> class edge
{
    friend class edgelist<T>;
public:
    edge(T first, T second, double value = 0);
    T origin(void);
    T destination(void);
    double getcost(void);
    void setorigin(T item);
    void setdestination(T item);
    void setcost(double value);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
    double cost;
};

template<class T> class edgelist
{
public:
    edgelist(void);
    int getnumedges(void);
    void add(T item1, T item2, double cost = 0);
    void insert(T item1, T item2, double value);
    edgelist<T> * findandmerge(Partition<T> * partition, int &sum);
    void prettyprint(void); // only for testing
private:
    edge<T> ** reprarray;
    int numedges;
};

template<class T> class graph
{
public:
    graph(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination, double value = 0);
    void addvertex(T item);
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    edgelist<T> * outgoingedges(T item);
    edgelist<T> * kruskal(int &sum);
    void prettyprint(void); // only for testing
private:
    vertexlist<T> * vertices;
};

#endif /* graph_h */
