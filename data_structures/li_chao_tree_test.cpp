// Universal Cup 15455 - AC
// https://contest.ucup.ac/contest/2668/problem/15455

#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef long double ld;

// LiChaoTree lct(sz) -> allows queries for all x in range [0,sz)
// lct.add(L)         -> add line L to range [0,sz) in O(log(sz))
// lct.add(L,st,en)   -> add line L to range [st,en) in O(log^2(sz))
// lct.query(x)       -> query maximum L(x) across all current lines in O(log(sz))

typedef ld T;
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

int main(){FIN;
	int n,m,k; cin>>n>>m>>k;
    vector<ll> a(n+1);
    fore(i,1,n+1) cin>>a[i];

    auto s=a;
    fore(i,1,n+1) s[i]+=s[i-1];

    vector<ll> mn(n+1,1e18),mx(n+1,-1e18);

    multiset<ll> all;
    fore(i,1,n+1){
        if(i+k<=n+1) all.insert(s[i+k-1]-s[i-1]);
        if(i-k>=1) all.erase(all.find(s[i-1]-s[i-k-1]));

        mn[i]=*all.begin();
        mx[i]=*all.rbegin();
    }

    vector<ld> ans(m+1, 2);

    for(auto x:a) ans[x]=0;

    {
        LiChaoTree lt(m+1);
    
        fore(i,1,n+1){
            if(mn[i]==a[i]*k) continue;

            ll low=(mn[i]+k-1)/k, up=a[i];
            ld avg=1.*mn[i]/k;

            ld A = 1. / (avg - a[i]);
            ld B = -1.*a[i] / (avg - a[i]);

            lt.add(Line(-A, -B), low, up+1);
        }

        fore(k,1,m+1) if(ans[k]>0){
            ans[k]=min(ans[k], -lt.query(k));
        }
    }

    {
        LiChaoTree lt(m+1);
    
        fore(i,1,n+1){
            if(mx[i]==a[i]*k) continue;

            ll low=a[i], up=mx[i]/k;
            ld avg=1.*mx[i]/k;

            ld A = 1. / (avg - a[i]);
            ld B = -1.*a[i] / (avg - a[i]);

            lt.add(Line(-A, -B), low, up+1);
        }

        fore(k,1,m+1) if(ans[k]>0){
            ans[k]=min(ans[k], -lt.query(k));
        }
    }

    cout<<fixed<<setprecision(10);
    fore(i,1,m+1){
        if(ans[i]>1.5) cout<<"-1\n";
        else cout<<ans[i]<<"\n";
    }
}
