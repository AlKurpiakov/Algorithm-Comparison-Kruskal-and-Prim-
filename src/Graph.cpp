#include "../include/Graph.h"

bool Edge::operator<(Edge other){
    return _weight < other._weight;
}

Graph::Graph(int n) : _num_of_vertex(n){
    _adjacency_list.assign(_num_of_vertex, {});
}
    
void Graph::AddEdge(int v, int u, weight w){
    _edges.push_back({v, u, w});
    _adjacency_list[v].push_back({u,w});
    _adjacency_list[u].push_back({v,w});
}

const int Graph::Size() const{
    return _num_of_vertex;
}

void Graph::Resize(int n) {
    _num_of_vertex = n;
    _adjacency_list.assign(_num_of_vertex, {});
}

const std::vector<std::pair<int, weight>> Graph::GetVertexList(int v) const {
    return _adjacency_list[v];
}

const std::vector<Edge> Graph::GetEdges() const{
    return _edges;
}

const bool Graph::IsConnected(int x, int y) const {
    for (int i = 0; i < _adjacency_list[x].size(); i++){
        if (_adjacency_list[x][i].first == y) {
            return true;
        }
    }

    return false;
}
    

std::istream& operator>>(std::istream& in, Graph& graph){
    int n, m;
    in >> n >> m;
    graph.Resize(n);

    int v, u;
    weight w;

    for (int i = 0; i < m; i++){
        in >> v >> u >> w;
        graph.AddEdge(v, u, w);
    }
    return in;
}