#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 105;
const int maxk = 1005;
const int maxm = 10005;
const ld eps = 0.0000001;
const ll inf = (ll)1e19;
ll b[maxn][maxk],s[maxn][maxk];
int n,m;
pair<pair<int,int>,ll> e[maxm], E[maxn*maxn];
ll dp[maxn][maxn];
ll c[maxn][maxn];
ld sp[maxn];
 
bool bellman(){
	for (int i = 1; i <= n; i++)
		sp[i] = inf;
	sp[1] = 0;
	for (int j = 1; j <= n; j++){
		for (int i = 1; i <= n*(n-1); i++){
			int v = E[i].first.first, u = E[i].first.second;
			ld w = E[i].second - eps;
			sp[u] = min(sp[u], sp[v] + w);
		}
	}
	for (int i = 1; i <= n*(n-1); i++){
		int v = E[i].first.first, u = E[i].first.second;
		ld w = E[i].second - eps;
		if (sp[u] > sp[v] + w)
			return true; // found negative cycle
	}
	return false;
}
 
bool check(ll x){
	memset(dp, 63, sizeof dp);
	for (int i = 1; i <= n; i++)
		dp[i][i] = 0;
	for (int i = 1; i <= m; i++){
		int v = e[i].first.first, u = e[i].first.second;
		ll w = e[i].second;
		dp[v][u] = x*w;
	}
	for (int k = 1; k <= n; k++)
		for (int v = 1; v <= n; v++)
			for (int u = 1; u <= n; u++)
				dp[v][u] = min(dp[v][u], dp[v][k] + dp[k][u]);
	int now = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			if (i != j){
				E[now ++] = {{i, j}, dp[i][j] - c[i][j]};
			}
	return bellman();
}
 
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	int k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= k; j++)
			cin >> b[i][j] >> s[i][j];
	for (int i = 1; i <= m; i++){
		int v, u, w;
		cin >> v >> u >> w;
		e[i] = {{v, u}, w};
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			for (int x = 1; x <= k; x++)
				if (b[i][x] != -1 and s[j][x] != -1)
					c[i][j] = max(c[i][j], s[j][x] - b[i][x]);
	ll lo = 0, hi = 1000 * 1000 * 1000 + 1;
	while (hi - lo > 1){
		ll mid = (lo + hi) >> 1;
		if (check(mid))
			lo = mid;
		else
			hi = mid;
	}
	cout << lo << endl;
}
