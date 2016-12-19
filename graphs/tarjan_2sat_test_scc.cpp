// SPOJ WEBISL - AC
// http://www.spoj.com/problems/WEBISL/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
#define MAXN (1<<20)

// MAXN: max number of nodes or 2 * max number of variables (2SAT)
//bool truth[MAXN]; // truth[cmp[i]]=value of variable i (2SAT)
//int nvar;int neg(int x){return x>=nvar?x-nvar:x+nvar;} // (2SAT)
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
//		truth[qcmp]=(cmp[neg(u)]<0); // (2SAT)
		qcmp++;
	}
}
void scc(){
	memset(idx,0,sizeof(idx));qidx=0;
	memset(cmp,-1,sizeof(cmp));qcmp=0;
	fore(i,0,n)if(!idx[i])tjn(i);
}
// Only for 2SAT:
//#define addor(a, b) (g[neg(a)].pb(b), g[neg(b)].pb(a))
//void init_2sat(int _nvar){nvar=_nvar;n=2*nvar;} // call before addor!
//bool satisf(){
//	scc();
//	fore(i,0,nvar)if(cmp[i]==cmp[neg(i)])return false;
//	return true;
//}

int m;
int s[MAXN];

int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		int x,y;
		scanf("%d%d",&x,&y);
		g[x].pb(y);
	}
	scc();
	fore(i,0,qcmp)s[i]=1<<30;
	fore(i,0,n)s[cmp[i]]=min(s[cmp[i]],i);
	fore(i,0,n)printf("%d\n",s[cmp[i]]);
	return 0;
}
