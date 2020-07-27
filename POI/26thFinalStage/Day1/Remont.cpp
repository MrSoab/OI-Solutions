#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5 + 20;

int a[maxn], start[maxn], nex[maxn];
map<pair<int,int>, int> last;
vector<int> g[2*maxn][2], topol;
int cmp[maxn], cmpcnt;
bool visited[2*maxn];

void dfs(int v, bool w){
	visited[v] = 1;
	for (auto u : g[v][w])
		if (!visited[u])
			dfs(u,w);
	if (w == 0)
		topol.push_back(v);
	cmp[v] = cmpcnt;
}

bool twosat(int n){
	topol.clear();
	memset(visited, 0, sizeof visited);
	for (int i = 0; i < 2*n; i++)
		if (!visited[i])
			dfs(i, 0);
	cmpcnt = 0;
	memset(visited, 0, sizeof visited);
	reverse(topol.begin(), topol.end());
	for (auto i : topol)
		if (!visited[i])
			dfs(i, 1), cmpcnt ++;
	for (int i = 0; i < 2*n; i += 2){
		if (cmp[i] == cmp[i+1])
			return false;
	}
	return true;
}

void addsat(int v, int u){
	g[v^1][0].push_back(u), g[u][1].push_back(v^1);
	g[u^1][0].push_back(v), g[v][1].push_back(u^1);
}

void solve(){
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	addsat(0,0);
	addsat(2*(n-2),2*(n-2));
	for (int i = 0; i < n-2; i++)
		addsat(2*i,2*(i+1));
	memset(nex, -1, sizeof nex);
	last.clear();
	memset(start, 0, sizeof start);
	for (int i = 0; i < n-1; i++){
		if (last.count({a[i],a[i+1]}))
			nex[last[{a[i],a[i+1]}]] = i;
		else
			start[i] = 1;
		last[{a[i],a[i+1]}] = i;
	}
	int m = n-1;
	for (int i = 0; i < n; i++){
		if (start[i] == 0 or nex[i] == -1)
			continue;
		addsat(2*i+1, 2*m); 
		int now = nex[i];
		int prep = m ++;
		while (now != -1){
			addsat(2*prep+1, 2*now+1);
			addsat(2*now+1, 2*m);
			addsat(2*prep+1, 2*m);
			prep = m ++;
			now = nex[now];
		}
	}
	if (twosat(m))
		cout << "TAK\n";
	else
		cout << "NIE\n";
	for (int i = 0; i < 2*m; i++)
		g[i][0].clear(), g[i][1].clear();
}

int main(){
	ios_base::sync_with_stdio(false);
	int tc;
	cin >> tc;
	while (tc --){
		solve();
	}
}
