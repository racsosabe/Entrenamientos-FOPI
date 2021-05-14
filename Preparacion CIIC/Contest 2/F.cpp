#include<bits/stdc++.h>
using namespace::std;

const long long inf = 1e18;
const int N = 1 << 14;
const int R = 15;

int r;
int n;
int a[N];
long long memo[R][N];

long long c(int i, int j){
	return a[i] >= a[j] ? 0 : 1ll * (a[j] - a[i]) * (a[j] - a[i]);
}

long long solve(){
	int len = 1;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < n; j++) memo[i + 1][j] = inf;
		for(int j = 0; j < n; j += 2 * len){
			for(int u = j; u < j + len; u++){
				for(int v = j + len; v < j + 2 * len; v++){
					memo[i + 1][u] = min(memo[i + 1][u], memo[i][u] + memo[i][v] + c(u, v));
					memo[i + 1][v] = min(memo[i + 1][v], memo[i][u] + memo[i][v] + c(v, u));
				}
			}
		}
		len <<= 1;
	}
	return memo[r][0];
}

int main(){
	scanf("%d", &r);
	n = 1 << r;
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	printf("%lld\n", solve());
	return 0;
}
