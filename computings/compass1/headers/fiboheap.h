/**
 * @file fiboheap.h
 * @author Li Rong
 * @brief 
 * @version 0.1
 * @date 2022-04-05
 * 
 * @copyright Copyright (c) 2022 Zhejiang University
 * 
 */

#include <bits/stdc++.h>
#ifndef _FIBONACCI_HEAP_H_
#define _FIBONACCI_HEAP_H_

typedef int64_t Type;
typedef struct _FibonacciNode
{
    Type key;                      // 关键字(键值)
    int degree;                    // 度数
    struct _FibonacciNode *left;   // 左兄弟
    struct _FibonacciNode *right;  // 右兄弟
    struct _FibonacciNode *child;  // 第一个孩子节点
    struct _FibonacciNode *parent; // 父节点
    int marked;                    //是否被删除第1个孩子(1表示删除，0表示未删除)
} FibonacciNode, FibNode;

typedef struct _FibonacciHeap
{
    int64_t keyNum;               // 堆中节点的总数
    int maxDegree;                // 最大度
    struct _FibonacciNode *min;   // 最小节点(某个最小堆的根节点)
    struct _FibonacciNode **cons; // 最大度的内存区域
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