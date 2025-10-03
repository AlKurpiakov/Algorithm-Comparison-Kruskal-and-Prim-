#ifndef TESTKIT_H
#define TESTKIT_H
#pragma once
#include "../include/Graph.h"
#include "../include/Kruskal.h"
#include "../include/Prim.h"
#include <chrono>
#include <random>
#include <fstream>

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
    inline Graph GenerateConnectedGraph(int n, int m, int max_weight);
    
    
    
    TestKit(int power_of_vertex_set, int power_of_edges_set,
            int step, int min_weight, int max_weight, int type);

    virtual void GenerateTests() = 0;
    void RunTests(const std::string& name_of_test);
    inline int CalcEgesCount(int num_of_edges);

    // int GetStep() const;
    // int GetVertexPower() const;
    // int GetEdgesPower() const;
    // int GetMinWeight() const;
    // int GetMaxWeight() const;
    // std::vector<Graph>& GetTestSet();

    virtual ~TestKit() = default;
};


class VertexTestKit : public TestKit 
{
public:
    VertexTestKit(int power_of_vertex_set, int power_of_edges_set,
                int step, int min_weight, int max_weight, int type)
    : TestKit(power_of_vertex_set, power_of_edges_set, step, min_weight, max_weight, type) {};

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

    void СreateAndRunTest(TestType test_of, int power_of_vertex_set,
                          int power_of_edges_set, int step, int min_weight,
                          int max_weight, int type);
};


#endif
