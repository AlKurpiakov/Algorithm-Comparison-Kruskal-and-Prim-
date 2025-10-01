#ifndef PRIM_H
#define PRIM_H
#pragma once

#include "Graph.h"
#include <limits.h>
#include <utility>
#include <vector>
#include <cstddef>
#include <limits.h>


std::pair<weight, std::vector<std::pair<int, int>>> PrimMst(const Graph& graph, int start_vertex = 0);

#endif