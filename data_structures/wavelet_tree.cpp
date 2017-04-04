struct WT {
	vector<int> wt[1<<20];int n;
	void init(int k, int s, int e){
		if(s+1==e)return;
		wt[k].clear();wt[k].pb(0);
		int m=(s+e)/2;
		init(2*k,s,m);init(2*k+1,m,e);
	}
	void add(int k, int s, int e, int v){
		if(s+1==e)return;
		int m=(s+e)/2;
		if(v<m)wt[k].pb(wt[k].back()),add(2*k,s,m,v);
		else wt[k].pb(wt[k].back()+1),add(2*k+1,m,e,v);
	}
	int query0(int k, int s, int e, int a, int b, int i){
		if(s+1==e)return s;
		int m=(s+e)/2;
		int q=(b-a)-(wt[k][b]-wt[k][a]);
		if(i<q)return query0(2*k,s,m,a-wt[k][a],b-wt[k][b],i);
		else return query0(2*k+1,m,e,wt[k][a],wt[k][b],i-q);
	}
	void upd(int k, int s, int e, int i){
		if(s+1==e)return;
		int m=(s+e)/2;
		int v0=wt[k][i+1]-wt[k][i],v1=wt[k][i+2]-wt[k][i+1];
		if(!v0&&!v1)upd(2*k,s,m,i-wt[k][i]);
		else if(v0&&v1)upd(2*k+1,m,e,wt[k][i]);
		else if(v0)wt[k][i+1]--;
		else wt[k][i+1]++;
	}
	void init(int _n){n=_n;init(1,0,n);} // (values in range [0,n))
	void add(int v){add(1,0,n,v);}
	int query0(int a, int b, int i){ // ith element in range [a,b)
		return query0(1,0,n,a,b,i);    // (if it was sorted)
	}
	void upd(int i){ // swap positions i,i+1
		upd(1,0,n,i);
	}
};
