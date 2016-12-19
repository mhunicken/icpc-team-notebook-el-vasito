// UVA 10319 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1260
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,to=b;i<to;++i)
using namespace std;
typedef long long ll;
#define MAXN 200005

// MAXN: max number of nodes or 2 * max number of variables (2SAT)
bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
int nvar;int neg(int x){return x>=nvar?x-nvar:x+nvar;} // (2SAT)
vector<int> g[MAXN];
int n,lw[MAXN],idx[MAXN],qidx,cmp[MAXN],qcmp;
stack<int> st;
void tjn(int u){
	lw[u]=idx[u]=++qidx;
	st.push(u);cmp[u]=-2;
	fore(_,0,g[u].size()){
		int v=g[u][_];
		if(!idx[v]||cmp[v]==-2){
			if(!idx[v]) tjn(v);
			lw[u]=min(lw[u],lw[v]);
		}
	}
	if(lw[u]==idx[u]){
		int x;
		do{x=st.top();st.pop();cmp[x]=qcmp;}while(x!=u);
		truth[qcmp]=(cmp[neg(u)]<0); // (2SAT)
		qcmp++;
	}
}
void scc(){
	memset(idx,0,sizeof(idx));qidx=0;
	memset(cmp,-1,sizeof(cmp));qcmp=0;
	fore(i,0,n)if(!idx[i])tjn(i);
}
// Only for 2SAT:
#define addor(a, b) (g[neg(a)].pb(b), g[neg(b)].pb(a))
void init_2sat(int _nvar){nvar=_nvar;n=2*nvar;} // call before addor!
bool satisf(){
	scc();
	fore(i,0,nvar)if(cmp[i]==cmp[neg(i)])return false;
	return true;
}

void verify(){
	fore(x,0,n){
		fore(_,0,g[x].size()){
			int y=g[x][_];
			assert(!truth[cmp[x]]||truth[cmp[y]]);
		}
		assert(truth[cmp[x]]!=truth[cmp[neg(x)]]);
	}
}

int main(){
	int tn;
	scanf("%d",&tn);
	while(tn--){
		int x,y;
		scanf("%d%d",&x,&y);
		init_2sat(x+y);
		int m;
		scanf("%d",&m);
		while(m--){
			int x0,y0,x1,y1;
			scanf("%d%d%d%d",&x0,&y0,&x1,&y1);x0--;y0--;x1--;y1--;
			if(x0==x1&&y0==y1)continue;
			bool ix=x1<x0,iy=y1<y0;
			y0+=x;y1+=x;
			if(ix)y0=neg(y0),y1=neg(y1);
			if(iy)x0=neg(x0),x1=neg(x1);
			if(x0==x1)addor(x0,x0);
			else if(y0==y1)addor(y0,y0);
			else {
				// (x0^y1)v(x1^y0)
				addor(x0,x1);addor(x0,y0);addor(y1,x1);addor(y1,y0);
			}
		}
		if(satisf())verify(),puts("Yes");
		else puts("No");
		fore(i,0,n)g[i].clear();
	}
	return 0;
}
