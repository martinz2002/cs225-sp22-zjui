//
//  test.cpp
//
//  for testing the graphtraversal class for finding articulation points
//
//  Created by KD on 06.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graphtraversal.cpp"
using std::cout;
using std::cin;

int main()
{
    // first graph
    graphtraversal<int> * mygraph = new graphtraversal<int>;
    (*mygraph).addedge(1,2);
    (*mygraph).addedge(1,3);
    (*mygraph).addedge(2,4);
    (*mygraph).addedge(3,4);
    (*mygraph).addedge(3,5);
    (*mygraph).addedge(5,6);
    (*mygraph).addedge(5,7);
    (*mygraph).addedge(5,8);
    (*mygraph).addedge(6,7);
    (*mygraph).addedge(8,9);
    (*mygraph).addedge(8,10);
    (*mygraph).prettyprint();
    elist<int> * myartlist = (*mygraph).articulation(1);
    (*myartlist).prettyprint();
    return 0;
}
