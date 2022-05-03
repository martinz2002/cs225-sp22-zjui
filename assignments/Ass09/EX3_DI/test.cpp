//
//  test.cpp
//
// for testing the DIgraph traversal class
//
//  Created by KD on 12.04.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "graphtraversal.cpp"
using std::cin;
using std::cout;

int main()
{
    // first DIgraph
    DI_graphtraversal<int> *mygraph = new DI_graphtraversal<int>;
    (*mygraph).addedge(2, 3);
    (*mygraph).addedge(1, 4);
    (*mygraph).addedge(1, 2);
    (*mygraph).addedge(3, 4);
    (*mygraph).addedge(2, 4);
    (*mygraph).addvertex(7);
    (*mygraph).addedge(3, 7);
    (*mygraph).addedge(7, 2);
    (*mygraph).addedge(1, 4);
    (*mygraph).prettyprint();
    searchtree<int> *mybfs = (*mygraph).bfs(1);
    (*mybfs).prettyprint();
    deepsearchtree<int> *mydfs = (*mygraph).dfs(1);
    (*mydfs).prettyprint();
    // second DIgraph
    DI_graphtraversal<int> *yourgraph = new DI_graphtraversal<int>;
    (*yourgraph).addedge(1, 2);
    (*yourgraph).addedge(2, 3);
    (*yourgraph).addedge(1, 3);
    (*yourgraph).addedge(1, 4);
    (*yourgraph).addedge(4, 5); // remove this line or next line to test acyclic case.
    (*yourgraph).addedge(5, 6); // The next line
    (*yourgraph).addedge(6, 4);
    (*yourgraph).addedge(6, 7);
    (*yourgraph).addedge(6, 8);
    (*yourgraph).addedge(6, 9);
    (*yourgraph).addedge(8, 10);
    (*yourgraph).addedge(10, 4);
    (*yourgraph).prettyprint();
    searchtree<int> *yourbfs = (*yourgraph).bfs(1);
    (*yourbfs).prettyprint();
    deepsearchtree<int> *yourdfs = (*yourgraph).dfs(1);
    (*yourdfs).prettyprint();
    cout << "Is your graph acyclic? " << (*yourgraph).is_acyclic(1) << "\n";
    return 0;
}
