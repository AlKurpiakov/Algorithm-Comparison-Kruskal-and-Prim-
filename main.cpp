#include "testkit/testkit.h"
#include <filesystem>

int main() {
    
    std::cout << "Current path: " << std::filesystem::current_path() << std::endl;

    TestKitFactory vertex_test_3_1_ab;
    // vertex_test_3_1_ab.GenerateAndRunTests(TestKitFactory::TestType::VERTEX, 2, 0, 100, 1, 1000000, 0);
    // vertex_test_3_1_ab.GenerateAndRunTests(TestKitFactory::TestType::VERTEX, 2, 0, 100, 1, 1000000, 1);

    // TestKitFactory vertex_test_3_2_ab;
    // vertex_test_3_2_ab.GenerateAndRunTests(TestKitFactory::TestType::VERTEX, 101, 0, 100, 1, 1000000, 2);
    // vertex_test_3_2_ab.GenerateAndRunTests(TestKitFactory::TestType::VERTEX, 101, 0, 100, 1, 1000000, 3);

    // TestKitFactory edges_test_3_3;
    // edges_test_3_3.GenerateAndRunTests(TestKitFactory::TestType::EDGES, 10001, 100000, 100000, 1, 1000000, 0);

    TestKitFactory weight_test_3_4_ab;
    // weight_test_3_4_ab.GenerateAndRunTests(TestKitFactory::TestType::WEIGHT, 10001, 0, 1, 2, 200, 0);
    weight_test_3_4_ab.GenerateAndRunTests(TestKitFactory::TestType::WEIGHT, 10001, 0, 1, 2, 200, 3);


    
    
    // Graph graph;
    // std::cin >> graph;

    // std::pair<weight, std::vector<std::pair<int, int>>> PrimResult;
    // std::pair<weight, std::vector<std::pair<int, int>>> KruskalResult;

    // auto Prim_start = std::chrono::high_resolution_clock::now();
    
    // PrimResult = PrimMst(graph);
    
    // auto Prim_end = std::chrono::high_resolution_clock::now();
    // auto Prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Prim_end - Prim_start);

    // auto Kruskal_start = std::chrono::high_resolution_clock::now();
    
    // KruskalResult = KruskalMst(graph);
    
    // auto Kruskal_end = std::chrono::high_resolution_clock::now();
    // auto Kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Kruskal_end - Kruskal_start);

    // std::cout << Kruskal_duration.count() << " " << Prim_duration.count() << std::endl;

    // std::cout << KruskalResult.first << " " << PrimResult.first << std::endl;
    
    // std::cout << "Kruskal\n";

    // for (int i = 0; i < graph.Size() - 1; i++){
    //     std::cout << KruskalResult.second[i].first << "  " << KruskalResult.second[i].second << "\n";
    // }
    // std::cout << "Prim\n";
    // for (int i = 0; i < graph.Size() - 1; i++){
    //     std::cout << PrimResult.second[i].first << "  " << PrimResult.second[i].second << "\n";
    // }
    return 0;
}