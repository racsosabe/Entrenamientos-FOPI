#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int a[N];

int get(int i, int j){
	int last = -1;
	int ans = 0;
	for(int pos = 1; pos <= n; pos++){
		if(pos == i or pos == j) continue;
		if(last == -1) last = pos;
		else{
			ans += a[pos] - a[last];
			last = -1;
		}
	}
	return ans;
}

int solve(){
	int ans = 1e9;
	for(int i = 1; i <= n; i++){
		for(int j = i + 1; j <= n; j++){
			ans = min(ans, get(i, j));
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	n <<= 1;
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	sort(a + 1, a + n + 1);
	printf("%d\n", solve());
	return 0;
}
