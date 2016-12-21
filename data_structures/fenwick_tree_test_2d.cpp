// SPOJ MATSUM - AC
// http://www.spoj.com/problems/MATSUM/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 1024

int ft[MAXN+1][MAXN+1];
void upd(int i0, int j0, int v){
	for(int i=i0+1;i<=MAXN;i+=i&-i)
	for(int j=j0+1;j<=MAXN;j+=j&-j)
		ft[i][j]+=v;
}
int get(int i0, int j0){
	int r=0;
	for(int i=i0;i;i-=i&-i)
	for(int j=j0;j;j-=j&-j)
		r+=ft[i][j];
	return r;
}
int get_sum(int i0, int j0, int i1, int j1){
	return get(i1,j1)-get(i1,j0)-get(i0,j1)+get(i0,j0);
}

int x[MAXN+1][MAXN+1];
int n;

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		memset(ft,0,sizeof(ft));memset(x,0,sizeof(x));
		char t[8];
		while(scanf("%s",t),t[1]!='N'){
			if(t[1]=='E'){
				int i,j,v;
				scanf("%d%d%d",&i,&j,&v);
				upd(i,j,v-x[i][j]);
				x[i][j]=v;
			}
			else {
				int x0,y0,x1,y1;
				scanf("%d%d%d%d",&x0,&y0,&x1,&y1);x1++;y1++;
				printf("%d\n",get_sum(x0,y0,x1,y1));
			}
		}
	}
	return 0;
}
