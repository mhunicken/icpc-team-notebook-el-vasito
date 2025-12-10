// LiChaoTree lct(sz) -> allows queries for all x in range [0,sz)
// lct.add(L)         -> add line L to range [0,sz) in O(log(sz))
// lct.add(L,st,en)   -> add line L to range [st,en) in O(log^2(sz))
// lct.query(x)       -> query maximum L(x) across all current lines in O(log(sz))

typedef long long T;
T INF=1e18;

struct Line{
	T a, b;
	Line():a(0),b(-INF){}
	Line(T a, T b):a(a),b(b){}
	T get(T x){return a*x+b;}
};

struct LiChaoTree{
	struct Node{
		Line line;
		Node *lc,*rc=0;
	}*root;
	int sz;
	LiChaoTree(int sz): root(new Node()), sz(sz){}

	void addRec(Node* &n, int tl, int tr, Line x){
		if(!n) n=new Node();
		if(n->line.get(tl)<x.get(tl)) swap(n->line,x);
		if(n->line.get(tr-1)>=x.get(tr-1)||tl+1==tr) return;
		int mid=(tl+tr)/2;
		if(n->line.get(mid)>x.get(mid)){
			addRec(n->rc,mid,tr,x);
		}
		else{
			swap(n->line,x);
			addRec(n->lc,tl,mid,x);
		}
	}

	void add(Node* &n, int tl, int tr, int l, int r, Line x){
		if(tr<=l||r<=tl) return;
		if(!n) n=new Node();
		if(l<=tl&&tr<=r) return addRec(n,tl,tr,x);
		int mid=(tl+tr)/2;
		add(n->lc,tl,mid,l,r,x);
		add(n->rc,mid,tr,l,r,x);
	}

	T query(Node* &n, int tl, int tr, int x){
		if(!n) return -INF;
		if(tl+1==tr) return n->line.get(x);
		T res=n->line.get(x);
		int mid=(tl+tr)/2;
		if(x<mid) res=max(res, query(n->lc,tl,mid,x));
		else res=max(res, query(n->rc,mid,tr,x));
		return res;
	}

	void add(Line x){add(root,0,sz,0,sz,x);}
	void add(Line x, int l, int r){add(root,0,sz,l,r,x);}
	T query(int x){return query(root,0,sz,x);}
};