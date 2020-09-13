#include "rainbow.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
map<char,int> adjr = {{'N', -1}, {'S', 1}};
map<char,int> adjc = {{'E', 1}, {'W', -1}};
set<pair<int,int>> Snake;
int R, C;
pair<int,int> Snakex, Snakey;

struct Segment2D{
	vector<int> fen[maxn], fex[maxn];
	vector<pair<int,int>> Q;
	int get(int X, int Y){
		int ret = 0;
		for (int x = X; x; x -= x & -x){
			int y = upper_bound(fex[x].begin(),fex[x].end(),Y)-fex[x].begin();
			for (; y; y -= y & -y)
				ret += fen[x][y-1];
		}
		return ret;
	}
	int get(int x1, int x2, int y1, int y2){
		if (x2 < x1 or y2 < y1)
			return 0;
		return get(x2, y2) - get(x2, y1-1) - get(x1-1, y2) + get(x1-1,y1-1);
	}
	void addreal(int X, int Y){
		for (int x = X; x < maxn; x += x & -x){
			int y = lower_bound(fex[x].begin(),fex[x].end(),Y)-fex[x].begin()+1;
			for (; y <= fen[x].size(); y += y & -y)
				fen[x][y-1] ++;
		}
	}
	void add(int X, int Y){
		for (int x = X; x < maxn; x += x & -x)
			fex[x].push_back(Y);
		Q.push_back({X,Y});
	}
	void build(){
		for (int i = 1; i < maxn; i++){
			sort(fex[i].begin(),fex[i].end());
			fex[i].resize(unique(fex[i].begin(),fex[i].end())-fex[i].begin());
			fen[i].resize(fex[i].size());
		}
		sort(Q.begin(),Q.end());
		Q.resize(unique(Q.begin(),Q.end())-Q.begin());
		for (auto it : Q)
			addreal(it.first, it.second);
	}
} seg[6];

void init(int r, int c, int sr, int sc, int M, char *S){
	R = r, C = c;
	Snake.insert({sr,sc});
	Snakex = {sr,sr};
	Snakey = {sc,sc};
	seg[0].add(sr,sc);
	for (int i = 0; i < M; i++){
		sr += adjr[S[i]], sc += adjc[S[i]];
		Snake.insert({sr,sc});
		seg[0].add(sr,sc);
		Snakex.first = min(Snakex.first,sr), Snakex.second = max(Snakex.second,sr);
		Snakey.first = min(Snakey.first,sc), Snakey.second = max(Snakey.second,sc);
	}
	for (auto it : Snake){
		int x = it.first, y = it.second;
		if (Snake.count({x-1,y}))
			seg[1].add(x,y);
		if (Snake.count({x,y-1}))
			seg[2].add(x,y);
		if (Snake.count({x,y-1}) and Snake.count({x-1,y}) and Snake.count({x-1,y-1}))
			seg[3].add(x,y);
		if (Snake.count({x-1,y-1}) and !Snake.count({x-1,y}) and !Snake.count({x,y-1}))
			seg[4].add(x,y);
		if (Snake.count({x-1,y+1}) and !Snake.count({x-1,y}) and !Snake.count({x,y+1}))
			seg[5].add(x,y+1);
	}
	for (int i = 0; i < 6; i++)
		seg[i].build();
}

int colour(int x1, int y1, int x2, int y2){
	int v = seg[0].get(x1, x2, y1, y2) + 2*(x2-x1+y2-y1+4);
	int e = seg[1].get(x1+1, x2, y1, y2) + seg[2].get(x1,x2, y1+1,y2)
		  + seg[0].get(x1, x1, y1, y2) + seg[0].get(x2, x2, y1, y2) + seg[0].get(x1, x2, y1, y1) + seg[0].get(x1, x2, y2, y2)
		  + 2*(x2-x1+y2-y1+4) + seg[4].get(x1+1, x2, y1+1, y2) + seg[5].get(x1+1, x2, y1+1, y2);
	int c = 1 + (Snakex.first > x1 and Snakex.second < x2 and Snakey.first > y1 and Snakey.second < y2);
	int f = seg[3].get(x1+1, x2, y1+1, y2) + seg[1].get(x1+1, x2, y1, y1) + seg[1].get(x1+1, x2, y2, y2)
		  + seg[2].get(x1, x1, y1+1, y2) + seg[2].get(x2, x2, y1+1, y2) + Snake.count({x1,y1}) + Snake.count({x1,y2})
		  + Snake.count({x2,y1}) + Snake.count({x2,y2});
	return c + e - v - f;
}
