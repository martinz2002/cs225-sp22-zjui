//
//  test.cpp
//  
//  Created by KD on 01.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "avl.cpp"
using std::cout;
using std::cin;

int main()
{
    AVL<int> mytree1 = AVL<int>();
    mytree1.insert(0);
    mytree1.insert(30);
    mytree1.insert(42);
    mytree1.insert(55);
    mytree1.insert(-4);
    mytree1.insert(1);
    mytree1.insert(2);
    mytree1.insert(-8);
    mytree1.insert(79);
    mytree1.insert(3);
    mytree1.insert(4);
    mytree1.insert(5);
    mytree1.insert(-1);
    mytree1.insert(6);
    mytree1.insert(9);
    mytree1.insert(187);
    mytree1.insert(-7);
    mytree1.insert(-6);
    mytree1.insert(-5);
    mytree1.insert(7);
    mytree1.insert(-3);
    mytree1.insert(264);
    mytree1.insert(8);
    mytree1.insert(-2);
    mytree1.display();
    int result = mytree1.median();
    cout << "The median of the given AVL tree is " << result << ".\n\n";
    return(0);
}
