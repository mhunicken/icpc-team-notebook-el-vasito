typedef ll tf;const tf INFFLUJO=1e14;
typedef ll tc;const tc INFCOSTO=1e14;
struct edge {
	int u,v;tf cap,flow;tc cost;
	tf rem(){return cap-flow;}
};
int nodes; // remember to init nodes
vector<int> g[MAXN];
vector<edge> e;
void add_edge(int u, int v, tf cap, tc cost) {
	g[u].pb(SZ(e));e.pb((edge){u,v,cap,0,cost});
	g[v].pb(SZ(e));e.pb((edge){v,u,0,0,-cost});
}
tc dist[MAXN],mncost;
int pre[MAXN];
tf cap[MAXN],mxflow;
bool in_queue[MAXN];
void flow(int s, int t){
	memset(in_queue,0,sizeof(in_queue));
	mxflow=mncost=0;
	while(1){
		fill(dist,dist+nodes,INFCOSTO);dist[s]=0;
		memset(pre,-1,sizeof(pre));pre[s]=0;
		memset(cap,0,sizeof(cap));cap[s]=INFFLUJO;
		queue<int> q;q.push(s);in_queue[s]=1;
		while(SZ(q)){
			int u=q.front();q.pop();in_queue[u]=0;
			fore(_,0,SZ(g[u])){
				int i=g[u][_];
				edge &E=e[i];
				if(E.rem()&&dist[E.v]>dist[u]+E.cost+1e-9){
					dist[E.v]=dist[u]+E.cost;
					pre[E.v]=i;
					cap[E.v]=min(cap[u],E.rem());
					if(!in_queue[E.v])q.push(E.v),in_queue[E.v]=1;
				}
			}
		}
		if(pre[t]<0)break;
		mxflow+=cap[t];mncost+=cap[t]*dist[t];
		for(int v=t;v!=s;v=e[pre[v]].u){
			e[pre[v]].flow+=cap[t];e[pre[v]^1].flow-=cap[t];
		}
	}
}
