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
        return 100 * num_of_edges;
    case 3:
        return 1000 * num_of_edges;
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


void TestKit::RunTests(const std::string& name_of_test) {

    std::filesystem::path out_dir = std::filesystem::current_path() / ".." / "tests"; 
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

    for (size_t i = 0; i < _test_set.size(); ++i) {
        const Graph& g = _test_set[i];

        auto prim_start = std::chrono::high_resolution_clock::now();
        auto prim_result = PrimMst(g);
        auto prim_end = std::chrono::high_resolution_clock::now();
        auto prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(prim_end - prim_start);

        auto kruskal_start = std::chrono::high_resolution_clock::now();
        auto kruskal_result = KruskalMst(g);
        auto kruskal_end = std::chrono::high_resolution_clock::now();
        auto kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(kruskal_end - kruskal_start);

        prim_file << g.Size() << " " << g.EdgeCount() << " " << prim_duration.count() << ' ' << g.Size() << "\n";

<<<<<<< HEAD
        kruskal_file << g.Size() << " " << g.EdgeCount() << " " << kruskal_duration.count() << "\n";
=======
        
>>>>>>> 58292d5d1422aec69c253b8f4e50823161920268


    }

    prim_file.close();
    kruskal_file.close();
}

void TestKit::OutGraphs(const std::string& name_of_test) const{
    std::filesystem::path out_dir = std::filesystem::current_path() / ".." / "tests"; 
    std::error_code ec;
    if (!std::filesystem::exists(out_dir, ec)) {
        if (!std::filesystem::create_directories(out_dir, ec)) {
            throw std::runtime_error("Could not create results directory '" + out_dir.string()
                                     + "'. error: " + ec.message());
        }
    }

    std::filesystem::path test_path = out_dir / (name_of_test + ".txt");
    
    std::ofstream test_file(test_path, std::ios::trunc);

    for (Graph it : _test_set){
        std::cout << it;
        test_file << it;
    }
}


void VertexTestKit::GenerateTests() {
<<<<<<< HEAD
    for (int i = _power_of_vertex_set; i <= 10'000 + 1; i += _step) {
=======
    for (int i = _power_of_vertex_set; i <= 30'00 + 1; i += _step) {
>>>>>>> 58292d5d1422aec69c253b8f4e50823161920268
        _power_of_edges_set = CalcEgesCount(i);
        _test_set.push_back(this->GenerateConnectedGraph(i, _power_of_edges_set, _max_weight));
    }
}

void WeightTestKit::GenerateTests() {
    _power_of_edges_set = CalcEgesCount(10000 + 1);
    for (int w = _min_weight; w <= _max_weight; w += _step) {
        _test_set.push_back(this->GenerateConnectedGraph(_power_of_vertex_set, _power_of_edges_set, w));
    }
}

void EdgesTestKit::GenerateTests() {
    for (int e = _power_of_edges_set; e <= 10000000; e += _step) {
        _test_set.push_back(this->GenerateConnectedGraph(_power_of_vertex_set, e, _max_weight));
    }
}

void TestKitFactory::CreateAndRunTest(TestType test_of, int power_of_vertex_set,
                                      int power_of_edges_set, int step, int min_weight,
                                      int max_weight, int type)
{
    switch (test_of) {
    case TestType::VERTEX: {
        VertexTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateTests();
        test.OutGraphs(std::string("VertexTest_") + std::to_string(type));
        break;
    }
    case TestType::EDGES: {
        EdgesTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateTests();
        test.OutGraphs(std::string("EdgesTest_") + std::to_string(type));
        break;
    }
    case TestType::WEIGHT: {
        WeightTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateTests();
        test.OutGraphs(std::string("WeightTest_") + std::to_string(type));
        break;
    }
    default:
        throw std::invalid_argument("Unknown test type");
    }
}