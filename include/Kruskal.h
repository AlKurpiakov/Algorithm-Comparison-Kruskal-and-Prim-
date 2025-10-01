#ifndef KRUSKAL_H
#define KRUSKAL_H
#pragma once
#include "Graph.h"
#include "DSU.h"
#include <algorithm>


std::pair<weight, std::vector<std::pair<int, int>>> KruskalMst(const Graph& graph);

#endif