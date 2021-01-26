// Codeforces 102920F - AC
//https://codeforces.com/gym/102920/problem/F
#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const int MAXN=1e5+10;
//idom[i]=parent of i in dominator tree with root=rt, or -1 if not exists
int n,rnk[MAXN],pre[MAXN],anc[MAXN],idom[MAXN],semi[MAXN],low[MAXN];
vector<int> g[MAXN],rev[MAXN],dom[MAXN],ord;
void dfspre(int pos){
	rnk[pos]=SZ(ord); ord.pb(pos);
	for(auto x:g[pos]){
		rev[x].pb(pos);
		if(rnk[x]==n) pre[x]=pos,dfspre(x);
	}
}
int eval(int v){
	if(anc[v]<n&&anc[anc[v]]<n){
		int x=eval(anc[v]);
		if(rnk[semi[low[v]]]>rnk[semi[x]]) low[v]=x;
		anc[v]=anc[anc[v]];
	}
	return low[v];
}
void dominators(int rt){
	fore(i,0,n){
		dom[i].clear(); rev[i].clear();
		rnk[i]=pre[i]=anc[i]=idom[i]=n;
		semi[i]=low[i]=i;
	}
	ord.clear(); dfspre(rt);
	for(int i=SZ(ord)-1;i;i--){
		int w=ord[i];
		for(int v:rev[w]){
			int u=eval(v);
			if(rnk[semi[w]]>rnk[semi[u]])semi[w]=semi[u];
		}
		dom[semi[w]].pb(w); anc[w]=pre[w];
		for(int v:dom[pre[w]]){
			int u=eval(v);
			idom[v]=(rnk[pre[w]]>rnk[semi[u]]?u:pre[w]);
		}
		dom[pre[w]].clear();
	}
	for(int w:ord) if(w!=rt&&idom[w]!=semi[w]) idom[w]=idom[idom[w]];
	fore(i,0,n) if(idom[i]==n)idom[i]=-1;
}

int main(){FIN;
	int m,k; cin>>n>>m>>k;
	fore(i,0,m) g[n].pb(i);
	fore(i,0,k){
		int x,y; cin>>x>>y; x--;y--;
		g[x].pb(y);
	}
	n++;
	dominators(n-1);
	int ans=0;
	fore(i,0,n-1) ans+=idom[i]==n-1;
	cout<<ans<<"\n";
}
