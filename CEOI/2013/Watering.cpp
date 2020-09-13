#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;
const int maxn = 600 + 10;

int adjx[] = {0,-1,0,+1};
int adjy[] = {-1,0,+1,0};
vector<int> v[maxn][maxn];
bool mark[maxn][maxn];
int n, m;
int cnt[maxn][maxn];

bool valid(int x, int y){
	return x >= 0 and x < 5*n and y >= 0 and y < 5*m;
}

string s[maxn];

struct Block{
	int x1, y1, x2, y2, x3, y3;
	bool isin;
	int cost;
	Block(int x1_, int y1_, int x2_, int y2_, int x3_, int y3_){
		x1 = x1_, y1 = y1_, x2 = x2_, y2 = y2_, x3 = x3_, y3 = y3_;
		isin = false;
		cost = (max({x1,x2,x3})/5 != min({x1,x2,x3})/5) + (max({y1,y2,y3})/5 != min({y1,y2,y3})/5);
	}
	Block(){
	}
	void turnon(){
		assert(!mark[x1][y1] and !mark[x2][y2] and !mark[x3][y3]);
		mark[x1][y1] = mark[x2][y2] = mark[x3][y3] = 1;
		isin = true;
		bool cam[26];
		for (int i = 0; i < 26; i++)
			cam[i] = 1;
		for (int z = 0; z < 4; z++){
			int x = x1+adjx[z], y = y1+adjy[z];
			if (valid(x,y) and isalpha(s[x][y]))
				cam[(int)(s[x][y]-'a')] = 0;
			x = x2+adjx[z], y = y2+adjy[z];
			if (valid(x,y) and isalpha(s[x][y]))
				cam[(int)(s[x][y]-'a')] = 0;
			x = x3+adjx[z], y = y3+adjy[z];
			if (valid(x,y) and isalpha(s[x][y]))
				cam[(int)(s[x][y]-'a')] = 0;
		}
		char c = 'a';
		for (int i = 0; i < 26; i++){
			if (cam[i]){
				c = (char)(i+'a');
				break;
			}
		}
		s[x1][y1] = s[x2][y2] = s[x3][y3] = c;
	}
	void turnoff(){
		assert(mark[x1][y1] and mark[x2][y2] and mark[x3][y3]);
		mark[x1][y1] = mark[x2][y2] = mark[x3][y3] = 0;
		s[x1][y1] = s[x2][y2] = s[x3][y3] = '.';
		isin = false;
	}
	bool operator < (const Block &other)const{
		return cost < other.cost;
	}
} b[6*maxn*maxn];

int newint;

int solve(){
	int ret = 0;
	for (int i = 0; i < newint; i++){
		if (b[i].cost > 0)
			break;
		int sum = 0;
		set<int> nom;
		for (auto j : v[b[i].x1][b[i].y1])
			if (b[j].isin)
				nom.insert(j);
		for (auto j : v[b[i].x2][b[i].y2])
			if (b[j].isin)
				nom.insert(j);
		for (auto j : v[b[i].x3][b[i].y3])
			if (b[j].isin)
				nom.insert(j);
		if (nom.size() > 1)
			continue;
		if (nom.empty())
			b[i].turnon(), ret++;
		else{
			int u = *nom.begin();
			if (rng() % 2 == 0){
				b[u].turnoff();
				b[i].turnon();
			}
		}
	}
	return ret;
}

int a[maxn][maxn];

