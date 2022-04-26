//
//  graph.h
//
//
//  Created by KD on 11.04.21.
//

#ifndef graph_h
#define graph_h
#include "id_hash.h"
template <class T>
class vertexlist;

template <class T>
class edgelist;

template <class T>
class edge;

template <class T>
class elist;

template <class T>
class vertex
{
    friend class vertexlist<T>;

public:
    vertex(T item = 0, bool gender = false, vertex<T> *pt_next = 0, vertex<T> *pt_prev = 0);
    int numoutedges(void);
    T getitem(void);
    vertex<T> *getnext(void);
    vertex<T> *getprevious(void);
    elist<T> *getedges(void);
    void setitem(T item, bool gender);
    void setnext(vertex<T> *pt_next);
    void setprevious(vertex<T> *pt_prev);
    void setedges(elist<T> *pt_edges);
    bool getgender();

private:
    T vertexid;
    bool gender;
    vertex<T> *next;
    vertex<T> *previous;
    elist<T> *edgelist;
};

template <class T>
class vertexlist
{
public:
    vertexlist(void);
    int getlength(void);
    int countedges(void);
    void append(T item, bool gender);
    void addvertex(T item, bool gender);
    bool contains(T item, bool gender);
    bool remove(T item, bool gender);
    void addedge(T first, bool first_gender, T second, bool second_gender);
    void removeedge(T first, bool first_gender, T second, bool second_gender);
    edgelist<T> *outgoingedges(T item, bool gender);
    void prettyprint(void); // only for testing
    bool is_balance();
    edgelist<T> *perfectly_match();
    bool find_pair(vertex<T> *pt, edgelist<T> *edges);

private:
    vertex<T> *dummy;
    int numvertices;
    int falsevertices;
    int truevertices;
    hashmap<T, bool> *vertexmap;
    hashmap<T, vertex<T> *> *item2ptr = new hashmap<T, vertex<T> *>;
};

template <class T>
class neighbour
{
    friend class elist<T>;

public:
    neighbour(T item = 0, bool gender = false, neighbour<T> *pt_next = 0, neighbour<T> *pt_prev = 0);
    T getitem(void);
    neighbour<T> *getnext(void);
    neighbour<T> *getprevious(void);
    void setitem(T item, bool gender);
    void setnext(neighbour<T> *pt);
    void setprevious(neighbour<T> *pt);
    bool getgender();
    void setgender(bool gender);

private:
    T secondvertex;
    bool gender;
    neighbour<T> *next;
    neighbour<T> *previous;
};

template <class T>
class elist
{
public:
    elist(T item, bool gender);
    int getlength(void);
    void append(T item, bool gender);
    void addvertex(T item, bool gender);
    bool contains(T item, bool gender);
    void remove(T item, bool gender);
    void addall(T item, bool gender, edgelist<T> *pt);
    neighbour<T> *get_first();

private:
    neighbour<T> *first;
    int length;
};

template <class T>
class edge
{
    friend class edgelist<T>;

public:
    edge(T first, bool first_gender, T second, bool second_gender);
    T origin(void);
    T destination(void);
    void setorigin(T item, bool gender);
    void setdestination(T item, bool gender);
    void prettyprint(void); // only for testing
private:
    T firstitem;
    T seconditem;
    bool first_gender;
    bool second_gender;
};

template <class T>
class edgelist
{
public:
    edgelist(void);
    int getnumedges(void);
    T* contain(T item, bool gender);
    void add(T item1, bool item1_gender, T item2, bool item2_gender);
    void prettyprint(void); // only for testing
private:
    edge<T> **reprarray;
    int numedges;
};

template <class T>
class BiPartite
{
public:
    BiPartite(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination, bool o_gender = false, bool d_gender = true);
    void addvertex(T item, bool gender);
    void deleteedge(T origin, T destination, bool o_gender = false, bool d_gender = true);
    void deletevertex(T item, bool gender);
    edgelist<T> *outgoingedges(T item, bool gender);
    void prettyprint(void); // only for testing
    edgelist<T> *perfectly_match();

private:
    vertexlist<T> *vertices;
};

#endif /* graph_h */
