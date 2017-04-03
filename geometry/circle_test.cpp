#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double DINF=numeric_limits<double>::infinity();
const double EPS=1e-9;

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
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>EPS;}
	pt rot(pt r){return pt(*this%r,*this*r);}
	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
pt ccw90(1,0);
pt cw90(-1,0);

int sgn(double x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<EPS;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<EPS;} // 3D
	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;} // 2D
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection
		if(*this/l)return pt(DINF,DINF);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
		return r;
	}
	double angle(ln l){return pq.angle(l.pq);}
	int side(pt r){return has(r)?0:sgn(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
//	double dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
ln bisector(pt p, pt q){ // segment bisector (2D)
	return ln((p+q)*.5,p).rot(ccw90);
}

struct circle {
	pt o;double r;
	circle(pt o, double r):o(o),r(r){}
	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<r+EPS;}
	vector<pt> operator^(circle c){
		vector<pt> s;
		double d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		double x=(d*d-c.r*c.r+r*r)/(2*d);
		double y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.pb(o+v*x+v.rot(ccw90)*y);
		if(y>EPS)s.pb(o+v*x-v.rot(ccw90)*y);
		return s;
	}
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		double d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<EPS){s.pb(p);return s;}
		d=sqrt(r*r-d*d);
		s.pb(p+l.pq.unit()*d);
		s.pb(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		double d=sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
};

double randd(){return 1.*rand()/RAND_MAX;}

int main(){
	fore(_,0,100000){
		pt c0(randd(),randd()),c1(randd(),randd());
		double r0=randd(),r1=randd();
		double d=(c0-c1).norm();
		auto v=circle(c0,r0)^circle(c1,r1);
		//printf("%d\n",(int)v.size());
		if(d-EPS>r0+r1||d+min(r0,r1)+EPS<max(r0,r1))assert(!v.size()),puts("OK CC 0");
		else {
			//assert(v.size());
			if(abs(d-r0-r1)<EPS||abs(d+min(r0,r1)-max(r0,r1))<EPS)assert(v.size()==1),puts("OK CC 1");
			else assert(v.size()==2&&!(v[0]==v[1])),puts("OK CC 2");
		}
		for(auto p:v)assert(abs((p-c0).norm()-r0)<EPS&&abs((p-c1).norm()-r1)<EPS);
	}
	fore(_,0,100000){
		pt c(randd(),randd());ln l(pt(randd(),randd()),pt(randd(),randd()));
		double r=randd();
		double d=l.dist(c);
		auto v=circle(c,r)^l;
		if(d-EPS>r)assert(!v.size()),puts("OK CL 0");
		else {
			if(abs(d-r)<EPS)assert(v.size()==1),puts("OK CL 1");
			else assert(v.size()==2&&!(v[0]==v[1])),puts("OK CL 2");
		}
		//printf("(%lf,%lf,%lf) (%lf,%lf) (%lf,%lf)  (%lf,%lf)\n",c.x,c.y,r,l.p.x,l.p.y,(l.p+l.pq).x,(l.p+l.pq).y,v[0].x,v[0].y);
		for(auto p:v)assert(l.has(p)),assert(abs((p-c).norm()-r)<EPS);
	}
	fore(_,0,100000){
		pt c(randd(),randd());pt p(randd(),randd());
		double r=randd();
		if(circle(c,r).has(p)){_--;continue;}
		auto v=circle(c,r).tang(p);
		assert(v.size()==2);
		for(auto q:v)assert(abs((q-c).norm()-r)<EPS&&abs((p-q)*(c-q))<EPS);
		puts("OK tang");
	}
	return 0;
}




