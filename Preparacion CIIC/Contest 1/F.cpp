#include<bits/stdc++.h>
using namespace::std;

const int SUML = 200000 * 30 + 5;
const int N = 200000 + 5;
const int L = 30;

int q;
int nodes = 1;
int frec[SUML];
int trie[SUML][2];

void insert(int x){
	int pos = 0;
	for(int i = L - 1; i >= 0; i--){
		int nxt = (x >> i) & 1;
		if(trie[pos][nxt] == 0){
			trie[pos][nxt] = nodes++;
		}
		pos = trie[pos][nxt];
		frec[pos] += 1;
	}
}

void remove(int x){
	int pos = 0;
	for(int i = L - 1; i >= 0; i--){
		int nxt = (x >> i) & 1;
		pos = trie[pos][nxt];
		frec[pos] -= 1;
	}
}

int maximize(int x){
	int ans = 0;
	int pos = 0;
	for(int i = L - 1; i >= 0; i--){
		int have = (x >> i) & 1;
		int nxt = have ^ 1;
		if(trie[pos][nxt] == 0 or frec[trie[pos][nxt]] == 0) nxt ^= 1;
		ans |= (have ^ nxt) << i;
		pos = trie[pos][nxt];
	}
	return ans;
}

int main(){
	scanf("%d", &q);
	insert(0);
	while(q--){
		char c = getchar();
		while(c != '+' and c != '-' and c != '?') c = getchar();
		int x;
		scanf("%d", &x);
		if(c == '+'){
			insert(x);
		}
		else if(c == '-'){
			remove(x);
		}
		else{
			printf("%d\n", maximize(x));
		}
	}
	return 0;
}
