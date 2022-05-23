//
//  test.cpp
//
//  for testing graph traversal for bipartite graphs
//
//  Created by KD on 12.04.21.
//  Modified on 06.05.22
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "bpgraph.cpp"
using std::cout;
using std::cin;

int main()
{
    // first graph
    bpgraphtraversal<int> * mygraph = new bpgraphtraversal<int>;
    (*mygraph).addedge(2,13);
    (*mygraph).addedge(1,14);
    (*mygraph).addedge(1,12);
    (*mygraph).addedge(3,14);
    (*mygraph).addedge(2,14);
    (*mygraph).addvertex1(7);
    (*mygraph).addedge(3,17);
    (*mygraph).addedge(7,12);
    (*mygraph).addedge(1,14);
    (*mygraph).prettyprint();
    searchtree<int> * mybfs = (*mygraph).bfs(1);
    (*mybfs).prettyprint();
    deepsearchtree<int> * mydfs = (*mygraph).dfs(1);
    (*mydfs).prettyprint();
    // second graph
    bpgraphtraversal<int> * yourgraph = new bpgraphtraversal<int>;
    (*yourgraph).addedge(1,22);
    (*yourgraph).addedge(2,23);
    (*yourgraph).addedge(1,23);
    (*yourgraph).addedge(1,24);
    (*yourgraph).addedge(4,25);
    (*yourgraph).addedge(5,22);
    (*yourgraph).addedge(6,24);
    (*yourgraph).addedge(6,27);
    (*yourgraph).addedge(6,28);
    (*yourgraph).addedge(6,29);
    (*yourgraph).addedge(8,25);
    (*yourgraph).addedge(4,24);
    (*yourgraph).addedge(9,28);
    (*yourgraph).prettyprint();
    searchtree<int> * yourbfs = (*yourgraph).bfs(1);
    (*yourbfs).prettyprint();
    deepsearchtree<int> * yourdfs = (*yourgraph).dfs(1);
    (*yourdfs).prettyprint();
    // third graph
    (*mygraph).addedge(31,22);
    (*mygraph).addedge(32,23);
    (*mygraph).addedge(31,23);
    (*mygraph).addedge(31,24);
    (*mygraph).addedge(34,25);
    (*mygraph).addedge(35,22);
    (*mygraph).addedge(36,24);
    (*mygraph).addedge(36,27);
    (*mygraph).addedge(36,28);
    (*mygraph).addedge(36,29);
    (*mygraph).addedge(38,25);
    (*mygraph).addedge(34,24);
    (*mygraph).addedge(39,28);
    (*mygraph).prettyprint();
    deepsearchtree<int> * mydfsall = (*mygraph).dfsall();
    (*mydfsall).prettyprint();
    return 0;
}
