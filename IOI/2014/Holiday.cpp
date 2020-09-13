#include "holiday.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int maxl = 22;
int n, opt[maxn], p[maxn], q[maxn], a[maxn], rt[maxn];
ll dp[maxn];
ll seg[maxn*maxl];
int teg[maxn*maxl], lc[maxn*maxl], rc[maxn*maxl];
int newint;

int add(int id, int L, int R, int idx, int val){
	if (idx < L or R <= idx)
		return id;
	int me = newint++;
	if (L+1 == R){
		teg[me] = 1, seg[me] = val;
		return me;
	}
	int mid = (L + R) >> 1;
	lc[me] = add(lc[id], L, mid, idx, val);
	rc[me] = add(rc[id], mid, R, idx, val);
	teg[me] = teg[lc[me]] + teg[rc[me]];
	seg[me] = seg[lc[me]] + seg[rc[me]];
	return me;
}

ll get(int id, int ID, int L, int R, int &k){
	if (k <= 0 or teg[ID]-teg[id] == 0)
		return 0;
	if (teg[ID]-teg[id] <= k){
		k -= (teg[ID]-teg[id]);
		return seg[ID]-seg[id];
	}
	int mid = (L + R) >> 1;
	return get(lc[id], lc[ID], L, mid, k) + get(rc[id], rc[ID], mid, R, k);
}

ll get(int l, int r, int k){
	return get(rt[l], rt[r], 0, n, k);
}

void calc(int l, int r, int lo, int hi, int d, int start){
	if (l >= r)
		return;
	int m = (l+r) >> 1;
	opt[m] = -1, dp[m] = -1;
	for (int i = lo; i < hi; i++){
		ll x = get(m, i+1, d-(i-m)-(start-m));
		if (x > dp[m])
			dp[m] = x, opt[m] = i;
	}
	calc(l,m,lo,opt[m]+1,d,start);
	calc(m+1,r,opt[m],hi,d,start);
}

ll solve(int N, int start, int d){
	n = N;
	for (int i = 0; i < n; i++)
		p[i] = i;
	sort(p, p+n, [](int x, int y){
		return a[x] > a[y];
	});
	for (int i = 0; i < n; i++)
		q[p[i]] = i;
	int root = 0;
	newint = 1;
	for (int i = 0; i < n; i++){
		rt[i+1] = add(root, 0, n, q[i], a[i]);
		root = rt[i+1];
	}
	calc(0, start+1, start, n, d, start);
	return *max_element(dp, dp+start+1);
}

long long int findMaxAttraction(int n, int start, int d, int attraction[]){
	for (int i = 0; i < n; i++)
		a[i] = attraction[i];
	ll answer = solve(n,start,d);
	for (int i = 0; i < n/2; i++)
		swap(a[i],a[n-i-1]);
	start = n-start-1;
	answer = max(answer, solve(n,start,d));
	return answer;
}
