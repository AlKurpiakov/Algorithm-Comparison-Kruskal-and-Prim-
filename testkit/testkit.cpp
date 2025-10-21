#include "testkit.h"

TestKit::TestKit(int power_of_vertex_set, int power_of_edges_set,
                 int step, int min_weight, int max_weight, int type)
{
    _power_of_vertex_set = power_of_vertex_set;
    _power_of_edges_set = power_of_edges_set;
    _step = step;
    _min_weight = min_weight;
    _max_weight = max_weight;
    _type = type;
}

int TestKit::CalcEgesCount(int num_of_edges) {
    switch (_type) {
    case 0:
        if (num_of_edges > 3000) num_of_edges * num_of_edges / 1000;
        return num_of_edges * num_of_edges / 10;
    case 1:
        if (num_of_edges > 3000) num_of_edges * num_of_edges / 100;
        return num_of_edges * num_of_edges;
    case 2:
        return 1000 * num_of_edges;
    case 3:
        return 100* num_of_edges;
    default:
        throw std::invalid_argument("Unknown type in CalcEgesCount");
    }
}

uint64_t GetEdgeKey(int u, int v){
    if (u > v) std::swap(u, v);
    return (static_cast<uint64_t>(static_cast<uint32_t>(u)) << 32) |
           static_cast<uint64_t>(static_cast<uint32_t>(v));
}


Graph TestKit::GenerateConnectedGraph(int n, int m, int max_weight) {

    long long max_possible_edges = static_cast<long long>(n) * (n - 1) / 2;
    if (m > max_possible_edges) m = static_cast<int>(max_possible_edges);

    Graph g(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weight_dist(1, max_weight);

    for (int i = 1; i < n; ++i) {
        std::uniform_int_distribution<int> pick(0, i - 1);
        int j = pick(gen);
        int w = weight_dist(gen);
        g.AddEdge(i, j, w);
    }

    int need = m - g.EdgeCount();
    if (need <= 0){
        return g;
    }

    std::vector<std::pair<int,int>> candidates;
    candidates.reserve(static_cast<size_t>(std::min<long long>(max_possible_edges - g.EdgeCount(), 1000000LL)));

    for (int u = 0; u < n; ++u) {
        for (int v = u + 1; v < n; ++v) {
            uint64_t k = GetEdgeKey(u, v);
            if (g.GetExistingEdgesMap().find(k) == g.GetExistingEdgesMap().end()) {
                candidates.emplace_back(u, v);
            }
        }
    }

    if (!candidates.empty()) {
        std::shuffle(candidates.begin(), candidates.end(), gen);
        int to_add = std::min(need, static_cast<int>(candidates.size()));
        for (int i = 0; i < to_add; ++i) {
            int u = candidates[i].first;
            int v = candidates[i].second;
            int w = weight_dist(gen);
            g.AddEdge(u, v, w); 
        }
    }
    
    return g;
}

void VertexTestKit::GenerateAndRunTests(const std::string& name_of_test) {
    
    std::filesystem::path out_dir = std::filesystem::current_path() / ".." / "results"; 
    std::error_code ec;
    if (!std::filesystem::exists(out_dir, ec)) {
        if (!std::filesystem::create_directories(out_dir, ec)) {
            throw std::runtime_error("Could not create results directory '" + out_dir.string()
                                     + "'. error: " + ec.message());
        }
    }

    std::filesystem::path prim_path = out_dir / (name_of_test + "_Prim.txt");
    std::filesystem::path kruskal_path = out_dir / (name_of_test + "_Kruskal.txt");
    
    std::ofstream prim_file(prim_path, std::ios::trunc);
    std::ofstream kruskal_file(kruskal_path, std::ios::trunc);
    prim_file << "n m duration_ms O(f(n))/T(n)\n";
    kruskal_file << "n m duration_ms O(f(n))/T(n)\n";
    
    if (!prim_file.is_open()) {
        std::cerr << "Failed to open Prim file: " << prim_path << std::endl;
    }
    if (!kruskal_file.is_open()) {
        std::cerr << "Failed to open Kruskal file: " << kruskal_path << std::endl;
    }

    for (int i = _power_of_vertex_set; i <= 10'000 + 1; i += _step) {
        _power_of_edges_set = CalcEgesCount(i);
        Graph g = GenerateConnectedGraph(i, _power_of_edges_set, _max_weight);
        
        auto prim_start = std::chrono::high_resolution_clock::now();
        auto prim_result = PrimMst(g);
        auto prim_end = std::chrono::high_resolution_clock::now();
        auto prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(prim_end - prim_start);

        auto kruskal_start = std::chrono::high_resolution_clock::now();
        auto kruskal_result = KruskalMst(g);
        auto kruskal_end = std::chrono::high_resolution_clock::now();
        auto kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kruskal_end - kruskal_start);  



        int size = g.Size();
        int edges = g.EdgeCount();
        std::cout << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";

        prim_file << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";
        kruskal_file << size << " " << edges << " " << kruskal_duration.count() << " " << double((edges * log2(edges * size)) / (double)kruskal_duration.count()) << "\n";

    }
    
    prim_file.close();
    kruskal_file.close();

}

