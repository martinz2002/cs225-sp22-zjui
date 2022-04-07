/**
 * @file fiboheap.cpp
 * @author skywang (original writer); Li Rong & Zhong Tiantian (Modifier & commentor)
 * @brief An implementation of fibonacci heap.
 * @version 0.1
 * @date 2014-04-05
 * 
 * @copyright Copyright (c) 2014
 * 
 */

#include "headers/fiboheap.h"
#define LOG2(x) ((log((double)(x))) / (log(2.0)))

static FibNode *fib_heap_search(FibHeap *heap, Type key);


/**
 * @brief Remove node from a doubly-linked list
 * 
 * @param node the node to be removed
 */
static void fib_node_remove(FibNode *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}


/**
 * @brief Add a node before the doubly-linked list "root"
 * 
 * @param node node to be added
 * @param root root of the doubly-linked list
 */
static void fib_node_add(FibNode *node, FibNode *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/**
 * @brief concat list B to the back of list A
 * 
 * @param a front node
 * @param b back node to be concated to a
 */
static void fib_node_cat(FibNode *a, FibNode *b)    // 
{
    FibNode *tmp;

    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}


/**
 * @brief Create a fibo heap
 * 
 * @return FibHeap* A pointer to the new heap
 */
FibHeap* fib_heap_make()
{
    FibHeap* heap;

    heap = (FibHeap *) malloc(sizeof(FibHeap));
    if (heap == NULL)
    {
        printf("Error: make FibHeap failed\n");
        return NULL;
    }

    heap->keyNum = 0;
    heap->maxDegree = 0;
    heap->min = NULL;
    heap->cons = NULL;

    return heap;
}


/**
 * @brief Create new nodes for fibo heap
 * 
 * @param key key for the new node
 * @return FibNode* the pointer to the heap with new node inserted
 */
static FibNode* fib_node_make(Type key)
{
    FibNode * node;

    node = (FibNode *) malloc(sizeof(FibNode));
    if (node == NULL)
    {
        printf("Error: make Node failed\n");
        return NULL;
    }
    node->key    = key;
    node->degree = 0;
    node->left   = node;
    node->right  = node;
    node->parent = NULL;
    node->child  = NULL;

    return node;
}

/**
 * @brief Insert a existing node into the heap
 * 
 * @param heap the heap where the node is inserted
 * @param node the node to insert
 */
static void fib_heap_insert_node(FibHeap *heap, FibNode *node)
{
    if (heap->keyNum == 0)
        heap->min = node;
    else
       {
        fib_node_add(node, heap->min);
        if (node->key < heap->min->key)
            heap->min = node;
    }
    heap->keyNum++;
}

/**
 * @brief Insert a key to the heap
 * 
 * @param heap the heap where the key is inserted
 * @param key the key to insert
 */
void fib_heap_insert_key(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap==NULL)
        return ;

    node = fib_node_make(key);
    if (node == NULL)
        return ;

    fib_heap_insert_node(heap, node);
}

/**
 * @brief combine h1 and h2 and return the merged heap
 * 
 * @param h1 a pointer to a heap
 * @param h2 a pointer to a heap
 * @return FibHeap* the pointer to the merged heap
 */
FibHeap* fib_heap_union(FibHeap *h1, FibHeap *h2)
{
    FibHeap *tmp;

    if (h1==NULL)
        return h2;
    if (h2==NULL)
        return h1;

    // set h1 as the father heap and attach h2 to h1, the operations below is to make sure the degree of h1 is maximized
    if(h2->maxDegree > h1->maxDegree)
    {
        tmp = h1;
        h1 = h2;
        h2 = tmp;
    }

    if((h1->min) == NULL)                // h1 has no minimum node
    {
        h1->min = h2->min;
        h1->keyNum = h2->keyNum;
        free(h2->cons);
        free(h2);
    }
    else if((h2->min) == NULL)           // h1 has minimum node && h2 has no minimum node
    {
        free(h2->cons);
        free(h2);
    }                                   // h1 has minimum node && h2 has minimum node
    else
    {
        // append the root linked list in h2 to h1
        fib_node_cat(h1->min, h2->min);
        if (h1->min->key > h2->min->key)
            h1->min = h2->min;
        h1->keyNum += h2->keyNum;
        free(h2->cons);
        free(h2);
    }

    return h1;
}

