#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 20;
const int inf = 1e9;
 
set<pair<int,int>> tindex[maxn];
int ans[maxn];
vector<int> cmp;
multiset<int> seg[8*maxn];
int mxm[8*maxn], mnm[8*maxn];
 
pair<int,int> get2(int id, int L, int R, int idx){
	if (R <= idx or idx < L)
		return {inf, 0};
	if (L + 1 == R)
		return {mnm[id], mxm[id]};
	pair<int,int> ret = {mnm[id], mxm[id]};
	int mid = (L + R) >> 1;
	auto it1 = get2(2*id+0, L, mid, idx);
	auto it2 = get2(2*id+1, mid, R, idx);
	ret.first = min({ret.first, it1.first, it2.first});
	ret.second = max({ret.second, it1.second, it2.second});
	return ret;
}
 
void change2(int id, int L, int R, int l, int r, int x){
	if (r <= L or R <= l)
		return;
	if (l <= L and R <= r){
		mxm[id] = max(mxm[id], x);
		mnm[id] = min(mnm[id], x);
		return;
	}
	int mid = (L + R) >> 1;
	change2(2*id+0, L, mid, l, r, x);
	change2(2*id+1, mid, R, l, r, x);
}
 
pair<int,int> get(int id, int L, int R, int idx){
	if (R <= idx or idx < L)
		return {inf, 0};
	if (L + 1 == R){
		if (seg[id].empty())
			return {inf,0};
		return {*seg[id].begin(), *seg[id].rbegin()};
	}
	pair<int,int> ret = {inf,0};
	if (!seg[id].empty())
		ret = {*seg[id].begin(), *seg[id].rbegin()};
	int mid = (L + R) >> 1;
	auto it1 = get(2*id+0, L, mid, idx);
	auto it2 = get(2*id+1, mid, R, idx);
	ret.first = min({ret.first, it1.first, it2.first});
	ret.second = max({ret.second, it1.second, it2.second});
	return ret;
}
 
void change(int id, int L, int R, int l, int r, int x, char type){
	if (r <= L or R <= l)
		return;
	if (l <= L and R <= r){
		if (type == 'A')
			seg[id].insert(x);
		else
			seg[id].erase(seg[id].find(x));
		return;
	}
	int mid = (L + R) >> 1;
	change(2*id+0, L, mid, l, r, x, type);
	change(2*id+1, mid, R, l, r, x, type);
}
 
int m;
 
pair<int,int> getpre(int x, int idx, int type){
	auto it = tindex[type].lower_bound(make_pair(x,idx));
	if (it == tindex[type].begin())
		return {-1,-1};
	it --;
	return *it;
}
 
pair<int,int> getnex(int x, int idx, int type){
	auto it = tindex[type].lower_bound(make_pair(x,idx));
	it ++;
	if (it == tindex[type].end())
		return {-1,-1};
	return *it;
}
 
void add2(int x, int idx, int type){
	if (x == -1)
		return;
	int pre = getpre(x,idx,type).first, nex = getnex(x,idx,type).first;
	if (pre == -1)
		pre = 0;
	else
		pre = lower_bound(cmp.begin(), cmp.end(), (cmp[pre]+cmp[x]+1)/2) - cmp.begin();
	if (nex == -1)
		nex = m;
	else
		nex = lower_bound(cmp.begin(), cmp.end(), (cmp[nex]+cmp[x]+1)/2) - cmp.begin();
	change2(1, 0, m, pre, nex, x);
}
 
void add(int x, int idx, int type){
	if (x == -1)
		return;
	int pre = getpre(x,idx,type).first, nex = getnex(x,idx,type).first;
	if (pre == -1)
		pre = 0;
	else
		pre = lower_bound(cmp.begin(), cmp.end(), (cmp[pre]+cmp[x]+1)/2) - cmp.begin();
	if (nex == -1)
		nex = m;
	else
		nex = lower_bound(cmp.begin(), cmp.end(), (cmp[nex]+cmp[x]+1)/2) - cmp.begin();
	change(1, 0, m, pre, nex, x, 'A');
}
 
