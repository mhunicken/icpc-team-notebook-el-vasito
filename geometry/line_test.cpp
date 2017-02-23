// SPOJ TAP2016D - AC
// http://www.spoj.com/problems/TAP2016D/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-6;

// double inf
const double DINF=numeric_limits<double>::infinity();
struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	pt operator*(double t){return pt(t*x,t*y);}
	pt operator/(double t){return pt(x/t,y/t);}
	double operator*(pt p){return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;} // 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
int sgn(double x){if(x<-EPS)return -1;return x>EPS;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return abs((r-p)%pq)<EPS;}
	bool operator/(ln l){return abs(pq%l.pq)<EPS;}
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection (2D)
		double s=l.pq%pq;
		if(abs(s)<EPS)return pt(DINF,DINF);
		return l.p+l.pq*((p-l.p)%pq/s);
	}
	double angle(ln l){return pq.angle(l.pq);}
	int side(pt r){return sgn(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}

set<pt> w;
int n;
pt ps[1024];

int main(){
	while(scanf("%d",&n)!=EOF){
		w.clear();
		fore(i,0,n)scanf("%lf%lf",&ps[i].x,&ps[i].y),w.insert(ps[i]);
		double a=ln(ps[0],ps[1]).angle(ln(ps[0],ps[2]));
		double b=ln(ps[1],ps[0]).angle(ln(ps[1],ps[2]));
		pt ra0(sin(a),cos(a));
		pt ra1(sin(-a),cos(-a));
		pt rb0(sin(b),cos(b));
		pt rb1(sin(-b),cos(-b));
		int r=0;
		fore(i,0,n)fore(j,i+1,n){
			pt p=ps[i],q=ps[j];
			r+=w.count(ln(p,q).rot(ra0)^ln(q,p).rot(rb1));
			r+=w.count(ln(p,q).rot(rb0)^ln(q,p).rot(ra1));
			r+=w.count(ln(p,q).rot(ra1)^ln(q,p).rot(rb0));
			r+=w.count(ln(p,q).rot(rb1)^ln(q,p).rot(ra0));
		}
		double l0=(ps[0]-ps[1]).norm();
		double l1=(ps[1]-ps[2]).norm();
		double l2=(ps[2]-ps[0]).norm();
		if(abs(l0-l1)<EPS||abs(l0-l2)<EPS||abs(l1-l2)<EPS)r/=2;
		printf("%d\n",r);
	}
	return 0;
}
