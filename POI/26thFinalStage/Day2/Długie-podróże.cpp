#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
const int maxn = 1e5 + 20;
const int C = 300;

int randnum(int L, int R){
	ll len = R-L+1;
	return L + rng() % len;
}

vector<int> g[maxn];
int h[C+2][maxn], Q[maxn], head, tail;

int main(){
	ios_base::sync_with_stdio(false);
	int n, m, q;
	cin >> n >> m >> q;
	for (int i = 0; i < m; i++){
		int v, u;
		cin >> v >> u;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	vector<int> med;
	for (int i = 1; i <= C; i++)
		med.push_back(randnum(1,n));
	int cnt = 0;
	memset(h, -1, sizeof h);
	for (auto v : med){
		tail = 0, head = 0;
		Q[head++] = v;
		h[cnt][v] = 0;
		while (tail < head){
			int u = Q[tail++];
			for (auto w : g[u])
				if (h[cnt][w] == -1)
					h[cnt][w] = h[cnt][u] + 1, Q[head++] = w;
		}
		cnt ++;
	}
	while (q --){
		int v, u;
		cin >> v >> u;
		int answer = n;
		for (int i = 0; i < C; i++)
			answer = min(answer, h[i][v] + h[i][u]);
		cout << answer << '\n';
	}
}
