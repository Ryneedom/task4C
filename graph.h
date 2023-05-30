#ifndef GRAPH_H
#define GRAPH_H

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

using edge = pair<int,int>;

class Graph
{
private:
    vector<pair<int, edge>> G;
    vector<pair<int, edge>> T;
    int *parent;
    int V;
public:
    Graph();
    Graph(int V);
    vector<pair<int, edge>> getG();
    vector<pair<int, edge>> getT();
    void AddWeightedEdge(int u, int v, int w);
    int find_set(int i);
    void union_set(int u, int v);
    void kruskal();
    void print();
};

#endif // GRAPH_H
