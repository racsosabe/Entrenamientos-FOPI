#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int d;
int len;
int par[N];
int memo[N];
long long h[N];
long long val[N];
pair<int, int> st[4 * N];

void compress(){
	set<long long> S;
	for(int i = 1; i <= n; i++) S.emplace(h[i]);
	map<long long, int> id;
	for(auto x : S){
		val[len] = x;
		id[x] = len++;
	}
	for(int i = 1; i <= n; i++) h[i] = id[h[i]];
}

void update(int x, int y, int z, int pos = 1, int l = 0, int r = len - 1){
	if(l == r){
		if(st[pos].first < y){	
			st[pos].first = y;
			st[pos].second = z;
		}
		return;
	}
	int mi = (l + r) / 2;
	if(x <= mi) update(x, y, z, 2 * pos, l, mi);
	else update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = max(st[2 * pos], st[2 * pos + 1]);
}

pair<int, int> query(int x, int y, int pos = 1, int l = 0, int r = len - 1){
	if(y < l or r < x or x > y) return {-1e9, 0};
	if(x <= l and r <= y) return st[pos];
	int mi = (l + r) / 2;
	return max(query(x, y, 2 * pos, l, mi), query(x, y, 2 * pos + 1, mi + 1, r));
}

int getLower(long long x){
	int lo = -1, hi = len - 1;
	while(lo < hi){
		int mi = lo + (hi - lo + 1) / 2;
		if(val[mi] <= x) lo = mi;
		else hi = mi - 1;
	}
	return lo;
}

int getUpper(long long x){
	int lo = 0, hi = len;
	while(lo < hi){
		int mi = lo + (hi - lo) / 2;
		if(val[mi] < x) lo = mi + 1;
		else hi = mi;
	}
	return lo;
}

void solve(){
	for(int i = 1; i <= n; i++){
		int l = getLower(val[h[i]] - d);
		int r = getUpper(val[h[i]] + d);
		pair<int, int> L = query(0, l);
		pair<int, int> R = query(r, len - 1);
		par[i] = -1;
		memo[i] = 1;
		if(L.first + 1 > memo[i]){
			memo[i] = L.first + 1;
			par[i] = L.second;
		}
		if(R.first + 1 > memo[i]){
			memo[i] = R.first + 1;
			par[i] = R.second;
		}
		update(h[i], memo[i], i);
	}
	int start = max_element(memo + 1, memo + n + 1) - memo;
	printf("%d\n", memo[start]);
	stack<int> S;
	while(start != -1){
		S.emplace(start);
		start = par[start];
	}
	while(!S.empty()){
		printf("%d", S.top());
		S.pop();
		putchar(S.empty() ? '\n' : ' ');
	}	
}

int main(){
	scanf("%d %d", &n, &d);
	for(int i = 1; i <= n; i++) scanf("%lld", h + i);
	compress();
	solve();
	return 0;
}
