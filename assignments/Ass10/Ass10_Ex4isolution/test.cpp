//
//  test.cpp
//
//  for testing Kruskal's algorithm
//
//  Created by KD on 11.04.21.
//  Modified on 16.05.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graph.cpp"
using std::cout;
using std::cin;

int main()
{
    graph<int> * mygraph = new graph<int>;
    (*mygraph).addedge(2,3,6);
    (*mygraph).addedge(1,4,11);
    (*mygraph).addedge(1,2,4);
    (*mygraph).addedge(3,4,7);
    (*mygraph).addedge(2,4,5);
    (*mygraph).addedge(3,7,5);
    (*mygraph).addedge(7,2,8);
    (*mygraph).addedge(5,4,2);
    (*mygraph).addedge(5,6,7);
    (*mygraph).addedge(5,8,6);
    (*mygraph).addedge(6,8,10);
    (*mygraph).addedge(9,8,3);
    (*mygraph).addedge(9,7,9);
    (*mygraph).prettyprint();
    int sum = 0;
    edgelist<int> * myedgelist1 = (*mygraph).kruskal(sum);
    cout << "Minimum Spanning Tree:\n";
    (*myedgelist1).prettyprint();
    cout << "Total costs: " << sum << "\n";
}
