#include <bits/stdc++.h>
#include "assistant.h"
using namespace std;
const int maxn = 1e5 + 10;

bool mark2[maxn];
int C[maxn];
int A[2*maxn];

void Assist(unsigned char *S, int N, int K, int R) {
	set<int> Bad;
	for (int i = 0; i < R; i++)
		A[i] = S[i];
	for (int i = 0; i < K; i++){
		if (A[i] == 0)
			Bad.insert(i);
		mark2[i] = 1;
	}
	for (int i = 0; i < N; i++) {
		int req = GetRequest();
		C[i] = req;
		if (mark2[req]){
			if (A[i+K] == 0)
				Bad.insert(C[i]);
			continue;
		}
		assert(!Bad.empty());
		int idx = *Bad.begin();
		PutBack(idx);
		mark2[idx] = 0;
		mark2[C[i]] = 1;
		Bad.erase(Bad.begin());
		if (A[i+K] == 0)
			Bad.insert(C[i]);
	}
}
