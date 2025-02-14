#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Function to check if it's possible to place N stores with at least 'minDist' distance
bool canPlaceStores(const vector<pair<int, int>>& intervals, int N, int minDist) {
    int count = 0;
    int lastPlaced = -1; // Position of the last placed store

    for (const auto& interval : intervals) {
        int start = max(interval.first, lastPlaced + minDist); // Start placing from the next valid point
        while (start <= interval.second) {
            count++;
            lastPlaced = start; // Update the last placed position
            start += minDist; // Move to the next possible position
            if (count >= N) return true; // Early exit if all stores are placed
        }
    }
    return count >= N; // Check if we managed to place all stores
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<pair<int, int>> intervals(M);
    for (int i = 0; i < M; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    // Sort intervals by their starting point for easier placement
    sort(intervals.begin(), intervals.end());

    // Binary search for the maximum minimum distance
    int left = 1, right = 1e9, result = 0;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (canPlaceStores(intervals, N, mid)) {
            result = mid; // Update result and search for a larger distance
            left = mid + 1;
        } else {
            right = mid - 1; // Search for a smaller distance
        }
    }

    cout << result << endl; // Output the maximum minimum distance
    return 0;
}
