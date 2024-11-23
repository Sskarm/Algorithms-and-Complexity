#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

// Edge class to represent a graph edge
class Edge {
public:
    int u, v; // Vertices
    int profit, weight; // Profit and weight of the edge

    Edge(int u, int v, int profit, int weight)
        : u(u), v(v), profit(profit), weight(weight) {}
};

// Union-Find class for managing connected components
class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 0);
        iota(parent.begin(), parent.end(), 0); // Initialize parents to self
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    bool unite(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);

        if (rootU == rootV) return false;

        if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
        return true;
    }
};

// Graph class to represent the graph and perform computations
class Graph {
private:
    int numVertices;
    vector<Edge> edges;

    // Helper function to check if a spanning tree exists for a given ratio
    bool canFormSpanningTree(double ratio, int& totalProfit, int& totalWeight) {
        // Calculate modified weights
        vector<pair<double, int>> modifiedEdges;
        for (int i = 0; i < edges.size(); ++i) {
            double modifiedWeight = edges[i].profit - ratio * edges[i].weight;
            modifiedEdges.emplace_back(modifiedWeight, i);
        }

        // Sort edges by modified weight in descending order
        sort(modifiedEdges.rbegin(), modifiedEdges.rend());

        UnionFind uf(numVertices);
        totalProfit = 0;
        totalWeight = 0;
        int edgeCount = 0;

        for (const auto& [_, idx] : modifiedEdges) {
            if (edgeCount == numVertices - 1) break;
            const Edge& edge = edges[idx];
            if (uf.unite(edge.u, edge.v)) {
                totalProfit += edge.profit;
                totalWeight += edge.weight;
                edgeCount++;
            }
        }

        // Return true if we formed a spanning tree
        return edgeCount == numVertices - 1;
    }

public:
    Graph(int numVertices) : numVertices(numVertices) {}

    void addEdge(int u, int v, int profit, int weight) {
        edges.emplace_back(u, v, profit, weight);
    }

    pair<int, int> findOptimalSpanningTree() {
        double left = 0.0, right = 1e6; // Large bounds for ratio
        int bestProfit = 0, bestWeight = 1;

        // Perform binary search for the maximum ratio
        for (int iter = 0; iter < 100; ++iter) { // Precision-based search
            double mid = (left + right) / 2.0;
            int totalProfit = 0, totalWeight = 0;

            if (canFormSpanningTree(mid, totalProfit, totalWeight)) {
                bestProfit = totalProfit;
                bestWeight = totalWeight;
                left = mid; // Try for a larger ratio
            } else {
                right = mid; // Try for a smaller ratio
            }
        }

        // Reduce the ratio to its simplest form
        int gcdValue = gcd(bestProfit, bestWeight);
        return {bestProfit / gcdValue, bestWeight / gcdValue};
    }
};

// Main function
int main() {
    int N, M;
    cin >> N >> M;

    Graph graph(N);

    for (int i = 0; i < M; ++i) {
        int u, v, p, w;
        cin >> u >> v >> p >> w;
        graph.addEdge(u, v, p, w);
    }

    auto [reducedProfit, reducedWeight] = graph.findOptimalSpanningTree();
    cout << reducedProfit << " " << reducedWeight << endl;

    return 0;
}
