#include "aliens.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5, maxm = 1e6 + 5;
int n, m, k;
const ll inf = 1e18;
 
ll dp[maxm], pd[maxm];
 
vector<pair<int,int>> A;

ll SQ(ll x){return x*x;}


pair<ll,ll> Q[maxm];
int tail, head, P[maxm];

ll intersect(pair<ll,ll> fi, pair<ll,ll> se){
	return 1. * (se.second - fi.second) / (fi.first - se.first);
}

ll gety(pair<ll,ll> L, ll x){
	return L.first*x + L.second;
}

void addLine(ll a, ll b, int p){
	pair<ll,ll> L = {a,b};
	while (tail+2 <= head and intersect(Q[head-2],Q[head-1]) > intersect(Q[head-1],L))
		head --;
	Q[head] = L;
	P[head++] = p;
}

pair<ll,ll> get(ll x){
	while (tail+1 < head and gety(Q[tail],x) > gety(Q[tail+1],x))
		tail ++;
	ll ans = gety(Q[tail],x);
	int ted = maxn;
	for (int i = tail; i < head; i++){
		if (gety(Q[i],x) != ans)
			break;
		ted = min(ted, P[i]);
	}
	return {ans,ted};
}

pair<ll,ll> solve(ll x){
	tail = head = 0;
	int sz = A.size();
	for (int i = 0; i < sz; i++){
		if (i == 0)
			addLine(-2*A[i].first, SQ(A[i].first)+x, 1);
		else{
			ll P = max(0,A[i-1].second-A[i].first+1);
			addLine(-2*A[i].first, SQ(A[i].first)-P*P+dp[i-1]+x, pd[i-1]+1);
		}
		auto it = get(A[i].second+1);
		dp[i] = it.first + SQ(A[i].second+1);
		pd[i] = it.second;
	}
	return {dp[sz-1],pd[sz-1]};
}
 
ll take_photos(int n, int m, int k, vector<int> r, vector<int> c){
	::n = n, ::m = m, ::k = k;
	for (int i = 0; i < n; i++)
		if (r[i] > c[i])
			swap(r[i],c[i]);
	vector<pair<int,int>> Tmp;
	for (int i = 0; i < n; i++)
		Tmp.push_back({r[i],c[i]});
	sort(Tmp.begin(),Tmp.end());
	for (int i = 0; i < n; i++){
		if (!A.empty() and A.back().first == Tmp[i].first){
			A.pop_back();
			A.push_back(Tmp[i]);
		}
		else if (A.empty() or A.back().second < Tmp[i].second)
			A.push_back(Tmp[i]);
	}
	ll lo = -1, hi = 1e12 + 1;
	while (hi-lo > 1){
		ll mid = (lo+hi) >> 1;
		if (solve(mid).second > k)
			lo = mid;
		else
			hi = mid;
	}
	auto it = solve(hi);
	return it.first - hi*k;
}
