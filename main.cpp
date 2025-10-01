#include "include/Prim.h"
#include "include/Kruskal.h"
#include "include/Graph.h"
#include <chrono>

int main() {
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