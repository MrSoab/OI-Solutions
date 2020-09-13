#include "werewolf.h"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 4e5 + 10;
const int N = 2e5 + 10;
vector<int> fex[N], fen[N];

void addinit(int x, int y){ // 0-index
	x ++, y ++;
	for (; x < N; x += x & -x)
		fex[x].push_back(y);
}

void add(int x, int y){
    x ++, y ++;
	for (; x < N; x += x & -x){
		int idy = lower_bound(fex[x].begin(),fex[x].end(),y)-fex[x].begin()+1;
		for (; idy < fen[x].size(); idy += idy & -idy)
			fen[x][idy] ++;
	}
}

int get(int x, int y){
    x ++, y ++;
	int ret = 0;
	for (; x; x -= x & -x){
		int idy = upper_bound(fex[x].begin(),fex[x].end(),y)-fex[x].begin();
		for (; idy; idy -= idy & -idy)
			ret += fen[x][idy];
	}
	return ret;
}

int get(int l1, int l2, int r1, int r2){
	return get(l2, r2) - get(l2,r1-1) - get(l1-1,r2) + get(l1-1,r1-1); 
}

struct DSU{
	int n;
	int p[maxn], w[maxn], lo[maxn], hi[maxn], lc[maxn], rc[maxn];
	int par[maxn][18];
	int newint, Time;
	DSU(int n_ = 0){
		n = n_, newint = n, Time = 0;
		memset(p, -1, sizeof p);
		memset(par, -1, sizeof par);
	}
	int get_par(int v){
		return p[v] < 0 ? v : p[v] = get_par(p[v]);
	}
	void merge(int v, int u, int weight){
		int Tv = v, Tu = u;
		if ((v = get_par(v)) == (u = get_par(u)))
			return;
		int me = newint ++;
		p[v] = p[u] = me;
		par[v][0] = par[u][0] = me;
		w[me] = weight;
		lc[me] = v, rc[me] = u;
	}
	void dfs(int v){
		if (v < n){
			lo[v] = Time, hi[v] = Time;
			Time ++;
			return;
		}
		lo[v] = Time;
		dfs(lc[v]);
		dfs(rc[v]);
		hi[v] = Time-1;
	}
	void init(){
		for (int v = newint-1; v >= 0; v--)
			for (int i = 1; i < 18 and par[v][i-1] != -1; i++)
				par[v][i] = par[par[v][i-1]][i-1];
		dfs(newint-1);
	}
	int getRoot(int v, int weight){
		for (int i = 17; i >= 0; i--)
			if (par[v][i] != -1 and w[par[v][i]] <= weight)
				v = par[v][i];
		return v;
	}
};

vector<int> g[maxn];

vector<int> check_validity(int n, vector<int> X, vector<int> Y, vector<int> S, vector<int> E, vector<int> L, vector<int> R){
	int m = X.size(), Q = S.size();
	for (int i = 0; i < m; i++){
		g[X[i]].push_back(Y[i]);
		g[Y[i]].push_back(X[i]);
		
	}
	DSU T1 = DSU(n), T2 = DSU(n);
	for (int v = 0; v < n; v++)
		for (auto u : g[v])
			if (u < v)
				T1.merge(v,u,v);
	for (int v = n-1; v >= 0; v--)
		for (auto u : g[v])
			if (u > v)
				T2.merge(v,u,-v);
	T1.init();
	T2.init();
	for (int v = 0; v < n; v++)
		addinit(T1.lo[v], T2.lo[v]);
	for (int i = 0; i < N; i++){
		sort(fex[i].begin(), fex[i].end());
		fex[i].resize(unique(fex[i].begin(),fex[i].end())-fex[i].begin());
		fen[i].resize(fex[i].size()+2);
	}
	for (int v = 0; v < n; v++)
		add(T1.lo[v], T2.lo[v]);
	vector<int> A(Q);
	for (int i = 0; i < Q; ++i){
		int v = T1.getRoot(E[i],R[i]);
		int u = T2.getRoot(S[i],-L[i]);
		int sum = get(T1.lo[v], T1.hi[v], T2.lo[u], T2.hi[u]);
		A[i] = (sum > 0);
	}
	return A;
}
