struct LCTree{ // Search MIN, Comments to MAX
    struct F{vector<ll> a;ll operator()(ll x)const{return a[0]+x*a[1];}};//intersect others 1
    const F NEUT={{ll(1e18), 0}}; // MAX: -1e18
    bool cmp(const F&fa, const F&fb,ll x){return fa(x)<fb(x);} // MAX: >
    struct Node{
        F f;Node *l,*r;
        Node(F ff):f(ff),l(0),r(0){}
        ~Node(){delete l;delete r;}
    };
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
//LCTree lt(a,b);LCTree::F f;lt.upd(f);lt.query(x);
//LCTree *plt;lt.merge(plt);delete plt;lt.sz;
};