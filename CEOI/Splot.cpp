#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
typedef long long ll;

const int maxn = 2e5 + 10;
const int inf = 1e9;

vector<int> t[maxn];
char src[maxn], snk[maxn];
int dp1[maxn], pd[maxn], dp2[maxn], dp3[maxn];
char type[maxn];

void print(int v, string s){
	if (t[v].empty()){
		if (pd[v] == 0 and (s == "free" or s == "pd"))
			cout << 'o';
		else
			cout << 'x';
		return;
	}
	int lc = t[v][0], rc = t[v][1];
	if (type[v] == 'S'){
		cout << "S";
		if (s == "dp1"){
			if (dp1[v] == pd[lc]+dp1[rc])
				print(lc,"pd"), print(rc,"dp1");
			else
				print(lc,"dp1"), print(rc,"free");
		}
		else if (s == "dp2"){
			if (dp2[v] == pd[rc]+dp2[lc])
				print(lc,"dp2"), print(rc,"pd");
			else
				print(lc,"free"), print(rc,"dp2");
		}
		else if (s == "dp3"){
			if (dp3[v] == dp1[lc]+dp2[rc])
				print(lc,"dp1"), print(rc,"dp2");
			else if (dp3[v] == pd[lc]+dp3[rc])
				print(lc,"pd"), print(rc,"dp3");
			else
				print(lc,"dp3"), print(rc,"pd");
		}
		else
			print(lc,s), print(rc,s);
		cout << "#";
		return;
	}
	if (src[v] == 'o'){
		if (snk[v] == 'o'){
			if (s == "dp1"){
				if (dp1[v] == dp1[lc]+dp1[rc])
					cout << "Po|", print(lc,"dp1"), print(rc,"dp1"), cout << "|o#";
				else if (dp1[v] == dp3[lc]+pd[rc])
					cout << "Po|", print(lc,"dp3"), print(rc,"pd"), cout << "|o#";
				else if (dp1[v] == pd[lc]+dp3[rc])
					cout << "Po|", print(lc,"pd"), print(rc,"dp3"), cout << "|o#";
				else if (dp1[v] == pd[lc]+dp1[rc]+1)
					cout << "Po|", print(lc,"pd"), print(rc,"dp1"), cout << "|x#";
				else
					cout << "Po|", print(lc,"dp1"), print(rc,"pd"), cout << "|x#";
			}
			else if (s == "dp2"){
				if (dp2[v] == dp2[lc]+dp2[rc])
					cout << "Po|", print(lc,"dp2"), print(rc,"dp2"), cout << "|o#";
				else if (dp2[v] == dp3[lc]+pd[rc])
					cout << "Po|", print(lc,"dp3"), print(rc,"pd"), cout << "|o#";
				else if (dp2[v] == pd[lc]+dp3[rc])
					cout << "Po|", print(lc,"pd"), print(rc,"dp3"), cout << "|o#";
				else if (dp2[v] == pd[lc]+dp2[rc]+1)
					cout << "Px|", print(lc,"pd"), print(rc,"dp2"), cout << "|o#";
				else
					cout << "Px|", print(lc,"dp2"), print(rc,"pd"), cout << "|o#";	
			}
			else if (s == "dp3"){
				if (dp3[v] == dp3[lc]+dp3[rc])
					cout << "Po|", print(lc,"dp3"), print(rc,"dp3"), cout << "|o#";
				else if (dp3[v] == dp1[lc]+dp1[rc]+1)
					cout << "Po|", print(lc,"dp1"), print(rc,"dp1"), cout << "|x#";
				else
					cout << "Px|", print(lc,"dp2"), print(rc,"dp2"), cout << "|o#";
			}
			else if (s == "pd"){
				if (pd[v] == pd[lc]+dp3[rc])
					cout << "Po|", print(lc,"pd"), print(rc,"dp3"), cout << "|o#";
				else
					cout << "Po|", print(lc,"dp3"), print(rc,"pd"), cout << "|o#";
			}
			else
				cout << "Po|", print(lc,"free"), print(rc,"free"), cout << "|o#";
		}
		else{
			if (s == "dp1"){
				if (dp1[v] == pd[lc]+dp1[rc]+1)
					cout << "Po|", print(lc,"pd"), print(rc,"dp1"), cout << "|x#";
				else
					cout << "Po|", print(lc,"dp1"), print(rc,"pd"), cout << "|x#";
			}
			else if (s == "dp2")
				cout << "Po|", print(lc,"free"), print(rc,"free"), cout << "|x#";
			else
				cout << "Po|", print(lc,"dp1"), print(rc,"dp1"), cout << "|x#";
		}
	}
	else{
		if (snk[v] == 'o'){
			if (s == "dp1")
				cout << "Px|", print(lc,"free"), print(rc,"free"), cout << "|o#";
			else if (s == "dp2"){
				if (dp2[v] == pd[lc]+dp2[rc]+1)
					cout << "Px|", print(lc,"pd"), print(rc,"dp2"), cout << "|o#";
				else
					cout << "Px|", print(lc,"dp2"), print(rc,"pd"), cout << "|o#";
			}
			else
				cout << "Px|", print(lc,"dp2"), print(rc,"dp2"), cout << "|o#";
		}
		else{
			cout << "Px|", print(lc,"free"), print(rc,"free"), cout << "|x#";
			if (s != "dp3")
				cout << s << endl;
			assert(s == "dp3");
		}
	}
}

