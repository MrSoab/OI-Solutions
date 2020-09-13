#include "rail.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 5000 + 10;
int dis[maxn], a[maxn];
int loc[maxn], type[maxn];
 
set<pair<int,int>> S[3];
 
int dist[maxn][maxn];
 
int getDis(int x, int y){
	if (dist[x][y] != 0)
		return dist[x][y];
	int ret = getDistance(x,y);
	dist[x][y] = dist[y][x] = ret;
	assert(ret > 0);
	return ret;
}
 
int getL(int i){
	auto it = (S[1].lower_bound(make_pair(loc[i],-1)));
	it --;
	return (*it).second;
}
 
int getR(int i){
	return (*S[2].lower_bound(make_pair(loc[i],-1))).second;
}
 
int getLocalDis(int x, int y){
	if (loc[x] > loc[y])
		swap(x,y);
	if (type[y] == 1)
		return getLocalDis(x,getR(y)) + loc[getR(y)]-loc[y];
	if (type[x] == 2)
		return getLocalDis(getL(x),y) + loc[x]-loc[getL(x)];
	return loc[y]-loc[x];
}
 
void findLocation(int n, int first, int location[], int stype[]){
	loc[0] = first, type[0] = 1;
	if (n == 1)
		return;
	for (int i = 1; i < n; i++)
		dis[i] = getDis(0,i);
	for (int i = 1; i < n; i++)
		a[i] = i;
	sort(a+1, a+n, [](int a, int b){
		return dis[a] < dis[b];
	});
	S[1].insert({first,0});
	S[2].insert({first+dis[a[1]],a[1]});
	int l = 0, r = loc[a[1]];
	loc[a[1]] = first+dis[a[1]], type[a[1]] = 2;
	for (int _ = 2; _ < n; _++){
		int i = a[_];
		
		loc[i] = loc[beg] + getDis(beg,i), type[i] = 2;
		if (getLocalDis(end,i) != getDis(end,i))
			loc[i] = loc[end] - getDis(end,i), type[i] = 1;
		S[type[i]].insert({loc[i],i});
	}
	for (int i = 0; i < n; i++)
		location[i] = loc[i], stype[i] = type[i];
}
