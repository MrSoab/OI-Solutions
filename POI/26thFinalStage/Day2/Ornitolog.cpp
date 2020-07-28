#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 20;

int a, b;

int main(){
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> a >> b >> k;
	stack<pair<pair<int,int>, pair<int,int>>> f;
	f.push({{n,m},{a,k}});
	int ret = -1;
	while (!f.empty()){
		auto it = f.top();
		int n = it.first.first, m = it.first.second, fi = it.second.first, k = it.second.second;
		if (fi > n+m)
			fi = (fi-1)%(n+m)+1;
		if (fi <= n){
			if (fi+1ll*(k-1)*a <= n){
				f.pop();
				ret = fi + (k-1)*a;
				continue;
			}
			int x = (n-fi)/a + 1;
			if (ret == -1){
				int then = fi + x*a;
				if (then > n+m)
					then -= (n+m);
				else
					then -= x;
				f.push({{n-x,m},{then,k-x}});
				continue;
			}
			f.pop();
			if (ret > n-x)
				ret = ret + x;
			else if (ret >= fi)
				ret = ret + (ret-fi)/(a-1) + 1;
		}
		else{
			if (fi+1ll*(k-1)*b <= n+m){
				f.pop();
				ret = fi + (k-1)*b;
				continue;
			}
			int x = (n+m-fi)/b + 1;
			if (ret == -1){
				int then = fi + x*b;
				then -= (n+m);
				f.push({{n,m-x},{then,k-x}});
				continue;
			}
			f.pop();
			if (ret >= fi)
				ret =  ret + (ret-fi)/(b-1) + 1;
		}
	}
	cout << ret << endl;
}
