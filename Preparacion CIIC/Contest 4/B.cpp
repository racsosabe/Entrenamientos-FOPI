#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;
const int E = 26;

int n;
int m;
char s[N];
int memo[N];
vector<int> G[N];

vector<int> toposort(){
	vector<int> deg(n + 1, 0);
	for(int i = 1; i <= n; i++){
		for(int v : G[i]) deg[v] += 1;
	}
	queue<int> Q;
	for(int i = 1; i <= n; i++){
		if(deg[i] == 0) Q.emplace(i);
	}
	vector<int> res;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		res.emplace_back(u);
		for(int v : G[u]){
			deg[v] -= 1;
			if(deg[v] == 0) Q.emplace(v);
		}
	}
	return res.size() == n ? res : vector<int>();
}

int solve(){
	vector<int> order = toposort();
	if(order.empty()) return -1;
	int ans = 0;
	for(int c = 0; c < E; c++){
		for(int i = 1; i <= n; i++) memo[i] = 0;
		for(auto x : order){
			if(s[x] - 'a' == c) memo[x] += 1;
			for(int v : G[x]){
				memo[v] = max(memo[v], memo[x]);
			}
		}
		ans = max(ans, *max_element(memo + 1, memo + n + 1));
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &m);
	scanf("%s", s + 1);
	for(int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
	}
	printf("%d\n", solve());
	return 0;
}
