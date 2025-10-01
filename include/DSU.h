#ifndef DSU_H
#define DSU_H
#include <vector>
#include <numeric>

#pragma once


class DSU{
private:
    size_t _size;
    std::vector<int> _parent;
    std::vector<int> _rank;

public:
    DSU(int size);
    int Find(int x) const;
    void UnionSet(int x, int y);
    const bool IsConnected(int x, int y) const;
};


#endif