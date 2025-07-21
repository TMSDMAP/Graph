#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
//思路：级别小的指向级别大的，构建有向图，使用拓扑排序+dp找到最长路径,也就是分层（像剥洋葱一样）
const int MAXN = 1005;
vector<int> G[MAXN];
int indeg[MAXN], dp[MAXN];
int adj[MAXN][MAXN]; // 邻接矩阵

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		G[i].clear();
		indeg[i] = 0;
		dp[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		int s;
		cin >> s;
		vector<int> stops(s);
		for (int j = 0; j < s; j++) cin >> stops[j];
		int l = stops[0];
		int r = stops[s - 1];
		vector<bool> is_stop(n + 1, false);
		for (int x : stops) is_stop[x] = true;
		//int vmin = *min_element(stops.begin(), stops.end());
		for (int u = l; u <= r; u++)
		{
			if (is_stop[u]) continue; // 如果u是站点，跳过
			for (int j = 0; j < s; j++)
			{
				if (!adj[u][stops[j]])
				{
					adj[u][stops[j]] = 1; // 标记u到stops[j]有边
					G[u].push_back(stops[j]);
					indeg[stops[j]]++;
				}
			} //需要加邻接矩阵保证避免同一条边被多次添加导致MLE
				/*
				for (int v : stops) {
					G[u].push_back(v);
					indeg[v]++;
				}*/
			
		}
	}
	//拓扑+dp
	queue<int> q;
	for (int i = 1; i <= n; i++)
		if (indeg[i] == 0) q.push(i);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v : G[u])
		{
			if (dp[v] < dp[u] + 1)
				dp[v] = dp[u] + 1;
			indeg[v]--;
			if(indeg[v] == 0)
				q.push(v);
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; i++) ans = max(ans, dp[i]);
	cout << ans + 1 << endl;
	return 0;
}