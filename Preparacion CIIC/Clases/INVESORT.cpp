#include<bits/stdc++.h>
using namespace::std;

const int n = 10;
const int MAX = 3628800 + 10;

int f[11];
int D[MAX];
int pot[11];
char s[15], t[15];

vector<int> getOrd(vector<int> &p){
	int have = (1 << 10) - 1;
	vector<int> res;
	for(int i = 0; i < n; i++){
		int val = (1 << p[i]) - 1;
		res.emplace_back(__builtin_popcount(have & val));
		have ^= 1 << p[i];
	}
	return res;
}

vector<int> getPerm(int val){
	vector<int> ord;
	for(int i = 0; i < n; i++){
		ord.emplace_back(val / f[n - 1 - i]);
		val %= f[n - 1 - i];
	}
	vector<int> p;
	int have = (1 << 10) - 1;
	for(int i = 0; i < n; i++){
		int cnt = 0;
		int pos = 0;
		while(cnt < ord[i]){
			if(have & pot[pos]) cnt++;
			pos++;
		}
		while(!(have & pot[pos])) pos++;
		p.emplace_back(pos);
		have ^= pot[pos];
	}
	return p;
}

void print(vector<int> p){
	for(auto x : p) cout << x << " ";
	cout << endl;
}

int getId(vector<int> &p){
	vector<int> a = getOrd(p);
	int res = 0;
	for(int i = 0; i < n; i++){
		res += a[i] * f[n - 1 - i];
	}
	return res;
}

void BFS(int src){
	memset(D, -1, sizeof D);
	queue<int> Q;
	Q.emplace(src);
	D[src] = 0;
	while(!Q.empty()){
		int u = Q.front();
		Q.pop();
		vector<int> p = getPerm(u);
		for(int l = 0; l + 1 < n; l++){
			for(int r = l + 1; r < n; r++){
				for(int k = 0; k < r - l - k; k++){
					swap(p[l + k], p[l + r - l - k]);
				}
				int v = getId(p);
				if(D[v] == -1){
					D[v] = D[u] + 1;
					Q.emplace(v);
				}
				for(int k = 0; k < r - l - k; k++){
					swap(p[l + k], p[l + r - l - k]);
				}
			}
		}
	}
}

int main(){
	f[0] = 1;
	for(int i = 1; i < n; i++) f[i] = i * f[i - 1];
	pot[0] = 1;
	for(int i = 1; i < n; i++) pot[i] = pot[i - 1] << 1;
	BFS(0);
	while(scanf("%s %s", s, t) == 2 and s[0] != '*'){
		vector<int> mapeo(n, -1);
		for(int i = 0; i < n; i++){
			mapeo[s[i] - 'a'] = i;
		}
		vector<int> p;
		for(int i = 0; i < n; i++){
			p.emplace_back(mapeo[t[i] - 'a']);
		}
		printf("%d\n", D[getId(p)]);
	}
	return 0;
}
