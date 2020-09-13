#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
long long a[maxn];

vector<int> find_subset(int l, int u, vector<int> w){
	vector<pair<int,int>> W;
	int n = w.size();
	for (int i = 0; i < n; i++)
		W.push_back({w[i],i});
	sort(W.begin(),W.end());
	for (int i = 1; i <= n; i++)
		a[i] = a[i-1] + W[i-1].first;
	vector<int> Ret;
	for (int i = 1; i <= n; i++){
		int idx = lower_bound(a, a+n+1, a[i]-u) - a;
		if (a[i] - a[idx] >= l){
			for (int j = idx+1; j <= i; j++)
				Ret.push_back(W[j-1].second);
			return Ret;
		}
	}
	return Ret;
}
