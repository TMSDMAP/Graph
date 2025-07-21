#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;
int N, M;
const int INF = 0x3f3f3f3f;
char G[1505][1505];
pair<int, int> vis[1505][1505];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void bfs(int sx,int sy)
{
	queue<pair<int, int>> q;
	q.push({ sx, sy });
	while (!q.empty())
	{
		int cx = q.front().first;
		int cy = q.front().second;
		q.pop();
		int nx = (cx % N + N) % N;
		int ny = (cy % M + M) % M;
		if (G[nx][ny] == '#') continue;
		if (vis[nx][ny].first == INF) vis[nx][ny] = { cx,cy };
		else if (vis[nx][ny] != make_pair(cx, cy))
		{
			cout << "Yes" << endl;
			return;
		}
		else continue;
		for (int i = 0; i < 4; i++)
		{
			int nnx = cx + dx[i];
			int nny = cy + dy[i];
			q.push({ nnx, nny });
		}
	}
	cout << "No" << endl;
}
int main()
{
	while (cin >> N >> M)
	{
		int sx, sy;
		for(int i = 0; i < N; i++)
		{
			for (int j = 0; j < M; j++)
			{
				cin >> G[i][j];
				if(G[i][j] == 'S')
				{
					sx = i;
					sy = j;
				}
			}
		}
		for(int i = 0; i < N; i++)
		{
			for(int j = 0; j < M; j++)
			{
				vis[i][j] = {INF, INF};
			}
		}
		bfs(sx, sy);
	}
}