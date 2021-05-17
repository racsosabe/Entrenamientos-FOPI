#include<bits/stdc++.h>
using namespace::std;

const int N = 4000000 + 5;

int n;
int m;
int len;
int r[N];
int L[2];
int st1[2][N];
int st2[2][N];
long long a[N];

void init(){
	L[0] = L[1] = 0;
	st1[0][0] = st1[1][0] = st2[0][0] = st2[1][0] = 2e9 + 10;
}

void push(int x){
	L[0]++;
	st1[0][L[0]] = x;
	st1[1][L[0]] = min(st1[1][L[0] - 1], x);
}

void pop(){
	if(L[1] == 0){
		while(L[0] > 0){
			L[1]++;
			st2[0][L[1]] = st1[0][L[0]];
			st2[1][L[1]] = min(st2[1][L[1] - 1], st1[0][L[0]]);
			L[0]--;
		}
	}
	L[1]--;
}

int getMin(){
	return min(st1[1][L[0]], st2[1][L[1]]);
}

int solve(){
	for(int i = 1; i < m; i++) push(r[i]);
	int ans = 0;
	for(int i = m; i <= len; i++){
		push(r[i]);
		if(i - m >= 1) pop();
		ans = max(ans, getMin());
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	len = n << 1;
	m = (n + 1) >> 1;
	for(int i = 1; i <= n; i++){
		scanf("%lld", a + i);
		a[i + n] = a[i];
	}
	for(int i = 1; i <= len; i++){
		a[i] += a[i - 1];
	}
	for(int i = 1; i + m - 1 <= len; i++){
		r[i] = a[i + m - 1] - a[i - 1];
	}
	init();
	printf("%d\n", solve());
	return 0;
}
