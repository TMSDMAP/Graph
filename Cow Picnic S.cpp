#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int K, N, M;
vector<vector<int>> G;
vector<int> cows;
vector<int> cnt;
vector<bool> visited;
void bfs(int s)
{
	visited.assign(N + 1, false);
	queue<int> q;
	q.push(s);
	cnt[s]++;
	visited[s] = true;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		for (int v : G[u])
		{
			if (!visited[v])
			{
				visited[v] = true;
				cnt[v]++;
				q.push(v);
			}
		}
	}
}



int main()
{
	cin >> K >> N >> M;
	G.resize(N + 1);
	cnt.resize(N + 1, 0);
	for (int i = 0; i < K; i++)
	{
		int x;
		cin >> x;
		cows.push_back(x);
	}
	for (int i = 0; i < M; i++)
	{
		int x, y;
		cin >> x >> y;
		G[x].push_back(y);
	}
	for(int i = 0; i < K; i++)
	{
		bfs(cows[i]);
	}
	int ans = 0;
	for (int j = 1; j <=N; j++)
	{
		if (cnt[j] == K) ans++;
	}
	cout << ans << endl;
	return 0;
}
/*
对每头奶牛，从其所在牧场出发，使用BFS或DFS遍历所有它能到达的牧场，并用一个技术数字
统计每个牧场被多少头奶牛访问过。最后统计被所有奶牛访问过的牧场数量。
*/