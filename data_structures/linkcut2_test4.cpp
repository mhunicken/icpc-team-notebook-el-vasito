// https://www.spoj.com/problems/DYNALCA/
#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

const int N_DEL = 0, N_VAL = 0; //delta, value
inline int mOp(int x, int y){return x+y;}//modify
inline int qOp(int lval, int rval){return lval + rval;}//query
inline int dOnSeg(int d, int len){return d==N_DEL ? N_DEL : d*len;}
//mostly generic
inline int joinD(int d1, int d2){
  if(d1==N_DEL)return d2;if(d2==N_DEL)return d1;return mOp(d1, d2);}
inline int joinVD(int v, int d){return d==N_DEL ? v : mOp(v, d);}
struct Node_t{
  int sz, nVal, tVal, d;
  bool rev;
  Node_t *c[2], *p;
  Node_t(int v) : sz(1), nVal(v), tVal(v), d(N_DEL), rev(0), p(0){
    c[0]=c[1]=0;
  }
  bool isRoot(){return !p || (p->c[0] != this && p->c[1] != this);}
  void push(){
    if(rev){
      rev=0; swap(c[0], c[1]);
      fore(x,0,2)if(c[x])c[x]->rev^=1;
    }
    nVal=joinVD(nVal, d); tVal=joinVD(tVal, dOnSeg(d, sz));
    fore(x,0,2)if(c[x])c[x]->d=joinD(c[x]->d, d);
    d=N_DEL;
  }
  void upd();
};
typedef Node_t* Node;
int getSize(Node r){return r ? r->sz : 0;}
int getPV(Node r){
  return r ? joinVD(r->tVal, dOnSeg(r->d,r->sz)) : N_VAL;}
void Node_t::upd(){
  tVal = qOp(qOp(getPV(c[0]), joinVD(nVal, d)), getPV(c[1]));
  sz = 1 + getSize(c[0]) + getSize(c[1]);
}
void conn(Node c, Node p, int il){if(c)c->p=p;if(il>=0)p->c[!il]=c;}
void rotate(Node x){
  Node p = x->p, g = p->p;
  bool gCh=p->isRoot(), isl = x==p->c[0];
  conn(x->c[isl],p,isl); conn(p,x,!isl);
  conn(x,g,gCh?-1:(p==g->c[0])); p->upd();
}
void spa(Node x){//splay
  while(!x->isRoot()){
    Node p = x->p, g = p->p;
    if(!p->isRoot())g->push();
    p->push(); x->push();
    if(!p->isRoot())rotate((x==p->c[0])==(p==g->c[0])? p : x);
    rotate(x);
  }
  x->push(); x->upd();
}
Node exv(Node x){//expose
  Node last=0;
  for(Node y=x; y; y=y->p)spa(y),y->c[0]=last,y->upd(),last=y;
  spa(x);
  return last;
}
void mkR(Node x){exv(x);x->rev^=1;}//makeRoot
Node getR(Node x){exv(x);while(x->c[1])x=x->c[1];spa(x);return x;}
Node lca(Node x, Node y){exv(x); return exv(y);}
bool connected(Node x, Node y){exv(x);exv(y); return x==y?1:x->p!=0;}
void link(Node x, Node y){mkR(x); x->p=y;}
void cut(Node x, Node y){mkR(x); exv(y); y->c[1]->p=0; y->c[1]=0;}
Node father(Node x){
	exv(x);
	Node r=x->c[1];
	if(!r)return 0;
	while(r->c[0])r=r->c[0];
	return r;
}
void cut(Node x){ // cuts x from father keeping tree root
	exv(father(x));x->p=0;}
int query(Node x, Node y){mkR(x); exv(y); return getPV(y);}
void modify(Node x, Node y, int d){mkR(x);exv(y);y->d=joinD(y->d,d);}
Node lift_rec(Node x, int t){
	if(!x)return 0;
	if(t==getSize(x->c[0])){spa(x);return x;}
	if(t<getSize(x->c[0]))return lift_rec(x->c[0],t);
	return lift_rec(x->c[1],t-getSize(x->c[0])-1);
}
Node lift(Node x, int t){
	exv(x);
	return lift_rec(x,t);
}
int depth(Node x){
	exv(x);
	return getSize(x)-1;
}

Node x[100005];
int n,m;

int main(){
	scanf("%d%d",&n,&m);
	fore(i,0,n)x[i]=new Node_t(i);
	while(m--){
		char s[8];
		scanf("%s",s);
		if(s[1]=='i'){
			int a,b;
			scanf("%d%d",&a,&b);a--;b--;
			link(x[a],x[b]);
		}
		else if(s[1]=='u'){
			int a;
			scanf("%d",&a);a--;
			cut(x[a]);
		}
		else {
			// Alternative inefficient version of LCA, just to test lift and depth
			int aa,bb,r;
			scanf("%d%d",&aa,&bb);aa--;bb--;
			Node a=x[aa],b=x[bb];
			int da=depth(a),db=depth(b);
			if(da<db){swap(da,db);swap(a,b);}
			for(int k=16;k>=0;--k)if(da-(1<<k)>=db){
				a=lift(a,1<<k);
				da-=1<<k;
			}
			if(a==b)r=a->nVal;
			else {
				for(int k=16;k>=0;--k){
					Node aa=lift(a,1<<k);
					Node bb=lift(b,1<<k);
					if(aa!=bb){
						a=aa;
						b=bb;
					}
				}
				r=father(a)->nVal;
			}
			printf("%d\n",r+1);
		}
	}
	return 0;
}
