// Min cut: nodes with dist>=0 vs nodes with dist<0
// Matching MVC: left nodes with dist<0 + right nodes with dist>0
int nodes,src,dst; // remember to init nodes
int dist[MAXN],q[MAXN],work[MAXN];
struct edge {int to,rev;ll f,cap;};
vector<edge> g[MAXN];
void add_edge(int s, int t, ll cap){
	g[s].pb((edge){t,SZ(g[t]),0,cap});
	g[t].pb((edge){s,SZ(g[s])-1,0,0});
}
bool dinic_bfs(){
	fill(dist,dist+nodes,-1);dist[src]=0;
	int qt=0;q[qt++]=src;
	for(int qh=0;qh<qt;qh++){
		int u=q[qh];
		fore(i,0,SZ(g[u])){
			edge &e=g[u][i];int v=g[u][i].to;
			if(dist[v]<0&&e.f<e.cap)dist[v]=dist[u]+1,q[qt++]=v;
		}
	}
	return dist[dst]>=0;
}
ll dinic_dfs(int u, ll f){
	if(u==dst)return f;
	for(int &i=work[u];i<SZ(g[u]);i++){
		edge &e=g[u][i];
		if(e.cap<=e.f)continue;
		int v=e.to;
		if(dist[v]==dist[u]+1){
			ll df=dinic_dfs(v,min(f,e.cap-e.f));
			if(df>0){e.f+=df;g[v][e.rev].f-=df;return df;}
		}
	}
	return 0;
}
ll max_flow(int _src, int _dst){
	src=_src;dst=_dst;
	ll result=0;
	while(dinic_bfs()){
		fill(work, work+nodes, 0);
		while(ll delta=dinic_dfs(src,INF))result+=delta;
	}
	return result;
}
