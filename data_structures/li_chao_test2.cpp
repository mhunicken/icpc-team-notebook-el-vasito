// C. Kalila and Dimna in the Logging Industry: AC
// https://codeforces.com/problemset/problem/319/C

#include <bits/stdc++.h>

using namespace std;

#define fore(i, a, b) for(ll i = a, bella = b; i < bella; i++)
#define mset(a, b) memset(a, b, sizeof(a))
#define ALL(a) a.begin(), a.end()
#define SZ(a) ll(a.size())
#define fst first 
#define snd second
#define pb push_back
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

const int MAXN = 1e5+7;
int a[MAXN], b[MAXN]; ll val[MAXN];

struct LCTree{ // Search MIN, Comments to MAX
    struct F{vector<ll> a;ll operator()(ll x)const{return a[0]+x*a[1];}};//intersect others 1
    const F NEUT={{ll(1e18), 0}}; // MAX: -1e18
    bool cmp(const F&fa, const F&fb,ll x){return fa(x)<fb(x);} // MAX: >
    struct Node{F f;Node *l,*r;
        Node(F ff):f(ff),l(0),r(0){}
        ~Node(){delete l;delete r;}};
    ll a,b;int sz;Node *root;
    LCTree(ll aa,ll bb):a(aa),b(bb),sz(1){root=new Node(NEUT);}
    ~LCTree(){delete root;}
    Node *upd2(ll s,ll e,F &f,Node *sig){
        if(!sig)sig=new Node(f),sz++;
        else upd(s,e,f,sig);
        return sig;
    }
    void upd(ll s,ll e,F &f,Node *st){
        if(s+1==e&&cmp(f,st->f,s))st->f=f;
        ll m=(s+e)/2;
        int val=cmp(f,st->f,s)*100+cmp(f,st->f,m)*10+cmp(f,st->f,e);
        if(val==11)swap(f,st->f),st->l=upd2(s,m,f,st->l);
        else if(val==110)swap(f,st->f),st->r=upd2(m,e,f,st->r);
        else if(val==111)st->f=f;
        else if(val==1)st->r=upd2(m,e,f,st->r);
        else if(val==100)st->l=upd2(s,m,f,st->l);
        assert(val!=10&&val!=101); // F prop
    }
    ll query(ll s,ll e,ll x,Node *st){
        if(s+1==e)return st->f(x);
        ll m=(s+e)/2;
        if(x<m&&st->l)return min(st->f(x),query(s,m,x,st->l)); // MAX: max()
        else if(st->r)return min(st->f(x),query(m,e,x,st->r)); // MAX: max()
        else return st->f(x);
    }
    void merge(Node *st){
        upd(st->f);if(st->l)merge(st->l);
        if(st->r)merge(st->r);
    }
    void upd(F f){upd(a,b,f,root);}
    ll query(ll x){return query(a,b,x,root);}
    void merge(LCTree *lct){merge(lct->root);}
    // LCTree lct(a,b);LCTree::F f;lct.upd(f);lct.query(x);
    // LCTree *plct;lct.merge(plct);delete plct;lct.sz;
};

int main() { FIO;

    int n; cin >> n;
    fore(i, 0, n) cin >> a[i];
    fore(i, 0, n) cin >> b[i];

    LCTree lct(1, 1e9+7);
    val[0] = 0;
    fore(i, 1, n){
    lct.upd({{val[i-1], b[i-1]}});
    val[i] = lct.query(a[i]);
    }
    cout << val[n-1] << '\n';

    return 0;
}