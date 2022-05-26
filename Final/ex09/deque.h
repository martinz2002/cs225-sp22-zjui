//
//  deque.h
//
//  Created by KD on 17.05.22.
//

#ifndef deque_h
#define deque_h

template<class T> class Deque;

template<class T> class node
{
    friend class Deque<T>;
public:
    node(T item = 0, node<T> *pt_n = 0);
    T getdata(void);
    node<T> *getnext(void);
    void setdata(T item);
    void setnext(node<T> *pt);
private:
    T dataitem;
    node<T> *pt_next;
};

template<class T> class Deque
{
public:
    Deque(void);
    int getlength(void);
    void pushback(T value);
    void pushfront(T value);
    bool isempty(void);
    T popfront(void);
    T popback(void);
    T front(void);
    T back(void);
    void printall(void); // for testing
private:
    node<T> *first;
    node<T> *last;
    int numitems;
};

#endif /* deque_h */
