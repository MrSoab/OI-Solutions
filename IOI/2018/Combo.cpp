#include "combo.h"
#include <bits/stdc++.h>
using namespace std;

map<char,char> mp;

string guess_sequence(int n){
	string p;
	if (press("AB") > 0){
		if (press("A")) p = "A";
		else p = "B";
	}
	else{
		if (press("X")) p = "X";
		else p = "Y";
	}
	if (n == 1)
		return p;
	char fi = p[0];
	mp['A'] = 'A', mp['B'] = 'B', mp['X'] = 'X', mp['Y'] = 'Y';
	mp[fi] = 'A', mp['A'] = fi;
	for (int i = 1; i < n-1; i++){
		string Tmp = (p + mp['B']) + (p+mp['X']+mp['B']) + (p+mp['X']+mp['X']) + (p+mp['X']+mp['Y']);
		assert(Tmp.size() <= 4*n);
		int t = press(Tmp);
		if (t == i)
			p += mp['Y'];
		else if (t == i+1)
			p += mp['B'];
		else if (t == i+2)
			p += mp['X'];
		else
			assert(false);
	}
	if (press(p+mp['B']) == n)
		p += mp['B'];
	else if (press(p+mp['X']) == n)
		p += mp['X'];
	else
		p += mp['Y'];
	return p;
}
