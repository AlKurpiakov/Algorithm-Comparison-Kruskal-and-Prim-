#include "testkit.h"

inline Graph TestKit::GenerateConnectedGraph(int n, int m, int max_weight){
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
        graph.AddEdge(vertex[i], vertex[v], rand()%max_weight);
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

/*
int TestKit::GetStep() const { 
    return _step; 
}

int TestKit::GetVertexPower() const { 
    return _power_of_vertex_set;
}

int TestKit::GetEdgesPower() const { 
    return _power_of_edges_set;
}

int TestKit::GetMinWeight() const { 
    return _min_weight;
}

int TestKit::GetMaxWeight() const { 
    return _max_weight;
}

std::vector<Graph>& TestKit::GetTestSet() { 
    return _test_set; 
}
*/

void TestKit::RunTests(const std::string& name_of_test) {

    std::pair<weight, std::vector<std::pair<int, int>>> PrimResult;
    std::pair<weight, std::vector<std::pair<int, int>>> KruskalResult; 

    for (int i = 0; i < _test_set.size(); i++){
        auto Prim_start = std::chrono::high_resolution_clock::now();

        PrimResult = PrimMst(_test_set[i]);

        auto Prim_end = std::chrono::high_resolution_clock::now();
        auto Prim_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Prim_end - Prim_start);

        auto Kruskal_start = std::chrono::high_resolution_clock::now();
    
        KruskalResult = KruskalMst(_test_set[i]);
        
        auto Kruskal_end = std::chrono::high_resolution_clock::now();
        auto Kruskal_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(Kruskal_end - Kruskal_start);
    }


}


TestKit::TestKit(int power_of_vertex_set, int power_of_edges_set, int step, int min_weight, int max_weight, int type){
    _power_of_vertex_set = power_of_vertex_set;
    _power_of_edges_set = power_of_edges_set;
    _step = step;
    _min_weight = min_weight;
    _max_weight = max_weight;
    _type = type;
    
}

inline int TestKit::CalcEgesCount(int num_of_edges){
    switch (_type)
    {
    case 0:
        return num_of_edges * num_of_edges ;
        break;

    case 1:
        return num_of_edges * num_of_edges / 10;
        break;
    
    case 2:
        return 1000 * num_of_edges;
        break;

    case 3:
        return 100 * num_of_edges;
        break;    
        
    default:
        break;
    }
    
    return 0;
}

void VertexTestKit::GenerateTests() {
    for (int i = _power_of_vertex_set; i < 10'000 + 2; i += _step ){
        _power_of_edges_set = CalcEgesCount(i);
        _test_set.push_back(this->GenerateConnectedGraph(i, _power_of_edges_set, _max_weight));
    }
}


void WeightTestKit::GenerateTests() {
    _power_of_edges_set = CalcEgesCount(10'000 + 1);
    for (int i = _min_weight; i < _max_weight; i += _step ){
        _test_set.push_back(this->GenerateConnectedGraph(_power_of_vertex_set, _power_of_edges_set, i));
    }
}


void EdgesTestKit::GenerateTests() {
    for (int i = _power_of_edges_set; i < 10'000'000 + 1; i += _step ){
        _test_set.push_back(this->GenerateConnectedGraph(_power_of_vertex_set, i, _max_weight));
    }
}