/**
 * @brief remove the minimum node of heap from the root of a linked list, which means the tree that the minimum node belongs to is removed from the heap
 * 
 * @param heap 
 * @return FibNode* 
 */
static FibNode *fib_heap_remove_min(FibHeap *heap)
{
    FibNode *min = heap->min;

    if (heap->min == min->right)
        heap->min = NULL;
    else
    {
        fib_node_remove(min);
        heap->min = min->right;
    }
    min->left = min->right = min;

    return min;
}

/**
 * @brief Link a node to the root node
 * 
 * @param heap 
 * @param node 
 * @param root 
 */
static void fib_heap_link(FibHeap * heap, FibNode * node, FibNode *root)
{
    // remove node from the doubly linked list
    fib_node_remove(node);
    // set node as the child of root
    if (root->child == NULL)
        root->child = node;
    else
        fib_node_add(node, root->child);

    node->parent = root;
    root->degree++;
    node->marked = 0;
}

/**
 * @brief allocate space for fib_heap_consolidate
 * 
 * @param heap 
 */
static void fib_heap_cons_make(FibHeap * heap)
{
    int old = heap->maxDegree;


    heap->maxDegree = LOG2(heap->keyNum) + 1;

    // reallocate the memory if the original space is not enough
    if (old >= heap->maxDegree)
        return ;

    // we need maxDegree+1 since the heap with degree of  heap->maxDegree may be combined
    heap->cons = (FibNode **)realloc(heap->cons,
            sizeof(FibHeap *) * (heap->maxDegree + 1));
}

/**
 * @brief combine the trees that have same degree on the left side and right side of the fibonacci heap's root linked list
 * 
 * @param heap 
 */
static void fib_heap_consolidate(FibHeap *heap)
{
    int i, d, D;
    FibNode *x, *y, *tmp;

    fib_heap_cons_make(heap);//create the space for hash
    D = heap->maxDegree + 1;

    for (i = 0; i < D; i++)
        heap->cons[i] = NULL;

    // combine the root nodes with the same degree to ensure there is only one tree with certain degree
    while (heap->min != NULL)
    {
        x = fib_heap_remove_min(heap);    // take out the tree that possesses the minimum node
        d = x->degree;                    // get the degree of the minimum tree's degree
        // heap->cons[d] != NULL，shows that the degree of x and y are the same
        while (heap->cons[d] != NULL)
        {
            y = heap->cons[d];            // y is the tree that has the same degree with x
            if (x->key > y->key)        // ensure the key value of x is smaller than y
            {
                tmp = x;
                x = y;
                y = tmp;

            }
            fib_heap_link(heap, y, x);    // link y to x
            heap->cons[d] = NULL;
            d++;
        }
        heap->cons[d] = x;
    }
    heap->min = NULL;

    // add the nodes in heap->cons to the root list
    for (i=0; i<D; i++)
    {
        if (heap->cons[i] != NULL)
        {
            if (heap->min == NULL)
                heap->min = heap->cons[i];
            else
            {
                fib_node_add(heap->cons[i], heap->min);
                if ((heap->cons[i])->key < heap->min->key)
                    heap->min = heap->cons[i];
            }
        }
    }
}

/**
 * @brief [helper] remove the minimum node and return the fibonacci heap whose nodes has been removed
 * 
 * @param heap 
 * @return FibNode* the fibonacci heap whose nodes has been removed
 */
FibNode* _fib_heap_extract_min(FibHeap *heap)
{
    if (heap==NULL || heap->min==NULL)
        return NULL;

    FibNode *child = NULL;
    FibNode *min = heap->min;
    // add every son of "min" to the root linked list of the fibonacci heap
    while (min->child != NULL)
    {
        child = min->child;
        fib_node_remove(child);
        if (child->right == child)
            min->child = NULL;
        else
            min->child = child->right;

        fib_node_add(child, heap->min);
        child->parent = NULL;
    }

    // remove min from the root linked list
    fib_node_remove(min);
    // if min is the only node in the heap, 若min是堆中唯一节点，则设置堆的最小节点为NULL；
    // 否则，设置堆的最小节点为一个非空节点(min->right)，然后再进行调节。
    if (min->right == min)
        heap->min = NULL;
    else
    {
        heap->min = min->right;
        fib_heap_consolidate(heap);
    }
    heap->keyNum--;

    return min;
}