void del(int x, int idx, int type){
	if (x == -1)
		return;
	int pre = getpre(x,idx,type).first, nex = getnex(x,idx,type).first;
	if (pre == -1)
		pre = 0;
	else
		pre = lower_bound(cmp.begin(), cmp.end(), (cmp[pre]+cmp[x]+1)/2) - cmp.begin();
	if (nex == -1)
		nex = m;
	else
		nex = lower_bound(cmp.begin(), cmp.end(), (cmp[nex]+cmp[x]+1)/2) - cmp.begin();
	change(1, 0, m, pre, nex, x, 'D');
}
 
int main(){
	int n, k, q;
	scanf("%d%d%d", &n, &k, &q);
	vector<pair<pair<int,int>, pair<int,int>>> event;
	for (int i = 0; i < n; i++){
		int x, t, a, b;
		scanf("%d%d%d%d", &x, &t, &a, &b);
		event.push_back({{a,i}, {x,t}}); 
		event.push_back({{b,n+1+i}, {x,t}});
		cmp.push_back(x);
	}
	for (int i = 0; i < q; i++){
		int l, y;
		scanf("%d%d", &l, &y);
		cmp.push_back(l);
		event.push_back({{y,n}, {l,i}});
	}
	sort(cmp.begin(), cmp.end());
	cmp.resize(unique(cmp.begin(), cmp.end()) - cmp.begin());
	m = cmp.size();
	for (int i = 0; i < event.size(); i++)
		event[i].second.first = lower_bound(cmp.begin(), cmp.end(), event[i].second.first) - cmp.begin();
	sort(event.begin(), event.end());
	if (n <= 60000 and q <= 60000){
		int cnt = 0;
		for (auto Q : event){
			if (Q.first.second < n){
				int x = Q.second.first, type = Q.second.second, idx = Q.first.second;
				if (tindex[type].empty())
					cnt ++;
				tindex[type].insert({x,idx});
				auto nex = getnex(x, idx, type), pre = getpre(x, idx, type);
				tindex[type].erase({x,idx});
				del(pre.first, pre.second, type);
				del(nex.first, nex.second, type);
				tindex[type].insert({x,idx});
				add(x, idx, type);
				add(pre.first, pre.second, type);
				add(nex.first, nex.second, type);
			}
			else if (Q.first.second > n){
				int x = Q.second.first, type = Q.second.second, idx = Q.first.second - n - 1;
				auto nex = getnex(x,idx,type), pre = getpre(x,idx,type);
				del(x, idx, type);
				del(pre.first, pre.second, type);
				del(nex.first, nex.second, type);
				tindex[type].erase({x,idx});
				if (tindex[type].empty())
					cnt --;
				add(pre.first, pre.second, type);
				add(nex.first, nex.second, type);
			}
			else{
				int x = Q.second.first, idx = Q.second.second;
				if (cnt < k){
					ans[idx] = -1;
					continue;
				}
				auto it = get(1, 0, m, x);
				ans[idx] = max(cmp[x]-cmp[it.first], cmp[it.second]-cmp[x]);
			}
		}
		for (int i = 0; i < q; i++)
			printf("%d\n", ans[i]);
		return 0;
	}
	memset(mnm, 63, sizeof mnm);
	int cnt = 0;
	for (auto Q : event){
		if (Q.first.second < n){
			int x = Q.second.first, type = Q.second.second, idx = Q.first.second;
			if (tindex[type].empty())
				cnt ++;
			tindex[type].insert({x,idx});
		}
	}
	memset(ans, -1, sizeof ans);
	if (cnt == k){
		for (int t = 1; t <= k; t++)
			for (auto [x,idx] : tindex[t])
				add2(x,idx,t);
		for (auto Q : event){
			if (Q.first.second == n){
				int x = Q.second.first, idx = Q.second.second;
				auto it = get2(1, 0, m, x);
				ans[idx] = max(cmp[x]-cmp[it.first], cmp[it.second]-cmp[x]);
			}
		}
	}
	for (int i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
