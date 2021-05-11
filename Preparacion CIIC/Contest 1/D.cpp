#include<bits/stdc++.h>
using namespace::std;

const int N = 100 + 5;
const int E = 26;

int n;
int len[N];
char s[N][N];
vector<int> G[E];

vector<char> toposort(){
	vector<int> deg(E, 0);
	for(int i = 0; i < E; i++){
		for(int v : G[i]){
			deg[v] += 1;
		}
	}
	queue<int> Q;
	for(int i = 0; i < E; i++){
		if(deg[i] == 0){
			Q.emplace(i);
		}
	}
	vector<char> res;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		res.emplace_back('a' + u);
		for(int v : G[u]){
			deg[v] -= 1;
			if(deg[v] == 0) Q.emplace(v);
		}
	}
	return res.size() == E ? res : vector<char>();
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%s", s[i]);
		len[i] = strlen(s[i]);
	}
	for(int i = 1; i < n; i++){
		int j = 0;
		while(s[i][j] and s[i + 1][j] and s[i][j] == s[i + 1][j]) j += 1;
		if(j == len[i] and j == len[i + 1]) continue;
		if(j < len[i] and j < len[i + 1]){
			G[s[i][j] - 'a'].emplace_back(s[i + 1][j] - 'a');
		}
		else if(j == len[i + 1]){
			puts("Impossible");
			return 0;
		}
	}
	vector<char> ans = toposort();
	if(ans.empty()){
		puts("Impossible");
		return 0;
	}
	for(int i = 0; i < E; i++) putchar(ans[i]);
	putchar('\n');
	return 0;
}
