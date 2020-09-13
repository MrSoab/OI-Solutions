#include "wall.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e6 + 10;

int segmx[4*maxn], segmn[4*maxn], seglz[4*maxn];

void shift(int id){
	if (seglz[id] == -1)
		return;
	segmn[2*id+0] = segmx[2*id+0] = seglz[2*id+0] = seglz[id];
	segmn[2*id+1] = segmx[2*id+1] = seglz[2*id+1] = seglz[id];
	seglz[id] = -1;
}

int get(int id, int L, int R, int idx){
	if (L + 1 == R)
		return segmn[id];
	shift(id);
	int mid = (L + R) >> 1;
	if (idx < mid)
		return get(2*id+0, L, mid, idx);
	return get(2*id+1, mid, R, idx);
}

void add(int id, int L, int R, int l, int r, int x){
	if (r <= L or R <= l or segmn[id] >= x)
		return;
	if (l <= L and R <= r and segmx[id] <= x){
		segmn[id] = segmx[id] = seglz[id] = x;
		return;
	}
	shift(id);
	int mid = (L + R) >> 1;
	add(2*id+0, L, mid, l, r, x);
	add(2*id+1, mid, R, l, r, x);
	segmx[id] = max(segmx[2*id+0], segmx[2*id+1]);
	segmn[id] = min(segmn[2*id+0], segmn[2*id+1]);
}

void del(int id, int L, int R, int l, int r, int x){
	if (r <= L or R <= l or segmx[id] <= x)
		return;
	if (l <= L and R <= r and segmn[id] >= x){
		segmn[id] = segmx[id] = seglz[id] = x;
		return;
	}
	shift(id);
	int mid = (L + R) >> 1;
	del(2*id+0, L, mid, l, r, x);
	del(2*id+1, mid, R, l, r, x);
	segmx[id] = max(segmx[2*id+0], segmx[2*id+1]);
	segmn[id] = min(segmn[2*id+0], segmn[2*id+1]);
}

void buildWall(int n, int k, int op[], int left[], int right[], int height[], int finalHeight[]){
	memset(seglz, -1, sizeof seglz);
	for (int i = 0; i < k; i++){
		if (op[i] == 1)
			add(1, 0, n, left[i], right[i]+1, height[i]);
		else
			del(1, 0, n, left[i], right[i]+1, height[i]);
	}
	for (int i = 0; i < n; i++)
		finalHeight[i] = get(1, 0, n, i);
	return;
}
