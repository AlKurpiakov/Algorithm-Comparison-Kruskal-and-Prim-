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
        return num_of_edges * num_of_edges / 10;
    case 1:
        return num_of_edges * num_of_edges;
    case 2:
        return 100 * num_of_edges;
    case 3:
        return 1000 * num_of_edges;
    default:
        throw std::invalid_argument("Unknown type in CalcEgesCount");
    }
}

Graph TestKit::GenerateConnectedGraph(int n, int m, int max_weight) {
    Graph graph(n);

    std::vector<int> vertices(n);
    std::iota(vertices.begin(), vertices.end(), 0);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(vertices.begin(), vertices.end(), gen);

    std::uniform_int_distribution<int> weightDist(1, max_weight);

    std::unordered_set<uint64_t> existing;
    existing.reserve(m * 2);

    auto getKey = [](int a, int b) -> uint64_t {
        if (a > b) std::swap(a, b);
        return (static_cast<uint64_t>(a) << 32) | b;
    };
    
    auto addEdgeSafe = [&](int a, int b, int w) -> bool {
        if (a == b) return false;
        uint64_t key = getKey(a, b);
        if (existing.count(key)) return false;
        
        graph.AddEdge(a, b, w);
        existing.insert(key);
        return true;
    };

    for (int i = 1; i < n; ++i) {
        std::uniform_int_distribution<int> pick(0, i - 1);
        int j = pick(gen);
        addEdgeSafe(vertices[i], vertices[j], weightDist(gen));
    }

    int edges_needed = m - (n - 1);
    if (edges_needed <= 0) return graph;
    
    if (n < 10000) {

        std::vector<std::pair<int, int>> possible_edges;
        possible_edges.reserve(n * (n - 1) / 2);
        
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                possible_edges.emplace_back(i, j);
            }
        }
        
        auto it = std::remove_if(possible_edges.begin(), possible_edges.end(),
            [&](const std::pair<int, int>& edge) {
                return existing.count(getKey(edge.first, edge.second));
            });

        possible_edges.erase(it, possible_edges.end());
        
        std::shuffle(possible_edges.begin(), possible_edges.end(), gen);
        
        for (int i = 0; i < edges_needed && i < possible_edges.size(); ++i) {
            const auto& edge = possible_edges[i];
            graph.AddEdge(edge.first, edge.second, weightDist(gen));
        }


    } else {

        std::uniform_int_distribution<int> pick(0, n - 1);
        
        for (int attempts = 0; edges_needed > 0 && attempts < edges_needed * 10; ++attempts) {
            int a = pick(gen);
            int b = pick(gen);
            
            if (addEdgeSafe(a, b, weightDist(gen))) {
                edges_needed--;
            }
        }
    }


    return graph;
}

void TestKit::RunTests(const std::string& name_of_test) {
    std::string prim_output_file = "../results"+ name_of_test + "_Prim.txt";
    std::string kruskal_output_file = "../results"+ name_of_test + "_Kruskal.txt";

    std::ofstream prim_file(prim_output_file);
    std::ofstream kruskal_file(kruskal_output_file);

    if (!prim_file.is_open() || !kruskal_file.is_open()) {
        throw std::runtime_error("Could not open output files for writing results");
    }

    for (size_t i = 0; i < _test_set.size(); ++i) {
        const Graph& g = _test_set[i];

        auto prim_start = std::chrono::high_resolution_clock::now();
        auto prim_result = PrimMst(g);
        auto prim_end = std::chrono::high_resolution_clock::now();
        auto prim_duration = std::chrono::duration_cast<std::chrono::milliseconds>(prim_end - prim_start);

        auto kruskal_start = std::chrono::high_resolution_clock::now();
        auto kruskal_result = KruskalMst(g);
        auto kruskal_end = std::chrono::high_resolution_clock::now();
        auto kruskal_duration = std::chrono::duration_cast<std::chrono::milliseconds>(kruskal_end - kruskal_start);
        
        for(int j = 0; j < g.Size() - 1; j++){
            for (int k = 0; k < g.Size() - 1; k++){
                if (kruskal_result.second[i].first == prim_result.second[k].second && kruskal_result.second[i].second == prim_result.second[k].first || kruskal_result.second[i].second == prim_result.second[k].second && kruskal_result.second[i].first == prim_result.second[k].first  ){
                    std::cout << j << std::endl;
                    break;
                }
            } 
            
        }
        std::cout << "_____________" <<'\n';

        prim_file << prim_duration.count() << "\n";
        kruskal_file << kruskal_duration.count() << "\n";
    }
}

void VertexTestKit::GenerateTests() {
    for (int i = _power_of_vertex_set; i <= 100 + 1; i += _step) {
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
        test.RunTests(std::string("VertexTest_") + std::to_string(type));
        break;
    }
    case TestType::EDGES: {
        EdgesTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateTests();
        test.RunTests(std::string("EdgesTest_") + std::to_string(type));
        break;
    }
    case TestType::WEIGHT: {
        WeightTestKit test(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type);
        test.GenerateTests();
        test.RunTests(std::string("WeightTest_") + std::to_string(type));
        break;
    }
    default:
        throw std::invalid_argument("Unknown test type");
    }
}