/**
 * @brief Extract the minimum node of a heap
 * 
 * @param heap 
 */
void fib_heap_extract_min(FibHeap *heap)
{
    FibNode *node;

    if (heap==NULL || heap->min==NULL)
        return ;

    node = _fib_heap_extract_min(heap);
    if (node!=NULL)
        free(node);
}

/**
 * @brief Check whether there's a node with value key
 * 
 * @param heap 
 * @param pkey the key to search
 * @return int exist -- 1; not exist -- 0
 */
int fib_heap_get_min(FibHeap *heap, Type *pkey)
{
    if (heap==NULL || heap->min==NULL || pkey==NULL)
        return 0;

    *pkey = heap->min->key;
    return 1;
}

/**
 * @brief Modify the degree of a node
 * 
 * @param parent 
 * @param degree 
 */
static void renew_degree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renew_degree(parent->parent, degree);
}

/**
 * @brief Make a node independent from its parents and become a member of the root list
 * 
 * @param heap the heap where the node lies
 * @param node the node to make independent
 * @param parent the parent node of the node
 */
static void fib_heap_cut(FibHeap *heap, FibNode *node, FibNode *parent)
{
    fib_node_remove(node);
    renew_degree(parent, node->degree);
    // node没有兄弟
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = 0;
    // 将"node所在树"添加到"根链表"中
    fib_node_add(node, heap->min);
}

/**
 * @brief Perform cascading cut to node
 * NOTE: 如果减小后的结点破坏了最小堆性质，则把它切下来(即从所在双向链表中删除，并将其插入到由最小树根节点形成的双向链表中)，然后再从"被切节点的父节点"到所在树根节点递归执行级联剪枝
 * 
 * @param heap 
 * @param node 
 */
static void fib_heap_cascading_cut(FibHeap *heap, FibNode *node)
{
    FibNode *parent = node->parent;
    if (parent != NULL)
        return ;

    if (node->marked == 0)
        node->marked = 1;
    else
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
}

/**
 * @brief Reduce the key of a node to a given value
 * 
 * @param heap 
 * @param node 
 * @param key the key to reduce to
 */
