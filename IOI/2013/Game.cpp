#include "game.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int SQ = 150;

ll gcd2(ll X, ll Y){
    ll tmp;
    while (X != Y && Y != 0){
        tmp = X;
        X = Y;
        Y = tmp % Y;
    }
    return X;
}

ll seg[SQ+100][8*SQ+100];

ll get(int id, int L, int R, int l, int r, int block){
	if (r <= L or R <= l)
		return 0;
	if (l <= L and R <= r)
		return seg[block][id];
	int mid = (L + R) >> 1;
	return gcd2(get(2*id+0, L, mid, l, r, block),
				get(2*id+1, mid, R, l, r, block));
}

void change(int id, int L, int R, int idx, ll K, int block){
	if (idx < L or R <= idx)
		return;
	if (L + 1 == R){
		seg[block][id] = K;
		return;
	}
	int mid = (L + R) >> 1;
	change(2*id+0, L, mid, idx, K, block);
	change(2*id+1, mid, R, idx, K, block);
	seg[block][id] = gcd2(seg[block][2*id+0], seg[block][2*id+1]);
}

int numBlock;
vector<pair<pair<int,int>,ll>> a[100+SQ];
map<pair<int,int>, ll> mp;
map<pair<int,int>, int> go;
vector<pair<int,ll>> b[SQ+100];

void changeblock(int block){
	assert(a[block].size() < 2*SQ);
	sort(a[block].begin(), a[block].end());
	for (int i = 0; i < 8*SQ; i++)
		seg[block][i] = 0;
	b[block].clear();
	for (auto it : a[block])
		b[block].push_back({it.first.second,it.second});
	sort(b[block].begin(), b[block].end());
	for (int i = 0; i < b[block].size(); i++)
		change(1, 0, b[block].size(), i, b[block][i].second, block);
}

void refresh(){
	go.clear();
	for (int i = 0; i < SQ; i++){
		a[i].clear();
		a[i].shrink_to_fit();
	}
	int n = mp.size();
	int idx = -1;
	numBlock = 1;
	for (auto it : mp){
		idx ++;
		numBlock = idx/SQ + 1;
		go[it.first] = idx/SQ;
		a[idx/SQ].push_back(it);
	}
	for (int i = 0; i < numBlock; i++)
		changeblock(i);

}

void init(int R, int C){
	numBlock = 1;
}

void update(int P, int Q, ll K){
	if (mp.count({P,Q})){
		mp[{P,Q}] = K;
		int block = go[{P,Q}];
		assert(block < SQ);
		for (int i = 0; i < a[block].size(); i++)
			if (a[block][i].first == make_pair(P,Q))
				a[block][i].second = K;
		changeblock(block);
		assert(block == numBlock-1 or a[block].back().first.first <= a[block+1][0].first.first);
		if (block == 0)
			return;
		block --;
		assert(block == numBlock-1 or a[block].back().first.first <= a[block+1][0].first.first);
		return;
	}
	mp[{P,Q}] = K;
	int block = numBlock-1;
	for (int i = numBlock-1; i >= 1; i--)
		if (P <= a[i][0].first.first)
			block = i-1;
	go[{P,Q}] = block;
	a[block].push_back({{P,Q},K});
	if (a[block].size() >= 2*SQ)
		refresh();
	else
		changeblock(block);
}

ll calculate(int P, int Q, int U, int V){
	ll answer = 0;
	for (int i = 0; i < numBlock; i++){
		if (a[i].empty())
			continue;
		if (a[i][0].first.first > U)
			break;
		if (a[i].back().first.first < P)
			continue;
		if (a[i][0].first.first >= P and a[i].back().first.first <= U){
			int lo = lower_bound(b[i].begin(), b[i].end(), make_pair(Q,-1LL)) - b[i].begin();
			int hi = lower_bound(b[i].begin(), b[i].end(), make_pair(V+1, -1LL)) - b[i].begin();
			answer = gcd2(answer, get(1, 0, b[i].size(), lo, hi, i));
			continue;
		}
		for (auto it : a[i]){
			int p = it.first.first, q = it.first.second;
			ll x = it.second;
			if (P <= p and p <= U and Q <= q and q <= V)
				answer = gcd2(answer, x);
		}
	}
	return answer;
}
