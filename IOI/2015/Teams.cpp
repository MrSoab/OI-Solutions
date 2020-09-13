#include "teams.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 10;
const int SQRT = 2000;

int n;
vector<int> fex[maxn], fen[maxn];

int TNT = 0;

void addinit(int x, int y){
	for (; x < maxn; x += x & -x)
		fex[x].push_back(y);
}

void add(int x, int y){
	for (int idx = x; idx < maxn; idx += idx & -idx){
		int idy = lower_bound(fex[idx].begin(),fex[idx].end(),y)-fex[idx].begin()+1;
		for (; idy <= fex[idx].size(); idy += idy & -idy)
			fen[idx][idy] ++;
	}
}

int get(int x, int y){
	int ret = 0;
	for (; x; x -= x & -x){
		int idy = upper_bound(fex[x].begin(),fex[x].end(),y)-fex[x].begin();
		for (;idy; idy -= idy & -idy){
			TNT ++;
			ret += fen[x][idy];
		}
	}
	return ret;
}

int get(int x, int l, int r){
	return get(x, r) - get(x, l-1);
}

void init(int N, int A[], int B[]){
	n = N;
	for (int i = 0; i < n; i++)
		addinit(A[i],B[i]);
	for (int i = 1; i < maxn; i++){
		sort(fex[i].begin(), fex[i].end());
		fex[i].resize(unique(fex[i].begin(),fex[i].end())-fex[i].begin());
		fen[i].resize(fex[i].size()+1);
	}
	for (int i = 0; i < n; i++)
		add(A[i],B[i]);
}

int up[SQRT], bup[SQRT];
int Uses[SQRT];

int can(int m, int k[]){
	sort(k,k+m);
	long long sum = 0;
	for (int i = 0; i < m; i++)
		sum += k[i];
	if (sum > n)
		return 0;
	int idx = 0, cnt = 0;
	for (int i = 0; i < m; i++){
		cnt ++;
		if (i == m-1 or k[i] != k[i+1]){
			up[idx] = k[i], bup[idx] = cnt*k[i];
			cnt = 0, idx++;
		}
	}
	int CommonUse = 0;
	up[idx] = n+1;
	for (int i = 0; i < idx; i++){
		Uses[i] = 0;
		int Marked = 0;
		for (int j = 0; j < i; j++){
			if (Uses[j] == 0)
				continue;
			int t = get(up[j], up[i], up[i+1]-1) - Marked;
			int tmp = min(t, Uses[j]);
			Marked += tmp, Uses[j] -= tmp, CommonUse -= tmp;
		}
		int me = get(up[i], up[i], up[i+1]-1) - Marked;
		bup[i] = max(0, bup[i]-me);
		int T = get(up[i], up[i+1], n) - CommonUse;
		if (T < bup[i])
			return 0;
		CommonUse += bup[i];
		Uses[i] += bup[i];
	}
	cout << TNT << endl;
	return 1;
}
