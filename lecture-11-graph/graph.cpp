#include <algorithm>
#include <cstdio>
#include <stdexcept>
#include <unordered_map>
#include <vector>

template<typename TVertex, typename TEdge>
struct link {
    const TVertex src;
    const TVertex dst;
    const TEdge edge;

    // TODO CTOR
};

template
<
    typename TVertex,
    typename TEdge,
    typename TVertexContainer = std::vector<TVertex>,
    typename TEdgeContainer = std::vector<link<TVertex, TEdge>>
>
class graph {
    TVertexContainer _vertices;
    std::unordered_map<TVertex, TEdgeContainer> _edges;

public:
    using VertexIterator = typename TVertexContainer::iterator;

    void add_vertex(const TVertex& vertex) {
        auto begin = _vertices.begin();
        auto end = _vertices.end();
        if (std::find(begin, end, vertex) != end) {
            throw std::logic_error("Vertex is already inserted!");
        }
        _vertices.insert(_vertices.end(), vertex);
    }

    VertexIterator begin() {
        return _vertices.begin();
    }

    VertexIterator end() {
        return _vertices.end();
    }
};

int main() {
    graph<int, double> g;
    g.add_vertex(5);
    g.add_vertex(4);
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);

    for (auto& v : g) {
        printf("%d\n", v);
    }
}
