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
    
    

    return 0;
}