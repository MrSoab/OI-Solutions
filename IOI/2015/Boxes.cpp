#include "boxes.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e7 + 10;
const ll inf = 1e18;
int n, k, L, a, b, A[maxn], B[maxn];
ll dp[maxn], pd[maxn], DP[maxn], opt[maxn], C[maxn];
 
void calc(int l, int r, int lo, int hi){
	if (l >= r)
		return;
	int m = (l+r) >> 1;
	DP[m] = inf;
	for (int cnt = lo; cnt < hi; cnt++){
		if (cnt*k < a-m)
			continue;
		int i = max(0,b-(cnt*k-(a-m)));
		ll x = dp[m] + pd[i] + 1LL*cnt*L;
		if (x < DP[m])
			DP[m] = x, opt[m] = cnt;
	}
	calc(l, m, opt[m], hi);
	calc(m+1, r, lo, opt[m]+1);
}
 
ll delivery(int N, int K, int LL, int p[]){
	n = N, k = K, L = LL;
	for (int i = 0; i < n; i++){
		if (p[i] <= L/2)
			A[++a] = p[i];
		else
			B[++b] = L-p[i];
	}
	sort(A+1,A+a+1);
	sort(B+1,B+b+1);
	for (int i = 1; i <= a; i++){
		if (i <= k)
			dp[i] = 2LL*A[i];
		else
			dp[i] = dp[i-k] + 2LL*A[i];
	}
	for (int i = 1; i <= b; i++){
		if (i <= k)
			pd[i] = 2LL*B[i];
		else
			pd[i] = pd[i-k] + 2LL*B[i];
	}
	calc(0, a+1, 0, (n+k-1)/k + 1);
	return min(1LL*((n+k-1)/k)*L, *min_element(DP, DP+a+1));
}
