//
//  graphtraversal.h
//
//  Created by KD on 12.04.21.
//  Modified on 06.05.21
//

#ifndef graphtraversal_h
#define graphtraversal_h

/* The representation of directed graphs does not require changes */

template<class T> class vertexlist;

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
    void addedge(T first, T second);
    void removeedge(T first, T second);
    vertex<T> * getdummy(void);
    elist<T> * edges(T node);
    void prettyprint(void); // only for testing
private:
    vertex<T> * dummy;
    int numvertices;
};

template<class T> class neighbour
{
    friend class elist<T>;
public:
    neighbour(T item = 0, neighbour<T> * pt_next = 0, neighbour<T> * pt_prev = 0);
    T getitem(void);
    neighbour<T> * getnext(void);
    neighbour<T> * getprevious(void);
    void setitem(T item);
    void setnext(neighbour<T> * pt);
    void setprevious(neighbour<T> * pt);
    void prettyprint(void);
private:
    T secondvertex;
    neighbour<T> * next;
    neighbour<T> * previous;
};

template<class T> class elist
{
public:
    elist(T item);
    int getlength(void);
    neighbour<T> * getfirst(void);
    void append(T item);
    void pushfront(T item);
    void popback(void);
    void addvertex(T item);
    bool contains(T item);
    void remove(T item);
    void addall(T item, edgelist<T> * pt);
    void prettyprint(void);
private:
    neighbour<T> * first;
    int length;
};

template<class T> class dirgraph
{
public:
    dirgraph(void);
    int numvertices(void);
    int numedges(void);
    void addedge(T origin, T destination);
    void addvertex(T item);
    void deleteedge(T origin, T destination);
    void deletevertex(T item);
    void prettyprint(void); // only for testing
protected:
    vertexlist<T> * vertices;
};

template<class T> class markerlist;

template<class T> class marker
{
    friend class markerlist<T>;
public:
    marker(T item = 0, marker<T> * pt = 0);
    T getitem(void);
    marker<T> * getnext(void);
    void setitem(T item);
    void setnext(marker<T> * pt);
private:
    T vertex;
    marker<T> * next;
};

template<class T> class markerlist
{
public:
    markerlist(void);
    void mark(T item);
    bool ismarked(T item);
private:
    marker<T> * first;
    marker<T> * last;
};

template<class T> class graphtraversal : public dirgraph<T>
{
public:
    graphtraversal(void) : dirgraph<T>(){};
    /* The decisive addition is the function to create a topological order */
    elist<T> * topol_order(T startnode);
private:
    void _dfs(T node, vertexlist<T> * vertices, elist<T> * output, markerlist<T> * markedvertices);
        // simplified dfs for topological sorting
    void _traverse_nontreeedge(T node, elist<T> * output);
        // This function will check, if the graph contains a cycle through node.
    bool suitablestart(T item);
    /* for topological sort we need to check, if the given item can be used as a start node */
};

#endif /* graphtraversal_h */
