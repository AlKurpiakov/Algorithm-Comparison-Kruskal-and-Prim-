#ifndef GRAPH_H
#define GRAPH_H

#pragma once
#include <limits.h>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>

using weight = long long;
const long long INF = LONG_LONG_MAX;


struct Edge{
    int _v, _u;     //стартовая вершина -> конечная вершина
    weight _weight; //вес ребра
    bool operator<(Edge other);
};

class Graph{
private:

    
    int _num_of_vertex;                                            //количество вершин
    std::vector<Edge> _edges;                                         //ребра графа
    std::vector<std::vector<std::pair<int, weight>>> _adjacency_list; //список смежности
    
    
public:
    
    Graph(int n = 0);   
    const std::vector<std::pair<int, weight>> GetVertexList(int v) const;
    const int Size() const;
    const std::vector<Edge> GetEdges() const;
    void Resize(int n);
    void AddEdge(int v, int u, weight w);
    const bool IsConnected(int x, int y) const;
    
    friend std::istream& operator>>(std::istream& in, Graph& graph);  
};

#endif