#include<bits/stdc++.h>
#include"alist.h"
#include"alist_template.cpp"

#define MAXLEN 100

using namespace std;
int dataInput[MAXLEN];
//int dataAnswer[MAXLEN];
int k; // The index after which the elements in the list is supposed to be deleted

int main()
{
    freopen("data/input.in", "r", stdin);
    // freopen("output.txt", "w", stdout);

    AList<int> iList;
    AList<int> stdList;
    // AList<double> dList;
    // AList<string> sList;

    // Delete the last k elements
    iList.delete_last(k);

    // Generate and compare
    int i = 0;
    bool correct = (iList.numitems == );   // false = wrong answer; true = correct
    while((i < k) && correct)
    {
        if (dataInput[i] != iList.getitem(i))
            correct = false;
        
        i++;
    }
    
    


    
    // Generate our answer
    

}