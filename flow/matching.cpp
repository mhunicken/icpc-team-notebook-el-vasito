// both sides numbered [0,n) and [0,m)
vector<int> g[MAXN];
int mat[MAXM];bool vis[MAXN];
int n,m;
int match(int x){
	if(vis[x])return 0;
	vis[x]=true;
	fore(i,0,g[x].size()){
		int y=g[x][i];
		if(mat[y]<0||match(mat[y])){mat[y]=x;return 1;}
	}
	return 0;
}
vector<pair<int,int> > max_matching(){
	vector<pair<int,int> > r;
	memset(mat,-1,sizeof(mat));
	fore(i,0,n)memset(vis,false,sizeof(vis)),match(i);
	fore(i,0,m)if(mat[i]>=0)r.pb(mp(mat[i],i));
	return r;
}
