//
//  solution.h
//

#ifndef TRIE_SOLUTION_H
#define TRIE_SOLUTION_H

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

// Helper function, convert AList<char> into string
string CharList2Str(AList<char> list) {
    string s;
    for (int i = 0; i < list.getlength(); ++i) {
        s += list[i+1];
    }
    return s;
}

template<class T> bool trie<T>::contains_extend(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result) {
    if (list.getlength() == 0)
        return false;
    if (pt == 0) {
        return false;
    }
    T key = list[1];  // examine the first element of the input list
    if (pt->getdata() == key)
    {
        path.append(pt->getdata());
        list.remove(1);
        /* if the input list is used up, check if the following elements was marked as terminal in the trie */
        if (list.getlength() == 0) {
            trienode<T> *curr = pt->getfollow();
            if (curr->last)
                result.append(CharList2Str(path) + curr->getdata());
            while (curr->getnext()) {
                curr = curr->getnext();
                if (curr->last)
                    result.append(CharList2Str(path) + curr->getdata());
            }
            return 0;
        }
        /* proceed recursively with the follow pointer */
        return contains_extend(pt->getfollow(), list, path, result);
    }
    /* otherwise follow the next pointer */
    return contains_extend(pt->getnext(), list, path, result);
}

template<class T> AList<string> trie<T>::return_extend(AList<T> list, AList<string> &result) {
    AList<T> path;
    if (this->intrie(list)) {
        cout << "word is in the dictionary" << endl;
        return result;
    }

    contains_extend(start, list, path, result);
    if (0 == result.getlength()) {
        cout << "no extension words dictrionary\n";
    }
    return result;
}

template<class T> AList<string> trie<T>::return_prefix(AList<T> list, AList<string> &result) {
    if (this->intrie(list)) {
        cout << "word is in the dictionary" << endl;
        return result;
    }

    int list_len = list.getlength();
    // Check for the first prefix
    list.remove(list_len);
    if (this->intrie(list))
        result.append(CharList2Str(list));

    // Check for the second prefix
    list.remove(list_len-1);
    if (this->intrie(list))
        result.append(CharList2Str(list));

    if (0 == result.getlength()){
        cout << "no prefix words dictrionary" << endl;
    }

    return result;
}

template<class T> bool trie<T>::contains_diff(trienode<T> *pt, AList<T> list, AList<T> path, AList<string> &result, int diff) {
    // Illegitimate cases
    if ((diff > 1) | (pt == 0) | (list.getlength() == 0))
        return false;
    // End cases, last char left for list
    if (list.getlength() == 1) {
        do {
            if (pt->getdata() != list[1]) {
                // Proper result if last char does not match and diff is originally 0
                if ((diff == 0) & (pt->getlast())) {
                    result.append(CharList2Str(path) + pt->getdata());
                }
            // Proper result if last char matches and diff is originally 1
            } else if ((diff == 1) & (pt->getlast())) {
                result.append(CharList2Str(path) + pt->getdata());
            }
            // Loop through the whole level
            pt = pt->getnext();
        } while (pt);
        // Found meet end of a layer, return
        return 0;   // Here 0 does not mean result not found since we don't know
    } else {
        // Recursive part, Depth-First-Search
        T key = list[1];
        // Create particular new_list and path_list for each node since they are unique
        AList<T> new_list;
        for (int i = 0; i < list.getlength(); ++i)
            new_list.append(list[i + 1]);
        new_list.remove(1);
        do {
            AList<T> new_path;
            for (int i = 0; i < path.getlength(); ++i)
                new_path.append(path[i + 1]);
            new_path.append(pt->getdata());
            if (pt->getdata() == key) {
                contains_diff(pt->getfollow(), new_list, new_path, result, diff);
            } else {
                contains_diff(pt->getfollow(), new_list, new_path, result, diff + 1);
            }
            pt = pt->getnext();
        } while (pt);
        return false;
    }
}

template<class T> AList<string> trie<T>::return_diff(AList<T> list, AList<string> &result) {
    AList<T> path;

    if (this->intrie(list)) {
        cout << "word is in the dictionary" << endl;
        return result;
    }

    contains_diff(start, list, path, result, 0);
    if (0 == result.getlength()) {
        cout << "no words differ 1 character from given word in dictionary\n";
    }
    return result;
}

#endif //TRIE_SOLUTION_H
