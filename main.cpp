#include "include/Prim.h"
#include "include/Kruskal.h"
#include "include/Graph.h"
#include <chrono>
#include <random>

inline Graph GenerateConnectedGraph(int n, int m){
    Graph graph(n);
    std::vector<int> vertex;
    std::random_device rd;
    std::mt19937 g(rd());

    std::iota(vertex.begin(), vertex.end(), 0);
    std::shuffle(vertex.begin(), vertex.end(), g);
    
    int v;
    int u;
    for (int i = 0; i < n - 1; i++){
        std::uniform_int_distribution<> dis(0, n-1);
        v = dis(g);
        graph.AddEdge(vertex[i], vertex[v], rand()%1000);
    }

    int k = n - 1;
    while (k < m){
        std::uniform_int_distribution<> dis(0, n-1);
        v = dis(g);
        u = dis(g);
        if (v != u && !graph.IsConnected(v, u)) {
            graph.AddEdge(vertex[v], vertex[u], rand()%1000);
            k++;
        }
    }
    
    return graph;
}



int main() {
    srand(time(NULL));
    Graph graph;
    std::cin >> graph;

    std::pair<weight, std::vector<std::pair<int, int>>> PrimResult;
    std::pair<weight, std::vector<std::pair<int, int>>> KruskalResult;

    auto Prim_start = std::chrono::high_resolution_clock::now();
    
    PrimResult = PrimMst(graph);
    
    auto Prim_end = std::chrono::high_resolution_clock::now();
    auto Prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Prim_end - Prim_start);

    auto Kruskal_start = std::chrono::high_resolution_clock::now();
    
    KruskalResult = KruskalMst(graph);
    
    auto Kruskal_end = std::chrono::high_resolution_clock::now();
    auto Kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Kruskal_end - Kruskal_start);

    std::cout << Kruskal_duration.count() << " " << Prim_duration.count() << std::endl;

    std::cout << KruskalResult.first << " " << PrimResult.first << std::endl;
    
    std::cout << "Kruskal\n";

    for (int i = 0; i < graph.Size() - 1; i++){
        std::cout << KruskalResult.second[i].first << "  " << KruskalResult.second[i].second << "\n";
    }
    std::cout << "Prim\n";
    for (int i = 0; i < graph.Size() - 1; i++){
        std::cout << PrimResult.second[i].first << "  " << PrimResult.second[i].second << "\n";
    }

    return 0;
}