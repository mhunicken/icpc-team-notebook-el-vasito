// SPOJ QTREE - AC
// http://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define oper max
#define NEUT -(1<<30)
struct STree { // segment tree for min over integers
	vector<int> st;int n;
	STree(int n): st(4*n+5,NEUT), n(n) {}
	void init(int k, int s, int e, int *a){
		if(s+1==e){st[k]=a[s];return;}
		int m=(s+e)/2;
		init(2*k,s,m,a);init(2*k+1,m,e,a);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	void upd(int k, int s, int e, int p, int v){
		if(s+1==e){st[k]=v;return;}
		int m=(s+e)/2;
		if(p<m)upd(2*k,s,m,p,v);
		else upd(2*k+1,m,e,p,v);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	int query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return NEUT;
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
	}
	void init(int *a){init(1,0,n,a);}
	void upd(int p, int v){upd(1,0,n,p,v);}
	int query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(i,v);rmq.query(s,e);

#define MAXN 100005

vector<int> g[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth
void dfs1(int x){
	wg[x]=1;
	for(int y:g[x])if(y!=dad[x]){
		dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
		wg[x]+=wg[y];
	}
}
int curpos,pos[MAXN],head[MAXN];
void hld(int x, int c){
	if(c<0)c=x;
	pos[x]=curpos++;head[x]=c;
	int mx=-1;
	for(int y:g[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
	if(mx>=0)hld(mx,c);
	for(int y:g[x])if(y!=mx&&y!=dad[x])hld(y,-1);
}
void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}
int query(int x, int y, STree& rmq){
	int r=NEUT;
	while(head[x]!=head[y]){
		if(dep[head[x]]>dep[head[y]])swap(x,y);
		r=oper(r,rmq.query(pos[head[y]],pos[y]+1));
		y=dad[head[y]];
	}
	if(dep[x]>dep[y])swap(x,y); // now x is lca
	r=oper(r,rmq.query(pos[x]+1,pos[y]+1));  // pos[x]+1 for not counting lca
	return r;
}
// for updating: rmq.upd(pos[x],v);

int n;
int a[MAXN],b[MAXN],c[MAXN];
int z[MAXN];

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		scanf("%d",&n);
		STree rmq(n);
		fore(i,0,n-1){
			scanf("%d%d%d",a+i,b+i,c+i);a[i]--;b[i]--;
			g[a[i]].pb(b[i]);g[b[i]].pb(a[i]);
		}
		hld_init();
		z[0]=NEUT;
		fore(i,0,n-1){
			int x=a[i],y=b[i];
			if(x==dad[y])z[pos[y]]=c[i];
			else z[pos[x]]=c[i];
		}
		rmq.init(z);
		char t[16];
		while(scanf("%s",t),t[0]!='D'){
			int i,j;
			scanf("%d%d",&i,&j);
			if(t[0]=='C'){
				int x=a[i-1],y=b[i-1];
				if(x==dad[y])rmq.upd(pos[y],j);
				else rmq.upd(pos[x],j);
			}
			else printf("%d\n",query(i-1,j-1,rmq));
		}
		fore(i,0,n)g[i].clear();
	}
	return 0;
}
// for updating: rmq.upd(pos[x],v);
