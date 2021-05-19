#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
vector<pair<int, int>> G[N];

void BFS1(vector<int> &src){
	queue<int> Q;
	vector<int> D(n, -1);
	vector<bool> vis(n, false);
	for(auto x : src){
		vis[x] = true;
		D[x] = 0;
		Q.emplace(x);
	}
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		for(int v : G[u]){
			if(vis[v]) continue;
			Q.emplace(v);
			vis[v] = true;
			D[v] = D[u] + 1;
		}
	}
}

void BFS01(int src){
	deque<int> Q;
	vector<int> D(n, -1);
	vector<bool> vis(n, false);
	vis[src] = true;
	D[src] = 0;
	Q.push_back(src);
	while(!Q.empty()){
		int u = Q.front();
		Q.pop_front();
		if(vis[u]) continue;
		for(auto [v, w] : G[u]){
			if(D[v] > D[u] + w){
				if(w == 0) Q.push_front(v);
				else Q.push_back(v);
				D[v] = D[u] + w;
			}
		}
		vis[v] = true;
	}
}

void BFS2(int src){
	vector<int> frontier;
	vector<int> D(n, -1);
	vector<bool> vis(n, false);
	frontier.emplace_back(src);
	D[src] = 0;
	vis[src] = true;
	while(!frontier.empty()){
		vector<int> new_frontier;
		for(auto u : frontier){
			for(int v : G[u]){
				if(vis[v]) continue;
				new_frontier.emplace_back(v);
				D[v] = D[u] + 1;
				vis[v] = true;
			}
		}
		swap(frontier, new_frontier);
	}
}

int main(){
	
	return 0;
}
