//
//  partition.h
//  
//
//  Created by KD on 15.05.22
//

#ifndef partition_h
#define partition_h

class Partition
{
public:
    Partition(int size);
    int getsize(void);
    int getparent(int index);
    int find(int value);
    void merge(int item1, int item2);
    // for testing
    void prettyprint(void);
private:
    int numitems;
    int *array;
    int *rank;
};

#endif /* partition_h */
