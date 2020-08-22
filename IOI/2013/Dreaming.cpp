#include "dreaming.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int inf = 1e9;

vector<pair<int,int>> t[maxn];
int dp[maxn], pd[maxn];
bool visited[maxn];

int dfsdw(int v, int par = -1){
	int ret = dp[v];
	for (auto [u,c] : t[v]){
		if (u == par)
			continue;
		int best = 0;
		if (dp[v] != dp[u]+c)
			best = dp[v];
		else
			best = pd[v];
		if (best+c > dp[u]){
			pd[u] = dp[u];
			dp[u] = best+c;
		}
		else if (best+c > pd[u])
			pd[u] = best+c;
		ret = min(ret, dfsdw(u,v));
	}
	return ret;
}

void dfsup(int v, int par = -1){
	visited[v] = 1;
	dp[v] = 0, pd[v] = -inf;
	for (auto [u,c] : t[v]){
		if (u == par)
			continue;
		dfsup(u,v);
		if (dp[u]+c >= dp[v]){
			pd[v] = dp[v];
			dp[v] = dp[u]+c;
		}
		else if (dp[u]+c >= pd[v])
			pd[v] = dp[u]+c;
	}
}

int travelTime(int N, int M, int L, int A[], int B[], int T[]) {
	for (int i = 0; i < M; i++){
		t[A[i]].push_back({B[i],T[i]});
		t[B[i]].push_back({A[i],T[i]});
	}
	vector<int> a;
	for (int i = 0; i < N; i++){
		if (visited[i])
			continue;
		dfsup(i);
		a.push_back(dfsdw(i));
	}
	sort(a.rbegin(), a.rend());
	int answer = *max_element(dp, dp+N);
	if (a.size() == 1)
		return answer;
	answer = max(answer, a[0]+a[1]+L);
	if (a.size() > 2)
		answer = max(answer, a[1]+a[2]+2*L);
	return answer;
}
