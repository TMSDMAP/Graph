#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

const int MAXN = 27;
int n, m;
vector<int> G[MAXN];
int indeg[MAXN];
bool used[MAXN];

bool topo_sort(string& result)
{
	int tmp[MAXN];
	memcpy(tmp, indeg, sizeof indeg);
	queue<int> q;
	result.clear();
	for (int i = 0; i < n; ++i) {
		if (tmp[i] == 0 && used[i]) q.push(i);
	}
	bool unique = true;
	for (int cnt = 0; cnt < n; cnt++)
	{
		if (q.empty()) return false; //有环
		if (q.size() > 1) unique = false; //不唯一
		int u = q.front();
		q.pop();
		result += (char)('A' + u);
		for (int v : G[u]) {
			if (--tmp[v] == 0) q.push(v);
		}
	}
	return unique;
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < n; ++i) G[i].clear();
	memset(indeg, 0, sizeof indeg);
	memset(used, 0, sizeof used);
	string ans;
	bool found = false;
	bool inconsistent = false;
	int step = 0;
	for (int i = 1; i <= m; ++i) //每加一条边就进行一次拓扑排序判断是否环化？是否唯一？是否足够？
	{
		char a, op, b;
		cin >> a >> op >> b;
		int u = a - 'A', v = b - 'A';
		G[u].push_back(v);
		indeg[v]++;
		used[u] = used[v] = true;
		if (found || inconsistent) continue;
		string res;
		bool unique = topo_sort(res);
		int cnt = 0;
		for (int j = 0; j < n; j++) if (used[j]) cnt++;
		if (res.size() < cnt) {
			cout << "Inconsistency found after " << i << " relations." << endl;
			inconsistent = true;
		}
		else if (unique) {
			cout << "Sorted sequence determined after " << i << " relations: " << res << "." << endl;
			found = true;
		}
	}
	if (!found && !inconsistent)
		cout << "Sorted sequence cannot be determined." << endl;
	return 0;
}