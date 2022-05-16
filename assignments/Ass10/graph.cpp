#include "graph.h"

using namespace std;

int main()
{
    Graph g(15);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 6);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 3, 15);
    g.addEdge(2, 4, 4);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 8);
    g.addEdge(4, 5, 7);
    g.addEdge(4, 6, 14);
    g.addEdge(5, 6, 2);
    g.addEdge(5, 7, 1);
    g.addEdge(6, 7, 10);
    g.addEdge(7, 8, 8);
    g.addEdge(7, 9, 7);
    g.addEdge(8, 9, 9);
    g.addEdge(8, 10, 11);
    g.addEdge(9, 10, 2);
    g.addEdge(9, 11, 4);
    g.addEdge(2, 12, 6);
    g.addEdge(7, 13, 5);
    g.addEdge(8, 14, 3);
    g.printGraph();
    g.kruskalMST();
    return 0;
}