// UVA 12532 - AC
// https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=3977
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define oper(a,b) (a*b)
#define NEUT 1
struct STree { // segment tree for min over integers
	vector<int> st;int n;
	STree(int n): st(4*n+5,NEUT), n(n) {}
	void init(int k, int s, int e, int *a){
		if(s+1==e){st[k]=a[s];return;}
		int m=(s+e)/2;
		init(2*k,s,m,a);init(2*k+1,m,e,a);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	void upd(int k, int s, int e, int p, int v){
		if(s+1==e){st[k]=v;return;}
		int m=(s+e)/2;
		if(p<m)upd(2*k,s,m,p,v);
		else upd(2*k+1,m,e,p,v);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	int query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return NEUT;
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
	}
	void init(int *a){init(1,0,n,a);}
	void upd(int p, int v){upd(1,0,n,p,v);}
	int query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(i,v);rmq.query(s,e);

int sgn(int a){
	if(a>0)return 1;
	if(a<0)return -1;
	return 0;
}

char tochar(int a){
	if(a>0)return '+';
	if(a<0)return '-';
	return '0';
}

int x[100005];

int main(){
	int n,q;
	while(scanf("%d%d",&n,&q)!=EOF){
		STree rmq(n);
		fore(i,0,n)scanf("%d",x+i),x[i]=sgn(x[i]);
		rmq.init(x);
		while(q--){
			char t[4];
			int a,b;
			scanf("%s%d%d",t,&a,&b);a--;
			if(t[0]=='C')rmq.upd(a,sgn(b));
			else putchar(tochar(rmq.query(a,b)));
		}
		puts("");
	}
	return 0;
}
