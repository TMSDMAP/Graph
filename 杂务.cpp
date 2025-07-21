#include <iostream>
#include <vector>
#include <queue>
//做法：拓扑排序+dp+bfs
using namespace std;
const int MAXN = 10005;
int n;
int indegree[MAXN];
int cost[MAXN]; //任务i的花费时间，不要写结构体！
vector<vector<int>> graph;
int dp[MAXN]; //任务i最早完成时间
void bfs()
{
	queue<int> q;
	//int ans = 0;
	for (int i = 1; i <= n; i++)
	{
		if (indegree[i] == 0)
		{
			q.push(i);
			dp[i] = cost[i];
		}
	}
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		for (int v : graph[cur])
		{
			dp[v] = max(dp[v], dp[cur] + cost[v]);
			indegree[v]--;
			if (indegree[v] == 0)
				q.push(v);
		}
	}
}


int main()
{
	cin >> n;
	graph.resize(n + 1);
	for (int i = 1; i <= n; i++)
	{
		int x, len,y;
		cin >> x >> len;
		cost[x] = len;
		while (1)
		{
			cin >> y;
			if (y == 0)	break;
			graph[y].push_back(x);
			indegree[i]++;
		}
	}
	bfs();
	int ans = 0;
	for(int i = 1; i <= n; i++)
	{
		ans = max(ans, dp[i]);
	}
	cout << ans << endl;
	return 0;
}
