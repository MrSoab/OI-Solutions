#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
 
const int maxn = 100 + 10;

int n;
map<pair<pair<int,int>,pair<int,int>>,int> mp;

int ask(int l, int r, int lo, int hi){
	if (l != 0 and r != n)
		return ask(0, r, lo, hi) + ask(l, n, lo, hi) - ask(0, n, lo, hi);
	if (lo != 0 and hi != n)
		return ask(l, r, 0, hi) + ask(l, r, lo, n) - ask(l, r, 0, n);
	if (l >= n-l)
		return ask(0, n, lo, hi) - ask(0, l, lo, hi);
	if (n-r > r)
		return ask(0, n, lo, hi) - ask(r, n, lo, hi);
	if (lo >= n-lo)
		return ask(l, r, 0, n) - ask(l, r, 0, lo);
	if (n-hi > hi)
		return ask(l, r, 0, n) - ask(l, r, hi, n);
	if (mp.count({{l,lo},{r,hi}}))
		return mp[{{l,lo},{r,hi}}];
	cout << l+1 << " " << lo+1 << " " << r << " " << hi << endl;
	int x;
	cin >> x;
	return mp[{{l,lo},{r,hi}}] = x;
}
 
int main(){
	ios_base::sync_with_stdio(false);
	cin >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			ask(i,i+1,j,j+1);
	cout << "END" << endl;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << ask(i,i+1,j,j+1);
		cout << endl;
	}
} 
