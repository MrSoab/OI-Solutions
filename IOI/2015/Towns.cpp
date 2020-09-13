#include "towns.h"
#include<bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
const int inf = 2e8 + 10;
int n, d[110][110];
bool in[110];
 
int Dis(int v, int u){
	if (v == u or d[v][u] > 0)
		return d[v][u];
	return d[v][u] = d[u][v] = getDistance(v,u);
}
 
int getDis(int v, int u, int w){
	return (Dis(v,u)+Dis(v,w)-Dis(u,w))/2;
}
 
int hubDistance(int N, int sub){
	memset(d, 0, sizeof d);
	n = N;
	int Q1 = 0, Q2 = 0;
	int r = rng()%N;
	for (int i = 1; i < n; i++)
		if (Dis(r,i) > Dis(r,Q1))
			Q1 = i;
	for (int i = 1; i < n; i++)
		if (Dis(Q1,i) > Dis(Q1,Q2))
			Q2 = i;
	int R = inf;
	vector<int> a;
	int P = getDis(Q1, r, Q2);
	for (int v = 0; v < n; v++){
		if (v == Q1 or v == r or getDis(Q1, r, v) > P)
			continue;
		int A = getDis(Q1, r, v);
		a.push_back(A);
		R = min(R,max(A,Dis(Q1,Q2)-A));
	}
	if (sub <= 2)
		return R;

	sort(a.begin(), a.end());
	a.resize(unique(a.begin(),a.end())-a.begin());
	int m = 1;
	for (auto it : a){
		int now = 0;
		vector<int> b;
		for (int v = 0; v < n; v++){
			if (v == Q1 or v == Q2)
				continue;
			if (getDis(Q1, r, v) == it)
				now ++, b.push_back(v);
		}
		int t = max(it, Dis(Q1,Q2)-it);
		if (t != R or m > n/2 or (n-m-now) > n/2){
			m += now;
			continue;
		}
		if (now <= n/2)
			return R;
		if (sub == 4)
			continue;
		shuffle(b.begin(),b.end(),rng);
		int check = b[0], cnt = 1; 
		in[0] = 1;
		for (int i = 1; i < now; i++){
			if (getDis(Q1,check,b[i]) > it)
				cnt ++, in[i] = 1;
			else
				cnt --, in[i] = 0;
			if (cnt == -1){
				check = b[i], cnt = 1;
				in[i] = 1;
				continue;
			}
		}
		cnt = 0;
		bool reach = 1;
		for (int i = now-1; i >= 0; i--){
			if (cnt > n/2)
				return -R;
			if (cnt+i+1 <= n/2)
				break;
			if (reach)
				cnt += in[i];
			else
				cnt += (getDis(Q1,check,b[i]) > it);
			if (b[i] == check)
				reach = 0;
		}
		if (cnt <= n/2)
			return R;
		m += now;
	}
	return -R;
}
