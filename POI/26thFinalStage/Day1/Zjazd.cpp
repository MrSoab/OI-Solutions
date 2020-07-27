#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 250 + 20;
const int maxl = 30;

bitset<maxn> adj[maxl+1][maxn];
bitset<maxn> adj2[maxl+1][maxn];
bitset<maxn> mat[maxn], tmp[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	bitset<maxn> init;
	for (int i = 1; i <= k; i++){
		int x;
		cin >> x;
		init[x] = 1;
	}
	if (init.count() == 1){
		cout << "TAK\n0\n";
		return 0;
	}
	for (int i = 1; i <= m; i++){
		int v, u;
		cin >> v >> u;
		adj[0][v][u] = 1;
	}
	for (int i = 1; i <= maxl; i++)
		for (int v = 1; v <= n; v++)
			for (int u = 1; u <= n; u++)
				if (adj[i-1][v][u])
					adj[i][v] = (adj[i][v] | adj[i-1][u]);
	for (int v = 1; v <= n; v++)
		adj2[0][v][v] = 1;
	for (int i = 1; i <= maxl; i++)
		for (int v = 1; v <= n; v++)
			for (auto u = 1; u <= n; u++)
				if (adj[i-1][v][u])
					adj2[i][v] = (adj2[i][v] | adj2[i-1][u]);
	bitset<maxn> now;
	for (int i = 1; i <= n; i++)
		now[i] = 1;
	for (int v = 1; v <= n; v++)
		if (init[v])
			now = (now & adj[maxl][v]);
	if (now == 0)
		return cout << "NIE\n", 0;
	cout << "TAK\n";
	int answer = 0;
	for (int v = 1; v <= n; v++)
		mat[v][v] = 1;
	for (int i = maxl; i >= 0; i--){
		for (int v = 1; v <= n; v++){
			tmp[v].reset();
			for (auto u = 1; u <= n; u++)
				if (mat[v][u])
					tmp[v] = (tmp[v] | adj2[i][u]);
		}
		bitset<maxn> now;
		for (int i = 1; i <= n; i++)
			now[i] = 1;
		for (int v = 1; v <= n; v++)
			if (init[v])
				now = (now & tmp[v]);
		if (now != 0)
			continue;
		answer += (1 << i);

		for (int v = 1; v <= n; v++){
			mat[v].reset();
			for (int u = 1; u <= n; u++)
				if (tmp[v][u])
					mat[v] = (mat[v] | adj[0][u]);
		}
	}
	cout << answer << endl;
}
