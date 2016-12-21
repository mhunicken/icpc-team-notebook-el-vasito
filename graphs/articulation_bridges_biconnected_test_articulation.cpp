// SPOJ SUBMERGE - AC
// http://www.spoj.com/problems/SUBMERGE/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;
#define MAXN 100005

vector<int> g[MAXN];int n;
struct edge {int u,v,comp;bool bridge;};
vector<edge> e;
void add_edge(int u, int v){
	g[u].pb(e.size());g[v].pb(e.size());
	e.pb((edge){u,v,-1,false});
}
int D[MAXN],B[MAXN],T;
//int nbc;  // number of biconnected components
int art[MAXN];  // articulation point iff !=0
//stack<int> st;  // only for biconnected
void dfs(int u,int pe){
	B[u]=D[u]=T++;
	fore(_,0,g[u].size()){
		int ne=g[u][_];if(ne==pe)continue;
		int v=e[ne].u^e[ne].v^u;
		if(D[v]<0){
//			st.push(ne);
			dfs(v,ne);
//			if(B[v]>D[u])e[ne].bridge = true; // bridge
			if(B[v]>=D[u]){
				art[u]++; // articulation
//				int last; // start biconnected
//				do {
//					last=st.top();st.pop();
//					e[last].comp=nbc;
//				} while(last!=ne);
//				nbc++;    // end biconnected
			}
			B[u]=min(B[u],B[v]);
		}
		else if(D[v]<D[u])/*st.push(ne),*/B[u]=min(B[u],D[v]);
	}
}
void doit(){
	memset(D,-1,sizeof(D));
	memset(art,0,sizeof(art));
	/*nbc=*/T=0;
	fore(i,0,n)if(D[i]<0)dfs(i,-1),art[i]--;
}

int m;

int main(){
	while(scanf("%d%d",&n,&m),n){
		while(m--){
			int x,y;
			scanf("%d%d",&x,&y);x--;y--;
			add_edge(x,y);
		}
		doit();
		int r=0;
		fore(i,0,n)if(art[i])r++;
		printf("%d\n",r);
		fore(i,0,n)g[i].clear();
		e.clear();
	}
	return 0;
}
