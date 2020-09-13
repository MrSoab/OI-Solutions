#include "sorting.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, x[3*maxn], y[3*maxn], a[maxn], b[maxn], pos[maxn], mex[3*maxn], mey[3*maxn];
bool mark[maxn];

bool check(int Q){
	for (int i = 0; i < n; i++){
		b[i] = a[i];
		pos[a[i]] = i;
	}
	for (int i = 0; i < Q; i++)
		swap(a[x[i]], a[y[i]]);
	int cnt = 0;
	memset(mark, 0, sizeof mark);
	for (int i = 0; i < n; i++){
		int now = i;
		mark[now] = 1;
		while (!mark[a[now]]){
			int last = now;
			now = a[now];
			mark[now] = 1;
			swap(b[x[cnt]], b[y[cnt]]);
			swap(pos[b[x[cnt]]], pos[b[y[cnt]]]);
			mex[cnt] = pos[now], mey[cnt] = pos[last];
			swap(pos[now],pos[last]);
			swap(b[pos[now]], b[pos[last]]);
			cnt ++;
		}
	}
	for (int i = cnt; i < Q; i++)
		mex[i] = mey[i] = 0;
	if (cnt <= Q)
		return true;
	return false;
}

int findSwapPairs(int N, int S[], int M, int X[], int Y[], int P[], int Q[]){
	n = N;
	for (int i = 0; i < M; i++)
		x[i] = X[i], y[i] = Y[i];
	int lo = -1, hi = M;
	while (hi-lo > 1){
		int mid = (lo + hi) >> 1;
		for (int i = 0; i < n; i++)
			a[i] = S[i];
		if (check(mid))
			hi = mid;
		else
			lo = mid;
	}
	for (int i = 0; i < n; i++)
		a[i] = S[i];
	check(hi);
	for (int i = 0; i < hi; i++)
		P[i] = mex[i], Q[i] = mey[i];
	return hi;
}
