#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;
const int inf = 1e9 + 10;

int n;
int k;
int r;
int temp1[N];
int temp2[N];
int subtree[N];
vector<int> G[N];
vector<int> W[N];
int memo[N][N][2];

void DP(int u, int p = 0){
	subtree[u] = 1;
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int w = W[u][i];
		if(v == p) continue;
		DP(v, u);
		fill(temp1, temp1 + k + 1, inf);
		fill(temp2, temp2 + k + 1, inf);
		temp1[0] = temp2[0] = temp1[1] = temp2[1] = 0;
		for(int s1 = 0; s1 <= min(subtree[u], k); s1++){
			for(int s2 = 0; s2 <= subtree[v] and s1 + s2 <= k; s2++){
				temp1[s1 + s2] = min(temp1[s1 + s2], memo[u][s1][0] + 2 * w * (s2 > 0) + memo[v][s2][0]);
				temp2[s1 + s2] = min(temp2[s1 + s2], memo[u][s1][0] + w * (s2 > 0) + memo[v][s2][1]);
				temp2[s1 + s2] = min(temp2[s1 + s2], memo[u][s1][1] + 2 * w * (s2 > 0) + memo[v][s2][0]);
			}
		}
		subtree[u] += subtree[v];
		for(int i = 0; i <= min(k, subtree[u]); i++){
			memo[u][i][0] = temp1[i];
			memo[u][i][1] = temp2[i];
		}
	}
}

int main(){
	scanf("%d %d %d", &n, &k, &r);
	for(int i = 1; i < n; i++){
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
		W[u].emplace_back(w);
		W[v].emplace_back(w);
	}
	DP(r);
	printf("%d\n",min(memo[r][k][0], memo[r][k][1]));
	return 0;
}
