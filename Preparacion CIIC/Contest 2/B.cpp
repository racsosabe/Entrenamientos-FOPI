#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int h[N];
vector<int> G[N];

void DFS(int u, int p = -1){
	for(int v : G[u]){
		if(v == p) continue;
		h[v] = h[u] ^ 1;
		DFS(v, u);
	}
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i < n; i++){
		int u, v;
		scanf("%d %d", &u, &v);
		G[u].emplace_back(v);
		G[v].emplace_back(u);
	}
	DFS(1);
	int cnt0 = 0, cnt1 = 0;
	for(int i = 1; i <= n; i++){
		cnt0 += h[i] == 0;
		cnt1 += h[i] == 1;
	}
	printf("%lld\n", 1ll * cnt0 * cnt1 - n + 1);
	return 0;
}
