#include <bits/stdc++.h>
#include "grader.h"
using namespace std;
const int maxn = 1e6 + 10;
int N;
int par[maxn][6], deg[maxn][6];
int e1[maxn], e2[maxn], m = 0;
bool three = false;
int a[6], good[6];
vector<int> g[maxn];
int cntcyc = -1;

int get_par(int v, int c){
	return par[v][c] < 0 ? v : par[v][c] = get_par(par[v][c],c);
}

void merge(int v, int u, int c){
	if (!good[c])
		return;
	int vp = get_par(v,c), up = get_par(u,c);
	if (vp == up){
		good[c] = 0;
		return;
	}
	if (deg[v][c] > 1 or deg[u][c] > 1){
		good[c] = 0;
		return;
	}
	deg[v][c] ++, deg[u][c] ++;
	par[vp][c] = up;
}

void Init(int N_){
	N = N_;
	memset(par, -1, sizeof par);
	for (int i = 1; i <= 4; i++)
		good[i] = 1;
}

void Link(int v, int u){
	if (g[v].size() < g[u].size())
		swap(v,u);
	g[v].push_back(u), g[u].push_back(v);
	if (g[v].size() == 3 and three == false){
		three = true;
		a[1] = v;
		for (int j = 0; j < 3; j++)
			a[j+2] = g[v][j];
		for (int j = 1; j <= 4; j++){
			for (int i = 0; i < m; i++){
				int v = e1[i], u = e2[i];
				if (v != a[j] and u != a[j])
					merge(v,u,j);
			}
		}
	}
	e1[m] = v, e2[m] = u, m++;
	if (three){
		for (int j = 1; j <= 4; j++){
			int v = e1[m-1], u = e2[m-1];
			if (v != a[j] and u != a[j])
				merge(v,u,j);
		}
		return;
	}
	if (get_par(v,0) == get_par(u,0)){
		if (cntcyc == -1)
			cntcyc = -par[get_par(v,0)][0];
		else
			cntcyc = 0;
	}
	else{
		v = get_par(v,0), u = get_par(u,0);
		par[u][0] += par[v][0];
		par[v][0] = u;
	}
}

int CountCritical(){
	if (three == 0){
		if (cntcyc == -1)
			return N;
		return cntcyc;
	}
	int ret = 0;
	for (int i = 1; i <= 4; i++)
		if (good[i])
			ret ++;
	return ret;
}
