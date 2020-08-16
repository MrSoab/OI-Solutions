#include "fun.h"
#include <bits/stdc++.h>

using namespace std;

const int maxn = 1e5 + 10;

int h[maxn];
vector<int> child, a[4];

vector<int> createFunTour(int n, int q) {
	int centroid = 0, sz = n;
	for (int i = 1; i < n; i++){
		int tmp = attractionsBehind(0, i);
		if (tmp*2 >= n and tmp < sz){
			centroid = i;
			sz = tmp;
		}
	}
	for (int i = 0; i < n; i++){
		if (i == centroid)
			continue;
		h[i] = hoursRequired(centroid, i);
		if (h[i] == 1)
			child.push_back(i);
	}
	sz = child.size();
	for (int i = 0; i < n; i++){
		if (i == centroid)
			continue;
		bool found = 0;
		for (int j = 0; j < sz-1; j++){
			if (hoursRequired(child[j], i) < h[i]){
				found = 1;
				a[j].push_back(i);
			}
		}
		if (!found)
			a[sz-1].push_back(i);
	}
	for (int i = 0; i < sz; i++)
		sort(a[i].begin(), a[i].end(), [](int x, int y){ return h[x] < h[y]; });
	vector<int> ret;
	int st = -1, bigChild = 0, rem = n, c;
	for (int i = 0; i < sz; i++)
		if (a[i].size() >= a[bigChild].size())
			bigChild = i;
	if (2*a[bigChild].size() >= n)
		st = a[bigChild].back(), c = bigChild;
	else
		for (int i = 0; i < sz; i++)
			if (st == -1 or (h[a[i].back()] > h[st]))
				st = a[i].back(), c = i;
	bool First = true;
	int t = -1;
	int last = n+1;
	for (int i = 0; i < n-1; i++){
		ret.push_back(st);
		a[c].pop_back();
		rem --;
		if (rem == 1)
			break;
		int nexst = -1, nexc = -1;
		for (int j = 0; j < sz; j++){
			if (j != c and !a[j].empty() and (nexst == -1 or h[a[j].back()] > h[nexst])){
				nexst = a[j].back();
				nexc = j;
			}
		}
		bool found = 0;
		for (int j = 0; j < sz; j++){
			if (j != c and 2*a[j].size() >= rem){
				if (First == true and sz == 3){
					int oth = (3^j^c);
					if (!a[oth].empty() and h[a[oth].back()] > h[st]){
						First = false;
						t = a[j][0];
						a[j].erase(a[j].begin() + 0);
						rem --;
						break;
					}
				}
				last = h[st] + h[a[j].back()];
				nexst = a[j].back();
				nexc = j;
			}	
		}
		if (found)
			continue;
		assert(h[st] + h[nexst] <= last);
		last = h[st] + h[nexst];
		st = nexst;
		c = nexc;
	}
	ret.push_back(centroid);
	if (t != -1)
		ret.push_back(t);
	return ret;
}
