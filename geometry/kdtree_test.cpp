// Codeforces gym 100402C - AC
// https://codeforces.com/gym/100402/problem/C
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

struct pt{
	ll x,y;
	pt(ll x, ll y):x(x),y(y){}
	pt(){}
	ll norm2(){return *this**this;}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator /(ll t){return pt(x/t,y/t);}
	ll operator*(pt p){return x*p.x+y*p.y;}
	bool operator<(pt p)const{return x<p.x|(x==p.x&&y<p.y);}
};

ll INF=1e9;

// given a set of points, answer queries of nearest point in O(log(n))
bool onx(pt a, pt b){return a.x<b.x;}
bool ony(pt a, pt b){return a.y<b.y;}
struct Node {
	pt pp;
	ll x0=INF, x1=-INF, y0=INF, y1=-INF;
	Node *first=0, *second=0;
	ll distance(pt p){
		ll x=min(max(x0,p.x),x1);
		ll y=min(max(y0,p.y),y1);
		return (pt(x,y)-p).norm2();
	}
	Node(vector<pt>&& vp):pp(vp[0]){
		for(pt p:vp){
			x0=min(x0,p.x); x1=max(x1,p.x);
			y0=min(y0,p.y); y1=max(y1,p.y);
		}
		if(SZ(vp)>1){
			sort(ALL(vp),x1-x0>=y1-y0?onx:ony);
			int m=SZ(vp)/2;
			first=new Node({vp.begin(),vp.begin()+m});
			second=new Node({vp.begin()+m,vp.end()});
		}
	}
};
struct KDTree {
	Node* root;
	KDTree(const vector<pt>& vp):root(new Node({ALL(vp)})) {}
	pair<ll,pt> search(pt p, Node *node){
		if(!node->first){
			//avoid query point as answer
			//if(p==node->pp) {INF,pt()};
			return {(p-node->pp).norm2(),node->pp};
		}
		Node *f=node->first, *s=node->second;
		ll bf=f->distance(p), bs=s->distance(p);
		if(bf>bs)swap(bf,bs),swap(f,s);
		auto best=search(p,f);
		if(bs<best.fst) best=min(best,search(p,s));
		return best;
	}
	pair<ll,pt> nearest(pt p){return search(p,root);}
};

vector<pair<pt,int>> solve(vector<pair<pt,int>> &v){
	if(SZ(v)<=1) return v;
	int m=SZ(v)/2;

	//left
	auto lef=vector<pair<pt,int>>(v.begin(),v.begin()+m);
	lef=solve(lef);
	vector<pt> now; for(auto x:lef) now.pb(x.fst);
	auto kd=KDTree(now);

	//right
	vector<pair<pt,int>> rig;
	fore(i,m,SZ(v)){
		pt mid=v[i].fst/2;
		auto now=kd.nearest(mid).snd;
		if((now-mid).norm2() > (v[i].fst-mid).norm2()) rig.pb(v[i]);
	}
	rig=solve(rig);
	
	for(auto x:rig) lef.pb(x);
	return lef;
}

bool cmp(pair<pt,int> a, pair<pt,int> b){return a.fst.norm2()<b.fst.norm2();}

int main(){FIN;
	#ifdef ONLINE_JUDGE
		freopen("nothingontv.in","r",stdin);
		freopen("nothingontv.out","w",stdout);
	#endif
	int n; cin>>n;
	vector<pair<pt,int>> v(n);
	fore(i,0,n){
		ll x,y; cin>>x>>y; x*=2; y*=2;
		v[i]={pt(x,y),i};
	}
	sort(ALL(v),cmp);
	v=solve(v);
	vector<int> r;
	for(auto x:v) r.pb(x.snd);
	sort(ALL(r));
	cout<<SZ(r)<<"\n";
	for(auto x:r)cout<<x+1<<" "; cout<<"\n";
}
