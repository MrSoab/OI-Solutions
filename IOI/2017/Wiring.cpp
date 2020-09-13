#include "wiring.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
int n, m;
pair<ll,ll> p[2*maxn];
ll dp[2*maxn], opt[2*maxn];
ll par[2*maxn], pre[2*maxn];

ll Cost(ll l, ll r){
	ll idx = pre[r];
	assert(idx >= l);
	assert(pre[idx] < l);
	ll C1 = p[idx].first*(idx-l+1) - (par[idx]-par[l-1]);
	ll C2 = (par[r]-par[idx]) - p[idx+1].first*(r-idx);
	return C1 + C2 + (p[idx+1].first-p[idx].first)*max(r-idx,idx-l+1);
}

void calc(int l, int r, int lo, int hi){
	if (l >= r)
		return;
	int m = (l+r) >> 1;
	for (int i = lo; i < hi; i++){
		ll now = min(dp[i],dp[i-1]) + Cost(i,m);
		if (now < dp[m])
			dp[m] = now, opt[m] = i;
	}
	calc(l, m, opt[m], hi);
	calc(m+1, r, lo, opt[m]+1);
}

ll min_total_length(vector<int> Red, vector<int> Blue){
	n = Red.size(), m = Blue.size();
	p[0] = {0, -1};
	for (int i = 1; i <= n; i++)
		p[i] = {Red[i-1],0};
	for (int i = 1; i <= m; i++)
		p[i+n] = {Blue[i-1],1};
	int tot = n+m;
	sort(p+1,p+tot+1);
	for (int i = 1; i <= tot; i++){
		if (p[i].second == p[i-1].second)
			pre[i] = pre[i-1];
		else
			pre[i] = i-1;
		par[i] = par[i-1] + p[i].first;
	}

	memset(dp, 63, sizeof dp);
	dp[0] = 0;
	for (int i = 1; i <= tot; i++){
		if (pre[i] == 0)
			continue;
		if (i == tot or p[i].second != p[i+1].second)
			calc(pre[i]+1, i+1, pre[pre[i]]+1, pre[i]+1);
	}
	return dp[tot];
}
