#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(n) ((int)(n).size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
  
#define oper(a,b) a+b
#define NEUT 0
struct STree { // persistent segment tree for min over integers
  vector<int> st, L, R; int n,sz,rt;
  STree(int n): st(1,NEUT),L(1,0),R(1,0),n(n),rt(0),sz(1){}
  int new_node(int v, int l=0, int r=0){
      int ks=SZ(st);
      st.pb(v);L.pb(l);R.pb(r);
      return ks;
  }
  int init(int s, int e, int *a){ // not necessary in most cases
      if(s+1==e)return new_node(a[s]);
      int m=(s+e)/2, l=init(s,m,a),r=init(m,e,a);
      return new_node(oper(st[l],st[r]),l,r);
  }
  int upd(int k, int s, int e, int p, int v){
      int ks=new_node(st[k],L[k],R[k]);
      if(s+1==e){st[ks]=v;return ks;}
      int m=(s+e)/2, ps;
      if(p<m)ps=upd(L[ks],s,m,p,v),L[ks]=ps;
      else ps=upd(R[ks],m,e,p,v),R[ks]=ps;
      st[ks] = oper(st[L[ks]],st[R[ks]]);
      return ks;
  }
  int query(int k, int s, int e, int a, int b){
      if(e<=a||b<=s)return NEUT;
      if(a<=s&&e<=b)return st[k];
      int m=(s+e)/2;
      return oper(query(L[k],s,m,a,b),query(R[k],m,e,a,b));
  }
	int init(int *a){return init(0,n,a);}
	int upd(int k, int p, int v){return rt=upd(k,0,n,p,v);}
	int upd(int p, int v){return upd(rt,p,v);} // update on last root
  int query(int k,int a, int b){return query(k,0,n,a,b);};
}; // usage: STree rmq(n);root=rmq.init(x);new_root=rmq.upd(root,i,v);rmq.query(root,s,e);

int lst[1000010];
 
int main(){FIN;
  int n; cin >> n;
  vector<int> root={0};
  STree s(n+1);
  fore(i,1,n+1){
    int x; cin >> x;
    int r=root.back();
    if(lst[x]) r=s.upd(lst[x],0);
    root.pb(s.upd(r,i,1));
    lst[x]=i;
  }
  int q; cin >> q;
  while(q--){
    int x,y; cin >> x >> y;
    cout << s.query(root[y],1,n+1)-s.query(root[y],1,x) << "\n";
  }
} 
