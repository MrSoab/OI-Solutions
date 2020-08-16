#include<bits/stdc++.h>
#include"homecoming.h"
using namespace std;
typedef long long ll;
const int maxn = 2e6 + 20;
const ll inf = 1e18 + 7;

ll dp[maxn][2];
ll par[2*maxn];
int N;

ll getsum(int l, int r){
	if (l < 0)
		l += N, r += N;
	return par[r+1] - par[l];
}

ll solve(int n, int k, int* a, int* b){
	N = n;
	for (int i = 1; i <= n; i++)
		par[i] = par[i-1] + b[i-1];
	for (int i = n+1; i <= 2*n; i++)
		par[i] = par[i-1] + b[i-n-1];
	dp[0][0] = 0, dp[0][1] = -inf;
	for (int i = 1; i < n; i++){
		dp[i][0] = max(dp[i-1][0],dp[i-1][1]);
		if (i-k+1 > 0)
			dp[i][1] = max(dp[i-k][0] + a[i-k+1] - getsum(i-k+1, i), dp[i-1][1] + a[i-k+1] - b[i]);
		else
			dp[i][1] = -inf;
	}
	ll answer = max(dp[n-1][0],dp[n-1][1]);
	ll tot = 0;
	for (int i = 0; i < n; i++)
		tot += a[i] - b[i];
	answer = max(answer, tot);
	for (int i = 1; i <= n; i++)
		par[i] = par[i-1] + a[i-1];
	for (int i = n+1; i <= 2*n; i++)
		par[i] = par[i-1] + a[i-n-1];
	dp[0][0] = -inf, dp[0][1] = 0;
	for (int i = 1; i < n; i++){
		dp[i][1] = max(dp[i-1][1], dp[i-1][0]);
		dp[i][0] = max(dp[i-1][0] + b[i] - a[i], dp[i-1][1] + b[i] - getsum(i-k+1, i));
	}
	answer = max(answer, tot + max(dp[n-1][0],dp[n-1][1]));
	return answer;
}
