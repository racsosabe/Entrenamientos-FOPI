#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;
const long long inf = 1e18;

int n;
int m;
int x;
set<int> valid;
long long memo[N];

void update(int t, int l, int r){
	if(t == 1){
		set<int>::iterator it = valid.lower_bound(l);
		vector< pair<int, long long> > transitions;
		while(it != valid.end() and *it <= r){
			transitions.emplace_back(make_pair(*it, memo[*it]));
			memo[*it] = inf;
			it++;
		}
		for(auto e : transitions){
			valid.erase(e.first);
			memo[l - 1] = min(memo[l - 1], e.second + abs(l - 1 - e.first));
			memo[r + 1] = min(memo[r + 1], e.second + abs(r + 1 - e.first));
			if(l - 1 >= 1) valid.emplace(l - 1);
			if(r + 1 <= n) valid.emplace(r + 1);
		}
	}
	else{
		set<int>::iterator it = valid.begin();
		vector< pair<int, long long> > transitions;
		while(it != valid.end() and *it < l){
			transitions.emplace_back(make_pair(*it, memo[*it]));
			memo[*it] = inf;
			it++;
		}
		it = valid.upper_bound(r);
		while(it != valid.end()){
			transitions.emplace_back(make_pair(*it, memo[*it]));
			memo[*it] = inf;
			it++;
		}
		for(auto e : transitions){
			valid.erase(e.first);
			memo[l] = min(memo[l], e.second + abs(l - e.first));
			memo[r] = min(memo[r], e.second + abs(r - e.first));
			valid.emplace(l);
			valid.emplace(r);
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &m, &x);
	for(int i = 1; i <= n; i++) memo[i] = inf;
	memo[x] = 0;
	valid.emplace(x);
	for(int i = 1; i <= m; i++){
		int l, r, op;
		scanf("%d %d %d", &op, &l, &r);
		update(op, l, r);
	}
	long long res = *min_element(memo + 1, memo + n + 1);
	if(res == inf) res = -1;
	printf("%lld\n", res);
	return 0;
}
