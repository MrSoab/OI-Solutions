#include "horses.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5 + 10;
const int inf = 1e9 + 1;
const int mod = 1e9 + 7;
int n;
int x[maxn], y[maxn];

struct Node{
	int ans;
	int opt;
	int mulx;
	int mudx;
} seg[4*maxn];

int Mul(int a, int b){
	return min(1LL*inf, 1LL*a*b);
}

int getmul(int id, int L, int R, int l, int r){
	if (r <= L or R <= l)
		return 1;
	if (l <= L and R <= r)
		return seg[id].mulx;
	int mid = (L+R) >> 1;
	return Mul(getmul(2*id+0,L,mid,l,r),getmul(2*id+1,mid,R,l,r));
}

int CmpFunc(int a, int b){
	if (a > b)
		swap(a, b);
	if (y[a] >= 1LL*y[b]*getmul(1, 0, n, a+1, b+1))
		return a;
	return b;
}

Node merge(Node a, Node b){
	if (CmpFunc(a.opt,b.opt) == a.opt){
		a.mulx = Mul(a.mulx, b.mulx);
		a.mudx = 1LL*a.mudx*b.mudx%mod;
		return a;
	}
	b.ans = 1LL*b.ans*a.mudx%mod;
	b.mulx = Mul(a.mulx, b.mulx);
	b.mudx = 1LL*a.mudx*b.mudx%mod;
	return b;
}

void change(int id, int L, int R, int idx){
	if (idx < L or R <= idx)
		return;
	if (L+1 == R){
		seg[id].ans = 1LL*x[L]*y[L]%mod, seg[id].opt = L, seg[id].mulx = seg[id].mudx = x[L];
		return;
	}
	int mid = (L + R) >> 1;
	change(2*id+0, L, mid, idx);
	change(2*id+1, mid, R, idx);
	seg[id] = merge(seg[2*id+0],seg[2*id+1]);
}

void build(int id, int L, int R){
	if (L+1 == R){
		seg[id].ans = 1LL*x[L]*y[L]%mod, seg[id].opt = L, seg[id].mulx = seg[id].mudx = x[L];
		return;
	}
	int mid = (L + R) >> 1;
	build(2*id+0, L, mid);
	build(2*id+1, mid, R);
	seg[id] = merge(seg[2*id+0],seg[2*id+1]);
}

int init(int N, int X[], int Y[]){
	n = N;
	for (int i = 0; i < n; i++)
		x[i] = X[i], y[i] = Y[i];
	build(1, 0, n);
	return seg[1].ans;
}

int updateX(int pos, int val){
	x[pos] = val;
	change(1, 0, n, pos);
	return seg[1].ans;
}

int updateY(int pos, int val){
	y[pos] = val;
	change(1, 0, n, pos);
	return seg[1].ans;
}
