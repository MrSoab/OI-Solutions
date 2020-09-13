#include "koala.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll; 
int B[100], R[100];
bool mark[100];
 
int minValue(int N, int W){
    for (int i = 0; i < N; i++)
		B[i] = 0;
	B[0] = 1;
	playRound(B, R);
	for (int i = 0; i < N; i++)
		if (R[i] == 0)
			return i;
	return 0;
}
 
int maxValue(int N, int W){
    int k = N;
	for (int i = 0; i < N; i++)
		mark[i] = 0;
	while (k > 1){
		int cost = min(13, W/k);
		for (int i = 0; i < N; i++){
			if (!mark[i])
				B[i] = cost;
			else
				B[i] = 0;
		}
		playRound(B, R);
		for (int i = 0; i < N; i++)
			if (!mark[i] and R[i] <= B[i])
				mark[i] = 1;
		k = 0;
		for (int i = 0; i < N; i++)
			if (mark[i] == 0)
				k ++;
	}
	for (int i = 0; i < N; i++)
		if (!mark[i])
			return i;
	return 0;
}
 
int v = 0, u = 1;
 
int greaterValue(int N, int W){
	int lo = 0, hi = 14;
	int sum = 0;
	while (hi - lo > 1){
		int mid = (lo + hi) >> 1;
		for (int i = 0; i < N; i++)
			B[i] = W/N - 1;
		B[v] = B[u] = mid * (W / N);
		playRound(B, R);
		bool fi = (R[v] > B[v]);
		bool se = (R[u] > B[u]);
		if (fi == se){
			if (fi == 1)
				lo = mid;
			else
				hi = mid;
		}
		else
			return se;
	}
	return 0;
}
 
int GlobW, GlobN;
 
bool cmp(int fi, int se){
	if (fi == se)
		return false;
	v = fi, u = se;
	return greaterValue(100, GlobW);
}
 
int T[110];
 
int playLocal(int n, int w, int l, int r, int cost){
	w -= (n-r+1);
	ll sum = 1LL*l*(l-1)/2, tot = l-1, idx = r;
	ll nowsum = sum, nowtot = tot;
	w -= (l-1);
	int ptr = 1;
	for (int i = r-1; i >= l; i--){
		while (w < cost+1 and ptr < l){
			w ++;
			nowsum -= ptr;
			tot --;
			ptr ++;
		}
		if (w >= cost+1){
			w -= cost+1;
			nowsum += i;
			nowtot += 1;
		}	
		if (make_pair(nowsum, nowtot) > make_pair(sum, tot))
			sum = nowsum, tot = nowtot, idx = i;
	}
	if (idx == l)
		return 0;
	if (idx == r)
		return 1;
	return 2;
}
 
void find(int l, int r, vector<int> a){
	if (l+1 == r){
		T[a[0]] = l;
		return;
	}
	int lo = 0, hi = min(14, GlobW/(r-l)+1);
	if (GlobW == 200)
		hi = GlobW/(r-l) + 1;
	while (hi - lo > 1){
		int mid = (lo + hi) >> 1;
		for (int i = 0; i < GlobN; i++)
			B[i] = 0;
		for (int i = 0; i < a.size(); i++)
			B[a[i]] = mid;
		int t = playLocal(GlobN, GlobW, l, r, mid);
		if (t == 0){
			lo = mid;
			continue;
		}
		if (t == 1){
			hi = mid;
			continue;
		}
		playRound(B, R);
		bool Good = 0, Bad = 0;
		for (int i = 0; i < a.size(); i++){
			if (R[a[i]] <= B[a[i]])
				Good = 1;
			else
				Bad = 1;
		}
		if (Good and Bad){
			vector<int> b, c;
			for (int i = 0; i < a.size(); i++){
				if (R[a[i]] <= B[a[i]])
					b.push_back(a[i]);
				else
					c.push_back(a[i]);
			}
			int sz = b.size();
			find(l, l+sz, b);
			find(l+sz, r, c);
			return;
		}
		if (Good)
			hi = mid;
		else
			lo = mid;
	}
}
 
void allValues(int N, int W, int *P) {
    GlobW = W, GlobN = N;
	vector<int> a;
	for (int i = 0; i < N; i++)
		a.push_back(i);
	find(1, N+1, a);
	for (int i = 0; i < N; i++)
		P[i] = T[i];
	return;
}
