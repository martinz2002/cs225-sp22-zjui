//
//  stacks.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 04.04.22.
//

#ifndef stacks_h
#define stacks_h

/* Use Lists to Represent two stacks */

template<class T> class Stacks
{
public:
    Stacks(int size = 20);
    T &operator[](int index);
    int getlength1(void);
    int getlength2(void);
    T top1(void);
    T top2(void);
    T pop1(void);
    T pop2(void);
    void push1(T item);
    void push2(T item);
    bool isempty1(void);
    bool isempty2(void);
    void display(void);  // for testing
private:
    int numitems1, numitems2;
    T *reprarray;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> Stacks<T>::Stacks(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems1 = 0;
    numitems2 = 0;
    reprarray = new T[maxsize];
}

#endif /* stacks_h */
