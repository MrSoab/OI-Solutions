#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;

int newint;
int par[maxn][19], fen[maxn];
int l[maxn], r[maxn];
vector<int> t[maxn];
int h[maxn];
int P[maxn];

int get_par(int v){ return P[v] < 0 ? v : P[v] = get_par(P[v]); }

int lca(int v, int u){
	if (h[v] < h[u])
		swap(v, u);
	for (int i = 18; i >= 0; i--)
		if (h[v] - (1 << i) >= h[u])
			v = par[v][i];
	if (v == u)
		return v;
	for (int i = 18; i >= 0; i--)
		if (par[v][i] != par[u][i])
			v = par[v][i], u = par[u][i];
	return par[v][0];
}

void dfs(int v, int p = -1){
	par[v][0] = p;
	for (int i = 1; i < 19 and par[v][i-1] != -1; i++)
		par[v][i] = par[par[v][i-1]][i-1];
	for (auto u : t[v]){
		h[u] = h[v]+1;
		dfs(u, v);
	}
}

int get(int x){
	int ret = 0;
	for (int i = 17; i >= 0; i--){
		if (ret + (1 << i) >= maxn)
			continue;
		if (fen[ret+(1<<i)] < x){
			ret += (1 << i);
			x -= fen[ret];
		}
	}
	return ret;
}

void add(int idx, int val){
	idx ++;
	for (; idx < maxn; idx += idx & -idx)
		fen[idx] += val;
}

int GetBestPosition(int n, int C, int R, int *K, int *S, int *E){
	memset(P, -1, sizeof P);
	newint = n;
	for (int i = 0; i < n; i++)
		add(i, +1);
	for (int i = 0; i < C; i++){
		for (int j = S[i]; j <= E[i]; j++){
			int x = get(j+1);
			t[newint].push_back(get_par(x));
		}
		for (int j = E[i]; j > S[i]; j--){
			int x = get(j+1);
			add(x, -1);
		}
		P[get(S[i]+1)] = newint ++;
	}
	int root = newint-1;
	memset(par, -1, sizeof par);
	dfs(root);
	l[0] = -1;
	for (int i = 1; i < n; i++){
		if (K[i-1] > R)
			l[i] = i-1;
		else
			l[i] = l[i-1];
	}
	r[n-1] = -1;
	for (int i = n-2; i >= 0; i--){
		if (K[i] > R)
			r[i] = i+1;
		else
			r[i] = r[i+1];
	}
	int answer = 0, sum = 0;
	for (int i = 0; i < n; i++){
		int me = h[i];
		if (l[i] != -1)
			me = min(me, h[i] - h[lca(i,l[i])]);
		if (r[i] != -1)
			me = min(me, h[i] - h[lca(i,r[i])]);
		if (me > sum){
			sum = me;
			answer = i;
		}
	}
	return answer;
}
