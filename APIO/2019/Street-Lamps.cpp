#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 3e5 + 20;

int n;
set<int> zi;
vector<int> fenidx[maxn], fen[maxn];
int Q1[maxn], Q2[maxn];
string type[maxn];

int get(int x, int y){
	int ret = 0;
	for (int i = x; i; i -= i & -i)
		for (int j = lower_bound(fenidx[i].begin(),fenidx[i].end(),y)-fenidx[i].begin()+1; j; j -= j & -j)
			ret += fen[i][j-1];
	return ret;
}

void add(int x, int y, int val){
	for (int i = x; i < maxn; i += i & -i)
		for (int j = lower_bound(fenidx[i].begin(),fenidx[i].end(),y)-fenidx[i].begin()+1; j <= fen[i].size(); j += j & -j)
			fen[i][j-1] += val;
}

void getinit(int x, int y){
	for (int i = x; i; i -= i & -i)
		fenidx[i].push_back(y);
}
void addinit(int x, int y){
	for (int i = x; i < maxn; i += i & -i)
		fenidx[i].push_back(y);
}
int getnex(int idx){
	auto it = zi.lower_bound(idx);
	return it == zi.end() ? n+1 : *it;
}
int getpre(int idx){
	auto it = zi.lower_bound(idx);
	if (it == zi.begin())
		return 1;
	it --;
	return it == zi.end() ? 1 : *it + 1;
}

int main(){
	ios_base::sync_with_stdio(false);
	int q;
	string s;
	cin >> n >> q >> s;
	for (int i = 1; i <= n; i++)
		if (s[i-1] == '0')
			zi.insert(i);
	string copys = s;
	for (int i = 1; i <= q; i++){
		cin >> type[i];
		if (type[i] == "toggle"){
			int now = Q1[i];
			cin >> Q1[i];
			if (s[now-1] == '1'){
				int pre = getpre(Q1[i]), now = Q1[i], nex = getnex(Q1[i]+1);
				addinit(pre, now+1), addinit(pre, nex+1), addinit(now+1, now+1), addinit(now+1, nex+1), s[now-1] = '0';
				zi.insert(now);
			}
			else{
				int pre = getpre(Q1[i]), now = Q1[i], nex = getnex(Q1[i]+1);
				addinit(pre, now+1), addinit(pre, nex+1), addinit(now+1, now+1), addinit(now+1, nex+1), s[now-1] = '1';
				zi.erase(now);
			}
		}
		else{
			cin >> Q1[i] >> Q2[i];
			getinit(Q1[i], Q2[i]);
		}
	}
	s = copys;
	zi.clear();
	for (int i = 1; i <= n; i++)
		if (s[i-1] == '0')
			zi.insert(i);
	for (int i = 1; i < maxn; i++){
		sort(fenidx[i].begin(), fenidx[i].end());
		fenidx[i].resize(unique(fenidx[i].begin(),fenidx[i].end())-fenidx[i].begin());
		fen[i].resize(fenidx[i].size());
	}
	for (int i = 1; i <= q; i++){
		if (type[i] == "toggle"){
			int now = Q1[i];
			if (s[now-1] == '1'){
				int pre = getpre(Q1[i]), now = Q1[i], nex = getnex(Q1[i]+1);
				add(pre, now+1, +i), add(pre, nex+1, -i), add(now+1, now+1, -i), add(now+1, nex+1, +i), s[now-1] = '0';
				zi.insert(now);
			}
			else{
				int pre = getpre(Q1[i]), now = Q1[i], nex = getnex(Q1[i]+1);
				add(pre, now+1, -i), add(pre, nex+1, +i), add(now+1, now+1, +i), add(now+1, nex+1, -i), s[now-1] = '1';
				zi.erase(now);
			}
		}
		else{
			cin >> Q1[i] >> Q2[i];
			int k = getnex(Q1[i]);
			if (k < Q2[i])
				cout << get(Q1[i], Q2[i]) << '\n';
			else
				cout << i + get(Q1[i], Q2[i]) << '\n';
		}
	}
}
