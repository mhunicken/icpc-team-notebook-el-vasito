#define oper min
#define NEUT INF
struct STree { // persistent segment tree for min over integers
	vector<int> st,l,r;int n,sz,rt;
	STree(int n): st(24*n,NEUT),l(24*n,0),r(24*n,0),n(n),rt(0),sz(1){}
	// be careful with memory! 4*n+q*log(n) . 24*n should be enough
	int init(int s, int e, int *a){ // not necessary in most cases
		int k=sz++;
		if(s+1==e){st[k]=a[s];return k;}
		int m=(s+e)/2;
		l[k]=init(s,m,a);r[k]=init(m,e,a);
		st[k]=oper(st[l[k]],st[r[k]]);
		return k;
	}
	int upd(int k, int s, int e, int p, int v){
		int nk=sz++;l[nk]=l[k];r[nk]=r[k];
		if(s+1==e){st[nk]=v;return nk;}
		int m=(s+e)/2;
		if(p<m)l[nk]=upd(l[k],s,m,p,v);
		else r[nk]=upd(r[k],m,e,p,v);
		st[nk]=oper(st[l[nk]],st[r[nk]]);
		return nk;
	}
	int query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return NEUT;
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(l[k],s,m,a,b),query(r[k],m,e,a,b));
	}
	int init(int *a){return init(0,n,a);}
	int upd(int k, int p, int v){return rt=upd(k,0,n,p,v);}
	int upd(int p, int v){return upd(rt,p,v);} // update on last root
	int query(int k, int a, int b){return query(k,0,n,a,b);}
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);
