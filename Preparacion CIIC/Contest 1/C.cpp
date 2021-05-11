#include<bits/stdc++.h>
using namespace::std;

const int MOD = 100000000;
const int N = 100 + 5;
const int K = 10 + 5;

int n1;
int n2;
int k1;
int k2;
bool vis[N][N][K][K];
int memo[N][N][K][K];

int DP(int u1, int u2, int c1, int c2){
	if(u1 == n1 and u2 == n2) return 1;
	if(vis[u1][u2][c1][c2]) return memo[u1][u2][c1][c2];
	int ans = 0;
	if(u1 < n1 and c1 + 1 <= k1) ans += DP(u1 + 1, u2, c1 + 1, 0);
	if(ans >= MOD) ans -= MOD;
	if(u2 < n2 and c2 + 1 <= k2) ans += DP(u1, u2 + 1, 0, c2 + 1);
	if(ans >= MOD) ans -= MOD;
	vis[u1][u2][c1][c2] = true;
	return memo[u1][u2][c1][c2] = ans;
}

int main(){
	scanf("%d %d %d %d", &n1, &n2, &k1, &k2);
	printf("%d\n", DP(0, 0, 0, 0));
	return 0;
}
