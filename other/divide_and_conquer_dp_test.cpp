// Codeforces 321E - AC
// http://codeforces.com/problemset/problem/321/E
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 4096
#define INF (1<<30)

int x[MAXN][MAXN];
int sx[MAXN][MAXN];

// O(knlogn). For 2D dps, when the position of optimal choice is non-decreasing as the second variable increases
int k,n,f[MAXN],f2[MAXN];
void doit(int s, int e, int s0, int e0, int i){
	// [s,e): range of calculation, [s0,e0): range of optimal choice
	if(s==e)return;
	int m=(s+e)/2;
	int r=INF,rp;
	fore(j,s0,min(e0,m)){
		int r0=f[j]+sx[m][m]-sx[m][j]-sx[j][m]+sx[j][j];
		if(r0<r){
			r=r0;
			rp=j; // position of optimal choice
		}
	}
	f2[m]=r;
	doit(s,m,s0,rp+1,i);
	doit(m+1,e,rp,e0,i);
}
int doall(){
	fore(i,0,n+1)f[i]=sx[i][i];
	fore(i,1,k){
		doit(1,n+1,0,n,i);
		memcpy(f,f2,sizeof(f));
	}
	return f[n];
}


int main(){
	scanf("%d%d",&n,&k);
	fore(i,0,n){
		fore(j,0,n){
			getchar();
			x[i][j]=getchar()-'0';
		}
	}
	fore(i,1,n+1){
		fore(j,1,n+1){
			sx[i][j]=sx[i-1][j]+sx[i][j-1]-sx[i-1][j-1]+x[i-1][j-1];
		}
	}
	printf("%d\n",doall()/2);
	return 0;
}
