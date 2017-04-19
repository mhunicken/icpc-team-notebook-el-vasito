struct UnionFind {
	int n,comp;
	vector<int> pre,si,c;
	UnionFind(int n=0):n(n),comp(n),pre(n),si(n, 1){
		fore(i,0,n)pre[i]=i;}
	int find(int x){return x==pre[x]?x:find(pre[x]);}
	bool join(int x, int y){
		if((x=find(x))==(y=find(y)))return false;
		if(si[x]<si[y])swap(x,y);
		si[x]+=si[y];pre[y]=x;comp--;c.pb(y);
		return true;
	}
	int snap(){return c.size();}
	void rollback(int snap){
		while(c.size()>snap){
			int x=c.back();c.pop_back();
			si[pre[x]]-=si[x];pre[x]=x;comp++;
		}
	}
};
enum {ADD,DEL,QUERY};
struct Query {int type,x,y;};
struct DynCon {
	vector<Query> q;
	UnionFind dsu;
	vector<int> mt;
	map<pair<int,int>,int> last;
	DynCon(int n):dsu(n){}
	void add(int x, int y){
		if(x>y) swap(x,y);
		q.pb((Query){ADD,x,y}),mt.pb(-1);
		last[mp(x,y)]=q.size()-1;
	}
	void remove(int x, int y){
		if(x>y)swap(x,y);
		q.pb((Query){DEL,x,y});
		int prev=last[mp(x,y)];
		mt[prev]=q.size()-1;
		mt.pb(prev);
	}
	void query(){
		q.pb((Query){QUERY,-1,-1});mt.pb(-1);}
	void process(){ // answers all queries in order
		if(!q.size())return;
		fore(i,0,q.size())if(q[i].type==ADD&&mt[i]<0)mt[i]=q.size();
		go(0,q.size());
	}
	void go(int l, int r){
		if(l+1==r){
			if(q[l].type == QUERY) // answer query using DSU
				printf("%d\n",dsu.comp);
			return;
		}
		int s=dsu.snap(),m=(l+r)/2;
		for(int i=r-1;i>=m;--i)if(mt[i]>=0&&mt[i]<l)dsu.join(q[i].x, q[i].y);
		go(l,m);
		dsu.rollback(s);
		for(int i=m-1;i>=l;--i)if(mt[i]>=r)dsu.join(q[i].x, q[i].y);
		go(m,r);
		dsu.rollback(s);
	}
};
