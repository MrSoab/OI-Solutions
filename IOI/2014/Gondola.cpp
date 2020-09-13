#include "gondola.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;
const int mod = 1e9+9;

int valid(int n, int inputSeq[]){
	vector<int> A;
	for (int i = 0; i < n; i++)
		A.push_back(inputSeq[i]);
	sort(A.begin(),A.end());
	for (int i = 1; i < n; i++)
		if (A[i] == A[i-1])
			return 0;
	int idx = min_element(inputSeq, inputSeq+n) - inputSeq;
	if (inputSeq[idx] > n)
		return true;
	int cnt = 0;
	for (int i = idx; i < n; i++){
		if (inputSeq[i] <= n and inputSeq[idx]+cnt != inputSeq[i])
			return false;
		cnt ++;
	}
	for (int i = 0; i < idx; i++){
		if (inputSeq[i] <= n and inputSeq[idx]+cnt != inputSeq[i])
			return false;
		cnt ++;
	}
	return true;
}

int p[maxn];

int replacement(int n, int gondolaSeq[], int replacementSeq[]){
	for (int i = 0; i < n; i++)
		p[i] = i+1;
	for (int i = 0; i < n; i++){
		if (gondolaSeq[i] > n)
			continue;
		int cnt = 0;
		for (int j = i; j < n; j++)
			p[j] = (gondolaSeq[i]+cnt-1)%n+1, cnt++;
		for (int j = 0; j < i; j++)
			p[j] = (gondolaSeq[i]+cnt-1)%n+1, cnt++;
		break;
	}
	vector<pair<int,int>> A;
	for (int i = 0; i < n; i++)
		A.push_back({gondolaSeq[i],i});
	sort(A.begin(),A.end());
	int l = 0, now = n+1;
	for (auto it : A){
		int i = it.second;
		if (gondolaSeq[i] <= n)
			continue;
		while (now <= gondolaSeq[i])
			replacementSeq[l++] = p[i], p[i] = now++;
	}
	return l;
}

int power(int a, int b){
	if (b == 0)
		return 1;
	int ret = power(a,b/2);
	ret = 1LL*ret*ret%mod;
	if (b&1)
		ret = 1LL*ret*a%mod;
	return ret;
}

int countReplacement(int n, int inputSeq[]){
	if (!valid(n, inputSeq))
		return 0;
	int Z = 1;
	if (*min_element(inputSeq,inputSeq+n) > n)
		Z = n;
	vector<pair<int,int>> A;
	for (int i = 0; i < n; i++)
		if (inputSeq[i] > n)
			A.push_back({inputSeq[i],i});
	sort(A.begin(),A.end());
	int now = n, m = A.size();
	int mx = *max_element(inputSeq,inputSeq+n);
	for (int i = 0; i < A.size(); i++){
		int diff = A[i].first-now;
		Z = 1LL*Z*power(m,diff-1)%mod;
		m --, now = A[i].first;
	}
	return Z;
}
