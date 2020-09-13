#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> point;
const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;
const int N = 1e7;
int SweepX;

struct Segment{
	int x1, y1;
	int x2, y2;
	long double shib;
	Segment(int x1_ = 0, int y1_ = 0, int x2_ = 0, int y2_ = 0){
		x1 = x1_, y1 = y1_, x2 = x2_, y2 = y2_;
		if (x1 > x2 or (x1 == x2 and y1 > y2))
			swap(x1,x2), swap(y1,y2);
		shib = 1.*(y2-y1)/(x2-x1);
	}
	long double getY(int x)const{
		assert(x1 <= x and x <= x2);
		if (x1 == x2)
			return y2;
		return y1 + shib*(x-x1);
	}
	bool operator < (const Segment &other)const{
		return this->getY(SweepX) < other.getY(SweepX);
	}
} seg[maxn];

map<point,point> mp;

int main(){
	ios_base::sync_with_stdio(false);
	int n;
	cin >> n;
	vector<pair<point,int>> p;
	for (int i = 1; i <= n; i++){
		int x1,y1,x2,y2;
		cin >> x1>>y1>>x2>>y2;
		if (x1 > x2 or (x1 == x2 and y1 > y2))
			swap(x1,x2), swap(y1,y2);
		p.push_back({{x1,y1}, -i});
		p.push_back({{x2,y2}, i});
		seg[i] = Segment(x1,y1,x2,y2);
	}
	sort(p.begin(),p.end());
	set<Segment> S;
	SweepX = -N-1;
	for (int it = 0; it < 2*n; it++){
		if (SweepX != p[it].first.first){
			for (int j = it-1; p[j].first.first == SweepX and j >= 0; j--)
				if (p[j].second > 0)
					S.erase(seg[p[j].second]);
			SweepX = p[it].first.first;
		}
		if (p[it].second > 0)
			continue;
		if (it != 0){
			point me = p[it].first;
			Segment now = Segment(me.first, me.second, me.first, me.second);
			Segment ub = Segment(-N, N, N, N), lb = Segment(-N, -N, N, -N);
			auto Sit = S.lower_bound(now);
			if (Sit != S.end())
				ub = (*Sit);
			if (Sit != S.begin()){
				Sit --;
				lb = (*Sit);
			}
			bool found = 0;
			for (int j = it-1; j >= 0; j--){
				if (ub.getY(p[j].first.first) >= p[j].first.second and lb.getY(p[j].first.first) <= p[j].first.second){
					cout << me.first << " " << me.second << " " << p[j].first.first << " " << p[j].first.second << '\n';
					found = 1;
					break;
				}
			}
			assert(found);
		}
		mp[p[it].first] = p[it].first;
		S.insert(seg[-p[it].second]);
	}
}
