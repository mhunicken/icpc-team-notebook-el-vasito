// UVA 11721 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2768
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define INF (1LL<<60)
#define MAXN 1024

vector<int> w;

int n;
vector<pair<int,int> > g[MAXN]; // u->[(v,cost)]
ll dist[MAXN];
void bford(int src){ // O(nm)
	fill(dist,dist+n,INF);dist[src]=0;
	fore(_,0,n-1)fore(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		dist[t.fst]=min(dist[t.fst],dist[x]+t.snd);
	}
	fore(x,0,n)if(dist[x]!=INF)for(auto t:g[x]){
		if(dist[t.fst]>dist[x]+t.snd){
			// neg cycle: all nodes reachable from t.fst have -INF distance
			// to reconstruct neg cycle: save "prev" of each node, go up from t.fst until repeating a node. this node and all nodes between the two occurences form a neg cycle
			w.pb(t.fst);
		}
	}
}

int m;
bool vis[MAXN];

void dfs(int x){
	if(vis[x])return;
	vis[x]=true;
	for(auto p:g[x])dfs(p.fst);
}

int main(){
	int tn;
	scanf("%d",&tn);
	fore(tc,1,tn+1){
		scanf("%d%d",&n,&m);
		fore(i,0,n)g[n].pb({i,0});
		n++;
		while(m--){
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
			g[y].pb({x,c});
		}
		bford(n-1);
		memset(vis,false,sizeof(vis));
		for(int x: w){
			dfs(x);
		}
		printf("Case %d:",tc);
		if(w.empty())puts(" impossible");
		else {fore(i,0,n)if(vis[i])printf(" %d",i);puts("");}
		fore(i,0,n)g[i].clear();
		w.clear();
	}
	return 0;
}
