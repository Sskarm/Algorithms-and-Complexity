#include <iostream>
#include <vector>
#include <climits>
using namespace std;

const int MAXN = 1500;
const int INF = 1e9;

// Dynamic programming table and energy matrix
vector<vector<int>> memo;
vector<vector<int>> energy_sum;
int reactions[MAXN][MAXN];
int N, K;

// Calculate prefix sum of energies for efficient range queries
void precompute_energy() {
    energy_sum.resize(N + 1, vector<int>(N + 1, 0));
    
    // Build cumulative sums
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            energy_sum[i][j] = energy_sum[i][j-1] + reactions[i][j];
            for(int k = i + 1; k < j; k++) {
                energy_sum[i][j] += reactions[k][j];
            }
        }
    }
}

// Calculate energy for a segment [l,r]
int get_segment_energy(int l, int r) {
    if(l >= r) return 0;
    return energy_sum[l][r];
}

// Solve using bottom-up dynamic programming
int solve_distribution() {
    memo.resize(N + 1, vector<int>(K + 1, INF));
    
    // Base cases
    for(int i = 0; i <= N; i++) {
        memo[i][1] = get_segment_energy(1, i);
    }
    
    // Fill dp table
    for(int k = 2; k <= K; k++) {
        for(int i = k; i <= N; i++) {
            for(int j = k-1; j < i; j++) {
                int current = memo[j][k-1] + get_segment_energy(j+1, i);
                memo[i][k] = min(memo[i][k], current);
            }
        }
    }
    
    return memo[N][K];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Read input
    cin >> N >> K;
    
    // Read reaction energies
    for(int i = 1; i <= N; i++) {
        for(int j = i + 1; j <= N; j++) {
            cin >> reactions[i][j];
        }
    }
    
    precompute_energy();
    int result = solve_distribution();
    cout << result << "\n";
    
    return 0;
}