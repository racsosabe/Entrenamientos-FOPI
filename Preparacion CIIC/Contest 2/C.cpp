#include<bits/stdc++.h>
using namespace::std;

bool fillThree(char c){
	return c == 'J' or c == 'L' or c == 'T';
}

int main(){
	int cnt = 0;
	while(true){
		char c = getchar();
		while(!isalpha(c)) c = getchar();
		if(c == 'W') break;
		if(c == 'I'){
			puts("1 1");
		}
		else if(fillThree(c)){
			puts("2 2");
		}
		else{
			printf("1 %d\n", 2 * cnt + 5);
			cnt += 1;
		}
		fflush(stdout);
	}
	return 0;
}
