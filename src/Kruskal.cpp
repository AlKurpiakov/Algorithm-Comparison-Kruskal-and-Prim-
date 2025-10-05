#include "../include/Kruskal.h"


std::pair<weight, std::vector<std::pair<int, int>>> KruskalMst(const Graph& graph){
    int n = graph.Size();
    weight total_weight = 0;
    
    std::vector<Edge> sorted_edges = graph.GetEdges();
    std::sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(n);

    std::vector<std::pair<int, int>> mst_edges;
    for (const Edge& edge : sorted_edges) {
        if (mst_edges.size() == n - 1) break;
        
        if (!dsu.IsConnected(edge._v, edge._u)) {
            total_weight += edge._weight;
            dsu.UnionSet(edge._v, edge._u);
            mst_edges.emplace_back(edge._v, edge._u);
        }
    }

    if (mst_edges.size() < n - 1) {
        return {INF, {} };
    }

    return {total_weight, mst_edges}; 
}
