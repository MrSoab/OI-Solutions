#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 5e5 + 20;
 
string s;
 
struct node{
	int T, LT, RT;
	int C, LC, RC;
	node(){
		T = LT = RT = C = LC = RC = 0;
	}
} seg[4*maxn];
 
node merge(node fi, node se){
	node ret;
	int tmp = min(fi.RC, se.LT);
	fi.RC -= tmp, se.LT -= tmp;
	tmp = min(fi.RC, se.T);
	fi.RC -= tmp, se.T -= tmp, se.RT += tmp;
	tmp = min(fi.C, se.LT);
	fi.C -= tmp, fi.LC += tmp, se.LT -= tmp;
	tmp = min(fi.C, se.T);
	fi.C -= tmp, fi.LC += tmp, se.T -= tmp, se.RT += tmp;
	
	tmp = min(fi.RT, se.LC);
	fi.RT -= tmp, se.LC -= tmp;
	tmp = min(fi.RT, se.C);
	fi.RT -= tmp, se.C -= tmp, se.RC += tmp;
	tmp = min(fi.T, se.LC);
	fi.T -= tmp, fi.LT += tmp, se.LC -= tmp;
	tmp = min(fi.T, se.C);
	fi.T -= tmp, fi.LT += tmp, se.C -= tmp, se.RC += tmp;
 
	tmp = min(fi.RT, se.LT);
	fi.RT -= tmp, se.LT -= tmp, ret.T += tmp;
	ret.T += fi.T + se.T;
	ret.LT = fi.LT + se.LT;
	ret.RT = fi.RT + se.RT;
	ret.C = fi.C + se.C;
	ret.LC = fi.LC + se.LC;
	ret.RC = fi.RC + se.RC;
	return ret;
}
 
node get(int id, int L, int R, int l, int r){
	if (l <= L and R <= r)
		return seg[id];
	int mid = (L + R) >> 1;
	if (r <= mid)
		return get(2*id+0, L, mid, l, r);
	if (mid <= l)
		return get(2*id+1, mid, R, l, r);
	return merge(get(2*id+0, L, mid, l, r), get(2*id+1, mid, R, l, r));
}
 
void build(int id, int L, int R){
	if (L + 1 == R){
		if (s[L] == 'C')
			seg[id].C = 1;
		else
			seg[id].T = 1;
		return;
	}
	int mid = (L + R) >> 1;
	build(2*id+0, L, mid);
	build(2*id+1, mid, R);
	seg[id] = merge(seg[2*id+0], seg[2*id+1]);
	
}
 
int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n >> s;
	build(1, 0, n);
	int q;
	cin >> q;
	while (q --){
		int l, r;
		cin >> l >> r;
		l --;
		auto it = get(1, 0, n, l, r);
		cout << it.T + it.LT + it.RT << '\n';
	}
}