int sz[maxn];

void dfs(int v){
	if (t[v].empty()){
		if (pd[v] != 0)
			sz[v] = 1;
		return;
	}
	int lc = t[v][0], rc = t[v][1];
	dfs(lc);
	dfs(rc);
	sz[v] = sz[lc] + sz[rc];
	if (type[v] == 'S'){
		dp1[v] = pd[lc] + dp1[rc];
		if (sz[rc] == 0)
			dp1[v] = max(dp1[v], dp1[lc]);
		dp2[v] = pd[rc] + dp2[lc];
		if (sz[lc] == 0)
			dp2[v] = max(dp2[v], dp2[rc]);
		dp3[v] = max({dp1[lc] + dp2[rc], pd[lc] + dp3[rc], dp3[lc] + pd[rc]});
		pd[v] = pd[lc] + pd[rc];
	}
	else{
		sz[v] += (src[v] == 'x') + (snk[v] == 'x');
		if (src[v] == 'o'){
			if (snk[v] == 'o'){
				dp1[v] = max({dp1[lc]+dp1[rc], dp3[lc]+pd[rc], pd[lc]+dp3[rc], pd[lc]+dp1[rc]+1, dp1[lc]+pd[rc]+1});
				dp2[v] = max({dp2[lc]+dp2[rc], dp3[lc]+pd[rc], pd[lc]+dp3[rc], pd[lc]+dp2[rc]+1, dp2[lc]+pd[rc]+1});
				dp3[v] = max({dp3[lc] + dp3[rc], dp1[lc]+dp1[rc]+1, dp2[lc]+dp2[rc]+1});
				pd[v] = max(pd[lc] + dp3[rc], dp3[lc] + pd[rc]);
			}
			else{
				dp1[v] = max(pd[lc]+dp1[rc]+1, dp1[lc]+pd[rc]+1);
				if (sz[v] == 1)
					dp2[v] = 1;
				else
					dp2[v] = -maxn;
				dp3[v] = dp1[lc] + dp1[rc] + 1;
			}
		}
		else{
			if (snk[v] == 'o'){
				if (sz[v] == 1)
					dp1[v] = 1;
				else
					dp1[v] = -maxn;
				dp2[v] = max(pd[lc] + dp2[rc] + 1, dp2[lc] + pd[rc] + 1);
				dp3[v] = dp2[lc] + dp2[rc] + 1;
			}
			else{
				dp1[v] = dp2[v] = -maxn;
				dp3[v] = 2;
			}
		}
	}
}
 
int main(){
	ios_base::sync_with_stdio(false);
	string park;
	cin >> park;
	if (park.size() == 1)
		return cout << 1 << endl << "x" << endl, 0;
	stack<int> s;
	int newint = 0;
	for (int i = 0; i < maxn; i++)
		pd[i] = -park.size();
	int root = 0;
	for (int i = 0; i < park.size(); i++){
		if (park[i] == 'S'){
			type[newint] = 'S';
			s.push(newint++);
		}
		if (park[i] == 'P'){
			type[newint] = 'P';
			s.push(newint++);
			src[newint-1] = park[i+1];
			i += 2;
			continue;
		}
		if (park[i] == '#'){
			int me = s.top();
			s.pop();
			if (me != 0)
				t[s.top()].push_back(me);
		}
		if (park[i] == '|'){
			i ++;
			snk[s.top()] = park[i];
			int me = s.top();
			continue;
		}
		if (park[i] == 'x' or park[i] == 'o'){
			t[s.top()].push_back(newint++);
			dp1[newint-1] = dp2[newint-1] = dp3[newint-1] = 1;
			if (park[i] == 'o')
				pd[newint-1] = 0;
		}
	}
	dfs(0);
	cout << dp1[0] << endl;
	print(0, "dp1");
	cout << endl;
}
