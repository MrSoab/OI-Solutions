#include "friend.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+10;
const int inf = 1e9;

int n, V[maxn], c[4*maxn];
short type[4*maxn];
int m = 0;
int last[4*maxn], pre[4*maxn], to[4*maxn];
int par[maxn];

pair<int,int> dfs(int v){
	if (type[v] == 1){
		int lc = to[pre[last[v]]], rc = to[last[v]];
		auto it1 = dfs(lc);
		auto it2 = dfs(rc);
		return {max(it1.first+it2.second,it1.second+it2.first),it1.second+it2.first};
	}
	else if (type[v] == 0){
		int dp = c[v], pd = 0;
		while (last[v] != -1){
			int u = to[last[v]];
			auto it = dfs(u);
			dp += it.first, pd += it.second;
			last[v] = pre[last[v]];
		}
		dp = max(dp,pd);
		return {dp,pd};
	}
	else{
		int lc = to[pre[last[v]]], rc = to[last[v]];
		auto it1 = dfs(lc);
		auto it2 = dfs(rc);
		int dp = max(it1.first+it2.second, it1.second+it2.first);
		int pd = it1.second+it2.second;
		dp = max(dp,pd);
		return {max({it1.first+it2.second,it1.second+it2.first,it1.second+it2.second}),it1.second+it2.second};
	}
}

void addEdge(int v, int u){
	pre[m] = last[v], to[m] = u, last[v] = m++;
}

int findSample(int N,int confidence[],int host[],int protocol[]){
	memset(last, -1, sizeof last);
	n = N;
	if (*min_element(protocol+1, protocol+n) == 2 and *max_element(protocol+1, protocol+n) == 2)
		return *max_element(confidence, confidence+n);
	int newint = n+1;
	addEdge(0, 1);
	V[0] = 1;
	c[1] = confidence[0];
	for (int i = 1; i < n; i++){
		int v = V[host[i]];
		if (protocol[i] == 0){
			c[v] = 0;
			type[v] = 1;
			addEdge(v, newint++);
			addEdge(newint-1, newint);
			par[host[i]] = newint-1;
			V[host[i]] = newint++;
			
			addEdge(v, newint++);
			addEdge(newint-1, newint);
			par[i] = newint-1;
			V[i] = newint++;
			c[V[i]] = confidence[i];
			c[V[host[i]]] = confidence[host[i]];
		}
		else if (protocol[i] == 1){
			addEdge(par[host[i]], newint);
			par[i] = par[host[i]];
			V[i] = newint++;
			c[V[i]] = confidence[i];
		}
		else{
			c[v] = 0;
			type[v] = 2;
			addEdge(v, newint++);
			addEdge(newint-1, newint);
			par[host[i]] = newint-1;
			V[host[i]] = newint++;

			addEdge(v, newint++);
			addEdge(newint-1, newint);
			par[i] = newint-1;
			V[i] = newint++;
			c[V[i]] = confidence[i];
			c[V[host[i]]] = confidence[host[i]];
		}
	}
	return dfs(0).first;
}
