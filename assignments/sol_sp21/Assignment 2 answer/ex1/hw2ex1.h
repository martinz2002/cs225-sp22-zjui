/*
 * @ Author     : 
 * 
 * @ File       : 
 * 
 * @ Purpose    : 
 * 
 * @ Usage      : 
 * 
 * @ Description: 
 * 
 * @ Input      : 
 * 
 * @ Output     : 
 * 
 */
#ifndef ex1
#define ex1

#include <iostream>
#include <vector>
using namespace std;

template <class T> class Solution {
    public:
        Solution(vector<T> input){
            data = input;
        };

        vector<T> MergeSort_k(vector<T> lst, int k);
        vector<T> MergeSort_t(vector<T> lst, int t);
        vector<T> SelfSort(vector<T> lst);
        void vec_print(vector<T> vec);
        vector<T> data;
        void test(int k, int t);
    private:
        vector<T> _merge(vector<T> lst1, vector<T> lst2);
};


template <class T> vector<T> Solution<T>::MergeSort_k(vector<T> lst, int k){
    int len = lst.size();
    if (len <= 1){
        return lst;
    }

    int sublen = (len < k) ? 1: len / k;
    // Two cases:
    // 1. len < k: each sublist has only 1 elements, but may not enough k list
    // 2. len >= k: all k sublist contains at least 1 element
    if (k <= len){
        int starti = 0;
        vector<T> res_lst = MergeSort_k(vector<T>(lst.begin()+starti, lst.begin()+starti+sublen), k);
        starti += sublen;
        for (int i = 0; i < k - 2; i++){
            res_lst = _merge(res_lst, MergeSort_k(vector<T>(lst.begin()+starti, lst.begin()+starti+sublen), k));
            starti += sublen;
        }
        return _merge(res_lst, MergeSort_k(vector<T>(lst.begin()+starti, lst.end()), k));
    }
    else{// k > len
        vector<T> res_lst({lst[0]});
        for(int i = 1; i < len; i ++){
            res_lst = _merge(res_lst, vector<T>({lst[i]}));
        }
        return res_lst;
    }
};


template <class T> vector<T> Solution<T>::_merge(vector<T> lst1, vector<T> lst2){
    vector<T> res;
    int i = 0, j = 0;
    while(i < lst1.size() || j < lst2.size()){
        if (i < lst1.size() && j < lst2.size()){
            if (lst1[i] < lst2[j]){
                res.push_back(lst1[i]);
                i++;
            }else{
                res.push_back(lst2[j]);
                j++;
            }
        }else if (i == lst1.size()){
            res.push_back(lst2[j]);
            j++;
        }else { // j == lst2.size()
            res.push_back(lst1[i]);
            i++;
        }
    }
    return res;
};


template<class T> vector<T> Solution<T>::MergeSort_t(vector<T> lst, int t){
    // size < threshold, alternative sort
    if (lst.size() < t ){
        return SelfSort(lst);
    }

    // Normal Merge Sort
    int halflen = lst.size() / 2;
    return _merge(MergeSort_t(vector<T>(lst.begin(), lst.begin()+halflen),t), MergeSort_t(vector<T>(lst.begin()+halflen, lst.end()), t));
}


template<class T> vector<T> Solution<T>::SelfSort(vector<T> lst){
    T temp;
    for(int i = 0; i < lst.size(); i++){
        for(int j = i; j > 0 && lst[j] < lst[j-1]; j--){
            temp = lst[j];
            lst[j] = lst[j-1];
            lst[j-1] = temp;
        }
    }
    return lst;
}


template<class T> void Solution<T>::vec_print(vector<T> vec){
    for (T i: vec){
        cout << i << "  ";
    }
    cout << endl;
    return ;
}

template <class T> void Solution<T>::test(int k, int t){
    cout << "Self-implemented Sort:          ";
    vec_print(SelfSort(data));
    cout << "Merge Sort with K sublist:      ";
    vec_print(MergeSort_k(data, k));
    cout << "Merge Sort with Insertion Sort: ";
    vec_print(MergeSort_t(data, t));
}
#endif 

