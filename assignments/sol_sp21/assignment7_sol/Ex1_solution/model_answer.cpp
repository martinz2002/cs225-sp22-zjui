#include "avl.cpp"
#include "fifo.cpp"



/*
*   Ex.1 (i)
*   return value:   a pointer to a new list containing the selected elements
*   notes:          typically, there are three variants of DFS in trees:
*                                       inorder, postorder and preorder.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::DFS(void){
    AList<T>* list = new AList<T>();     // initialize a new AList to store the elements
    // call the helper function, recurse staring from the root                   
    _DFS_inorder(list, root);          // you can use whichever order you prefer                       
    return list;
};



// helper function
template<class T> void AVL<T>::_DFS_inorder(AList<T>* list, avlnode<T>* node){
    if (node == 0) return;  // if the current node doesn't exist, do nothing
    _DFS_inorder(list, node->getleft());
    list->append(node->getdata());
    _DFS_inorder(list, node->getright());
}



template<class T> void AVL<T>::_DFS_preorder(AList<T>* list, avlnode<T>* node){
    if (node == 0) return;  // if the current node doesn't exist, do nothing
    list->append(node->getdata());
    _DFS_preorder(list, node->getleft());
    _DFS_preorder(list, node->getright());
}



template<class T> void AVL<T>::_DFS_postorder(AList<T>* list, avlnode<T>* node){
    if (node == 0) return;  // if the current node doesn't exist, do nothing
    _DFS_postorder(list, node->getleft());
    _DFS_postorder(list, node->getright());
    list->append(node->getdata());
}



/*
*   Ex.1 (ii)
*   return value:   a pointer to a new list containing the selected elements
*   notes:          BFS is usually implemented with a FIFO queue, you may
*                   want to make use of that. Typically, when pushing the
*                   children of a node, there are two orders:
*                                   left child first or right child first.
*                   choose whichever you like the most.
*/
template<class T> AList<T>* AVL<T>::BFS(void){
    fifo<avlnode<T>*> queue = fifo<avlnode<T>*>(20);    // a FIFO queue which stores BFS-related info
    AList<T>* list = new AList<T>();                    // initialize a new AList to store the elements

    if (root == 0) return list;      // if the tree is empty, return an empty list

    queue.pushback(root);
    while (!queue.isempty()){
        avlnode<T>* temp = queue.popfront();    
        list->append(temp->getdata());
        if (temp->getright() != NULL)
            queue.pushback(temp->getright());
        if (temp->getleft() != NULL)
            queue.pushback(temp->getleft());

    }
    return list;
};



/*
*   Ex.1 (iii)
*   return value:   a pointer to a new list containing the selected elements
*/
template<class T> AList<T>* AVL<T>::range(T x, T y){
    AList<T>* list = this->DFS();
    AList<T>* res = new AList<T>();
    if (x > y)  return res;     // if the input parameters are invalid, return an empty list
    for (int i = 1; i <= list->getlength(); ++i){
        T temp = list->getitem(i);
        if (temp >= x && temp <= y)
            res->append(temp);
    }
    return res;
};
