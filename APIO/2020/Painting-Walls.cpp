#include "paint.h"
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

vector<int> D[maxn];
int dp[maxn][633], pd[maxn];
int idx[maxn];
bool Good[maxn];

int minimumInstructions(int n, int m, int k, vector<int> C, vector<int> A, vector<vector<int>> B){
	for (int i = 0; i < m; i++)
		for (int j = 0; j < A[i]; j++)
			D[B[i][j]].push_back(i);
	memset(idx, -1, sizeof idx);
	for (int i = n-1; i >= 0; i--){
		int c = C[i];
		for (int j = 0; j < D[C[i+1]].size(); j++)
			idx[D[C[i+1]][j]] = j;
		for (int j = 0; j < D[c].size(); j++){
			int me = D[c][j], then = (me+1)%m;
			if (idx[then] == -1)
				dp[i][j] = 1;
			else
				dp[i][j] = dp[i+1][idx[then]] + 1;
			if (dp[i][j] >= m)
				Good[i] = 1;
		}
		for (int j = 0; j < D[C[i+1]].size(); j++)
			idx[D[C[i+1]][j]] = -1;
	}
	if (Good[0] == 0 or Good[n-m] == 0)
		return -1;
	queue<int> Q;
	Q.push(0);
	pd[0] = 1;
	for (int i = 1; i < n; i++){
		if (Good[i] == 0)
			continue;
		while (!Q.empty() and i-Q.front() > m)
			Q.pop();
		if (Q.empty())
			return -1;
		pd[i] = pd[Q.front()] + 1;
		Q.push(i);
	}
	return pd[n-m];
}
