#include<bits/stdc++.h>
using namespace::std;

const int N = 1000 + 5;
const int inf = 1e9;

int n;
int a[2];
int b[2];
int L[2];
int D[N];
vector< pair<int, int> > G[N];

void addEdge(int u, int v, int w){
	G[u].emplace_back(make_pair(v, w));
}

void buildGraph(){
	for(int i = 1; i <= n; i++){
		addEdge(i - 1, i, 1);
		addEdge(i, i - 1, 0);
	}
	for(int i = 0; i < 2; i++){
		for(int l = 1; l + L[i] - 1 <= n; l++){
			int r = l + L[i] - 1; 
			int rml = i == 0 ? L[i] - a[i] : b[i];
			int lmr = i == 0 ? b[i] - L[i] : -a[i];
			addEdge(l - 1, r, rml);
			addEdge(r, l - 1, lmr);
		}
	}
}

bool Bellman(){
	for(int i = 0; i <= n; i++) D[i] = inf;
	D[0] = 0;
	bool relaxed;
	for(int step = 0; step <= n; step++){
		relaxed = false;
		for(int i = 0; i <= n; i++){
			if(D[i] == inf) continue;
			for(auto e : G[i]){
				if(D[e.first] > D[i] + e.second){
					relaxed = true;
					D[e.first] = D[i] + e.second;
				}
			}
		}
	}
	return not relaxed;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < 2; i++) scanf("%d %d %d", a + i, b + i, L + i);
	buildGraph();
	if(Bellman()){
		for(int i = 1; i <= n; i++){
			putchar('0' + D[i] - D[i - 1]);
		}
		putchar('\n');
	}
	else puts("-1");
	return 0;
}
