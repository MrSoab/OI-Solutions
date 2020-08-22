#include "wombats.h"
#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int T = 20;
int M, R, C, H[5000][200], V[5000][200];
int bl[255][200][200], dp[1026][200][200], opt[200][200];

void change(int id, int L, int R, int idx){
	if (idx < L or R <= idx)
		return;
	if (L + 1 == R){
		for (int i = 0; i < C; i++)
			for (int j = 0; j < C; j++)
				dp[id][i][j] = bl[L][i][j];
		return;
	}
	int mid = (L + R) >> 1;
	change(2*id+0, L, mid, idx);
	change(2*id+1, mid, R, idx);
	for (int i = 0; i < C; i++){
		for (int j = C-1; j >= 0; j--){
			int lo = 0, hi = C-1;
			if (j+1 < C)
				hi = opt[i][j+1];
			if (i > 0)
				lo = opt[i-1][j];
			dp[id][i][j] = inf;
			for (int x = lo; x <= hi; x++){
				if (dp[id][i][j] > dp[2*id+0][i][x] + dp[2*id+1][x][j]){
					dp[id][i][j] = dp[2*id+0][i][x] + dp[2*id+1][x][j];
					opt[i][j] = x;
				}
			}
		}
	}
}

void ChangeBlock(int block){
	for (int j = 0; j < C; j++){
		for (int k = 0; k < C; k++)
			bl[block][j][k] = inf;
		bl[block][j][j] = 0;
		for (int k = j+1; k < C; k++)
			bl[block][j][k] = bl[block][j][k-1] + H[T*block][k-1];
		for (int k = j-1; k >= 0; k--)
			bl[block][j][k] = bl[block][j][k+1] + H[T*block][k];
		for (int k = 0; k < C; k++)
			bl[block][j][k] += V[T*block][k];
		for (int i = T*block+1; i < min(R, T*(block+1)); i++){
			for (int k = 1; k < C; k++)
				bl[block][j][k] = min(bl[block][j][k], bl[block][j][k-1] + H[i][k-1]);
			for (int k = C-2; k >= 0; k--)
				bl[block][j][k] = min(bl[block][j][k], bl[block][j][k+1] + H[i][k]);
			for (int k = 0; k < C; k++)
				bl[block][j][k] += V[i][k];
		}
	}
}
 
void init(int r, int c, int h[5000][200], int v[5000][200]){
	M = (r-1)/T + 1;
	R = r, C = c;
	for (int i = 0; i < 5000; i++)
		for (int j = 0; j < 200; j++)
			H[i][j] = h[i][j], V[i][j] = v[i][j];
	for (int i = 0; i < R; i += T)
		ChangeBlock(i/T);
	for (int i = 0; i < M; i++)
		change(1, 0, M, i);	
}
 
void changeH(int P, int Q, int W){
	H[P][Q] = W;
	ChangeBlock(P/T);
	change(1, 0, M, P/T);
}
 
void changeV(int P, int Q, int W){
	V[P][Q] = W;
	ChangeBlock(P/T);
	change(1, 0, M, P/T);
}
 
int escape(int V1, int V2){
	return dp[1][V1][V2];
}
