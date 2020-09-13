#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
 
const int maxn = 2500 + 10;
const int inf = 1e9;
const int N = 250000 + 10;
 
ll ans[N];
pair<int,int> p[N];
int black[maxn][maxn];
int SouthEast[maxn][maxn], NorthWest[maxn][maxn];
ll dp[maxn][maxn], par[maxn][maxn];
 
void solve(int n){
	memset(black, 0, sizeof black);
	for (int i = 1; i <= n; i++)
		black[p[i].first][p[i].second] ++;
	memset(SouthEast, -1, sizeof SouthEast);
	for (int i = 2500; i >= 1; i--)
		for (int j = 2500; j >= 1; j--)
			SouthEast[i][j] = max({SouthEast[i+1][j], SouthEast[i][j+1], (black[i+1][j+1] > 0 ? i+1 : -1)});
	memset(NorthWest, 63, sizeof NorthWest);
	for (int i = 1; i <= 2500; i++)
		for (int j = 1; j <= 2500; j++)
			NorthWest[i][j] = min({NorthWest[i-1][j], NorthWest[i][j-1], (black[i-1][j-1] > 0 ? j-1 : inf)});
	for (int i = 2500; i >= 1; i--)
		for (int j = 1; j <= 2500; j++)
			par[i][j] = par[i+1][j] + par[i][j-1] - par[i+1][j-1] + black[i][j];
	for (int i = 2500; i >= 1; i--){
		for (int j = 1; j <= 2500; j++){
			dp[i][j] = 0;
			if (SouthEast[i][j] == -1 and NorthWest[i][j] > 2500)
				continue;
			int x = i, y = j;
			if (SouthEast[i][j] != -1)
				x = SouthEast[i][j];
			if (NorthWest[i][j] <= 2500)
				y = NorthWest[i][j];
//			if (black[i][j])
//				cout << x << " " << y << " : " << i << " " << j << " : " << par[i][j] << " - " << par[x][y] << " " << dp[x][y] << endl;
			dp[i][j] = 2LL*(par[i][j]-par[x][y]-black[i][j]+black[x][y]) + dp[x][y] + par[x][y];
		}
	}
	for (int i = 1; i <= n; i++){
		int x = p[i].first, y = p[i].second;
		ans[i] += dp[x][y] + (par[x+1][2500] - par[x+1][y]);
	}
}
 
int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> p[i].first >> p[i].second;
	solve(n);
	for (int i = 1; i <= n; i++)
		p[i].first = 2500 - p[i].first + 1, p[i].second = 2500 - p[i].second + 1;
	solve(n);
	for (int i = 1; i <= n; i++)
		cout << ans[i] << '\n';
}
