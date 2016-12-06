typedef double th;
const th INF=1e18;  // to maximize: set INF to 1, use negative values
struct Hungarian {
	int n,m;  // important: n must be <=m
	vector<vector<th> > a;
	vector<th> u,v;vector<int> p,way;  // p: assignment
	Hungarian(int n, int m):
	n(n),m(m),a(n+1,vector<th>(m+1,INF-1)),u(n+1),v(m+1),p(m+1),way(m+1){}
	void set(int x, int y, th v){a[x+1][y+1]=v;}
	th assign(){
		fore(i,1,n+1){
			int j0=0;p[0]=i;
			vector<th> minv(m+1,INF);
			vector<char> used(m+1,false);
			do {
				used[j0]=true;
				int i0=p[j0],j1;th delta=INF;
				fore(j,1,m+1)if(!used[j]){
					th cur=a[i0][j]-u[i0]-v[j];
					if(cur<minv[j])minv[j]=cur,way[j]=j0;
					if(minv[j]<delta)delta=minv[j],j1=j;
				}
				fore(j,0,m+1)
					if(used[j])u[p[j]]+=delta,v[j]-=delta;
					else minv[j]-=delta;
				j0=j1;
			} while(p[j0]);
			do {
				int j1=way[j0];p[j0]=p[j1];j0=j1;
			} while(j0);
		}
		return -v[0];  // cost
	}
};
