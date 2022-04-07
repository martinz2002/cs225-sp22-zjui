/**
 * @file fiboheap.cpp
 * @author skywang (Original author), Li Rong (Modification for this assignment), Zhong Tiantian (Commentor)
 * @brief Declearation of fibonacci heap.
 * @version 0.2
 * @date 2014-04-05, 2022-04-07
 * 
 * @copyright Copyright (c) 2014
 * 
 */

#include <bits/stdc++.h>
#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

typedef int64_t Type;
typedef struct _FibonacciNode
{
    Type key;                      // key value
    int degree;                    // degree value
    struct _FibonacciNode *left;   // left sibling
    struct _FibonacciNode *right;  // right sibling
    struct _FibonacciNode *child;  // node of the first child
    struct _FibonacciNode *parent; // parent node
    int marked;                    // indicating whether the first child is removed
} FibonacciNode, FibNode;

typedef struct _FibonacciHeap
{
    int64_t keyNum;               // Total number of nodes
    int maxDegree;                // maximum degree
    struct _FibonacciNode *min;   // minimum node, i.e. a root node of a minimum heap
    struct _FibonacciNode **cons; // the memory space for a maximum heap
} FibonacciHeap, FibHeap;

FibHeap *fib_heap_make();                                      // Build a new heap
void fib_heap_insert_key(FibHeap *heap, Type key);             // Insert a node with value key into heap
void fib_heap_delete(FibHeap *heap, Type key);                 // Delete a node with value key from heap
void fib_heap_extract_min(FibHeap *heap);                      // Remove the minimum node
void fib_heap_update(FibHeap *heap, Type oldkey, Type newkey); // Update the node with value oldkey with value newkey
FibHeap *fib_heap_union(FibHeap *h1, FibHeap *h2);             // Merge h1 and h2, and return the merged heap
int fib_heap_contains(FibHeap *heap, Type key);                // Check if there is any node with value key in heap; return 1 if yes, and 0 if no
int fib_heap_get_min(FibHeap *heap, Type *pkey);               // Store the value of the minimum node into pkey; return 1 if success, and 0 if failure
void fib_heap_destroy(FibHeap *heap);                          // Dispose a heap
void fib_print(FibHeap *heap);                                 // Print a heap

#endif