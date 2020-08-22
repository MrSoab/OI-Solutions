#include "grader.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 10;

int me, newint, a[maxn], command = 1;
int par[maxn][20], h[maxn];
char cp[maxn];

void Init(){
	me = 0;
	newint = 1;
	memset(par, -1, sizeof par);
}

void TypeLetter(char L){
	int now = newint++;
	a[command++] = now;
	par[now][0] = me, h[now] = h[me]+1;
	cp[now] = L;
	for (int i = 1; par[now][i-1] != -1 and i < 20; i++)
		par[now][i] = par[par[now][i-1]][i-1];
	me = now;
}

void UndoCommands(int U){
	assert(U < command);
	a[command] = a[command-U-1], me = a[command++];
}

char GetLetter(int P){
	int now = me;
	int up = h[now]-P-1;
	for (int i = 0; i < 20; i++)
		if (up & (1 << i))
			now = par[now][i];
	return cp[now];
}
