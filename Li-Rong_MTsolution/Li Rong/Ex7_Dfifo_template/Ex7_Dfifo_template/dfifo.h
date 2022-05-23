//
//  dfifo.h
//  
//
//  Created by KD on 16.01.21.
//  Modified on 04.04.22.
//

#ifndef dfifo_h
#define dfifo_h

template<class T> class Dfifo;

template<class T> class node
{
    friend class Dfifo<T>;
public:
    node(T item = 0, node<T> *pt_n = 0, node<T> *pt_p = 0);
//    virtual ~node(void);
    T getdata(void);
    node<T> *getnext(void);
    node<T> *getprevious(void);
    void setdata(T item);
    void setnext(node<T> *pt);
    void setprevious(node<T> *pt);
private:
    T dataitem;
    node<T> *pt_next;
    node<T> *pt_previous;
};

template<class T> class Dfifo
{
public:
    Dfifo(void);
    // T operator[](int index);
    int getlength(void);
    void pushback(T value);
    T popfront(void);
    T front(void);
    bool isempty(void);
    void reverse(void); // The function to be implemented
    void display(void); // for testing
private:
    node<T> *dummy;
    int numitems;
};

#endif /* dfifo_h */
