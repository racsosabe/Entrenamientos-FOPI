#include<bits/stdc++.h>
using namespace::std;

const int MOD = 1000000000 + 7;
const int N = 100000 + 5;

int n;
int m;
int c[N];
int mini;
int frec;
bool vis[N];
stack<int> S;
vector<int> G[2][N];

void DFS(int u, int id){
	vis[u] = id ^ 1;
	for(int v : G[id][u]){
		if(vis[v] ^ id) continue;
		DFS(v, id);
	}
	if(id == 0) S.emplace(u);
	else{
		if(c[u] < mini){
			mini = c[u];
			frec = 1;
		}
		else if(c[u] == mini) frec++;
	}
}

void solve(){
	int ways = 1;
	long long sum = 0;
	for(int i = 1; i <= n; i++){
		if(vis[i]) continue;
		DFS(i, 0);
	}
	while(!S.empty()){
		int u = S.top();
		S.pop();
		if(!vis[u]) continue;
		mini = 1e9 + 10;
		frec = 0;
		DFS(u, 1);
		sum += mini;
		ways = (1ll * ways * frec) % MOD;
	}
	printf("%lld %d\n", sum, ways);
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", c + i);
	scanf("%d", &m);
	for(int i = 1; i <= m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[0][u].emplace_back(v);
		G[1][v].emplace_back(u);
	}
	solve();
	return 0;
}
