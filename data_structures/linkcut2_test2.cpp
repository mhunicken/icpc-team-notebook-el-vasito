#include <bits/stdc++.h>
#define fore(x,a,b) for(int x=a,qwe=b; x<qwe; x++)
using namespace std;

const int N_DELTA = 0, N_VALUE = 0;
inline int modifyOp(int x, int y){return x+y;}
inline int queryOp(int lval, int rval){return max(lval,rval);}
inline int dOnSeg(int d, int len){return d==N_DELTA ? N_DELTA : d;}
//mostly generic
inline int joinVD(int v, int d){ return d==N_DELTA ? v : modifyOp(v, d);}
inline int joinDeltas(int d1, int d2){
  if(d1==N_DELTA)return d2; if(d2==N_DELTA)return d1; return modifyOp(d1, d2);
}
struct Node_t{
  int sz, nVal, stVal, d;
  bool rev;
  Node_t *ch[2], *p;
  Node_t(int v) : sz(1), nVal(v), stVal(v), d(N_DELTA), rev(0), p(0){
    ch[0]=ch[1]=0;
  }
  bool isRoot(){return !p || (p->ch[0] != this && p->ch[1] != this);}
  void push(){
    if(rev){
      rev=0; swap(ch[0], ch[1]);
      fore(x,0,2)if(ch[x])ch[x]->rev^=1;
    }
    nVal=joinVD(nVal, d); stVal=joinVD(stVal, dOnSeg(d, sz));
    fore(x,0,2)if(ch[x])ch[x]->d=joinDeltas(ch[x]->d, d);
    d=N_DELTA;
  }
  void upd();
};
typedef Node_t* Node;
int getSize(Node r){return r ? r->sz : 0;}
int getstVal(Node r){
  return r ? joinVD(r->stVal, dOnSeg(r->d,r->sz)) : N_VALUE;}
void Node_t::upd(){
  stVal = queryOp(queryOp(getstVal(ch[0]), joinVD(nVal, d)), getstVal(ch[1]));
  sz = 1 + getSize(ch[0]) + getSize(ch[1]);
}
void connect(Node ch, Node p, int isl){if(ch)ch->p=p; if(isl>=0)p->ch[1-isl]=ch;}
void rotate(Node x){
  Node p = x->p, g = p->p;
  bool gCh=p->isRoot(), isl = x==p->ch[0];
  connect(x->ch[isl],p,isl);connect(p,x,!isl);connect(x,g,gCh?-1:(p==g->ch[0]));
  p->upd();
}
void splay(Node x){
  while(!x->isRoot()){
    Node p = x->p, g = p->p;
    if(!p->isRoot())g->push();
    p->push(); x->push();
    if(!p->isRoot())rotate((x==p->ch[0])==(p==g->ch[0])? p : x);
    rotate(x);
  }
  x->push(); x->upd();
}
Node expose(Node x){
  Node last=0;
  for(Node y=x; y; y=y->p)splay(y),y->ch[0]=last,y->upd(),last=y;
  splay(x);
  return last;
}
Node findRoot(Node x){expose(x); while(x->ch[1])x=x->ch[1]; splay(x); return x;}
Node lca(Node x, Node y){expose(x); return expose(y);}
void makeRoot(Node x){expose(x); x->rev^=1;}
bool connected(Node x, Node y){if(x==y)return 1; expose(x);expose(y); return x->p;}
void link(Node x, Node y){makeRoot(x); x->p=y;}
void cut(Node x, Node y){makeRoot(x); expose(y); y->ch[1]->p = 0; y->ch[1]=0;}
int query(Node x, Node y){makeRoot(x); expose(y); return getstVal(y);}
void modify(Node x, Node y, int d){makeRoot(x); expose(y); y->d = joinDeltas(y->d, d);}

const int N=1e5;
int n;
Node x[N];

int main(){ios_base::sync_with_stdio(0);cout.tie(0);cin.tie(0);
    cin >> n;
	fore(i,0,n)x[i]=new Node_t(0);
    fore(i,0,n-1){
        int a, b; cin >> a >> b;a--;b--;
        link(x[a],x[b]);
    }
    int q; cin >> q;
    while(q--){
        char c; int a, b; cin >> c >> a >> b; a--; b--;
        if(c=='G') cout << query(x[a],x[b]) << "\n";
        else if(c=='I') b++, modify(x[a],x[a],b);
    }
}
