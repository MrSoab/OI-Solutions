#include "artclass.h"
#include <bits/stdc++.h>
using namespace std;
int maxn = 500 + 10;

int cnt[256][256][256];

int style(int H, int W, int R[500][500], int G[500][500], int B[500][500]) {
	for (int i = 0; i < H; i++)
		for (int j = 0; j < W; j++)
			cnt[R[i][j]][G[i][j]][B[i][j]] ++;
	int Green = 0, Yellow = 0;
	for (int i = 0; i < 255; i++)
		for (int j = 0; j < 255; j++)
			for (int k = 0; k < 255; k++){
				if (cnt[i][j][k] >= 1 and max({i,j,k}) == j and max({i,j,k}) - min({i,j,k}) >= 30 and j > i)
					Green += cnt[i][j][k];
				if (cnt[i][j][k] >= 1 and max({i,j,k}) == i and max({i,j,k}) - min({i,j,j}) >= 30 and i - j <= 50)
					Yellow += cnt[i][j][k];
			}
	int diffcol = 0;
	for (int i = 4; i < H; i++)
		for (int j = 4; j < W; j++){
			if (abs(R[i][j]-R[i][j-4]) + abs(G[i][j]-G[i][j-4]) + abs(B[i][j]-B[i][j-4]) >= 300)
				diffcol ++;
			if (abs(R[i][j]-R[i-4][j]) + abs(G[i][j]-G[i-4][j]) + abs(B[i][j]-B[i-4][j]) >= 300)
				diffcol ++;
		}
	int cnt = 0, mnm = W/2;
	for (int i = 0; i < H; i++){
		int ted = 0;
		for (int j = 1; j < W; j++){
			if (abs(R[i][j]-R[i][j-1]) + abs(G[i][j]-G[i][j-1]) + abs(B[i][j]-B[i][j-1]) >= 110)
				ted ++;
		}
		if (ted >= W/8)
			cnt ++;
	}
	if (cnt >= H/2)
		return 3;	
	if (Green > 2000 and (Green+Yellow) > H*W/10 and diffcol < 10000 and diffcol > 100)
		return 2;
	if (diffcol > 2000)
		return 1;
	return 4;
}
