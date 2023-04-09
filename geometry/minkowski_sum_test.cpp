// Codeforces gym 104288K - AC
// http://codeforces.com/gym/104288/problem/K
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

ll EPS=0;

struct pt{
	ll x,y;
	pt(){}
	pt(ll x, ll y):x(x),y(y){}
	ll norm2(){return *this**this;}
	pt operator +(pt p){return pt(x+p.x,y+p.y);}
	pt operator -(pt p){return pt(x-p.x,y-p.y);}
	pt operator *(ll k){return pt(x*k,y*k);}
	pt operator /(ll k){return pt(x/k,y/k);}
	ll operator *(pt p){return x*p.x+y*p.y;}
	ll operator %(pt p){return x*p.y-y*p.x;}
	bool left(pt p, pt q){return (q-p)%(*this-p)>=0;}
	bool operator <(pt p){return x<p.x||(x==p.x&&y<p.y);}
};

typedef vector<pt> poly;
 
vector<pt> chull(vector<pt> p){
	if(SZ(p)<3)return p;
	vector<pt> r;
	sort(ALL(p));
	fore(i,0,p.size()){
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}

// Compute Minkowski sum of two CONVEX polygons (remove collinear first)
// Returns answer in CCW order
void reorder(vector<pt> &p){
	if(!p[2].left(p[0],p[1])) reverse(ALL(p));
	int pos=0;
	fore(i,1,SZ(p)) if(pt(p[i].y,p[i].x) < pt(p[pos].y,p[pos].x)) pos=i;
	rotate(p.begin(), p.begin()+pos, p.end());
}
vector<pt> minkowski_sum(vector<pt> p, vector<pt> q){
	if(min(SZ(p),SZ(q))<3){
	  vector<pt> v;
		for(pt pp:p) for(pt qq:q) v.pb(pp+qq);
		return chull(v);
	}
	reorder(p); reorder(q);
	fore(i,0,2) p.pb(p[i]), q.pb(q[i]);
	vector<pt> r;
	int i=0,j=0;
	while(i+2<SZ(p)||j+2<SZ(q)){
		r.pb(p[i]+q[j]);
		auto cross=(p[i+1]-p[i])%(q[j+1]-q[j]);
		i+=cross>=-EPS;
		j+=cross<=EPS;
	}
	return r;
}

vector<pt> add(vector<pt> p, vector<pt> q){
	if(!SZ(p)) return q;
	if(!SZ(q)) return p;
	return minkowski_sum(p,q);
}

poly mul(poly p, ll k){
	for(auto &x:p) x=x*k;
	return p;
}

const int MAXN=10010;
poly wh[MAXN];
vector<int> g[MAXN];

void dfs(int pos){
	if(!SZ(g[pos])) return;
	
	for(auto x:g[pos]) dfs(x);
	
	vector<poly> lef,rig;
	
	poly now;
	fore(i,0,SZ(g[pos])){
		lef.pb(now);
		now=add(now,mul(wh[g[pos][i]],-1));
	}
	
	now.clear();
	for(int i=SZ(g[pos])-1;i>=0;i--){
		rig.pb(now);
		now=add(now,mul(wh[g[pos][i]],-1));
	}
	reverse(ALL(rig));
	
	poly all;
	fore(i,0,SZ(g[pos])){
		now=add(wh[g[pos][i]], add(lef[i],rig[i]));
		for(auto p:now) all.pb(p);
	}
	
	wh[pos]=chull(all);
}

int main(){FIN;
	int n; cin>>n;
	fore(i,0,n){
		int k; cin>>k;
		if(k==0){
			int x,y; cin>>x>>y;
			wh[i].pb(pt(x,y));
		}
		else{
			fore(j,0,k){
				int x; cin>>x; x--;
				g[i].pb(x);
			}
		}
	}
	
	dfs(0);
	
	ll ans=0;
	for(auto p:wh[0]) ans=max(ans, p.norm2());
	cout<<ans<<"\n";
}
