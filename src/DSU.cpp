#include "../include/DSU.h"

DSU::DSU(int n) : _size(n), _parent(_size), _rank(n, 0) {
    std::iota(_parent.begin(), _parent.end(), 0);
}

int DSU::Find(int x) {
    
    if (_parent[x] == x){ 
        return x;
    }

    return _parent[x] = Find(_parent[x]);
}

void DSU::UnionSet(int x, int y)
{
    int rootX = Find(x);
    int rootY = Find(y);
    if (_rank[x] < _rank[y])
        _parent[x] = y;
    else
    {
        _parent[y] = x;
        if (_rank[x] == _rank[y])
            ++_rank[x];
    }
}

bool DSU::IsConnected(int x, int y) {
    int rootX = Find(x);
    int rootY = Find(y);
    return rootX == rootY;
}