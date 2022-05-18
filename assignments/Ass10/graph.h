#ifndef GRAPH_H_FOR_ASSIGNMENT_10
#define GRAPH_H_FOR_ASSIGNMENT_10
#include <bits/stdc++.h>
using namespace std;

class Edge
{
public:
    int64_t weight;
    int src, dest;
    Edge(int src, int dest, int64_t weight)
    {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
};

class vertex
{
public:
    int id;
    vector<Edge> edges;
    vertex(int id)
    {
        this->id = id;
    }
    void addEdge(int dest, int64_t weight)
    {
        edges.push_back(Edge(id, dest, weight));
    }
};

class Graph
{
public:
    int v_size;
    void DFSUtil(int v, bool visited[]);
    Graph(int V);
    void addEdge(int v, int w, int64_t weight);
    void DFS(int v);
    vector<vertex> vertex_set;
    void printGraph();
    void kruskalMST();
};

void Graph::kruskalMST()
{
    int V = v_size;
    vector<Edge> result;
    vector<Edge> edges;
    int _new_v = 0;
    bool is_edge = false;
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < vertex_set[i].edges.size(); j++)
        {
            edges.push_back(vertex_set[i].edges[j]);
            is_edge = true;
        }
        if (!is_edge)
        {
            is_edge = false;
            _new_v--;
        }
    }
    V += _new_v;
    sort(edges.begin(), edges.end(), [](Edge a, Edge b)
         { return a.weight < b.weight; });
    int i = 0;
    int e = 0;
    vector<Edge> mst;
    int now_color = 0;
    int *color = new int[V];
    for (int v = 0; v < V; v++)
        color[v] = 0;
    while (e < V - 1)
    {
        Edge next_edge = edges[i++];
        int src = color[next_edge.src];
        int dest = color[next_edge.dest];
        bool isCycle = false;
        if (src == 0 && dest == 0)
        {
            color[next_edge.src] = ++now_color;
            color[next_edge.dest] = now_color;
            mst.push_back(next_edge);
            e++;
        }
        else if (src == 0)
        {
            color[next_edge.src] = color[next_edge.dest];
            mst.push_back(next_edge);
            e++;
        }
        else if (dest == 0)
        {
            color[next_edge.dest] = color[next_edge.src];
            mst.push_back(next_edge);
            e++;
        }
        else if (src == dest)
        {
            isCycle = true;
        }
        else
        {
            for (int j = 0; j < V; j++)
            {
                if (color[j] == src)
                    color[j] = dest;
            }
            mst.push_back(next_edge);
            e++;
        }
    }
    for (int i = 0; i < mst.size(); i++)
    {
        cout << mst[i].src << " - " << mst[i].dest << " : " << mst[i].weight << endl;
    }
}

Graph::Graph(int V)
{
    this->v_size = V;
    for (int i = 0; i < V; i++)
    {
        vertex v(i);
        vertex_set.push_back(v);
    }
}

void Graph::addEdge(int v, int w, int64_t weight)
{
    vertex_set[v].addEdge(w, weight);
    vertex_set[w].addEdge(v, weight);
}

void Graph::DFSUtil(int v, bool visited[])
{
    visited[v] = true;
    cout << v << " ";
    for (int i = 0; i < vertex_set[v].edges.size(); i++)
    {
        int n = vertex_set[v].edges[i].dest;
        if (!visited[n])
            DFSUtil(n, visited);
    }
}

void Graph::DFS(int v)
{
    bool *visited = new bool[v_size];
    for (int i = 0; i < v_size; i++)
        visited[i] = false;
    DFSUtil(v, visited);
}

void Graph::printGraph()
{
    for (int i = 0; i < v_size; i++)
    {
        cout << "Vertex " << i << ": ";
        for (int j = 0; j < vertex_set[i].edges.size(); j++)
            cout << "-> " << vertex_set[i].edges[j].dest;
        cout << endl;
    }
}

#endif