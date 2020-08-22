#include "advisor.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 10;

int last[maxn], nex[maxn];
bool mark[maxn], Good[2*maxn];

void ComputeAdvice(int *C, int N, int K, int M) {
	set<pair<int,int>> S;
	memset(last, 63, sizeof last);
	for (int i = N-1; i >= 0; i--){
		nex[i] = last[C[i]];
		last[C[i]] = i;
	}
	for (int i = 0; i < K; i++){
		S.insert({-last[i], -(i+1)});
		mark[i] = 1;
	}
	for (int i = 0; i < N; i++){
		if (mark[C[i]]){
			auto it = S.lower_bound(make_pair(-i,-maxn));
			int idx = (*it).second;
			if (idx < 0)
				Good[-(idx+1)] = 1;
			else
				Good[idx+K] = 1;
			S.erase(it);
			S.insert({-nex[i], i});
		}
		else{
			auto it = S.begin();
			int idx = (*it).second;
			if (idx < 0){
				Good[-(idx+1)] = 0;
				mark[-(idx+1)] = 0;
			}
			else{
				Good[idx+K] = 0;
				mark[C[idx]] = 0;
			}
			S.erase(it);
			mark[C[i]] = 1;
			S.insert({-nex[i], i});
		}
	}
	for (int i = 0; i < N+K; i++)
		WriteAdvice(Good[i]);
}
