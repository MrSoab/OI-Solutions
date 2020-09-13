#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
const int maxn = 500 + 10;

int n, m;
string s[maxn];
int x[maxn][maxn], y[maxn][maxn], p[maxn][maxn];
int cnt[maxn][maxn];
vector<int> v[maxn][maxn];

int adjx[] = {-1,-1,-1,0};
int adjy[] = {-1,0,+1,+1};
char adjc[] = {(char)(92), '|', '/', '-'};
int mark[maxn][maxn];

struct Block{
	int x1, y1, x2, y2, x3, y3;
	char c;
	int isin;
	int Danger;
	Block(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_, char c_){
		x1 = x1_, y1 = y1_, x2 = x2_, y2 = y2_, x3 = x3_, y3 = y3_, c = c_;
		Danger = cnt[x1][y1] + cnt[x2][y2] + cnt[x3][y3];
		isin = 0;
	}
	Block(){
	}
	void turnon(){
		mark[x1][y1] = mark[x2][y2] = mark[x3][y3] = 1;
		isin = 1;
		s[x2][y2] = c;
	}
	void turnoff(){
		mark[x1][y1] = mark[x2][y2] = mark[x3][y3] = 0;
		isin = 0;
		s[x2][y2] = 'W';
	}
	bool operator < (const Block &other)const{
		return Danger < other.Danger;
	}
} b[maxn*maxn];

bool valid(int x, int y){
	return x >= 0 and x < n and y >= 0 and y < m;
}

int sz = 0;

int solve(int x){
	int ret = 0;
	for (int i = 0; i < sz; i++){
		if (b[i].isin)
			continue;
		int now = 0;
		for (auto j : v[b[i].x1][b[i].y1])
			now += b[j].isin;
		for (auto j : v[b[i].x2][b[i].y2])
			now += b[j].isin;
		for (auto j : v[b[i].x3][b[i].y3])
			now += b[j].isin;
		if (now == 0){
			ret ++;
			b[i].turnon();
			continue;
		}
	}
	for (int i = 0; i < sz; i++){
		if (b[i].isin)
			continue;
		int now = 0;
		for (auto j : v[b[i].x1][b[i].y1])
			now += b[j].isin;
		for (auto j : v[b[i].x2][b[i].y2])
			now += b[j].isin;
		for (auto j : v[b[i].x3][b[i].y3])
			now += b[j].isin;
		if (now == 0){
			ret ++;
			b[i].turnon();
			continue;
		}
		else if (now == 1 and rng() % 5 == 0){
			for (auto j : v[b[i].x1][b[i].y1])
				if (b[j].isin)
					b[j].turnoff();
			for (auto j : v[b[i].x2][b[i].y2])
				if (b[j].isin)
					b[j].turnoff();
			for (auto j : v[b[i].x3][b[i].y3])
				if (b[j].isin)
					b[j].turnoff();
			b[i].turnon();
		}
	}
	return ret;
}

void findblock(){
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (s[i][j] != 'W')
				continue;
			for (int z = 0; z < 4; z++){
				if (valid(i+adjx[z],j+adjy[z]) and valid(i-adjx[z],j-adjy[z])){
					int nx = i+adjx[z], ny = j+adjy[z];
					int bx = i-adjx[z], by = j-adjy[z];
					if ((s[nx][ny]=='P' and s[bx][by]=='G') or (s[nx][ny]=='G' and s[bx][by]=='P'))
						cnt[i][j] ++, cnt[nx][ny] ++, cnt[bx][by] ++;
				}
			}
		}
	}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (s[i][j] != 'W')
				continue;
			for (int z = 0; z < 4; z++){
				if (valid(i+adjx[z],j+adjy[z]) and valid(i-adjx[z],j-adjy[z])){
					int nx = i+adjx[z], ny = j+adjy[z];
					int bx = i-adjx[z], by = j-adjy[z];
					if ((s[nx][ny]=='P' and s[bx][by]=='G') or (s[nx][ny]=='G' and s[bx][by]=='P')){
						b[sz] = Block(bx,by,i,j,nx,ny,adjc[z]);
						sz ++;
					}
				}
			}
		}
	}
}

int main(){
	int needscore = 48620;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> s[i];
	findblock();
	sort(b, b+sz);
	for (int _ = 0; _ < sz; _++){
		int i = b[_].x1, j = b[_].y1, bx = b[_].x2, by = b[_].y2, nx = b[_].x3, ny = b[_].y3;
		v[i][j].push_back(_), v[bx][by].push_back(_), v[nx][ny].push_back(_);
	}
	int score = 0;
	int _ = 0;
	while (score < needscore){
		int k = solve(_);
		score += k;
		if (k > 0 or _ % 100 == 0)
			cerr << _ << " : " << k << " - " << score << endl;
		_++;
	}
	cerr << score << endl;
	for (int i = 0; i < n; i++)
		cout << s[i] << '\n';
}
