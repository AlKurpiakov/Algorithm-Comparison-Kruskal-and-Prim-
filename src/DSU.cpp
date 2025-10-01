#include "../include/DSU.h"

DSU::DSU(int n) : _size(n), _parent(_size), _rank(n, 0) {
    std::iota(_parent.begin(), _parent.end(), 1);
}

int DSU::Find(int x) const{
    while (x != _parent[x]) {
        x = _parent[x];
    }
    return x;
}

void DSU::UnionSet(int x, int y){
    int rootX = Find(x);
    int rootY = Find(y);

    if(rootX == rootY){
        return;
    }

    if (_rank[rootX] < _rank[rootY]) {
        _parent[rootX] = rootY;
    }   
    else if (_rank[rootX] > _rank[rootY]) {
        _parent[rootY] = rootX;
    }
    else {
        _parent[rootY] = rootX;
        _rank[rootX]++;
    }
}

const bool DSU::IsConnected(int x, int y) const{
    return Find(x) == Find(y);
}