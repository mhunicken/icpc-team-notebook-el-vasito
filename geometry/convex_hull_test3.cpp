// Codeforces 105254V - AC
// https://codeforces.com/gym/105254/problem/V
#include <bits/stdc++.h>
#define fore(i,a,b) for(ll i = a,jet = b;i<jet;i++)
#define fst first
#define snd second
#define pb push_back
#define ALL(x) x.begin(),x.end()
#define SZ(x) ((ll)x.size())
#define mset(a,v) memset((a),(v),sizeof(a))
#define JET ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> ii;
typedef vector<ll> vv;

const ld EPS=1e-10;

struct pt {
	ld x,y;
	pt(ld x, ld y):x(x),y(y){}
	pt(){}
	ld norm2(){return *this**this;}
	ld norm(){return sqrt(norm2());}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(ld t){return pt(x*t,y*t);}
	pt operator/(ld t){return pt(x/t,y/t);}
	ld operator*(pt p){return x*p.x+y*p.y;}
	pt unit(){return *this/norm();}
	ld operator%(pt p){return x*p.y-y*p.x;}
	bool operator==(pt p){return abs(x-p.x)<=EPS&&abs(y-p.y)<=EPS;}
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<=EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){return (q-p)%(*this-p)>-EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
};
#define str to_string
string cv(pt p){return str(p.x)+","+str(p.y);}
pt ccw90(1,0), cw90(-1,0);
// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	p.erase(unique(ALL(p)), p.end());
	fore(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size(),pr=k-1;
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().left(r[r.size()-2],p[i]))r.pop_back();
		while(pr>=0&&p[i]<r[pr]) pr--;
		if(pr<0||!(p[i]==r[pr])) r.pb(p[i]);
	}
	return r;
}

struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<=EPS;} // 2D
	bool has(pt r){return ln(p,r)/ *this;}
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))<=EPS;}
	pt operator^(ln l){ // intersection
		// if(*this/l)return pt(DINF,DINF);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
		return r;
	}
};
int main(){
	JET
	ll n; cin>>n;
	vv a(n);
	fore(i,0,n)cin>>a[i];
	ll m; cin>>m;
	vv b(m);
	fore(i,0,m)cin>>b[i];
	sort(ALL(a)); sort(ALL(b));
	ll dif=0;
	fore(i,0,m){
		ll l=lower_bound(ALL(a),b[i])-a.begin();
		ll r=upper_bound(ALL(a),b[i])-a.begin();
		dif+=l; dif-=n-r;
	}
	assert(dif);
	if(dif>0){
		swap(a,b),swap(n,m);
		// cerr<<"estaban al reves\n";
	}
	
	// a le gana a b
	vector<pt> bu;
	auto agr=[&](pt p){
		p.x/=n;
		p.y/=m;
		bu.pb(p);
	};
	map<ll,ii> mp;
	
	mp[1]={0,0};
	for(auto i:a)mp[i+1]={0,0};
	for(auto i:b)mp[i+1]={0,0};
	
	for(auto i:a)mp[i].fst++;
	for(auto i:b)mp[i].snd++;

	pt cur(0,0);
	for(auto [asd,now]:mp){
		// exactly equal
		pt cand=cur;
		cand.x+=now.fst/2.;
		cand.y+=now.snd/2.;
		agr(cand);
		
		cur.x+=now.fst;
		cur.y+=now.snd;
	}
	auto c=chull(bu);
	// for(auto p:c)cout<<cv(p)<<" ";;cout<<"\n";
	ld res1=1,res2=0;
	ll k=SZ(c);
	auto cand=[&](pt p){
		if(p.x>=0.5-EPS)res1=min(res1,p.y);
		if(p.y<=0.5+EPS)res2=max(res2,p.x);
	};
	ln ver(pt(0.5,0),pt(0.5,0.5));
	ln hor(pt(0,0.5),pt(0.5,0.5));
	fore(i,0,k){
		cand(c[i]);
		ln l(c[i],c[(i+1)%k]);
		if(abs(l.pq.x)>EPS){ // !(l/ver)
			pt p=l^ver;
			if(l.seghas(p))cand(p);
		}
		if(abs(l.pq.y)>EPS){ // !(l/hor)
			pt p=l^hor;
			if(l.seghas(p))cand(p);
		}
	}
	cout<<fixed<<setprecision(15);
	cout<<res1<<" "<<res2<<"\n";
	return 0;
}