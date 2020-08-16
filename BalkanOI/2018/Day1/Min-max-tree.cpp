#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 70000 + 20;

int E1[maxn], E2[maxn], W[maxn], c[maxn];
vector<int> t[maxn], g[maxn];
set<pair<int,int>> mn[maxn], mx[maxn];
char Qtype[maxn];
int Qv[maxn], Qu[maxn], Qz[maxn], p[maxn];
bool visited[maxn];
int match[maxn];

bool dfs(int v){
	if (visited[v])
		return 0;
	visited[v] = 1;
	for (auto u : g[v]){
		if (match[u] == -1 or dfs(match[u])){
			match[u] = v;
			return true;
		}
	}
	return false;
}

void dfssack(int v, int par = -1){
	p[v] = par;
	for (auto u : t[v]){
		if (u == par)
			continue;
		dfssack(u,v);
		if (mx[c[u]].size() + mn[c[u]].size() > mx[c[v]].size() + mn[c[u]].size())
			swap(c[v],c[u]);
		for (auto it : mn[c[u]]){
			if (mn[c[v]].find(it) != mn[c[v]].end())
				mn[c[v]].erase(it);
			else
				mn[c[v]].insert(it);
		}
		for (auto it : mx[c[u]]){
			if (mx[c[v]].find(it) != mx[c[v]].end())
				mx[c[v]].erase(it);
			else
				mx[c[v]].insert(it);
		}
		mn[c[u]].clear(), mx[c[u]].clear();
	}
	if (!mx[c[v]].empty()){
		int idx = (*mx[c[v]].begin()).second;
		g[v].push_back(idx);
		W[v] = Qz[idx];
	}
	if (!mn[c[v]].empty()){
		int idx = (*mn[c[v]].begin()).second;
		g[v].push_back(idx);
		W[v] = Qz[idx];
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n-1; i++){
		cin >> E1[i] >> E2[i];
		t[E1[i]].push_back(E2[i]);
		t[E2[i]].push_back(E1[i]);
	}
	for (int i = 1; i <= n; i++)
		c[i] = i;
	int q;
	cin >> q;
	for (int i = 1; i <= q; i++){
		cin >> Qtype[i] >> Qv[i] >> Qu[i] >> Qz[i];
		if (Qtype[i] == 'm'){
			mn[c[Qv[i]]].insert({-Qz[i],i});
			mn[c[Qu[i]]].insert({-Qz[i],i});
		}
		else{
			mx[c[Qv[i]]].insert({+Qz[i],i});
			mx[c[Qu[i]]].insert({+Qz[i],i});
		}
	}
	dfssack(1);
	int maxMatch = 0;
	memset(match, -1, sizeof match);
	for (int i = 2; i <= n; i++){
		memset(visited, 0, sizeof visited);
		maxMatch += dfs(i);
	}
	for (int i = 1; i <= q; i++)
		W[match[i]] = Qz[i];
	for (int i = 2; i <= n; i++)
		cout << p[i] << " " << i << " " << W[i] << '\n'; 
}
