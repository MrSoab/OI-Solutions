#include "scales.h"
#include <bits/stdc++.h>
using namespace std;

int P[720][6], p[6], dp[720 + 10];
vector<int> per[100*720 + 100], t[100*720 + 100];
int newint = 2;
vector<int> Q[100*720+100];

int getMax(int x, int i, int j, int k){
	for (int idx = 5; idx >= 0; idx--)
		if (P[x][idx] == i or P[x][idx] == j or P[x][idx] == k)
			return P[x][idx];
}

int getMin(int x, int i, int j, int k){
	for (int idx = 0; idx <= 5; idx++)
		if (P[x][idx] == i or P[x][idx] == j or P[x][idx] == k)
			return P[x][idx];
}

int getMid(int x, int i, int j, int k){
	bool found = 0;
	for (int idx = 5; idx >= 0; idx--){
		if (P[x][idx] == i or P[x][idx] == j or P[x][idx] == k){
			if (found)
				return P[x][idx];
			else
				found = 1;
		}
	}
}

int getNext(int x, int i, int j, int k, int z){
	bool found = 0;
	for (int idx = 0; idx <= 5; idx++){
		if (P[x][idx] == z)
			found = true;
		if ((P[x][idx] == i or P[x][idx] == j or P[x][idx] == k) and found == true)
			return P[x][idx];
	}
	return getMin(x, i, j, k);
}

bool dfs(int v, int h = 0){
	if (per[v].size() <= 1)
		return true;
	int cnt = per[v].size();
	for (int i = 1; i <= 6; i++){
		for (int j = i+1; j <= 6; j++){
			for (int k = j+1; k <= 6; k++){
				int a = 0, b = 0, c = 0;
				for (auto x : per[v]){
					if (getMax(x, i, j, k) == i)
						a ++;
					else if (getMax(x, i, j, k) == j)
						b ++;
					else
						c ++;
				}
				if (dp[max({a,b,c})]+h+1 <= 6){
					Q[v] = {1, i, j, k};
					int q = newint;
					newint += 3;
					t[v] = {q, q+1, q+2};
					for (auto x : per[v]){
						if (getMax(x, i, j, k) == i)
							per[q].push_back(x);
						else if (getMax(x, i, j, k) == j)
							per[q+1].push_back(x);
						else
							per[q+2].push_back(x);
					}
					bool ret = (dfs(q, h+1) and dfs(q+1, h+1) and dfs(q+2, h+1));
					if (ret == 1)
						return true;
					per[q].clear(), per[q+1].clear(), per[q+2].clear();
					newint -= 3;
				}

				a = 0, b = 0, c = 0;
				for (auto x : per[v]){
					if (getMin(x, i, j, k) == i)
						a ++;
					else if (getMin(x, i, j, k) == j)
						b ++;
					else
						c ++;
				}
				if (dp[max({a,b,c})]+h+1 <= 6){
					Q[v] = {2, i, j, k};
					int q = newint;
					newint += 3;
					t[v] = {q, q+1, q+2};
					for (auto x : per[v]){
						if (getMin(x, i, j, k) == i)
							per[q].push_back(x);
						else if (getMin(x, i, j, k) == j)
							per[q+1].push_back(x);
						else
							per[q+2].push_back(x);
					}
					bool ret = (dfs(q, h+1) and dfs(q+1, h+1) and dfs(q+2, h+1));
					if (ret == 1)
						return true;
					per[q].clear(), per[q+1].clear(), per[q+2].clear();
					newint -= 3;
				}

				a = 0, b = 0, c = 0;
				for (auto x : per[v]){
					if (getMid(x, i, j, k) == i)
						a ++;
					else if (getMid(x, i, j, k) == j)
						b ++;
					else
						c ++;
				}
				if (dp[max({a,b,c})]+h+1 <= 6){
					Q[v] = {3, i, j, k};
					int q = newint;
					newint += 3;
					t[v] = {q, q+1, q+2};
					for (auto x : per[v]){
						if (getMid(x, i, j, k) == i)
							per[q].push_back(x);
						else if (getMid(x, i, j, k) == j)
							per[q+1].push_back(x);
						else
							per[q+2].push_back(x);
					}
					bool ret = (dfs(q, h+1) and dfs(q+1, h+1) and dfs(q+2, h+1));
					if (ret == 1)
						return true;
					per[q].clear(), per[q+1].clear(), per[q+2].clear();
					newint -= 3;
				}

				for (int z = 1; z <= 6; z++){
					if (z == i or z == j or z == k)
						continue;
					a = 0, b = 0, c = 0;
					for (auto x : per[v]){
						if (getNext(x, i, j, k, z) == i)
							a ++;
						else if (getNext(x, i, j, k, z) == j)
							b ++;
						else
							c ++;
					}
					if (dp[max({a,b,c})]+h+1 <= 6){
						Q[v] = {4, i, j, k, z};
						int q = newint;
						newint += 3;
						t[v] = {q, q+1, q+2};
						for (auto x : per[v]){
							if (getNext(x, i, j, k, z) == i)
								per[q].push_back(x);
							else if (getNext(x, i, j, k, z) == j)
								per[q+1].push_back(x);
							else
								per[q+2].push_back(x);
						}
						bool ret = (dfs(q, h+1) and dfs(q+1, h+1) and dfs(q+2, h+1));
						if (ret == 1)
							return true;
						per[q].clear(), per[q+1].clear(), per[q+2].clear();
						newint -= 3;
					}
				}
			}
		}
	}
	return false;
}

void init(int T){
	for (int i = 0; i < 6; i++)
		p[i] = i+1;
	int cnt = 0;
	do{
		for (int i = 0; i < 6; i++)
			P[cnt][i] = p[i];
		cnt ++;
	} while(next_permutation(p,p+6));
	int root = 1;
	for (int i = 0; i < cnt; i++)
		per[root].push_back(i);
	dp[1] = 0;
	for (int i = 2; i <= 720; i++)
		dp[i] = dp[(i+2)/3] + 1;
	assert(dfs(root) == true);
}

void orderCoins(){
	int v = 1;
	while (per[v].size() > 1){
		if (Q[v][0] == 1){
			int x = getHeaviest(Q[v][1], Q[v][2], Q[v][3]);
			if (x == Q[v][1])
				v = t[v][0];
			else if (x == Q[v][2])
				v = t[v][1];
			else
				v = t[v][2];
		}
		else if (Q[v][0] == 2){
			int x = getLightest(Q[v][1], Q[v][2], Q[v][3]);
			if (x == Q[v][1])
				v = t[v][0];
			else if (x == Q[v][2])
				v = t[v][1];
			else
				v = t[v][2];
		}
		else if (Q[v][0] == 3){
			int x = getMedian(Q[v][1], Q[v][2], Q[v][3]);
			if (x == Q[v][1])
				v = t[v][0];
			else if (x == Q[v][2])
				v = t[v][1];
			else
				v = t[v][2];	
		}
		else{
			int x = getNextLightest(Q[v][1], Q[v][2], Q[v][3], Q[v][4]);
			if (x == Q[v][1])
				v = t[v][0];
			else if (x == Q[v][2])
				v = t[v][1];
			else
				v = t[v][2];
		}
	}
	assert(per[v].size() == 1);
	answer(P[per[v][0]]);
}
