#include "robots.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6 + 10;

int P[maxn], Q[maxn];
ll Ted[maxn];
vector<int> V[maxn];

bool check(int A, int B, int x){
	priority_queue<int> PQ;
	for (int i = 0; i <= A; i++){
		for (auto j : V[i])
			PQ.push(j);
		if (i == A)
			break;
		int cnt = x;
		while (cnt > 0 and !PQ.empty()){
			PQ.pop();
			cnt --;
		}
	}
	for (int i = 0; i <= B; i++)
		Ted[i] = 0;
	while (!PQ.empty()){
		int x = PQ.top();
		Ted[x] ++;
		PQ.pop();
	}
	if (Ted[B] > 0)
		return false;
	for (int i = B-1; i >= 0; i--){
		if (Ted[i] > 1LL*(B-i)*x)
			return false;
		if (i > 0)
			Ted[i-1] += Ted[i];
	}
	return true;
}

int putaway(int A, int B, int T, int X[], int Y[], int W[], int S[]) {
	sort(X, X+A);
	sort(Y, Y+B);
	for (int i = 0; i < T; i++){
		P[i] = upper_bound(X, X+A, W[i]) - X;
		Q[i] = upper_bound(Y, Y+B, S[i]) - Y;
		if (P[i] == A and Q[i] == B)
			return -1;
		V[P[i]].push_back(Q[i]);
	}
	for (int i = 0; i <= A; i++)
		sort(V[i].begin(), V[i].end());
	int lo = 0, hi = T;
	while (hi - lo > 1){
		int mid = (lo+hi) >> 1;
		if (check(A, B, mid) == 0)
			lo = mid;
		else
			hi = mid;
	}
	return hi;
}
