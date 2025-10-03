#ifndef TESTKIT_FIXED_H
#define TESTKIT_FIXED_H

#include "../include/Graph.h"
#include "../include/Kruskal.h"
#include "../include/Prim.h"    
#include <chrono>
#include <random>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>
#include <stdexcept>
#include <filesystem>
#include <string>
#include <iostream>

class TestKit 
{
public:
    int _step;
    int _power_of_vertex_set;
    int _power_of_edges_set;
    int _min_weight;
    int _max_weight;
    int _type;

    std::vector<Graph> _test_set;

    Graph GenerateConnectedGraph(int n, int m, int max_weight);

    TestKit(int power_of_vertex_set, int power_of_edges_set,
            int step, int min_weight, int max_weight, int type);

    virtual void GenerateTests() = 0;
    void RunTests(const std::string& name_of_test);
    int CalcEgesCount(int num_of_edges);

    virtual ~TestKit() = default;
};


class VertexTestKit : public TestKit 
{
public:
    VertexTestKit(int power_of_vertex_set, int power_of_edges_set,
                  int step, int min_weight, int max_weight, int type)
        : TestKit(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type) {}

    void GenerateTests() override;
};


class EdgesTestKit : public TestKit 
{
public:
    EdgesTestKit(int power_of_vertex_set, int power_of_edges_set,
                 int step, int min_weight, int max_weight, int type)
        : TestKit(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type) {}

    void GenerateTests() override;
};

class WeightTestKit : public TestKit 
{
public:
    WeightTestKit(int power_of_vertex_set, int power_of_edges_set,
                  int step, int min_weight, int max_weight, int type)
        : TestKit(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type) {}

    void GenerateTests() override;
};


class TestKitFactory {
public:
    enum class TestType {
        VERTEX,
        EDGES,
        WEIGHT
    };

    void CreateAndRunTest(TestType test_of, int power_of_vertex_set,
                          int power_of_edges_set, int step, int min_weight,
                          int max_weight, int type);
};


#endif
