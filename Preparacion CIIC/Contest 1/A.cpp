#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;

int n;
int x;
int cnt[N];

int get(int l, int r){
	int ans = 0;
	for(int i = l; i <= r; i++){
		ans += cnt[i] == 0;
	}
	return ans;
}

int main(){
	scanf("%d %d", &n, &x);
	for(int i = 0; i < n; i++){
		int a;
		scanf("%d", &a);
		cnt[a] += 1;
	}
	int mex = 0;
	while(cnt[mex]) mex += 1;
	int ans = 0;
	if(mex > x) ans = 1;
	else if(mex < x) ans = get(mex, x - 1) + cnt[x];
	printf("%d\n", ans);
	return 0;
}