static void fib_heap_decrease(FibHeap *heap, FibNode *node, Type key)
{
    FibNode *parent;

    if (heap==NULL || heap->min==NULL ||node==NULL)
        return ;

    if ( key>=node->key)
    {
        printf("decrease failed: the new key(%d) is no smaller than current key(%d)\n", key, node->key);
        return ;
    }

    node->key = key;
    parent = node->parent;
    if (parent!=NULL && node->key < parent->key)
    {
        // 将node从父节点parent中剥离出来，并将node添加到根链表中
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    // 更新最小节点
    if (node->key < heap->min->key)
        heap->min = node;
}

/**
 * @brief Increase the key of a node to a given value
 * 
 * @param heap 
 * @param node 
 * @param key the key to increase to
 */
static void fib_heap_increase(FibHeap *heap, FibNode *node, Type key)
{
    FibNode *child, *parent, *right;

    if (heap==NULL || heap->min==NULL ||node==NULL)
        return ;

    if (key <= node->key)
    {
        printf("increase failed: the new key(%d) is no greater than current key(%d)\n", key, node->key);
        return ;
    }

    // 将node每一个儿子(不包括孙子,重孙,...)都添加到"斐波那契堆的根链表"中
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // 将child从node的子链表中删除
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // 将child添加到根链表中
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // 如果node不在根链表中，
    //     则将node从父节点parent的子链接中剥离出来，
    //     并使node成为"堆的根链表"中的一员，
    //     然后进行"级联剪切"
    // 否则，则判断是否需要更新堆的最小节点
    parent = node->parent;
    if(parent != NULL)
    {
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }
    else if(heap->min == node)
    {
        right = node->right;
        while(right != node)
        {
            if(node->key > right->key)
                heap->min = right;
            right = right->right;
        }
    }
}

/**
 * @brief [helper] update the key of a node
 * 
 * @param heap 
 * @param node 
 * @param key 
 */
void _fib_heap_update(FibHeap *heap, FibNode *node, Type key)
{
    if(key < node->key)
        fib_heap_decrease(heap, node, key);
    else if(key > node->key)
        fib_heap_increase(heap, node, key);
    else
        printf("No need to update!!!\n");
}

void fib_heap_update(FibHeap *heap, Type oldkey, Type newkey)
{
    FibNode *node;

    if (heap==NULL)
        return ;

    node = fib_heap_search(heap, oldkey);
    if (node!=NULL)
        _fib_heap_update(heap, node, newkey);
}

/**
 * @brief look for a node with key in root
 * 
 * @param root 
 * @param key 
 * @return FibNode* 
 */
static FibNode* fib_node_search(FibNode *root, Type key)
{
    FibNode *t = root;    // 临时节点
    FibNode *p = NULL;    // 要查找的节点

    if (root==NULL)
        return root;

    do
    {
        if (t->key == key)
        {
            p = t;
            break;
        }
        else
        {
            if ((p = fib_node_search(t->child, key)) != NULL)
                break;
        }
        t = t->right;
    } while (t != root);

    return p;
}

/**
 * @brief Find a node with key
 * 
 * @param heap 
 * @param key 
 * @return FibNode* 
 */
static FibNode *fib_heap_search(FibHeap *heap, Type key)
{
    if (heap==NULL || heap->min==NULL)
        return NULL;

    return fib_node_search(heap->min, key);
}

/**
 * @brief Find a node with key in the heap
 * 
 * @param heap 
 * @param key 
 * @return int 1 if exists; 0 if not
 */
int fib_heap_contains(FibHeap *heap, Type key)
{
    return fib_heap_search(heap,key)!=NULL ? 1: 0;
}

/**
 * @brief Remove a node
 * 
 * @param heap 
 * @param node the node to remove
 */
static void _fib_heap_delete(FibHeap *heap, FibNode *node)
{
    Type min = heap->min->key;
    fib_heap_decrease(heap, node, min-1);
    _fib_heap_extract_min(heap);
    free(node);
}

/**
 * @brief Remove a node
 * 
 * @param heap 
 * @param key 
 */
void fib_heap_delete(FibHeap *heap, Type key)
{
    FibNode *node;

    if (heap==NULL || heap->min==NULL)
        return ;

    node = fib_heap_search(heap, key);
    if (node==NULL)
        return ;

    _fib_heap_delete(heap, node);
}

/**
 * @brief Dispose a node
 * 
 * @param node 
 */
static void fib_node_destroy(FibNode *node)
{
    FibNode *start = node;

    if(node == NULL)
        return;

    do {
        fib_node_destroy(node->child);
        // 销毁node，并将node指向下一个
        node = node->right;
        free(node->left);
    } while(node != start);
}

/**
 * @brief Destroy a fibonacci heap
 * 
 * @param heap 
 */
void fib_heap_destroy(FibHeap *heap)
{
    fib_node_destroy(heap->min);
    free(heap->cons);
    free(heap);
}

/*
 * 打印"斐波那契堆"
 *
 * 参数说明：
 *     node       -- 当前节点
 *     prev       -- 当前节点的前一个节点(父节点or兄弟节点)
 *     direction  --  1，表示当前节点是一个左孩子;
 *                    2，表示当前节点是一个兄弟节点。
 */

/**
 * @brief [helper] Print fibonacci heap
 * 
 * @param node current node
 * @param prev precedental node of current node
 * @param direction indicating the type of current node; 1 = left child; 2 = sibling
 */
static void _fib_print(FibNode *node, FibNode *prev, int direction)
{
    FibonacciNode *start=node;

    if (node==NULL)
        return ;
    do
    {
        if (direction == 1)
            printf("%8d(%d) is %2d's child\n", node->key, node->degree, prev->key);
        else
            printf("%8d(%d) is %2d's next\n", node->key, node->degree, prev->key);

        if (node->child != NULL)
            _fib_print(node->child, node, 1);

        // 兄弟节点
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

/**
 * @brief Print a fibonacci heap
 * 
 * @param heap 
 */
void fib_print(FibHeap *heap)
{
    int i=0;
    FibonacciNode *p;

    if (heap==NULL || heap->min==NULL)
        return ;

    printf("== 斐波那契堆的详细信息: ==\n");
    p = heap->min;
    do {
        i++;
        printf("%2d. %4d(%d) is root\n", i, p->key, p->degree);

        _fib_print(p->child, p, 1);
        p = p->right;
    } while (p != heap->min);
    printf("\n");
}