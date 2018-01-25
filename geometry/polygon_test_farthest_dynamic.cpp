// AC
// http://codeforces.com/group/3qadGzUdR4/contest/101707/problem/I
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

#define double ll
#define EPS 0

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(x*t,y*t);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x||x==p.x&&y<p.y;}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>=0;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

ll nq,tq,ta,nit;

// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;//r.reserve(SZ(p));
	sort(p.begin(),p.end()); // first x, then y
	fore(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	if(!SZ(r))return p;
	return r;
}

struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	pt farthest(pt v){ // O(log(n)) only CONVEX
		if(n<10){
			int k=0;
			fore(i,1,n)if(v*(p[i]-p[k])>EPS)k=i;
			return p[k];
		}
		if(n==SZ(p))p.pb(p[0]);
		pt a=p[1]-p[0];
		int s=0,e=n,ua=v*a>EPS;
		if(!ua&&v*(p[n-1]-p[0])<=EPS)return p[0];
		while(1){
			int m=(s+e)/2;pt c=p[m+1]-p[m];
			int uc=v*c>EPS;
			if(!uc&&v*(p[m-1]-p[m])<=EPS)return p[m];
			if(ua&&(!uc||v*(p[s]-p[m])>EPS))e=m;
			else if(ua||uc||v*(p[s]-p[m])>=-EPS)s=m,a=c,ua=uc;
			else e=m;
			assert(e>s+1);
		}
	}
};


#define INF ((1LL<<63)-1)

vector<pol> w;
void add(pt q){
	vector<pt> p={q};
	while(!w.empty()&&SZ(w.back().p)<2*SZ(p)){
		for(pt v:w.back().p)p.pb(v);
		w.pop_back();
	}
	w.pb(pol(chull(p)));
}
ll query(pt v){
	ll r=-INF;
	for(auto& p:w)r=max(r,p.farthest(v)*v);
	return r;
}

int n,m;

int main(){
	scanf("%d",&n);
	fore(i,0,n){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		add(pt(x,y));
	}
	scanf("%d",&m);
	fore(i,0,m){
		ll x,y;
		char t[16];
		scanf("%s%lld%lld",t,&x,&y);
		pt p(x,y);
		if(t[0]=='a')add(p);
		else printf("%lld\n",query(p));
	}
	//printf("%lld %lld\n",nq,nit);
	//printf("%.5lf %.5lf\n",1.*tq/CLOCKS_PER_SEC,1.*ta/CLOCKS_PER_SEC);
	return 0;
}


