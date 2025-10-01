#include "../include/Prim.h"


std::pair<weight, std::vector<std::pair<int, int>>> PrimMst(const Graph& graph, int start_vertex) {
    int n = graph.Size();
    weight total_weight;
    std::vector<int> result(n,-1);
    std::vector<bool> used(n, false);
    std::vector<weight> min_edge(n, INF);
    min_edge[start_vertex] = 0;

    int v;
    int to;
    weight w;
    for (int i = 0; i < n; i++){
        v = -1;
        for (int j = 0; j < n; j++){
            if (!used[j] && (v == -1 || min_edge[j] < min_edge[v])){
                v = j;
            }
        }

        if (min_edge[v] == INF){
            return { INF, {} };
        } 

        used[v] = true;
        total_weight += min_edge[v];

        for (std::pair<int, long long> edge : graph.GetVertexList(v)){
            to = edge.first;
            w = edge.second;
            if (!used[to] && min_edge[to] > w){
                min_edge[to] = w;
                result[to] = v;
            }
        }      
    }
    
    std::vector<std::pair<int, int>> mst_edges;
    for (int i = 0; i < n; i++){
        if (result[i] != -1) {
            mst_edges.emplace_back(result[i], i);
        }
    }

    return  {total_weight, mst_edges};
}
