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
#define op(a,b) (a+b)
#define NEUT 0

int n,m;
int a[MAXN][MAXN],st[2*MAXN][2*MAXN];
void build(){
	fore(i,0,n)fore(j,0,m)st[i+n][j+m]=a[i][j];
	fore(i,0,n)for(int j=m-1;j;--j)
		st[i+n][j]=op(st[i+n][j<<1],st[i+n][j<<1|1]);
	for(int i=n-1;i;--i)fore(j,0,2*m)
		st[i][j]=op(st[i<<1][j],st[i<<1|1][j]);
}
void upd(int x, int y, int v){
	st[x+n][y+m]=v;
	for(int j=y+m;j>1;j>>=1)st[x+n][j>>1]=op(st[x+n][j],st[x+n][j^1]);
	for(int i=x+n;i>1;i>>=1)for(int j=y+m;j;j>>=1)
		st[i>>1][j]=op(st[i][j],st[i^1][j]);
}
int query(int x0, int x1, int y0, int y1){
	int r=NEUT;
	for(int i0=x0+n,i1=x1+n;i0<i1;i0>>=1,i1>>=1){
		int t[4],q=0;
		if(i0&1)t[q++]=i0++;
		if(i1&1)t[q++]=--i1;
		fore(k,0,q)for(int j0=y0+m,j1=y1+m;j0<j1;j0>>=1,j1>>=1){
			if(j0&1)r=op(r,st[t[k]][j0++]);
			if(j1&1)r=op(r,st[t[k]][--j1]);
		}
	}
	return r;
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);m=n;
		memset(st,0,sizeof(st));
		char s[8];
		while(scanf("%s",s),s[0]!='E'){
			if(s[1]=='E'){
				int x,y,v;
				scanf("%d%d%d",&x,&y,&v);
				upd(x,y,v);
			}
			else {
				int x0,y0,x1,y1;
				scanf("%d%d%d%d",&x0,&y0,&x1,&y1);x1++;y1++;
				printf("%d\n",query(x0,x1,y0,y1));
			}
		}
	}
	return 0;
}

