#include <bits/stdc++.h>
#include "chameleon.h"
using namespace std;
typedef long long ll;

const int maxn = 1000 + 10;

int cnt[maxn][maxn];
vector<int> g[maxn];
int h[maxn];
vector<int> a, b;

void dfs(int v){
	if (h[v] % 2 == 0)
		a.push_back(v);
	else
		b.push_back(v);
	for (auto u : g[v])
		if (h[u] == -1){
			h[u] = h[v] + 1;
			dfs(u);
		}
}

int now = 0;

bool find(int l, int r, int v, vector<int> &x, bool sure = false){
	if (now == 3)
		return false;
	vector<int> Q;
	if (!sure){
		for (int i = l; i < r; i++)
			Q.push_back(x[i]);
		Q.push_back(v);
		if (Query(Q) == Q.size())
			return false;
	}
	if (l+1 == r){
		g[v].push_back(x[l]);
		g[x[l]].push_back(v);
		now ++;
		return true;
	}
	int mid = (l+r) >> 1;
	bool ret = find(l, mid, v, x);
	ret |= find(mid, r, v, x, ret^1);
	return ret;
}

void Solve(int n){
	for (int i = 2; i <= 2*n; i++){
		memset(h, -1, sizeof h);
		a.clear();
		b.clear();
		for (int j = 1; j <= i-1; j++){
			if (h[j] == -1){
				h[j] = 0;
				dfs(j);
			}
		}
		now = 0;
		find(0, a.size(), i, a);
		find(0, b.size(), i, b);
	}

	for (int i = 1; i <= 2*n; i++){
		if (g[i].size() == 1){
			cnt[i][g[i][0]] ++, cnt[g[i][0]][i] ++;
			continue;
		}
		bool found = false;
		for (int x = 0; !found and x < 3; x++){
			for (int y = x+1; !found and y < 3; y++){
				vector<int> v = {i, g[i][x], g[i][y]};
				if (Query(v) == 1){
					cnt[i][g[i][x]] ++, cnt[g[i][x]][i] ++;
					cnt[i][g[i][y]] ++, cnt[g[i][y]][i] ++;
					found = true;
				}
			}
		}
	}
	for (int i = 1; i <= 2*n; i++)
		for (int j = 1; j < i; j++)
			if (cnt[i][j] == 2)
				Answer(i,j);
}

