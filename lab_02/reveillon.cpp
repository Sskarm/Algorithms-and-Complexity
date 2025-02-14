#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    // Input
    int N, K;
    cin >> N >> K;
    vector<int> h(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> h[i];
    }

    // DP table
    vector<long long> dp(N + 1, 0);

    // Fill DP table
    for (int i = 1; i <= N; ++i) {
        long long current_max = 0;
        dp[i] = LLONG_MIN;
        for (int k = 1; k <= min(K, i); ++k) {
            current_max = max(current_max, (long long)h[i - k + 1]); // Maximum in the last k elements
            dp[i] = max(dp[i], dp[i - k] + current_max * k);        // Update dp[i]
        }
    }

    // Output the result
    cout << dp[N] << endl;

    return 0;
}