void WeightTestKit::GenerateAndRunTests(const std::string& name_of_test) {
    std::filesystem::path out_dir = std::filesystem::current_path() / ".." / "results"; 
    std::error_code ec;
    if (!std::filesystem::exists(out_dir, ec)) {
        if (!std::filesystem::create_directories(out_dir, ec)) {
            throw std::runtime_error("Could not create results directory '" + out_dir.string()
                                     + "'. error: " + ec.message());
        }
    }

    std::filesystem::path prim_path = out_dir / (name_of_test + "_Prim.txt");
    std::filesystem::path kruskal_path = out_dir / (name_of_test + "_Kruskal.txt");
    
    std::ofstream prim_file(prim_path, std::ios::trunc);
    std::ofstream kruskal_file(kruskal_path, std::ios::trunc);
    prim_file << "n m duration_ms\n";
    kruskal_file << "n m duration_ms\n";
    
    if (!prim_file.is_open()) {
        std::cerr << "Failed to open Prim file: " << prim_path << std::endl;
    }
    if (!kruskal_file.is_open()) {
        std::cerr << "Failed to open Kruskal file: " << kruskal_path << std::endl;
    }

    _power_of_edges_set = CalcEgesCount(10000 + 1);
    for (int w = _min_weight; w <= _max_weight; w += _step) {
        Graph g = GenerateConnectedGraph(_power_of_vertex_set, _power_of_edges_set, w);
        
        auto prim_start = std::chrono::high_resolution_clock::now();
        auto prim_result = PrimMst(g);
        auto prim_end = std::chrono::high_resolution_clock::now();
        auto prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(prim_end - prim_start);

        auto kruskal_start = std::chrono::high_resolution_clock::now();
        auto kruskal_result = KruskalMst(g);
        auto kruskal_end = std::chrono::high_resolution_clock::now();
        auto kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kruskal_end - kruskal_start);  


        int size = g.Size();
        int edges = g.EdgeCount();
        std::cout << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";

        prim_file << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";
        kruskal_file << size << " " << edges << " " << kruskal_duration.count() << " " << double((edges * log2(edges * size)) / (double)kruskal_duration.count()) << "\n";
    }

    prim_file.close();
    kruskal_file.close();
}

void EdgesTestKit::GenerateAndRunTests(const std::string& name_of_test) {

    std::filesystem::path out_dir = std::filesystem::current_path() / ".." / "results"; 
    std::error_code ec;
    if (!std::filesystem::exists(out_dir, ec)) {
        if (!std::filesystem::create_directories(out_dir, ec)) {
            throw std::runtime_error("Could not create results directory '" + out_dir.string()
                                     + "'. error: " + ec.message());
        }
    }

    std::filesystem::path prim_path = out_dir / (name_of_test + "_Prim.txt");
    std::filesystem::path kruskal_path = out_dir / (name_of_test + "_Kruskal.txt");
    
    std::ofstream prim_file(prim_path, std::ios::trunc);
    std::ofstream kruskal_file(kruskal_path, std::ios::trunc);
    prim_file << "n m duration_ms\n";
    kruskal_file << "n m duration_ms\n";
    
    if (!prim_file.is_open()) {
        std::cerr << "Failed to open Prim file: " << prim_path << std::endl;
    }
    if (!kruskal_file.is_open()) {
        std::cerr << "Failed to open Kruskal file: " << kruskal_path << std::endl;
    }

    for (int e = _power_of_edges_set; e <= 10000000; e += _step) {
        Graph g = GenerateConnectedGraph(_power_of_vertex_set, e, _max_weight);
        
        auto prim_start = std::chrono::high_resolution_clock::now();
        auto prim_result = PrimMst(g);
        auto prim_end = std::chrono::high_resolution_clock::now();
        auto prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(prim_end - prim_start);

        auto kruskal_start = std::chrono::high_resolution_clock::now();
        auto kruskal_result = KruskalMst(g);
        auto kruskal_end = std::chrono::high_resolution_clock::now();
        auto kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kruskal_end - kruskal_start);  


        int size = g.Size();
        int edges = g.EdgeCount();
        std::cout << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";

        prim_file << size << " " << edges << " " << prim_duration.count() << " " << double(size*size) / (double)prim_duration.count() << "\n";
        kruskal_file << size << " " << edges << " " << kruskal_duration.count() << " " << double((edges * log2(edges * size)) / (double)kruskal_duration.count()) << "\n";

    }

    prim_file.close();
    kruskal_file.close();
}

void TestKitFactory::GenerateAndRunTests(TestType test_of, int power_of_vertex_set,
                                      int power_of_edges_set, int step, int min_weight,
                                      int max_weight, int type)
{
    switch (test_of) {
    case TestType::VERTEX: {
        VertexTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateAndRunTests(std::string("VertexTest_") + std::to_string(type));
        break;
    }
    case TestType::EDGES: {
        EdgesTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateAndRunTests(std::string("EdgesTest_") + std::to_string(type));
        break;
    }
    case TestType::WEIGHT: {
        WeightTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateAndRunTests(std::string("WeightTest_") + std::to_string(type));
        break;
    }
    default:
        throw std::invalid_argument("Unknown test type");
    }
}