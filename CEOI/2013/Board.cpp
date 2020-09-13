#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 4e5 + 10;
 
int l[maxn], r[maxn], lc[maxn], rc[maxn], par[maxn];
int newint = 2;
 
void addrc(int v, int u){
	rc[v] = u;
	par[u] = v;
 
	if (lc[r[v]] != 0){
		l[lc[r[v]]] = u;
		r[u] = lc[r[v]];
	}
 
	if (lc[v] != 0){
		r[lc[v]] = u;
		l[u] = lc[v];
	}
}
 
void addlc(int v, int u){
	lc[v] = u;
	par[u] = v;
 
	if (rc[l[v]] != 0){
		r[rc[l[v]]] = u;
		l[u] = rc[l[v]];
	}
 
	if (rc[v] != 0){
		l[rc[v]] = u;
		r[u] = rc[v];
	}
}
 
string s;
 
int get(int now, string& s){
	for (int idx = 0; idx < s.size(); idx++){
		char c = s[idx];
		if (c == '1'){
			if (lc[now] == 0)
				addlc(now, newint++);
			now = lc[now];
			continue;
		}
		if (c == '2'){
			if (rc[now] == 0)
				addrc(now, newint++);
			now = rc[now];
			continue;
		}
		if (c == 'U'){
			now = par[now];
			continue;
		}
		if (c == 'L'){
			if (l[now] == 0){
				int cnt = 0;
				int tmp = now;
				while (tmp == lc[par[tmp]] and l[tmp] == 0){
					cnt ++;
					tmp = par[tmp];
				}
				if (lc[par[tmp]] == 0)
					addlc(par[tmp], newint++);
				tmp = l[tmp];
				while (cnt --){
					if (rc[tmp] == 0)
						addrc(tmp, newint++);
					tmp = rc[tmp];
				}
			}
			now = l[now];
			continue;
		}
		if (r[now] == 0){
			int cnt = 0;
			int tmp = now;
			while (tmp == rc[par[tmp]] and r[tmp] == 0){
				cnt ++;
				tmp = par[tmp];
			}
			if (rc[par[tmp]] == 0)
				addrc(par[tmp], newint++);
			tmp = r[tmp];
			while (cnt --){
				if (lc[tmp] == 0)
					addlc(tmp, newint++);
				tmp = lc[tmp];
			}
		}
		now = r[now];
	}
	return now;
}
 
int main(){
	ios_base::sync_with_stdio(false);
	string s, t;
	cin >> s >> t;
	int ds = 0, dt = 0;
	for (auto c : s)
		ds += (c == '1' or c == '2') - (c == 'U');
	for (auto c : t)
		dt += (c == '1' or c == '2') - (c == 'U');
	if (ds < dt){
		swap(ds, dt);
		swap(s, t);
	}
	int v = get(1, s);
	int u = get(1, t);
	int now = 0;
	while (ds > dt){
		now ++;
		v = par[v];
		ds --;
	}
	for (int i = newint-1; i >= 1; i--){
		if (lc[i] == 0)
			addlc(i, newint++);
		if (rc[i] == 0)
			addrc(i, newint++);
	}
	int answer = maxn;
	while (v != u){
		if (r[v] == u or l[v] == u)
			answer = min(answer, now+1);
		if (r[r[v]] == u or l[l[v]] == u)
			answer = min(answer, now+2);
		if (r[r[r[v]]] == u or l[l[l[v]]] == u)
			answer = min(answer, now+3);
		v = par[v];
		u = par[u];
		now += 2;
	}
	answer = min(answer, now);
	cout << answer << endl;
 
}
