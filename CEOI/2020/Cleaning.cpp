#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;

vector<int> t[maxn];
int n, sz[maxn], Time = 0, st[maxn], par[maxn], up[maxn];

int seg[4*maxn], lazy[4*maxn];

void shift(int,int,int);

void change(int id, int L, int R, int l, int r){
	if (r <= L or R <= l)
		return;
	if (l <= L and R <= r){
		seg[id] = (R-L)-seg[id];
		lazy[id] ^= 1;
		return;
	}
	shift(id,L,R);
	int mid = (L + R) >> 1;
	change(2*id+0, L, mid, l, r);
	change(2*id+1, mid, R, l, r);
	seg[id] = seg[2*id+0] + seg[2*id+1];
}

void shift(int id, int L, int R){
	if (lazy[id] == 0)
		return;
	int mid = (L + R) >> 1;
	change(2*id+0,L,mid,L,mid);
	change(2*id+1,mid,R,mid,R);
	lazy[id] = 0;
}

void change(int v){
	while (up[v] != 1){
		change(1, 1, n, st[up[v]], st[v]+1);
		v = par[up[v]];
	}
	if (v != 1)
		change(1, 1, n, st[up[v]]+1, st[v]+1);
}

void dfs(int v){
	st[v] = Time++;
	bool bigChild = true;
	for (auto u : t[v]){
		if (bigChild == true){
			up[u] = up[v], par[u] = v;
			dfs(u);
			bigChild = false;
			continue;
		}
		up[u] = u, par[u] = v;
		dfs(u);
	}	
}

int dfsSize(int v, int par = -1){
	sz[v] = 1;
	for (auto u : t[v])
		if (u != par)
			sz[v] += dfsSize(u,v);
	for (int i = t[v].size()-1; i >= 0; i--)
		if (t[v][i] == par)
			t[v].erase(t[v].begin()+i);
	sort(t[v].begin(),t[v].end(),[](int x, int y){
		return sz[x] > sz[y];
	});
	return sz[v];
}

bool isleaf[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int q;
	cin >> n >> q;
	for (int i = 0; i < n-1; i++){
		 int v, u;
		 cin >> v >> u;
		 t[v].push_back(u);
		 t[u].push_back(v);
	}
	int cntLeaf = 0;
	for (int i = 1; i <= n; i++){
		isleaf[i] = (t[i].size() == 1);
		cntLeaf += isleaf[i];
	}
	dfsSize(1);
	up[1] = 1;
	dfs(1);
	for (int i = 1; i <= n; i++)
		if (isleaf[i])
			change(i);
	while (q --){
		int d;
		cin >> d;
		vector<int> a(d);
		for (int i = 0; i < d; i++)
			cin >> a[i];
		sort(a.begin(), a.end());
		int cnt = cntLeaf;
		for (int i = 0; i < d; i++){
			cnt ++;
			if ((i == 0 or a[i] != a[i-1]) and isleaf[a[i]])
				cnt --;
		}
		if (cnt % 2 == 1){
			cout << -1 << '\n';
			continue;
		}
		for (int i = 0; i < d; i++){
			change(a[i]);
			if ((i == 0 or a[i] != a[i-1]) and isleaf[a[i]])
				change(a[i]);
		}
		cout << n+d-1 + (n-1-seg[1]) << '\n';
		for (int i = 0; i < d; i++){
			change(a[i]);
			if ((i == 0 or a[i] != a[i-1]) and isleaf[a[i]])
				change(a[i]);
		}
	}
}
