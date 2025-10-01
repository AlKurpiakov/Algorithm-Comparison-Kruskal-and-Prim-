#include "../include/Kruskal.h"


std::pair<weight, std::vector<std::pair<int, int>>> KruskalMst(const Graph& graph){
    int n = graph.Size();
    weight total_weight = 0;
    
    std::vector<Edge> sorted_edges = graph.GetEdges();
    std::sort(sorted_edges.begin(), sorted_edges.end());

    DSU dsu(n);

    std::vector<std::pair<int, int>> mst_edges;
    for (int i = 0; i < n-1; i++){
        if (!dsu.IsConnected(sorted_edges[i]._v, sorted_edges[i]._u)){
            total_weight += sorted_edges[i]._weight;
            dsu.UnionSet(sorted_edges[i]._v,  sorted_edges[i]._u);
            mst_edges.emplace_back(sorted_edges[i]._v, sorted_edges[i]._u);
        }

    }

    if (mst_edges.size() < n - 1) {
        return {INF, {} };
    }

    return {total_weight, mst_edges}; 
}
