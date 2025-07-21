#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;

int n;
vector<string> words;  //存所有单词
vector<int> G[26];		//邻接表，存单词编号
int in[26], out[26];  //入度和出度
vector<int> path;//存单词编号(逆序)

//Hierholzer算法递归DFS，构造欧拉路径/回路
void dfs(int u) {
	while (!G[u].empty()) {
		int idx = G[u].back();  //取字典序最小的单词编号
		G[u].pop_back();		//移除这条边
		dfs(words[idx].back() - 'a');	//递归到该单词的末尾字母
		path.push_back(idx);		//回溯时记录单词编号
	}
}
bool compare(int a,int b)
{
	return words[a] < words[b];
}
int main()
{
	cin >> n;
	words.resize(n);
	for (int i = 0; i < n; ++i) cin >> words[i];
	for (int i = 0; i < 26; ++i) G[i].clear();
	memset(in, 0, sizeof(in));
	memset(out, 0, sizeof(out));
	//建图，每个单词是边，首字母为起点，末字母为终点
	for (int i = 0; i < n; i++)
	{
		int u = words[i][0] - 'a';
		int v = words[i].back() - 'a';
		G[u].push_back(i); //存的是单词编号
		out[u]++;
		in[v]++;
	}
	//每个邻接表逆序排序，保证pop_back时取字典序最小的单词
	for (int i = 0; i < 26; i++)
	{
		sort(G[i].rbegin(), G[i].rend(), compare);
	}
	//判断是否存在欧拉路径或回路，确定起点
	int start = -1, cnt1 = 0, cnt2 = 0;
	for (int i = 0; i < 26; ++i) {
		if (out[i] - in[i] == 1) {
			start = i;  //出度比入度多1的点是起点
			cnt1++;
		}
		else if (in[i] - out[i] == 1) cnt2++;  //入度比出度多1的点是终点
		else if (in[i] != out[i]) { cout << "***" << endl; return 0; } //其他情况不满足欧拉路径/回路
	}
	//只能有1个起点和终点
	if (cnt1 > 1 || cnt2 > 1) { cout << "***" << endl; return 0; }
	if (start == -1)  //欧拉回路，从任意有出边的点出发
	{
		for(int i = 0;i<26;i++)
			if (out[i]) { start = i; break; }
	}
	path.clear();
	dfs(start);  //构造路径
	if(path.size()!=n){
		cout << "***" << endl;
		return 0;
	}
	reverse(path.begin(), path.end());  //逆序输出
	cout << words[path[0]];
	for (int i = 1; i < n; i++)
		cout << "." << words[path[i]];
	cout << endl;
	return 0;
}