#include <algorithm>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename TVertex, typename TEdge>
struct link {
    TVertex src;
    TVertex dst;
    TEdge edge;

    link(const TVertex& src, const TVertex& dst, const TEdge& edge) : src(src), dst(dst), edge(edge) { }
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
    using AdjacentLinkIterator = typename TEdgeContainer::iterator;

    void add_vertex(const TVertex& vertex) {
        auto begin = _vertices.begin();
        auto end = _vertices.end();
        if (std::find(begin, end, vertex) != end) {
            throw std::logic_error("Vertex is already inserted!");
        }
        _vertices.insert(_vertices.end(), vertex);
    }

    void add_edge(const TVertex& src, const TVertex& dst, const TEdge& edge) {
        // TODO Проверить src и dst - вершины графа
        link<TVertex, TEdge> new_link(src, dst, edge);
        auto& adjacent_edges = _edges[src];
        adjacent_edges.insert(adjacent_edges.end(), new_link);
    }

    size_t size() const {
        return _vertices.size();
    }

    VertexIterator begin() {
        return _vertices.begin();
    }

    VertexIterator end() {
        return _vertices.end();
    }

    AdjacentLinkIterator begin_adjacent_link(const TVertex& src) {
        return _edges[src].begin();
    }

    AdjacentLinkIterator end_adjacent_link(const TVertex& src) {
        return _edges[src].end();
    }
};

struct dijkstra_comparator {
    std::unordered_map<char, double>& d;
    const std::unordered_set<char>& used;

    dijkstra_comparator(std::unordered_map<char, double>& d, const std::unordered_set<char>& used)
        : d(d), used(used) { }

    bool operator()(char src, char dst) {     // src < dst

        auto end = used.end();
        auto src_used = used.find(src) != end;
        auto dst_used = used.find(dst) != end;
        if (src_used && dst_used) {
            return d[src] < d[dst];
        }
        else if (src_used) {
            return false;
        }
        else if (dst_used) {
            return true;
        }
        else {
            return d[src] < d[dst];
        }
    }
};

double dijkstra(graph<char, double>& g, char src, char dst) {
    // TODO src, dst включены в граф?

    std::unordered_map<char, double> d;
    std::unordered_set<char> used;
    std::unordered_map<char, char> p;

    const auto max =
        std::numeric_limits<double>::has_infinity
        ? std::numeric_limits<double>::infinity()
        : std::numeric_limits<double>::max();
    for (const auto& v : g) {
        if (v != src)
            d[v] = max;
        else
            d[v] = 0;
    }

    dijkstra_comparator comparator(d, used);
    const auto n = g.size();
    for (size_t i = 0; i < n; ++i) {
        // Шаг 1
        auto v = *std::min_element(g.begin(), g.end(), comparator);
        if (d[v] == max) {
            break;
        }

        // Шаг 2
        used.insert(v);

        // Шаг 3
        auto begin = g.begin_adjacent_link(v);
        auto end = g.end_adjacent_link(v);
        while (begin != end) {
            auto link = *begin;
            auto q = link.dst;
            auto w = link.edge;
            if (d[v] + w < d[q]) {
                d[q] = d[v] + w;
                p[q] = v;
            }
            ++begin;
        }
    }

    return d[dst];
}

int main() {
    graph<char, double> g;
    g.add_vertex('A');
    g.add_vertex('B');
    g.add_vertex('C');
    g.add_vertex('D');
    g.add_vertex('E');
    g.add_vertex('F');
    g.add_edge('A', 'B', 1);
    g.add_edge('B', 'C', 1);
    g.add_edge('C', 'D', 1);
    g.add_edge('D', 'E', 1);
    g.add_edge('A', 'E', 9);
    g.add_edge('A', 'F', 1);
    g.add_edge('F', 'E', 9);

    for (auto& v : g) {
        printf("%c\n", v);
        {
            auto begin = g.begin_adjacent_link(v);
            auto end = g.end_adjacent_link(v);
            while (begin != end) {
                printf("\t %c -> %c (%f)\n", begin->src, begin->dst, begin->edge);
                ++begin;
            }
        }
    }

    printf("%f", dijkstra(g, 'A', 'E'));
}
