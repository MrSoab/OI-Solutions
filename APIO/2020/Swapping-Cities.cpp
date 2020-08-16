#include "swap.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 4e5 + 10;
const int inf = 1e9 + 1;

int n, m;
int par[maxn][19], fastpar[maxn], nexW[maxn], val[maxn], h[maxn];
bool ispath[maxn];
int src[maxn], snk[maxn];
int newint;

int get_par(int v){
	return fastpar[v] < 0 ? v : fastpar[v] = get_par(fastpar[v]);
}

void merge(int v, int u, int w){
	int mainv = v, mainu = u;
	if ((v = get_par(v)) == (u = get_par(u))){
		if (ispath[v])
			nexW[v] = min(nexW[v], w);
		return;
	}
	int p = newint ++;
	fastpar[v] = fastpar[u] = p;
	par[v][0] = p, par[u][0] = p;
	val[p] = w;
	if (ispath[v] and ispath[u] and nexW[v] >= inf and nexW[u] >= inf){
		if ((mainv == src[v] or mainv == snk[v]) and (mainu == src[u] or mainu == snk[u])){
			ispath[p] = 1;
			src[p] = (mainv^src[v]^snk[v]);
			snk[p] = (mainu^src[u]^snk[u]);
		}
	}
}

int ed[maxn], wed[maxn], maxW;

void init(int N, int M, vector<int> U, vector<int> V, vector<int> W) {
	n = N, m = M;
	for (int i = 0; i < m; i++)
		ed[i] = i, wed[i] = W[i];
	sort(ed, ed + m, [](int x, int y){ return wed[x] < wed[y]; });
	maxW = *max_element(wed, wed+m);
	newint = n;
	memset(par, -1, sizeof par);
	memset(fastpar, -1, sizeof fastpar);
	memset(nexW, 63, sizeof nexW);
	for (int i = 0; i < n; i++)
		ispath[i] = 1, src[i] = snk[i] = i;
	for (int i = 0; i < m; i++){
		int idx = ed[i];
		merge(V[idx], U[idx], W[idx]);
	}
	for (int i = newint-1; i >= 0; i--)
		for (int j = 1; par[i][j-1] != -1 and j < 19; j++)
			par[i][j] = par[par[i][j-1]][j-1];
	for (int i = 0; i < newint-1; i++){
		h[i] = 0;
		int x = i;
		for (int j = 18; j >= 0; j--){
			if (par[x][j] != -1){
				h[i] += (1 << j);
				x = par[x][j];
			}
		}
	}
}

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

int canReach(int l, int x, int y){
	if (ispath[l] == false or nexW[l] < inf)
		return true;
	return false;
}

int getMinimumFuelCapacity(int x, int y){
	int l = lca(x, y);
	if (canReach(l,x,y)){
		if (ispath[l] == false)
			return val[l];
		return nexW[l];
	}
	if (!canReach(newint-1,x,y))
		return -1;
	for (int i = 18; i >= 0; i--)
		if (par[l][i] != -1 and !canReach(par[l][i],x,y))
			l = par[l][i];
	l = par[l][0];
	int tmp = nexW[l];
	nexW[l] = inf;
	if (canReach(l,x,y)){
		nexW[l] = tmp;
		return val[l];
	}
	nexW[l] = tmp;
	return nexW[l];
}
