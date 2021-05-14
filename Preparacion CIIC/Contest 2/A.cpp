#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int a[N];

int cut(int p){
	int ans = 0;
	for(int i = 1; i <= p; i++) ans += a[i];
	for(int i = p + 1; i <= n; i++) ans += 1 - a[i];
	return ans;
}

int solve(){
	int ans = n;
	for(int i = 0; i <= n; i++){
		ans = min(ans, cut(i));
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%d\n", n - solve());
	return 0;
}
