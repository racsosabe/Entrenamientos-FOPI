#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int E = 26;

int n;
int m;
vector<int> G[N];
vector<int> W[N];
bool vis[N][N][2][E];
int memo[N][N][2][E];

int DP(int u, int v, int turn, int last){
	if(vis[u][v][turn][last]) return memo[u][v][turn][last];
	int ans = turn ^ 1;
	if(!turn){
		// Muevo u
		for(int i = 0; i < G[u].size(); i++){
			int nxt_u = G[u][i];
			int nxt_last = W[u][i];
			if(nxt_last < last) continue;
			int res = DP(nxt_u, v, turn ^ 1, nxt_last);
			if(res == turn) ans = turn;
		}
	}
	else{
		// Muevo v
		for(int i = 0; i < G[v].size(); i++){
			int nxt_v = G[v][i];
			int nxt_last = W[v][i];
			if(nxt_last < last) continue;
			int res = DP(u, nxt_v, turn ^ 1, nxt_last);
			if(res == turn) ans = turn;
		}
	}
	vis[u][v][turn][last] = true;
	return memo[u][v][turn][last] = ans;
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 0; i < m; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		char w = getchar();
		while(!isalpha(w)) w = getchar();
		G[u].emplace_back(v);
		W[u].emplace_back(w - 'a');
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			putchar(DP(i, j, 0, 0) + 'A');
		}
		putchar('\n');
	}
	return 0;
}
