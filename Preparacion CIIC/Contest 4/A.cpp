#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int a[N];

int hill(int i){
	if(i <= 1 or i >= n) return 0;
	return a[i] > a[i + 1] and a[i] > a[i - 1];
}

int valley(int i){
	if(i <= 1 or i >= n) return 0;
	return a[i] < a[i + 1] and a[i] < a[i - 1];
}

int has(int i){
	return valley(i) | hill(i);
}

int solve(){
	int total = 0;
	for(int i = 1; i <= n; i++){
		if(has(i)) total += 1;
	}
	int ans = total;
	for(int i = 1; i <= n; i++){
		int act = a[i];
		if(i > 1){
			int cur = total - has(i) - has(i - 1) - has(i + 1);
			a[i] = a[i - 1];
			cur += has(i) + has(i - 1) + has(i + 1);
			ans = min(ans, cur);
			a[i] = act;
		}
		if(i + 1 <= n){
			int cur = total - has(i) - has(i - 1) - has(i + 1);
			a[i] = a[i + 1];
			cur += has(i) + has(i - 1) + has(i + 1);
			ans = min(ans, cur);
			a[i] = act;
		}
	}
	return ans;
}

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d", &n);
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		printf("%d\n", solve());
	}
	return 0;
}
