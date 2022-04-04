#include "headers/fiboheap.h"
/**
 * fibonacci heap realized by C
 *copied from
 * @author skywang
 * @date 2014/04/05
 */





#define LOG2(x) ((log((double)(x))) / (log(2.0)))

static FibNode *fib_heap_search(FibHeap *heap, Type key);

/*
 * remove nodes from doubly-linked lists
 */
static void fib_node_remove(FibNode *node)
{
    node->left->right = node->right;
    node->right->left = node->left;
}

/*add a single "node" before the doubly-linked list "root"
 *   a …… root
 *   a …… node …… root

*/
static void fib_node_add(FibNode *node, FibNode *root)
{
    node->left        = root->left;
    root->left->right = node;
    node->right       = root;
    root->left        = node;
}

/*linked list B to the back of list A*/
static void fib_node_cat(FibNode *a, FibNode *b)
{
    FibNode *tmp;

    tmp            = a->right;
    a->right       = b->right;
    b->right->left = a;
    b->right       = tmp;
    tmp->left      = b;
}


/*
 * create fibonacci heap
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

/*
 * create nodes of fibonacci heap
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

/*
 * insert nodes into fibonacci heap
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

/*
 * create a node with key value "key", and insert it into heap
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

/*
 * combine h1 and h2 and return the combined heap
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

/*
 * remove the minimum node of heap from the root linked list，
 * which means the tree that the minimum node belongs to is removed from the heap!
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

/*
 * link node to the root nodes
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

/*
 * create space for fib_heap_consolidate
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

/*
 * combine the trees that have same degree on the left side and right side of the fibonacci heap's root linked list
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

/*
 * remove the minimum node and return the fibonacci heap whose nodes has been removed
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
    // Otherwise，set the minimum node as the non-empty node(min->right)，and then adjust it;
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

void fib_heap_extract_min(FibHeap *heap)
{
    FibNode *node;

    if (heap==NULL || heap->min==NULL)
        return ;

    node = _fib_heap_extract_min(heap);
    if (node!=NULL)
        free(node);
}

/*
 * explore if there is the node whose value equals to key in the fiboheap; if there exists it, return 1; otherwise, return 0
 */
int fib_heap_get_min(FibHeap *heap, Type *pkey)
{
    if (heap==NULL || heap->min==NULL || pkey==NULL)
        return 0;

    *pkey = heap->min->key;
    return 1;
}

/*
 * modify the degree
 */
static void renew_degree(FibNode *parent, int degree)
{
    parent->degree -= degree;
    if (parent-> parent != NULL)
        renew_degree(parent->parent, degree);
}

/*
 * strip the nodes from the parent nodes' subchains
 * set the node as the number of the heap's root list
 */
static void fib_heap_cut(FibHeap *heap, FibNode *node, FibNode *parent)
{
    fib_node_remove(node);
    renew_degree(parent, node->degree);
    // no silbings with the node (there are no other nodes with the node whose parent node is the same)
    if (node == node->right)
        parent->child = NULL;
    else
        parent->child = node->right;

    node->parent = NULL;
    node->left = node->right = node;
    node->marked = 0;
    // add the trees which node belongs to to the root list.
    fib_node_add(node, heap->min);
}

/*
 * cascade cut the node
 *
 *     cascade cut：if the node that decreases breaks the property of the minimum heap,
 *     cut it out(delete it in the double linked list it belongs to，and then insert it into the double linked list 
 *     which is formed by the minimum root node
 *     Then excute "cascade cut" in a recursion way from the cut node's paerent node to its root node 
 *     
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

/*
 * decrease the value of the node in the fiboheap to the key 
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
        // strip the node from the parent node and add the node into the root list.
        fib_heap_cut(heap, node, parent);
        fib_heap_cascading_cut(heap, parent);
    }

    // update the minimum node
    if (node->key < heap->min->key)
        heap->min = node;
}

/*
 * increase the value of the node in the fiboheap to the key
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

    // add the node's child without grandchild and so on to theroot list in the fiboheap
    while (node->child != NULL)
    {
        child = node->child;
        fib_node_remove(child);               // delete the child from the node's child list
        if (child->right == child)
            node->child = NULL;
        else
            node->child = child->right;

        fib_node_add(child, heap->min);       // add the child to the root list
        child->parent = NULL;
    }
    node->degree = 0;
    node->key = key;

    // if the node isn't in the root list
    // strip the node from the paerent node's root list 
    // set the node as the number of the heap's root list    
    // and then cascade cut it   
    // otherwise, judge if we need to update the minimum node
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

/*
 * uodate the value of the node in the bionomial heap to the key
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

/*
 * search for the node whose value equals to the key in the minimum heap root
 */
static FibNode* fib_node_search(FibNode *root, Type key)
{
    FibNode *t = root;    // temporary node
    FibNode *p = NULL;    // the node searched for

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

/*
 * search for the node in the fiboheap whose value equals to the key
 */
static FibNode *fib_heap_search(FibHeap *heap, Type key)
{
    if (heap==NULL || heap->min==NULL)
        return NULL;

    return fib_node_search(heap->min, key);
}

/*
 * judge if there exists the node whose value equals to the key in the fiboheap
 * if there exists, return 1; otherwise, return 0
int fib_heap_contains(FibHeap *heap, Type key)
{
    return fib_heap_search(heap,key)!=NULL ? 1: 0;
}

/*
 * delete the node
 */
static void _fib_heap_delete(FibHeap *heap, FibNode *node)
{
    Type min = heap->min->key;
    fib_heap_decrease(heap, node, min-1);
    _fib_heap_extract_min(heap);
    free(node);
}

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

/*
 * dispose the fiboheap
 */
static void fib_node_destroy(FibNode *node)
{
    FibNode *start = node;

    if(node == NULL)
        return;

    do {
        fib_node_destroy(node->child);
        // dispose the node and point the node to the next
        node = node->right;
        free(node->left);
    } while(node != start);
}

void fib_heap_destroy(FibHeap *heap)
{
    fib_node_destroy(heap->min);
    free(heap->cons);
    free(heap);
}

/*
 *print the fiboheap
 *
 * variable instructions:
 *     node       -- present node
 *     prev       -- the last node before the present node (parent node or sibling node)
 *     direction  --  1，present node is a left child node
 *                    2，present node is a silbing node。
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

        // silbing node
        prev = node;
        node = node->right;
        direction = 2;
    } while(node != start);
}

void fib_print(FibHeap *heap)
{
    int i=0;
    FibonacciNode *p;

    if (heap==NULL || heap->min==NULL)
        return ;

    printf("== fiboheap's details: ==\n");
    p = heap->min;
    do {
        i++;
        printf("%2d. %4d(%d) is root\n", i, p->key, p->degree);

        _fib_print(p->child, p, 1);
        p = p->right;
    } while (p != heap->min);
    printf("\n");
}