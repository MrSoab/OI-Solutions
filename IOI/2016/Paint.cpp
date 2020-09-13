#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

const int maxn = 2e5 + 10, maxk = 100 + 10;

bool dp[maxn][maxk], pd[maxn][maxk];

int par[maxn], nex[maxn], pre[maxn];

string solve_puzzle(string s, vector<int> c){
	int n = s.size(), k = c.size();
	int last = n+1;
	for (int i = n; i >= 1; i--){
		if (s[i-1] == '_')
			last = i;
		nex[i] = last;
	}
	last = 0;
	for (int i = 1; i <= n; i++){
		if (s[i-1] == '_')
			last = i;
		pre[i] = last;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++){
		if (s[i-1] == 'X')
			dp[i][0] = 0;
		else
			dp[i][0] = dp[i-1][0];
		for (int j = 1; j <= k; j++){
			if (c[j-1] > i)
				continue;
			if (s[i-1] != 'X')
				dp[i][j] |= dp[i-1][j];
			if (i-pre[i] >= c[j-1]){
				if (i == c[j-1])
					dp[i][j] |= (j == 1);
				else
					dp[i][j] |= (s[i-c[j-1]-1] != 'X' and dp[i-c[j-1]-1][j-1]);
			}
		}
	}
	pd[n+1][k+1] = pd[n+2][k+1] = 1;
	for (int i = n; i >= 1; i--){
		if (s[i-1] == 'X')
			pd[i][k+1] = 0;
		else
			pd[i][k+1] = pd[i+1][k+1];
		for (int j = 1; j <= k; j++){
			if (c[j-1] > n-i+1)
				continue;
			if (s[i-1] != 'X')
				pd[i][j] |= pd[i+1][j];
			if (nex[i]-i >= c[j-1]){
				if (i+c[j-1] == n+1)
					pd[i][j] |= (j == k);
				else
					pd[i][j] |= (s[i+c[j-1]-1] != 'X' and pd[i+c[j-1]+1][j+1]);
			}
		}
	}
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= k; j++){
			if (nex[i]-i < c[j-1])
				continue;
			if (i > 1 and s[i-2] == 'X')
				continue;
			if (i+c[j-1] <= n and s[i+c[j-1]-1] == 'X')
				continue;
			if (dp[max(0,i-2)][j-1] == 0)
				continue;
			if (pd[min(n+1,i+c[j-1]+1)][j+1] == 0)
				continue;
			par[i] ++, par[i+c[j-1]] --;
		}
	}
	for (int i = 1; i <= n; i++)
		par[i] += par[i-1];
	string ret;
	for (int i = 1; i <= n; i++){
		if (s[i-1] != '.')
			ret += s[i-1];
		else{
			bool W = 0;
			for (int j = 0; j <= k; j++)
				if (dp[i-1][j] and pd[i+1][j+1])
					W = 1;
			bool B = (par[i] > 0);
			if (W and B)
				ret += '?';
			else if (B)
				ret += 'X';
			else
				ret += '_';
		}
	}
    return ret;
}
