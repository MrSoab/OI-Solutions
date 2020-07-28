#include "gralib.hpp"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int maxn = 250000 + 20;

vector<int> divs[maxn];
ld dp[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n = dajN();
	int k = dajK();
	int m = dajM();
	for (int i = 1; i <= k; i++){
		divs[0].push_back(i);
		for (int j = i; i+j <= n; j += i)
			divs[j].push_back(i);
	}
	dp[n] = 0;
	for (int i = n-1; i >= 0; i--){
		int good = divs[i].size();
		ld lo = 0, hi = n*sqrt(n)+1;
		int ts = 50;
		while (ts --){
			ld mid = .5 * (lo + hi);
			ld now = (k-good)*(mid+1)/k;
			for (auto j : divs[i])
				now += 1.*min(dp[i+j]+1,mid+1)/k;
			if (now >= mid)
				lo = mid;
			else
				hi = mid;
		}
		dp[i] = lo;
		ld now = (k-good)*(lo+1)/k;
		for (auto j : divs[i])
			now += 1.*min(dp[i+j]+1,lo+1)/k;
	}
	int TC = 100;
	while (TC --){
		int x = 0;
		while (x != n){
			int y = nastepna();
			if (x % y != 0)
				continue;
			if (x+y <= n and dp[x+y] <= dp[x]){
				zwieksz();
				x += y;
			}
		}
		koniec();
	}
}
