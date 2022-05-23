//
//  fifo.h
//  
//
//  Created by KD on 18.01.21.
//  Modified on 02.04.22.
//

#ifndef fifo_h
#define fifo_h

/* Changes may also be necessary in this header file. */

template<class T> class fifo
{
public:
    fifo(int size = 10);
//    virtual ~fifo();
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T back(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
    void reverse(void);
    void display(void); // for testing
private:
    int maxsize, minsize;
    int first, last;
    int numitems;
    T *reprarray;
    bool revdir;
    void allocate(void);
    void deallocate(void);
    void pushf(T value);
    T popf(void);
    void pushb(T value);
    T popb(void);
};

#endif /* fifo_h */
