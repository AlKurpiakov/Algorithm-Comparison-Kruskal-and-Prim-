#ifndef GRAPH_H
#define GRAPH_H

#include <cstdint>
#pragma once
#include <limits.h>
#include <cstddef>
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>

using weight = long long;
const long long INF = 100000000;


struct Edge{
    int _v, _u;     //стартовая вершина -> конечная вершина
    weight _weight; //вес ребра
    Edge(int v, int u, weight w);
    const bool operator<(Edge other) const;
    const bool operator==(Edge other) const;
    const uint64_t GetEdgeKey() const; 
};

class Graph{
private:

    
    int _num_of_vertex;                                               //количество вершин
    std::vector<Edge> _edges;                                         //ребра графа
    std::vector<std::vector<std::pair<int, weight>>> _adjacency_list; //список смежности
    std::unordered_set<uint64_t> _existing_edges;                     //вспомогательная структура для добавления ребер и генерации графов
    
public:
    
    Graph(int n = 0);   
    const std::vector<std::pair<int, weight>> GetVertexList(int v) const;
    const int Size() const;
    const int EdgeCount() const;
    const std::vector<Edge> GetEdges() const;
    void Resize(int n);
    void AddEdge(int v, int u, weight w);
    const bool IsConnected(int x, int y) const;
    const std::unordered_set<uint64_t>& GetExistingEdgesMap() const;
    friend std::istream& operator>>(std::istream& in, Graph& graph);  
    friend std::ostream& operator<<(std::ostream& os, Graph& graph);  

};

#endif