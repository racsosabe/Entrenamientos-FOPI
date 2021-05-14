#include<bits/stdc++.h>
using namespace::std;

const int N = 300000 + 5;

int n;
int m;
int mex;
int a[N];
int b[N];
int h[N];
int par[N];
int ans[N];
int pnode[N];
int pedge[N];
int sizes[N];
int upper[N];
bool want[N];
bool used[N];
vector<int> G[N];
vector<int> E[N];

void DFS(int u, int p = -1){
	for(int i = 0; i < G[u].size(); i++){
		int v = G[u][i];
		int e = E[u][i];
		if(v == p) continue;
		h[v] = h[u] + 1;
		pnode[v] = u;
		pedge[v] = e;
		DFS(v, u);
	}
}

int get(int x){
	return par[x] == x ? x : par[x] = get(par[x]);
}

int g(int x){
	return upper[get(x)];
}

void join(int u, int v){
	u = get(u);
	v = get(v);
	if(u == v) return;
	if(sizes[u] > sizes[v]) swap(u, v);
	par[u] = v;
	sizes[v] += sizes[u];
	if(h[upper[v]] > h[upper[u]]) upper[v] = upper[u];
}

void update(int u, int v){
	vector<int> edges;
	while(get(u) != get(v)){
		if(h[g(u)] < h[g(v)]) swap(u, v);
		u = upper[get(u)];
		if(pedge[u] >= 1) edges.emplace_back(pedge[u]);
		join(u, pnode[u]);
		u = pnode[u];
	}
	sort(edges.begin(), edges.end());
	for(auto e : edges){
		ans[e] = mex++;
	}
}

void solve(){
	h[0] = -1;
	DFS(1);
	for(int i = 1; i <= n; i++){
		par[i] = upper[i] = i;
		sizes[i] = 1;
	}
	mex = 1;
	for(int i = 1; i <= m; i++){
		if(ans[i]) continue;
		if(want[i]){
			ans[i] = mex++;
			join(a[i], b[i]);
		}
		else{
			update(a[i], b[i]);
			ans[i] = mex++;
		}
	}
}

int main(){
	scanf("%d %d", &n, &m);
	for(int i = 1; i <= m; i++){
		scanf("%d %d", a + i, b + i);
	}
	for(int i = 1; i < n; i++){
		int x;
		scanf("%d", &x);
		want[x] = true;
		G[a[x]].emplace_back(b[x]);
		G[b[x]].emplace_back(a[x]);
		E[a[x]].emplace_back(x);
		E[b[x]].emplace_back(x);
	}
	solve();
	for(int i = 1; i <= m; i++){
		printf("%d%c", ans[i], " \n"[i == m]);
	}
	return 0;
}
