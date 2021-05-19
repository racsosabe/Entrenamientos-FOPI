#include<bits/stdc++.h>
using namespace::std;

const int N = 4000 + 5;
const int E = 26;

int n;
int l;
char a[N];
char v[N];
int h[N];
int nodes;
int pot[E];
bool pat[N];
int mask[N];
int closest[N];
int trie[E][N];
int memo[N][N][2];

void addNode(){
	mask[nodes] = 0;
	pat[nodes] = false;
	nodes++;
}

void insert(){
	int pos = 0;
	for(int i = 0; v[i]; i++){
		int nxt = v[i] - 'A';
		if(!(mask[pos] & pot[nxt])){
			trie[nxt][pos] = nodes;
			mask[pos] |= pot[nxt];
			addNode();
		}
		pos = trie[nxt][pos];
	}
	pat[pos] = true;
}

void DFS(int u){
	closest[u] = pat[u]? 0 : 1e9;
	for(int e = 0; e < E; e++){
		if(!(mask[u] & pot[e])) continue;
		int v = trie[e][u];
		h[v] = h[u] + 1;
		DFS(v);
		if(closest[v] + 1 < closest[u]){
			closest[u] = closest[v] + 1;
		}
	}
}

int solve(){
	DFS(0);
	n = strlen(a);
	vector<int> p(nodes);
	iota(p.begin(), p.end(), 0);
	sort(p.begin(), p.end(), [&] (int i, int j){
		return h[i] > h[j];
	});
	for(int cut = 0; cut < 2; cut++){
		for(int state = 0; state < nodes; state++){
			memo[n][state][cut] = state ? closest[state] : 0;
		}
	}
	for(int pos = n - 1; pos >= 0; pos--){
		for(int cut = 0; cut < 2; cut++){
			for(int state : p){
				int ans = 1e9;
				for(int m = mask[state]; m > 0; m &= m - 1){
					int e = __builtin_ctz(m);
					int v = trie[e][state];
					int cand = (e + 'A' != a[pos]) + memo[pos + 1][v][1];
					if(ans > cand) ans = cand;
					cand = 1 + memo[pos][v][0];
					if(ans > cand) ans = cand;
				}
				if(cut) ans = min(ans, closest[state] + memo[pos][0][0]);
				ans = min(ans, 1 + memo[pos + 1][state][1]);
				memo[pos][state][cut] = ans;
			}
		}
	}
	return min(n, memo[0][0][1]);
}

int main(){
	int t;
	scanf("%d", &t);
	pot[0] = 1;
	for(int i = 1; i < E; i++) pot[i] = pot[i - 1] << 1;
	while(t--){
		scanf("%d", &l);
		nodes = 0;
		addNode();
		for(int i = 1; i <= l; i++){
			scanf("%s", v);
			insert();
		}
		scanf("%s", a);
		printf("%d\n", solve());
	}
	return 0;
}

