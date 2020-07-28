#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 20;
const int SQ = 600;

int E1[maxn], E2[maxn], W[maxn], Wtmp[maxn], Q1[maxn], Q2[maxn], Qtype[maxn];
bool modify[maxn], visited[maxn];
vector<int> g[maxn];
int par[maxn], ans[maxn];

void dfsoff(int v){
	visited[v] = 0;
	for (auto u : g[v])
		if (visited[u])
			dfsoff(u);
}

int dfs(int v){
	int ret = -par[v];
	visited[v] = 1;
	for (auto u : g[v])
		if (!visited[u])
			ret += dfs(u);
	return ret;
}

int get_par(int v){ return par[v] < 0 ? v : par[v] = get_par(par[v]); }
void merge(int v, int u){
	if ((v = get_par(v)) == (u = get_par(u)))
		return;
	if (par[v] > par[u])
		swap(v, u);
	par[v] += par[u];
	par[u] = v;
}

int main(){
	int n, m;
	scanf("%d%d", &n, &m);
	vector<int> Edge;
	for (int i = 1; i <= m; i++){
		scanf("%d%d%d", &E1[i], &E2[i], &W[i]);
		Edge.push_back(i);
	}
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++)
		scanf("%d%d%d", &Qtype[i], &Q1[i], &Q2[i]);
	for (int i = 0; i < q; i += SQ){
		memset(par, -1, sizeof par);
		int l = i, r = min(i+SQ,q);
		vector<int> a, b;
		for (int j = l; j < r; j++){
			if (Qtype[j] == 1)
				modify[Q1[j]] = 1, b.push_back(Q1[j]);
			if (Qtype[j] == 2)
				a.push_back(j);
		}
		sort(b.begin(), b.end());
		b.resize(unique(b.begin(),b.end())-b.begin());
		sort(a.begin(), a.end(), [](int x, int y){return Q2[x] > Q2[y];});
		sort(Edge.begin(), Edge.end(), [](int x, int y){return W[x] > W[y];});
		int ptr = 0;
		for (int x = l; x < r; x++)
			if (Qtype[x] == 1)
				Wtmp[Q1[x]] = W[Q1[x]];
		for (auto j : a){
			while (ptr < m and W[Edge[ptr]] >= Q2[j]){
				if (!modify[Edge[ptr]])
					merge(E1[Edge[ptr]], E2[Edge[ptr]]);
				ptr ++;
			}
			for (int x = l; x < j; x++)
				if (Qtype[x] == 1)
					W[Q1[x]] = Q2[x];
			for (auto x : b){
				if (W[x] >= Q2[j]){ 
					g[get_par(E1[x])].push_back(get_par(E2[x]));
					g[get_par(E2[x])].push_back(get_par(E1[x]));
				}
			}
			ans[j] = dfs(get_par(Q1[j]));
			dfsoff(get_par(Q1[j]));
			for (auto x : b)
				if (W[x] >= Q2[j])
					g[get_par(E1[x])].pop_back(), g[get_par(E2[x])].pop_back();
			for (int x = l; x < j; x++)
				if (Qtype[x] == 1)
					W[Q1[x]] = Wtmp[Q1[x]];
		}
		for (int j = l; j < r; j++)
			if (Qtype[j] == 1)
				modify[Q1[j]] = 0, W[Q1[j]] = Q2[j];
	}
	for (int i = 0; i < q; i++)
		if (Qtype[i] == 2)
			printf("%d\n", ans[i]);
}
