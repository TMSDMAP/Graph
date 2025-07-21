#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
//DAG最长路就用拓扑排序+动态规划
const int MAXN = 1510;
const int INF = 0xc0c0c0c0; // 负无穷
int n, m;
vector<pair<int, int>> G[MAXN];
int indeg[MAXN];
int dp[MAXN];

int main() {
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({ v, w });
        indeg[v]++;
    }
    for (int i = 1; i <= n; ++i) dp[i] = INF;
    dp[1] = 0;
    queue<int> q;
    for (int i = 1; i <= n; ++i)
        if (indeg[i] == 0) q.push(i);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& e : G[u]) {
            int v = e.first, w = e.second;
            if (dp[u] != INF && dp[v] < dp[u] + w)
                dp[v] = dp[u] + w;
            indeg[v]--;
            if (indeg[v] == 0) q.push(v);
        }
    }
    if (dp[n] == INF) cout << -1 << endl;
    else cout << dp[n] << endl;
    return 0;
}