//
//  test.cpp
//
//for testing the graph class
//
//  Created by KD on 11.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.cpp"
using std::cout;
using std::cin;

int main()
{
    BiPartite<int> * mygraph = new BiPartite<int>;
    (*mygraph).addedge(2,3);
    (*mygraph).addedge(1,4);
    (*mygraph).addedge(1,3);
    (*mygraph).addedge(2,4);
    (*mygraph).addedge(7,3);
    (*mygraph).addedge(1,5);
    mygraph->addedge(6,4);
    mygraph->addedge(6,5);
    mygraph->addedge(6,8);


    edgelist<int> * myedgelist6 = (*mygraph).perfectly_match();
    (*myedgelist6).prettyprint();
}
