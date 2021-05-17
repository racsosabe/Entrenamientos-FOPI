#include<bits/stdc++.h>
using namespace::std;

const int N = 10000 + 5;

int gcd(int a, int b){
	while(b){
		a %= b;
		swap(a, b);
	}
	return a;
}

int n;
int a[N];

bool primo(int x){
	if(x == 1) return false;
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0) return false;
	}
	return true;
}

bool test(int p){
	int deg = min(n + 1, p);
	vector<int> carry(deg, 0);
	carry[0] = a[0] % p;
	for(int i = 1; i <= n; i++){
		int pos = (i - 1) % (p - 1) + 1;
		carry[pos] += a[i] % p;
		if(carry[pos] >= p) carry[pos] -= p;
		if(carry[pos] < 0) carry[pos] += p;
	}
	for(int i = 0; i < deg; i++){
		if(carry[i]) return false;
	}
	return true;
}

void solve(){
	vector<int> res;
	int x = abs(a[0]);
	for(int i = 1; i <= n; i++) x = gcd(x, abs(a[i]));
	for(int i = 1; i <= n; i++){
		if(primo(i) and test(i)) res.emplace_back(i);
	}
	for(int i = 2; i * i <= x; i++){
		if(x % i == 0){
			if(test(i)) res.emplace_back(i);
			while(x % i == 0) x /= i;
		}
	}
	if(x > 1 and test(x)) res.emplace_back(x);
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	printf("%d\n", (int)res.size());
	for(auto x : res) printf("%d%c", x, " \n"[x == res.back()]);
}

int main(){
	scanf("%d", &n);
	for(int i = n; i >= 0; i--) scanf("%d", a + i);
	solve();
	return 0;
}
