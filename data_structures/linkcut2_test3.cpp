/*
 * Contest: XVIII Open Cup named after E.V. Pankratiev
 *          Grand Prix of Korea
 * Problem: G
 * 
 * An example of adapting linkcut for queries of max edge in a path.
 * Change are mostly (if not all) in how Node_t does update and returns
 * value
 */

#include <bits/stdc++.h>
#define fore(x,a,b) for(int x=a,qwe=b; x<qwe; x++)
#define pb push_back
using namespace std;
typedef long long ll;

const int N_VALUE = -1;
struct Node_t{
  int sz; ll val; int u, v;
  bool rev;
  Node_t *ch[2], *p, *mxedge;
  Node_t(int u):sz(1),val(-1),u(u),v(u),rev(0),p(0){
    ch[0]=ch[1]=0;mxedge=this;
  }
  Node_t(int u, int v, ll c):sz(1),val(c),u(u),v(v),rev(0),p(0){
    ch[0]=ch[1]=0;mxedge=this;
  }
  bool isRoot(){return !p || (p->ch[0] != this && p->ch[1] != this);}
  void push(){
    if(rev){
      rev=0; swap(ch[0], ch[1]);
      fore(x,0,2)if(ch[x])ch[x]->rev^=1;
    }
  }
  void upd();
};
typedef Node_t* Node;
inline Node queryOp(Node lval, Node rval){
    if(!lval||!rval)return lval?lval:rval;
    return (lval->val>rval->val) ? lval : rval;
}
int getSize(Node r){return r ? r->sz : 0;}
Node getstVal(Node r){return r ? r->mxedge : 0;}
void Node_t::upd(){
  mxedge = queryOp(queryOp(this,getstVal(ch[0])),getstVal(ch[1]));
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
  for(Node y=x; y; y=y->p){
    splay(y);
    y->ch[1]=last;y->upd();last=y;
  }
  splay(x);
  return last;
}
Node findRoot(Node x){expose(x); while(x->ch[0])x=x->ch[0]; splay(x); return x;}
Node lca(Node x, Node y){expose(x);return expose(y);}//not tested
void makeRoot(Node x){expose(x);x->rev^=1;}
bool connected(Node x, Node y){if(x==y)return 1;expose(x);expose(y);return x->p;}
void link(Node x, Node y){makeRoot(x); x->p=y;}
void cut(Node x, Node y){makeRoot(x);expose(y);y->ch[0]->p = 0; y->ch[0]=0;}
Node query(Node x, Node y){makeRoot(x); expose(y); return getstVal(y);}

const int N=3e5+5;
int n, m, P[N];
vector<pair<int,ll> > g[N];
Node vs[N], es[N];

ll calc(int u){
    vector<tuple<Node,Node,int> > log;
    ll ans = 0;
    for(auto p : g[u]){
        int v=p.first;
        Node e=query(vs[u],vs[v]);
        cut(e,vs[e->v]);cut(vs[e->u],e);
        Node tmp=new Node_t(-1);
        link(tmp,vs[u]);link(vs[v],tmp);
        ans -= e->val;
        ans += p.second;
        log.push_back(make_tuple(tmp,e,v));
    }
    //restore
    for(auto t : log){
        Node erem=get<0>(t);
        cut(erem,vs[get<2>(t)]);cut(erem,vs[u]);
        delete erem;
    }
    for(auto t : log){
        Node eold=get<1>(t);
        link(eold,vs[eold->u]);link(eold,vs[eold->v]);
    }
    return ans;
}

struct Edge { 
    int u, v; ll c;
    bool operator<(const Edge& o)const{
        return c<o.c;
    }
};
vector<Edge> edges;
int find(int i){return i==P[i]?i:P[i]=find(P[i]);}

int main(){ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> n >> m;
    fore(x,0,n)P[x]=x,vs[x]=new Node_t(x);
    fore(x,0,m){
        int u,v;ll c; cin >> u >> v >> c; u--; v--;
        g[u].pb({v,c});g[v].pb({u,c});
        edges.pb(Edge{u,v,c});
    }
    sort(edges.begin(),edges.end());
    ll total = 0;
    fore(x,0,m){
        int u=edges[x].u,v=edges[x].v;
        es[x]=new Node_t(u,v,edges[x].c);
        int i=find(u), j=find(v);
        if(i!=j){
            total += edges[x].c;
            P[i]=j;
            link(es[x],vs[u]); link(vs[v],es[x]);
        }
    }
    fore(x,0,n)cout<<total+calc(x)<<"\n";   
}
