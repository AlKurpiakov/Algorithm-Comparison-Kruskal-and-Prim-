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

    if (rootX == rootY) return;

    if (_rank[rootX] < _rank[rootY]) {
        _parent[rootX] = rootY;
    } else if (_rank[rootX] > _rank[rootY]) {
        _parent[rootY] = rootX;
    } else {
        _parent[rootY] = rootX;
        _rank[rootX]++;
    }

}

bool DSU::IsConnected(int x, int y) {
    return Find(y) == Find(x);
}