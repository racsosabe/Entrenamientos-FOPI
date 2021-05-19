#include<bits/stdc++.h>
using namespace::std;

int n;

void incorrect(){
	if(n < 6) puts("-1");
	else{
		printf("1 2\n2 3\n2 4\n");
		for(int i = 5; i <= n; i++){
			printf("1 %d\n", i);
		}
	}
}

void correct(){
	for(int i = 2; i <= n; i++){
		printf("1 %d\n", i);
	}
}

int main(){
	scanf("%d", &n);
	incorrect();
	correct();
	return 0;
}
