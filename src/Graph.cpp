#include "../include/Graph.h"

const bool Edge::operator<(Edge other) const {
    return _weight < other._weight;
}

const bool Edge::operator==(Edge other) const {
    return _u == other._u && _v == other._v;
}


Edge::Edge(int v, int u, weight w){
    if (v > u) {
        _v = u;
        _u = v;
    }
    else {
        _v = v;
        _u = u;
    }
    _weight = w;
}

const uint64_t Edge::GetEdgeKey() const{
    return (static_cast<uint64_t>(static_cast<uint32_t>(_v)) << 32) |
           static_cast<uint64_t>(static_cast<uint32_t>(_u));
}

Graph::Graph(int n) : _num_of_vertex(n){
    _adjacency_list.assign(_num_of_vertex, {});
}
    
void Graph::AddEdge(int v, int u, weight w){
    // _edges.push_back({v, u, w});
    // _adjacency_list[v].push_back({u,w});
    // _adjacency_list[u].push_back({v,w});

    if (v == u) return; 
    Edge edge(v, u, w); 
    uint64_t key = edge.GetEdgeKey();
    if (!_existing_edges.insert(key).second) return; // уже существует
    _edges.emplace_back(edge);
    _adjacency_list[edge._v].emplace_back(edge._u, w);
    _adjacency_list[edge._u].emplace_back(edge._v, w);
}

const int Graph::Size() const{
    return _num_of_vertex;
}

const int Graph::EdgeCount() const{
    return _edges.size();
}

const std::unordered_set<uint64_t>& Graph::GetExistingEdgesMap() const{
    return _existing_edges;
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

std::ostream& operator<<(std::ostream& os, Graph& graph){
    os << graph.Size() << ' ' << graph.EdgeCount() << "\n";
    std::vector<Edge> edges = graph.GetEdges();
    for (Edge e : edges){
        os << e._v  << ' ' << e._u << ' ' << e._weight << '\n';
    }
    os << '\n';
    return os;
}
