// Codeforces 487E - AC
// http://codeforces.com/contest/487/problem/E
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
#define MAXN 200005

#define oper min
#define NEUT (1<<30)
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

vector<int> gg[MAXN];
int wg[MAXN],dad[MAXN],dep[MAXN]; // weight,father,depth
void dfs1(int x){
	wg[x]=1;
	for(int y:gg[x])if(y!=dad[x]){
		dad[y]=x;dep[y]=dep[x]+1;dfs1(y);
		wg[x]+=wg[y];
	}
}
int curpos,pos[MAXN],head[MAXN];
void hld(int x, int c){
	if(c<0)c=x;
	pos[x]=curpos++;head[x]=c;
	int mx=-1;
	for(int y:gg[x])if(y!=dad[x]&&(mx<0||wg[mx]<wg[y]))mx=y;
	if(mx>=0)hld(mx,c);
	for(int y:gg[x])if(y!=mx&&y!=dad[x])hld(y,-1);
}
void hld_init(){dad[0]=-1;dep[0]=0;dfs1(0);curpos=0;hld(0,-1);}

int nbc;  // number of biconnected components

int query(int x, int y, STree& rmq){
	int r=NEUT;
	while(head[x]!=head[y]){
		if(dep[head[x]]>dep[head[y]])swap(x,y);
		r=min(r,rmq.query(pos[head[y]],pos[y]+1));
		y=dad[head[y]];
	}
	if(dep[x]>dep[y])swap(x,y); // now x is lca
	r=min(r,rmq.query(pos[x],pos[y]+1));
	if(x<nbc&&dad[x]>=0){
		r=min(r,rmq.query(pos[dad[x]],pos[dad[x]]+1));
	}
	return r;
}
// for updating: rmq.upd(pos[x],v);

vector<int> g[MAXN];int n;
struct edge {int u,v,comp;bool bridge;};
vector<edge> e;
void add_edge(int u, int v){
	g[u].pb(e.size());g[v].pb(e.size());
	e.pb((edge){u,v,-1,false});
}
int D[MAXN],B[MAXN],T;
int art[MAXN];  // articulation point iff !=0
stack<int> st;  // only for biconnected
void dfs(int u,int pe){
	B[u]=D[u]=T++;
	for(int ne:g[u])if(ne!=pe){
		int v=e[ne].u^e[ne].v^u;
		if(D[v]<0){
			st.push(ne);
			dfs(v,ne);
			if(B[v]>D[u])e[ne].bridge = true; // bridge
			if(B[v]>=D[u]){
				art[u]++; // articulation
				int last; // start biconnected
				do {
					last=st.top();st.pop();
					e[last].comp=nbc;
				} while(last!=ne);
				nbc++;    // end biconnected
			}
			B[u]=min(B[u],B[v]);
		}
		else if(D[v]<D[u])st.push(ne),B[u]=min(B[u],D[v]);
	}
}
void doit(){
	memset(D,-1,sizeof(D));
	memset(art,0,sizeof(art));
	nbc=T=0;
	fore(i,0,n)if(D[i]<0)dfs(i,-1),art[i]--;
}

int m,q;
multiset<int> z[MAXN];
set<int> cc[MAXN];
int w[MAXN];
int nart;

void add_comp0(int c, int x){
	if(cc[x].count(c))return;
	cc[x].insert(c);
	z[c].insert(w[x]);
	if(!art[x])return;
	x=art[x];
	gg[x].pb(c);
	gg[c].pb(x);
}

int ar[MAXN];

int main(){
	scanf("%d%d%d",&n,&m,&q);
	fore(i,0,n)scanf("%d",w+i);
	fore(_,0,m){
		int x,y;
		scanf("%d%d",&x,&y);x--;y--;
		add_edge(x,y);
	}
	doit();
	fore(i,0,n)if(art[i])art[i]=nbc+nart++;
	fore(i,0,m){
		add_comp0(e[i].comp,e[i].u);
		add_comp0(e[i].comp,e[i].v);
	}
	hld_init();
	fore(i,0,n){
		if(art[i]){
			for(int c:cc[i])if(c!=dad[art[i]])z[c].erase(z[c].find(w[i]));
		}
	}
	fore(i,0,nbc)ar[pos[i]]=*z[i].begin();
	fore(i,0,n)if(art[i])ar[pos[art[i]]]=w[i];
	STree rmq(nbc+nart);
	rmq.init(ar);
	while(q--){
		char t[4];int a,b;
		scanf("%s%d%d",t,&a,&b);
		if(t[0]=='C'){
			a--;
			if(art[a]){
				int c=dad[art[a]];
				z[c].erase(z[c].find(w[a]));
				w[a]=b;
				z[c].insert(w[a]);
				rmq.upd(pos[c],*z[c].begin());
				rmq.upd(pos[art[a]],w[a]);
			}
			else {
				int c=*cc[a].begin();
				z[c].erase(z[c].find(w[a]));
				w[a]=b;
				z[c].insert(w[a]);
				rmq.upd(pos[c],*z[c].begin());
			}
		}
		else {
			a--;b--;
			if(a==b){printf("%d\n",w[a]);continue;}
			if(art[a])a=art[a];
			else a=*cc[a].begin();
			if(art[b])b=art[b];
			else b=*cc[b].begin();
			printf("%d\n",query(a,b,rmq));
		}
	}
	return 0;
}
