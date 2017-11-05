vector<int> g[MAXN];
int n,m,mt[MAXN],qh,qt,q[MAXN],ft[MAXN],bs[MAXN];
bool inq[MAXN],inb[MAXN],inp[MAXN];
int lca(int root, int x, int y){
	memset(inp,0,sizeof(inp));
	while(1){
		inp[x=bs[x]]=true;
		if(x==root)break;
		x=ft[mt[x]];
	}
	while(1){
		if(inp[y=bs[y]])return y;
		else y=ft[mt[y]];
	}
}
void mark(int z, int x){
	while(bs[x]!=z){
		int y=mt[x];
		inb[bs[x]]=inb[bs[y]]=true;
		x=ft[y];
		if(bs[x]!=z)ft[x]=y;
	}
}
void contr(int s, int x, int y){
	int z=lca(s,x,y);
	memset(inb,0,sizeof(inb));
	mark(z,x);mark(z,y);
	if(bs[x]!=z)ft[x]=y;
	if(bs[y]!=z)ft[y]=x;
	fore(x,0,n)if(inb[bs[x]]){
		bs[x]=z;
		if(!inq[x])inq[q[++qt]=x]=true;
	}
}
int findp(int s){
	memset(inq,0,sizeof(inq));
	memset(ft,-1,sizeof(ft));
	fore(i,0,n)bs[i]=i;
	inq[q[qh=qt=0]=s]=true;
	while(qh<=qt){
		int x=q[qh++];
		for(int y:g[x])if(bs[x]!=bs[y]&&mt[x]!=y){
			if(y==s||mt[y]>=0&&ft[mt[y]]>=0)contr(s,x,y);
			else if(ft[y]<0){
				ft[y]=x;
				if(mt[y]<0)return y;
				else if(!inq[mt[y]])inq[q[++qt]=mt[y]]=true;
			}
		}
	}
	return -1;
}
int aug(int s, int t){
	int x=t,y,z;
	while(x>=0){
		y=ft[x];
		z=mt[y];
		mt[y]=x;mt[x]=y;
		x=z;
	}
	return t>=0;
}
int edmonds(){ // O(n^2 m)
	int r=0;
	memset(mt,-1,sizeof(mt));
	fore(x,0,n)if(mt[x]<0)r+=aug(x,findp(x));
	return r;
}
