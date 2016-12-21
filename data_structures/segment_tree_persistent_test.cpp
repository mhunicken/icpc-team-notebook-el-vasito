#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define oper(a,b) ((a)+(b))
#define NEUT 0
struct STree { // persistent segment tree for min over integers
	vector<int> st,l,r;int n,sz;
	STree(int n): st(24*n,NEUT), l(24*n,0), r(24*n,0), n(n), sz(1) {}
	// be careful with memory! 4*n+q*log(n) . 24*n should be enough
	// if not initialized: 0 is root, equivalent to all neutral
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
	int upd(int k, int p, int v){return upd(k,0,n,p,v);}
	int query(int k, int a, int b){return query(k,0,n,a,b);}
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);

int n,X;
int p[1<<20],iq[1<<20],root[1<<20];

int f(int z){
	return (z-1+X)%n+1;
}

int main(){
	scanf("%d",&n);
	fore(i,0,n)scanf("%d",p+i),p[i]--;
	fore(i,0,n){
		int q;
		scanf("%d",&q);q--;
		iq[q]=i;
	}
	STree st(n);
	fore(i,0,n)root[i+1]=st.upd(root[i],iq[p[i]],1);
	int a,b,c,d,l1,r1,l2,r2,m;
	scanf("%d",&m);
	while(m--){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		l1=f(a);r1=f(b);if(l1>r1)swap(l1,r1);
		l2=f(c);r2=f(d);if(l2>r2)swap(l2,r2);
		l1--;l2--;
		int w=st.query(root[r1],l2,r2)-st.query(root[l1],l2,r2);
		printf("%d\n",w);
		X=w+1;
	}
	return 0;
}
