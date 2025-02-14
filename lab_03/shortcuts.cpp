#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Edge {
    int v, w;
};

struct State {
    int city, k, time;
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

bool canReach(int N, const vector<vector<Edge>>& adj, int s, int t, int B, int maxK) {
    vector<vector<int>> dist(N + 1, vector<int>(maxK + 1, INT_MAX));
    priority_queue<State, vector<State>, greater<State>> pq;

    pq.push({s, 0, 0});
    dist[s][0] = 0;

    while (!pq.empty()) {
        State curr = pq.top();
        pq.pop();

        if (curr.city == t && curr.time <= B) {
            return true;
        }

        if (curr.time > dist[curr.city][curr.k]) continue;

        for (const Edge& e : adj[curr.city]) {
            // Option 1: Do not speed up this road
            if (curr.time + e.w < dist[e.v][curr.k]) {
                dist[e.v][curr.k] = curr.time + e.w;
                pq.push({e.v, curr.k, curr.time + e.w});
            }

            // Option 2: Speed up this road (if we haven't exceeded maxK)
            if (curr.k < maxK && curr.time < dist[e.v][curr.k + 1]) {
                dist[e.v][curr.k + 1] = curr.time;
                pq.push({e.v, curr.k + 1, curr.time});
            }
        }
    }

    return false;
}

int main() {
    int N, M, s, t, B;
    cin >> N >> M >> s >> t >> B;

    vector<vector<Edge>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
    }

    // Binary search for the minimum number of roads to speed up
    int left = 0, right = M, result = -1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (canReach(N, adj, s, t, B, mid)) {
            result = mid;
            right = mid - 1; // Try to find a smaller k
        } else {
            left = mid + 1; // Need to speed up more roads
        }
    }

    cout << result << endl;

    return 0;
}