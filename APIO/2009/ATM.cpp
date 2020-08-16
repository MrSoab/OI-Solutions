#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 20;

vector<int> g[maxn], topol;
int c[maxn], cmp[maxn], cmpnow = 1;
int dp[maxn], pd[maxn];
bool visited[maxn];
int E1[maxn], E2[maxn];

void dfs(int v, bool w){
	visited[v] = 1;
	for (auto u : g[v])
		if (!visited[u])
			dfs(u,w);
	if (w == 0)
		topol.push_back(v);
	cmp[v] = cmpnow;
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++)
		cin >> E1[i] >> E2[i];
	for (int i = 1; i <= n; i++)
		cin >> c[i];
	for (int i = 0; i < m; i++)
		g[E1[i]].push_back(E2[i]);
	for (int i = 1; i <= n; i++)
		if (!visited[i])
			dfs(i, 0);
	for (int i = 1; i <= n; i++)
		g[i].clear(), g[i].shrink_to_fit();
	for (int i = 0; i < m; i++)
		g[E2[i]].push_back(E1[i]);
	memset(visited, 0, sizeof visited);
	reverse(topol.begin(), topol.end());
	for (auto i : topol)
		if (!visited[i])
			dfs(i, 1), cmpnow ++;
	for (int i = 1; i <= n; i++)
		g[i].clear(), g[i].shrink_to_fit();
	for (int i = 1; i <= n; i++)
		pd[cmp[i]] += c[i];
	for (int i = 0; i < m; i++)
		if (cmp[E1[i]] != cmp[E2[i]])
			g[cmp[E2[i]]].push_back(cmp[E1[i]]);
	int s, p;
	cin >> s >> p;
	memset(dp, -63, sizeof dp);
	dp[cmp[s]] = pd[cmp[s]];
	for (int i = 1; i < cmpnow; i++)
		for (auto j : g[i])
			dp[i] = max(dp[i], dp[j] + pd[i]);
	int answer = 0;
	for (int i = 1; i <= p; i++){
		int x;
		cin >> x;
		answer = max(answer, dp[cmp[x]]);
	}
	cout << answer << endl;
}
