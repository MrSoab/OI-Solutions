#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1500 + 20;

int a[maxn][maxn], b[maxn][maxn], dp[maxn][maxn], m1[maxn][maxn], row[maxn][maxn], col[maxn][maxn];;
int answer = 0;

void solve(int n, int m, int k){
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			m1[i][j] = max({b[i][j], m1[i-1][j], m1[i][j-1]});
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			row[i][j] = max(row[i][j-1], b[i][j]);
			col[i][j] = max(col[i-1][j], b[i][j]);
		}
	}
	memset(dp, -63, sizeof dp);
	for (int i = 1; i <= n; i++){
		for (int j = 1; j <= m; j++){
			dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
			if (i > k)
				dp[i][j] = max(dp[i][j], row[i][j] + m1[i-k][j]);
			if (j > k)
				dp[i][j] = max(dp[i][j], col[i][j] + m1[i][j-k]);
		}
	}
	for (int i = k+1; i <= n; i++)
		answer = max(answer, dp[i-k][m] + row[i][m]);
}

int tmp[maxn][maxn];

void rotate(int &n, int &m){
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			tmp[j][n-i+1] = b[i][j];
	swap(n,m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			b[i][j] = tmp[i][j];
}

int main(){
	ios_base::sync_with_stdio(false);
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
			cin >> a[i][j], a[i][j] += a[i-1][j] + a[i][j-1] - a[i-1][j-1];
	for (int i = 1; i <= n-k+1; i++)
		for (int j = 1; j <= m-k+1; j++)
			b[i][j] = a[i+k-1][j+k-1] - a[i-1][j+k-1] - a[i+k-1][j-1] + a[i-1][j-1];
	n = n-k+1, m = m-k+1;
	for (int i = 0; i < 4; i++){
		solve(n,m,k);
		rotate(n,m);
	}
	cout << answer << endl;
}
