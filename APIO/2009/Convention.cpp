#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 4e5 + 20;

int l[maxn], r[maxn], p[maxn];
int lef[maxn], rig[maxn];
int nex[maxn][20];

int getMIS(int L, int R){
	int ret = 0;
	for (int i = 19; i >= 0; i--){
		if (nex[L][i] != -1 and nex[L][i] <= R){
			ret += (1 << i);
			L = nex[L][i] + 1;
		}
	}
	return ret;
}

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> cmp;
	for (int i = 1; i <= n; i++){
		cin >> l[i] >> r[i];
		cmp.push_back(l[i]);
		cmp.push_back(r[i]);
	}
	sort(cmp.begin(), cmp.end());
	cmp.resize(unique(cmp.begin(),cmp.end())-cmp.begin());
	for (int i = 1; i <= n; i++){
		l[i] = lower_bound(cmp.begin(), cmp.end(), l[i]) - cmp.begin() + 1;
		r[i] = lower_bound(cmp.begin(), cmp.end(), r[i]) - cmp.begin() + 1;
	}
	int m = cmp.size();
	for (int i = 1; i <= n; i++)
		p[i] = i;
	sort(p+1, p+n+1, [](int x, int y){
		if (l[x] != l[y])
			return l[x] < l[y];
		return r[x] > r[y];
	});
	int sz = 0;
	int minr = m + 1;
	for (int i = n; i >= 1; i--){
		int idx = p[i];
		if (r[idx] < minr){
			minr = r[idx];
			lef[++sz] = l[idx], rig[sz] = r[idx];
		}
	}
	memset(nex, -1, sizeof nex);
	for (int i = 1; i <= sz; i++)
		nex[lef[i]][0] = rig[i];
	for (int i = m; i >= 1; i--)
		if (nex[i][0] == -1)
			nex[i][0] = nex[i+1][0];
	for (int i = m; i >= 1; i--)
		for (int l = 1; nex[i][l-1] != -1 and l <= 18; l++)
			nex[i][l] = nex[nex[i][l-1]+1][l-1];
	set<pair<int,bool>> untilnow;
	vector<int> ops;
	for (int i = 1; i <= n; i++){
		auto it = untilnow.lower_bound({l[i],0});
		if (it != untilnow.end() and ((*it).first <= r[i] or (*it).second == 1))
			continue;
		int L, R;
		if (it == untilnow.end())
			R = m;
		else
			R = (*it).first - 1;
		
		if (it == untilnow.begin())
			L = 1;
		else{
			it --;
			L = (*it).first + 1;
		}
		int MIS = getMIS(L,R);
		if (MIS == getMIS(L, l[i]-1) + 1 + getMIS(r[i]+1,R)){
			ops.push_back(i);
			untilnow.insert({l[i],0}), untilnow.insert({r[i],1});
		}
	}
	cout << ops.size() << endl;
	for (auto it : ops)
		cout << it << " ";
	cout << endl;
}
