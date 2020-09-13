#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
 
const int maxn = 2e5 + 10;
 
int n, x[maxn], y[maxn];
set<pair<ll,pair<int,int>>> S;
int col[maxn];
 
void del(int l, int r){
	if (l == 0 and r == n+1){
		S.erase({-1LL*n*n-2, {1,1}});
		return;
	}
	if (l == 0){
		if (r == 1)
			return;
		if (col[r] == 1)
			S.erase({-1LL*(r-1)*(r-1)-1, {1,2}});
		if (col[r] == 2)
			S.erase({-1LL*(r-1)*(r-1)-1, {1,1}});
		if (col[r] == 3)
			S.erase({-1LL*(r-1)*(r-1), {1,2}});
		return;
	}
	if (r == n+1){
		if (l == n and col[l] == 3)
			return;
		int dif = n-l;
		if (col[l] == 1)
			S.erase({-1LL*dif*dif-1, {n,2}});
		if (col[l] == 2)
			S.erase({-1LL*dif*dif-1, {n,1}});
		if (col[l] == 3)
			S.erase({-1LL*dif*dif, {n,1}});
		return;
	}
	if (l+1 == r){
		if (col[l] == 3)
			return;
		if (col[l] == 1)
			S.erase({-1LL, {l,2}});
		if (col[l] == 2)
			S.erase({-1LL, {l,1}});
		return;
	}
 
	if (l+2 == r and (col[l]|col[r]) == 3 and col[l] != 3){
		S.erase({-1, {l,3^col[l]}});
		return;
	}
	if ((l+r) & 1){
		int diff = (r-l)>>1;
		if (col[l] == 3 and col[r] != 3){
			S.erase({-1LL*diff*diff-1, {(l+r+2)>>1, 3^col[r]}});
			return;
		}
		if (col[l] == 1)
			S.erase({-1LL*diff*diff-1, {(l+r)>>1, 2}});
		else
			S.erase({-1LL*diff*diff-(col[l]==2), {(l+r)>>1, 1}});
		return;
	}
	int m = (l+r)>>1;
	ll diff = (m-l), dis = 0;
	if ((col[l] | col[r]) != 3)
		dis = 1;
	if (col[l] == 1 and col[r] == 1)
		S.erase({-1LL*diff*diff-dis, {m,2}});
	else
		S.erase({-1LL*diff*diff-dis, {m,1}});
}
 
void add(int l, int r){
	if (l == 0 and r == n+1){
		S.insert({-1LL*n*n-2, {1,1}});
		return;
	}
	if (l == 0){
		if (r == 1)
			return;
		if (col[r] == 1)
			S.insert({-1LL*(r-1)*(r-1)-1, {1,2}});
		if (col[r] == 2)
			S.insert({-1LL*(r-1)*(r-1)-1, {1,1}});
		if (col[r] == 3)
			S.insert({-1LL*(r-1)*(r-1), {1,2}});
		return;
	}
	if (r == n+1){
		if (l == n and col[l] == 3)
			return;
		int dif = n-l;
		if (col[l] == 1)
			S.insert({-1LL*dif*dif-1, {n,2}});
		if (col[l] == 2)
			S.insert({-1LL*dif*dif-1, {n,1}});
		if (col[l] == 3)
			S.insert({-1LL*dif*dif, {n,1}});
		return;
	}
	if (l+1 == r){
		if (col[l] == 3)
			return;
		if (col[l] == 1)
			S.insert({-1LL, {l,2}});
		if (col[l] == 2)
			S.insert({-1LL, {l,1}});
		return;
	}
	if (l+2 == r and (col[l]|col[r]) == 3 and col[l] != 3){
		S.insert({-1, {l,3^col[l]}});
		return;
	}
	if ((l+r) & 1){
		int diff = (r-l)>>1;
		if (col[l] == 3 and col[r] != 3){
			S.insert({-1LL*diff*diff-1, {(l+r+2)>>1, 3^col[r]}});
			return;
		}
		if (col[l] == 1)
			S.insert({-1LL*diff*diff-1, {(l+r)>>1, 2}});
		else
			S.insert({-1LL*diff*diff-(col[l]==2), {(l+r)>>1, 1}});
		return;
	}
	int m = (l+r)>>1;
	ll diff = (m-l), dis = 0;
	if ((col[l] | col[r]) != 3)
		dis = 1;
	if (col[l] == 1 and col[r] == 1)
		S.insert({-1LL*diff*diff-dis, {m,2}});
	else
		S.insert({-1LL*diff*diff-dis, {m,1}});
}
 
int main(){
	ios_base::sync_with_stdio(false);
	int q;
	cin >> n >> q;
	set<int> row;
	add(0, n+1);
	for (int Q = 1; Q <= q; Q++){
		char type;
		cin >> type;
		if (type == 'E'){
			auto it = (*S.begin()).second;
			x[Q] = it.first, y[Q] = it.second;
			cout << x[Q] << " " << y[Q] << '\n';
			if (row.find(x[Q]) == row.end()){
				auto it = row.upper_bound(x[Q]);
				int nex = (it == row.end() ? n+1 : *it);
				it = row.lower_bound(x[Q]);
				int pre = (it == row.begin() ? 0 : *(--it));
				del(pre,nex);
				row.insert(x[Q]);
				col[x[Q]] |= y[Q];
				add(pre,x[Q]);
				add(x[Q],nex);
			}
			else{
				auto it = row.upper_bound(x[Q]);
				int nex = (it == row.end() ? n+1 : *it);
				it = row.lower_bound(x[Q]);
				int pre = (it == row.begin() ? 0 : *(--it));
				del(pre, x[Q]);
				del(x[Q], nex);
				col[x[Q]] |= y[Q];
				add(pre, x[Q]);
				add(x[Q], nex);
			}
		}
		else{
			int idx;
			cin >> idx;
			if (col[x[idx]] == 3){
				auto it = row.upper_bound(x[idx]);
				int nex = (it == row.end() ? n+1 : *it);
				it = row.lower_bound(x[idx]);
				int pre = (it == row.begin() ? 0 : *(--it));
				del(pre, x[idx]);
				del(x[idx], nex);
				col[x[idx]] ^= y[idx];
				add(pre, x[idx]);
				add(x[idx], nex);
			}
			else{
				auto it = row.upper_bound(x[idx]);
				int nex = (it == row.end() ? n+1 : *it);
				it = row.lower_bound(x[idx]);
				int pre = (it == row.begin() ? 0 : *(--it));
				del(pre,x[idx]);
				del(x[idx],nex);
				row.erase(x[idx]);
				col[x[idx]] ^= y[idx];
				add(pre, nex);
			}
		}
	}
}
