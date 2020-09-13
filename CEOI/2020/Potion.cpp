#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 2e5 + 10;
const int inf = 1e9;

vector<int> pos[maxn];
vector<int> V1[2*maxn];
pair<int,int> Cmp[maxn];
int E1[maxn], E2[maxn], h[maxn];
int mp[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n, d, u, q;
	cin >> n >> d >> u >> q;
	int C = 8;
	for (int i = 0; i < n; i++){
		cin >> h[i];
		Cmp[i] = {h[i],i};
	}
	sort(Cmp,Cmp+n);
	for (int i = 0; i < n; i++)
		mp[Cmp[i].second] = i;
	for (int i = 0; i < u; i++){
		cin >> E1[i] >> E2[i];
		E1[i] = mp[E1[i]], E2[i] = mp[E2[i]];
		if (pos[E1[i]].empty()){
			V1[2*i].push_back(E2[i]);
			pos[E1[i]].push_back(2*i+0);
		}
		else if ((int)pos[E1[i]].size() % C == 0){
			pos[E1[i]].push_back(2*i+0);
			int me = 2*i+0;
			int sz = pos[E1[i]].size();
			V1[me] = V1[pos[E1[i]][sz-C-1]];
			for (int j = pos[E1[i]].size()-C; j < pos[E1[i]].size(); j++){
				int t = pos[E1[i]][j]/2;
				int w = (E1[t]^E2[t]^E1[i]);
				int idx = lower_bound(V1[me].begin(), V1[me].end(), w) - V1[me].begin();
				if (idx < V1[me].size() and V1[me][idx] == w)
					V1[me].erase(V1[me].begin()+idx);
				else
					V1[me].insert(V1[me].begin()+idx, w);
			}
		}
		else
			pos[E1[i]].push_back(2*i+0);
		if (pos[E2[i]].empty()){
			V1[2*i+1].push_back(E1[i]);
			pos[E2[i]].push_back(2*i+1);
		}
		else if (pos[E2[i]].size() % C == 0){
			pos[E2[i]].push_back(2*i+1);
			int me = 2*i+1;
			int sz = pos[E2[i]].size();
			V1[me] = V1[pos[E2[i]][sz-C-1]];
			for (int j = pos[E2[i]].size()-C; j < pos[E2[i]].size(); j++){
				int t = pos[E2[i]][j]/2;
				int w = (E1[t]^E2[t]^E2[i]);
				int idx = lower_bound(V1[me].begin(), V1[me].end(), w) - V1[me].begin();
				if (idx < V1[me].size() and V1[me][idx] == w)
					V1[me].erase(V1[me].begin()+idx);
				else
					V1[me].insert(V1[me].begin()+idx, w);
			}
		}
		else
			pos[E2[i]].push_back(2*i+1);
	}
	while (q --){
		int v, u, x;
		cin >> v >> u >> x;
		v = mp[v], u = mp[u];
		int idx = lower_bound(pos[v].begin(), pos[v].end(), 2*x) - pos[v].begin() - 1;
		if (idx < 0){
			cout << inf << endl;
			continue;
		}
		int then = idx;
		idx -= (idx % C);
		vector<int> V = V1[pos[v][idx]];
		for (int _ = idx+1; _ <= then; _++){
			int i = pos[v][_]/2;
			int u = (E1[i]^E2[i]^v);
			int idx = lower_bound(V.begin(), V.end(), u) - V.begin();
			if (idx < V.size() and V[idx] == u)
				V.erase(V.begin()+idx);
			else
				V.insert(V.begin()+idx, u);
		}
		idx = lower_bound(pos[u].begin(), pos[u].end(), 2*x) - pos[u].begin() - 1;
		if (idx < 0){
			cout << inf << endl;
			continue;
		}
		then = idx;
		idx -= (idx % C);
		vector<int> U = V1[pos[u][idx]];
		for (int _ = idx+1; _ <= then; _++){
			int i = pos[u][_]/2;
			int v = (E1[i]^E2[i]^u);
			int idx = lower_bound(U.begin(), U.end(), v) - U.begin();
			if (idx < U.size() and U[idx] == v)
				U.erase(U.begin()+idx);
			else
				U.insert(U.begin()+idx, v);
		}	
		if (V.empty() or U.empty()){
			cout << inf << endl;
			continue;
		}
		int ptr = 0;
		int answer = inf;
		for (auto it : V){
			int h = Cmp[it].first;
			while (ptr+1 < U.size() and Cmp[U[ptr+1]].first <= h)
				ptr ++;
			answer = min(answer, abs(h-Cmp[U[ptr]].first));
			if (ptr+1 < U.size())
				answer = min(answer, abs(h-Cmp[U[ptr+1]].first));
		}
		cout << answer << endl;
	}
}
