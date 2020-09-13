#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 10;
const int mod = 1e9 + 7;

ll h[maxn], w[maxn], pre[maxn], nex[maxn];

int power(int a, int b){
	if (b == 0)
		return 1;
	int ret = power(a,b/2);
	ret = 1LL*ret*ret % mod;
	if (b & 1)
		ret = 1LL*ret*a % mod;
	return ret;
}

ll getsum(int l, int r){
	return w[r] - w[l-1];
}

bool mark[maxn];

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> h[i];
	for (int i = 1; i <= n; i++)
		cin >> w[i], w[i] += w[i-1];
	pre[1] = 0;
	for (int i = 2; i <= n; i++){
		pre[i] = i-1;
		while (pre[i] != 0 and h[pre[i]] > h[i])
			pre[i] = pre[pre[i]];
	}
	nex[n] = n+1;
	for (int i = n-1; i >= 1; i--){
		nex[i] = i+1;
		while (nex[i] != n+1 and h[nex[i]] > h[i])
			nex[i] = nex[nex[i]];
	}
	ll pw2 = power(2, mod-2);
	int answer = 0;
	for (int i = 1; i <= n; i++){
		if (mark[i] == 1)
			continue;
		while (h[nex[i]] == h[i]){
			mark[nex[i]] = 1;
			nex[i] = nex[nex[i]];
		}
		ll W = getsum(pre[i]+1, nex[i]-1), H1 = h[i] - max(h[pre[i]], h[nex[i]]), H2 = max(h[pre[i]],h[nex[i]]);
		W %= mod;
		ll T = 1LL*W*(W+1)%mod*pw2%mod;
		T %= mod;
		ll Q = (1LL*H1*H2%mod + 1LL*H1*(H1+1)%mod*pw2%mod) % mod;
		answer = (answer + 1LL*T*Q%mod) % mod;
	}
	cout << answer << endl;
}