int main(){
	cin >> n >> m;
	int idx = 0;
	for (int i = 0; i < 6*n-1; i++){
		string t;
		cin >> t;
		if (i % 6 != 5){
			for (int j = 0; j < 6*m-1; j++)
				if (t[j] != '|')
					s[idx] += t[j];
			s[idx] += '#';
			s[idx] += '#';
			s[idx] += '#';
			idx ++;

		}
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			for (int x = 5*i; x < 5*i+5; x++)
				for (int y = 5*j; y < 5*j+5; y++)
					if (s[x][y] == '.')
						a[i][j] ++;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			if (a[i][j] % 3 == 0)
				continue;
			if (j < m-1){
				if (a[i][j] % 3 == 2)
					for (int x = 5*i; x < 5*i+5; x++)
						for (int ny = 5*j+4, by = 5*j+5; ny >= 5*j; ny--,by++)
							swap(s[x][ny],s[x][by]);
				
				int x = 5*i+4, y = 5*j+4;
				if (s[x][y] == '.' and s[x][y+1] == '.'){
					s[x][y] = s[x][y+1] = 'z';
					if (s[x][y+2] == '.')
						s[x][y+2] = 'z';
					else
						s[x-1][y+1] = 'z';
				}
				else if (s[x][y] == '.' and s[x][y+1] == '#'){
					s[x-1][y+1] = s[x-2][y+1] = 'z';
					if (s[x-1][y] == '.' and s[x][y-1] == '.')
						s[x-1][y] = 'z';
					else
						s[x-2][y] = 'z';
				}
				else if (s[x][y] == '#' and s[x][y+1] == '.'){
					if (s[x-1][y+1] == '.')
						s[x-1][y] = s[x-1][y+1] = s[x][y+1] = 'z';
					else
						s[x-2][y] = s[x-2][y+1] = s[x-2][y+2] = 'z';
				}
				else{
					s[x-1][y] = s[x-1][y+1] = s[x-2][y+1] = 'z';
				}
				if (a[i][j] % 3 == 2){
					for (int x = 5*i; x < 5*i+5; x++)
						for (int ny = 5*j+4, by = 5*j+5; ny >= 5*j; ny--,by++)
							swap(s[x][ny],s[x][by]);
					a[i][j+1] --;
				}
				else
					a[i][j+1] -= 2;
			}
			else{
				if (a[i][j] % 3 == 2)
					for (int nx = 5*i+4, bx = 5*i+5; nx >= 5*i; nx--,bx++)
						for (int y = 5*j; y < 5*j+5; y++)	
							swap(s[nx][y],s[bx][y]);
				int x = 5*i+4, y = 5*j+4;
				if (s[x][y] == '.' and s[x+1][y] == '.'){
					s[x][y] = s[x+1][y] = 'z';
					if (s[x+1][y-1] == '.')
						s[x+1][y-1] = 'z';
					else
						s[x+2][y] = 'z';
				}
				else if (s[x][y] == '.' and s[x+1][y] == '#'){
					s[x+1][y-1] = s[x+1][y-2] = 'z';
					if (s[x][y-1] == '.')
						s[x][y-1] = 'z';
					else
						s[x][y-2] = 'z';
				}
				else if (s[x][y] == '#' and s[x+1][y] == '.'){
					if (s[x+1][y-1] == '.')
						s[x][y-1] = s[x+1][y-1] = s[x+1][y] = 'z';
					else
						s[x][y-2] = s[x+1][y-2] = s[x+2][y-2] = 'z';
				}
				else
					s[x][y-1] = s[x+1][y-1] = s[x+1][y-1] = 'z';
				if (a[i][j] % 3 == 2){
					for (int nx = 5*i+4, bx = 5*i+5; nx >= 5*i; nx--,bx++)
						for (int y = 5*j; y < 5*j+5; y++)	
							swap(s[nx][y],s[bx][y]);
					a[i+1][j] --;
				}
				else
					a[i+1][j] -= 2;

			}
		}
	}
	int score = 0;
	for (int i = 0; i < 5*n; i++){
		for (int j = 0; j < 5*m; j++){
			if (s[i][j] != '.')
				continue;
			score ++;
			for (int z = 0; z < 4; z++){
				for (int p = z+1; p < 4; p++){
					int bx = i+adjx[z], by = j+adjy[z];
					int nx = i+adjx[p], ny = j+adjy[p];
					if (!valid(nx,ny) or !valid(bx,by) or s[nx][ny] != '.' or s[bx][by] != '.')
						continue;
					b[newint++] = Block(i,j,bx,by,nx,ny);
				
				}
			}
		}
	}
	sort(b, b+newint);
	for (int x = 0; x < newint; x++){
		int i = b[x].x1, j = b[x].y1, bx = b[x].x2, by = b[x].y2, nx = b[x].x3, ny = b[x].y3;
		v[i][j].push_back(x), v[bx][by].push_back(x), v[nx][ny].push_back(x);
	}
	assert(score%3 == 0);
	score /= 3;
	int now = 0, _ = 0;
	while (_ < 300 and now < score){
		int k = solve();
		now += k;
		if (k > 0 or _ % 100 == 0)
			cerr << "# " << _ << " - " << k << " - " << now << " " << score << endl;
		_++;
	}
	int Fault = n*m;
	idx = 0;
	for (int i = 0; i < n; i++){
		for (int j = 0; j < m; j++){
			bool found = 0;
			for (int x = 5*i; x < 5*i+5; x++)
				for (int y = 5*j; y < 5*j+5; y++)
					if (s[x][y] == '.')
						found = 1;
			if (found){
				cout << i << " " << j << endl;
				for (int x = 5*(i-1); x < 5*i+10; x++){
					if (x % 5 == 0)
						cout << endl;
					for (int y = 5*(j-1); y < 5*j+10; y++){
						if (y%5 == 0)
							cout << ' ';
						cout << s[x][y];
					}
					cout << endl;
				}
				cerr << "Wrong " << endl;
				return 0;
			}
		}
	}
	for (int i = 0; i < 6*n-1; i++){
		if (i % 6 == 5){
			int cnt = 0;
			for (int j = 0; j < 6*m-1; j++){
				if (j % 6 == 5)
					cout << '+';
				else if (s[idx-1][cnt] != s[idx][cnt])
					cout << '-';
				else
					cout << '_', Fault --;
				if (j % 6 != 5)
					cnt ++;
			}
			cout << '\n';
			continue;
		}
		int cnt = 0;
		for (int j = 0; j < 6*m-1; j++){
			if (j % 6 != 5)
				cout << s[idx][cnt++];
			else if (s[idx][cnt-1] == s[idx][cnt])
				cout << '_', Fault --;
			else
				cout << '|';
		}
		cout << '\n';
		idx ++;
	}
	assert(Fault >= 0);
}
