#include "cave.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5e3 + 10;

int s[maxn], p[maxn];

void exploreCave(int n){
	vector<int> Key;
	for (int i = 0; i < n; i++)
		Key.push_back(i);
	for (int i = 0; i < n; i++){
		int lo = 0, hi = Key.size();
		bool last = (tryCombination(s) == i);
		while (hi - lo > 1){
			int mid = (lo + hi) >> 1;
			for (int j = lo; j < mid; j++)
				s[Key[j]] ^= 1;
			bool now = (tryCombination(s) == i);
			if (now == last)
				lo = mid;
			else
				hi = mid, last ^= 1;
		}
		if (last == 1)
			s[Key[lo]] ^= 1;
		p[Key[lo]] = i;
		Key.erase(Key.begin()+lo);
	}
	answer(s, p);
}
