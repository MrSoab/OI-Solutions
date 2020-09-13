#include <bits/stdc++.h>
#include "messy.h"
using namespace std;

int n;
string s;
vector<int> p;

void ask(int L, int R){
	if (L+1 == R)
		return;
	int mid = (L + R) >> 1;
	for (int i = L; i < R; i++)
		s[i] = '0';
	for (int i = L; i < mid; i++){
		s[i] = '1';
		add_element(s);
		s[i] = '0';
	}
	for (int i = L; i < R; i++)
		s[i] = '1';
	ask(L, mid);
	ask(mid,R);
}

void solve(int L, int R, vector<int> a){
	if (L+1 == R){
		p[a[0]] = L;
		return;
	}
	string check;
	for (int i = 0; i < n; i++)
		check += '1';
	for (auto i : a)
		check[i] = '0';
	vector<int> lc, rc;
	for (auto i : a){
		check[i] = '1';
		if (check_element(check))
			lc.push_back(i);
		else
			rc.push_back(i);
		check[i] = '0';
	}
	int mid = (L + R) >> 1;
	solve(L, mid, lc);
	solve(mid, R, rc);
}

vector<int> restore_permutation(int n, int w, int r){
	::n = n;
	for (int i = 0; i < n; i++)
		s += '1';
	ask(0, n);
	compile_set();
	vector<int> a;
	for (int i = 0; i < n; i++)
		a.push_back(i);
	p.resize(n);
	solve(0, n, a);
	return p;
}
