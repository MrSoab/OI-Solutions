#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 1e9;

int n, p[maxn], par[maxn], lef[maxn], rig[maxn];
vector<int> t[maxn];
int answer = 0;

int Sum = 0, Num = 0;
int SZ;

int fen1[maxn], fen2[maxn];

void vitex(){
	Sum = Num = 0;
	for (int i = 1; i <= SZ; i++)
		fen1[i] = fen2[i] = 0;
}

pair<int,int> get(int idx){
	int ret = 0, ted = 0;
	for (; idx; idx -= idx & -idx){
		ret = (ret + fen1[idx]) % mod;
		ted = (ted + fen2[idx]);
	}
	return {ret,ted};
}

int get(int idx, int Dis, int Ted){
	idx ++;
	int ret = (1LL*Sum*Ted + 1LL*Dis*Num) % mod;
	pair<int,int> i1 = get(SZ), i2 = get(idx);
	i1.first = (i1.first - i2.first + mod) % mod, i1.second -= i2.second;
	int A = (1LL*Ted*i1.first%mod - 1LL*i1.second*idx%mod*Ted%mod) % mod;
	if (A < 0)
		A += mod;
	int B = (1LL*i2.second*idx%mod*Ted - 1LL*i2.first*Ted%mod) % mod;
	if (B < 0)
		B += mod;
	return (0LL + ret + A + B) % mod;
}

void add(int idx, int Dis, int Ted){
	idx ++;
	Sum = (Sum + Dis) % mod;
	Num += Ted;
	for (int i = idx; i <= SZ; i += i & -i){
		fen1[i] = (fen1[i] + 1LL*Ted*idx) % mod;
		fen2[i] += Ted;
	}
}

int minDis(int x, int L, int R){
	if (x < L)
		return L;
	if (x > R)
		return R;
	return x;
}

vector<pair<int,int>> dfs(int v, int parent = -1){
	int Size = rig[v]-lef[v]+1;
	vector<vector<pair<int,int>>> All;
	int L = lef[v], R = rig[v];
	for (auto u : t[v]){
		if (u == parent)
			continue;
		All.push_back(dfs(u,v));
	}
	SZ = Size;
	for (int i = 0; i < Size; i++){
		answer = (answer + get(i, 0, 1)) % mod;
		add(i, 0, 1);
	}
	vector<pair<int,int>> Ret(Size);
	for (int i = 0; i < Size; i++)
		Ret[i].second = 1;
	int cnt = 0;
	for (auto u : t[v]){
		if (u == parent)
			continue;
		vector<pair<int,int>> Tmp = All[cnt++];
		int l = lef[u], r = rig[u];
		for (int j = 0; j < r-l+1; j++){
			int me = j+lef[u], nex = minDis(me, L, R);
			int Dis = (Tmp[j].first + (1LL*abs(me-nex)+1)*Tmp[j].second) % mod;
			answer = (answer + get(nex-L, Dis, Tmp[j].second)) % mod;		
		}
		for (int j = 0; j < r-l+1; j++){
			int me = j+lef[u], nex = minDis(me, L, R);
			int Dis = (Tmp[j].first + (1LL*abs(me-nex)+1)*Tmp[j].second) % mod;
			add(nex-L, Dis, Tmp[j].second);
			Ret[nex-L].first = (Ret[nex-L].first + Dis) % mod;
			Ret[nex-L].second += Tmp[j].second;
		}
	}
	vitex();
	return Ret;
}

int x[maxn], y[maxn];

	
int DistanceSum(int N, int *X, int *Y){
	n = N;
	for (int i = 0; i < n; i++)
		x[i] = X[i], y[i] = Y[i];
	for (int i = 0; i < n; i++)
		p[i] = i;
	sort(p, p+n, [](int a, int b){
		if (x[a] != x[b])
			return x[a] < x[b];
		return y[a] < y[b];
	});
	for (int i = 0; i < n; i++)
		par[i] = i, lef[i] = rig[i] = Y[i];
	for (int i = 1; i < n; i++)
		if (X[p[i]] == X[p[i-1]] and Y[p[i]] == Y[p[i-1]]+1)
			par[p[i]] = par[p[i-1]], rig[par[p[i]]] = Y[p[i]];
	sort(p, p+n, [](int a, int b){
		if (y[a] != y[b])
			return y[a] < y[b];
		return x[a] < x[b];
	});
	for (int i = 1; i < n; i++)
		if (Y[p[i]] == Y[p[i-1]] and X[p[i]] == X[p[i-1]]+1 and (par[p[i]] == p[i] or par[p[i-1]] == p[i-1]))
			t[par[p[i]]].push_back(par[p[i-1]]), t[par[p[i-1]]].push_back(par[p[i]]);
	bool found = 0;
	for (int i = 0; i < n; i++)
		if (par[i] == i and !found)
			dfs(i), found = 1;
	return answer;
}
