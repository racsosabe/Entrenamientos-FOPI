#include<bits/stdc++.h>
using namespace::std;

long long n;

long long solve(){
	long long ans = 0;
	long long val = 1;
	for(int b = 0; b <= 40; b++){
		long long total = n / val;
		ans += val * (total - total / 2);
		val <<= 1;
	}
	return ans;
}

int main(){
	scanf("%lld", &n);
	n--;
	printf("%lld\n", solve());
	return 0;
}
