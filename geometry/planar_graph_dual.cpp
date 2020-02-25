vector<int> g[MAXN];int n; // input graph (must be connected)
vector<int> gd[MAXN];int nd; // output graph
vector<int> nodes[MAXN]; // nodes delimiting region (in CW order)
map<pair<int,int>,int> ps,es;
void get_dual(vector<pt> p){ // p: points corresponding to nodes
	ps.clear();es.clear();
	fore(x,0,n){
		Cmp pc(p[x]); // (radial order of points)
		auto comp=[&](int a, int b){return pc(p[a],p[b]);};
		sort(g[x].begin(),g[x].end(),comp);
		fore(i,0,g[x].size())ps[{x,g[x][i]}]=i;
	}
	nd=0;
	fore(xx,0,n)for(auto yy:g[xx])if(!es.count({xx,yy})){
		int x=xx,y=yy;gd[nd].clear();nodes[nd].clear();
		while(!es.count({x,y})){
			es[{x,y}]=nd;nodes[nd].pb(y);
			int z=g[y][(ps[{y,x}]+1)%g[y].size()];x=y;y=z;
		}
		nd++;
	}
	for(auto p:es){
		pair<int,int> q={p.fst.snd,p.fst.fst};
		assert(es.count(q));
		if(es[q]!=p.snd)gd[p.snd].pb(es[q]);
	}
	fore(i,0,nd){
		sort(gd[i].begin(),gd[i].end());
		gd[i].erase(unique(gd[i].begin(),gd[i].end()),gd[i].end());
	}
}
