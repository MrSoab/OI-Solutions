#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int maxn = 1e5 + 10;

set<int> adj[maxn], self[maxn], go[maxn];
int par[maxn];
map<int,int> cnt[maxn];

int get_par(int v){
	return par[v] < 0 ? v : par[v] = get_par(par[v]);
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		self[i].insert(i);
	ll now = 0;
	memset(par, -1, sizeof par);
	while (m --){
		int v, u;
		cin >> v >> u;
		int vp = get_par(v), up = get_par(u);
		if (vp == up or adj[up].count(v)){
			cout << now << '\n';
			continue;
		}
		if (go[up].count(vp)){
			stack<pair<int,int>> s;
			s.push({v,u});
			while (!s.empty()){
				int v = s.top().first, u = s.top().second;
				int vp = get_par(v), up = get_par(u);
				s.pop();
				if (vp == up)
					continue;
				now -= 1LL*par[vp]*(par[vp]+1) + 1LL*par[up]*(par[up]+1);
				now -= -1LL*par[vp]*adj[vp].size() + -1LL*par[up]*adj[up].size();
				if (par[vp] < par[up]){
					swap(vp, up);
					swap(v, u);
				}
				for (auto it : go[vp])
					if (go[it].count(up))
						s.push({up,it});
				for (auto it : adj[vp])
					if (go[up].count(get_par(it)))
						s.push({get_par(it),up});
				for (auto it : self[vp])
					adj[up].erase(it);
				for (auto it : adj[vp])
					if (!self[up].count(it))
						adj[up].insert(it);
				for (auto it : go[vp])
					go[up].insert(it);
				go[up].erase(vp);
				for (auto it : adj[vp]){
					go[get_par(it)].erase(vp);
					go[get_par(it)].insert(up);
				}
				go[vp].clear();
				for (auto it : self[vp])
					self[up].insert(it);
				self[vp].clear(), adj[vp].clear();
				par[up] += par[vp];
				par[vp] = up;
				now += 1LL*par[up]*(par[up]+1) -1LL*par[up]*adj[up].size();
			}
		}
		else{
			now += -par[up];
			go[vp].insert(up);
			adj[up].insert(v);
		}
		cout << now << '\n';
	}
}

