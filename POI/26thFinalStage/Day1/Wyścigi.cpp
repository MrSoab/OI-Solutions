#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 20;

int p[maxn];
ll seg[4*maxn], lazy[4*maxn];

void shift(int,int,int);

ll get(int id, int L, int R, int l, int r){
	if (r <= L or R <= l)
		return 0;
	if (l <= L and R <= r)
		return seg[id] + (r-R);
	shift(id,L,R);
	int mid = (L + R) >> 1;
	if (r <= mid)
		return get(2*id+0, L, mid, l, r);
	if (mid <= l)
		return get(2*id+1, mid, R, l, r);
	return max(get(2*id+0, L, mid, l, r), get(2*id+1, mid, R, l, r));
}

void add(int id, int L, int R, int l, int r, ll val){
	if (r <= L or R <= l)
		return;
	if (l <= L and R <= r){
		seg[id] += val;
		lazy[id] += val;
		return;
	}
	shift(id, L, R);
	int mid = (L + R) >> 1;
	add(2*id+0, L, mid, l, r, val);
	add(2*id+1, mid, R, l, r, val);
	seg[id] = max(seg[2*id+0]+R-mid, seg[2*id+1]);
}

void shift(int id, int L, int R){
	if (lazy[id] == 0)
		return;
	int mid = (L + R) >> 1;
	add(2*id+0, L, mid, L, mid, lazy[id]);
	add(2*id+1, mid, R, mid, R, lazy[id]);
	lazy[id] = 0;
}

void build(int id, int L, int R){
	if (L + 1 == R){
		seg[id] = p[L] + 1;
		return;
	}
	int mid = (L + R) >> 1;
	build(2*id+0, L, mid);
	build(2*id+1, mid, R);
	seg[id] = max(seg[2*id+0]+R-mid, seg[2*id+1]);
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; i++)
		cin >> p[i];
	sort(p+1, p+n+1);
	build(1, 1, n+1);
	while (q --){
		char type;
		cin >> type;
		if (type == 'Z'){
			int lo = 0, hi = n;
			while (hi - lo > 1){
				int mid = (lo+hi) >> 1;
				if (get(1, 1, n+1, mid, mid+1)-1+n >= get(1, 1, n+1, mid+1, n+1))
					hi = mid;
				else
					lo = mid;
			}
			cout << n-hi+1 << '\n';
		}
		else if (type == 'B'){
			ll x, y;
			cin >> x >> y;
			int lo = 0, hi = n+1;
			while (hi - lo > 1){
				int mid = (lo + hi) >> 1;
				if (get(1, 1, n+1, mid, mid+1)-1 >= x)
					hi = mid;
				else
					lo = mid;
			}
			add(1, 1, n+1, hi, n+1, y);
		}
		else{
			ll x, y;
			cin >> x >> y;
			int lo = 0, hi = n+1;
			while (hi - lo > 1){
				int mid = (lo + hi) >> 1;
				if (get(1, 1, n+1, mid, mid+1)-1 <= x)
					lo = mid;
				else
					hi = mid;
			}
			add(1, 1, n+1, 1, hi, -y);
		}
	}
}
