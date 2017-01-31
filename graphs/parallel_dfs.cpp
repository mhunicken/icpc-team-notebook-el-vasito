struct Tree {
	int n,z[2];
	vector<vector<int>> g;
	vector<int> ex,ey,p,w,f,v[2];
	Tree(int n):g(n),w(n),f(n){}
	void add_edge(int x, int y){
		p.pb(g[x].size());g[x].pb(ex.size());ex.pb(x);ey.pb(y);
		p.pb(g[y].size());g[y].pb(ex.size());ex.pb(y);ey.pb(x);
	}
	bool go(int k){ // returns true if it finds new node
		int& x=z[k];
		while(x>=0&&
			(w[x]==g[x].size()||w[x]==g[x].size()-1&&(g[x].back()^1)==f[x]))
			x=f[x]>=0?ex[f[x]]:-1;
		if(x<0)return false;
		if((g[x][w[x]]^1)==f[x])w[x]++;
		int e=g[x][w[x]],y=ey[e];
		f[y]=e;w[x]++;w[y]=0;x=y;
		v[k].pb(x);
		return true;
	}
	vector<int> erase_edge(int e){
		e*=2; // erases eth edge, returns smaller component
		int x=ex[e],y=ey[e];
		p[g[x].back()]=p[e];
		g[x][p[e]]=g[x].back();g[x].pop_back();
		p[g[y].back()]=p[e^1];
		g[y][p[e^1]]=g[y].back();g[y].pop_back();
		f[x]=f[y]=-1;
		w[x]=w[y]=0;
		z[0]=x;z[1]=y;
		v[0]={x};v[1]={y};
		bool d0=true,d1=true;
		while(d0&&d1)d0=go(0),d1=go(1);
		if(d1)return v[0];
		return v[1];
	}
};
