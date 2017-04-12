typedef ll tw;const tw INF=1LL<<60;
struct edge {int src,dst;tw w;};
struct ChuLiu {
	int n,r;tw cost;bool found;
	vector<int> no,pr,mark;
	vector<vector<int> > comp,nx;
	vector<tw> mcost;
	vector<vector<edge> > h;
	ChuLiu(int n):n(n),h(n){}
	void add_edge(int x, int y, tw w){h[y].pb((edge){x,y,w});}
	void visit(int v, int s){
		if(mark[v]){
			vector<int> temp=no;found=true;
			do {
				cost+=mcost[v];v=pr[v];
				if(v!=s)while(comp[v].size()>0){
					no[comp[v].back()]=s;
					comp[s].pb(comp[v].back());
					comp[v].pop_back();
				}
			}while(v!=s);
			for(int j:comp[s])if(j!=r)for(edge& e:h[j])
				if(no[e.src]!=s)e.w-=mcost[temp[j]];
		}
		mark[v]=true;
		for(int i:nx[v])if(no[i]!=no[v]&&pr[no[i]]==v)
			if(!mark[no[i]]||i==s)
				visit(i,s);
	}
	tw doit(int _r){ // r: root (O(nm))
		r=_r;
		no.resize(n);comp.clear();comp.resize(n);
		fore(x,0,n)comp[x].pb(no[x]=x);
		for(cost=0;;){
			pr.clear();pr.resize(n,-1);
			mcost=vector<tw>(n,INF);
			fore(j,0,n)if(j!=r)for(edge e:h[j])
				if(no[e.src]!=no[j]&&e.w<mcost[no[j]])
					mcost[no[j]]=e.w,pr[no[j]]=no[e.src];
			nx.clear();nx.resize(n);
			fore(x,0,n)if(pr[x]>=0)nx[pr[x]].pb(x);
			bool stop=true;
			mark.clear();mark.resize(n);
			fore(x,0,n)if(x!=r&&!mark[x]&&!comp[x].empty()){
				found=false;visit(x,x);
				if(found)stop=false;
			}
			if(stop){
				fore(x,0,n)if(pr[x]>=0)cost+=mcost[x];
				return cost;
			}
		}
	}
};
