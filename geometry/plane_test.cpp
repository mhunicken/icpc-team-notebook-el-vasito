#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double DINF=1e200;
const double EPS=1e-7;

struct pt {  // for 3D add z coordinate
	double x,y,z;
	pt(double x, double y, double z):x(x),y(y),z(z){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS&&abs(z-p.z)<EPS;}
	pt operator+(pt p){return pt(x+p.x,y+p.y,z+p.z);}
	pt operator-(pt p){return pt(x-p.x,y-p.y,z-p.z);}
	pt operator*(double t){return pt(x*t,y*t,z*t);}
	pt operator/(double t){return pt(x/t,y/t,z/t);}
	double operator*(pt p){return x*p.x+y*p.y+z*p.z;}
	pt operator^(pt p){ // only for 3D
		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double angle(pt p){ // redefine acos for values out of range
		return acos(*this*p/(norm()*p.norm()));}
	pt unit(){return *this/norm();}
	double operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
//	bool operator<(pt p)const{ // for convex hull
//		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
//	bool left(pt p, pt q){ // is it to the left of directed line pq?
//		return (q-p)%(*this-p)>EPS;}
//	pt rot(pt r){return pt(*this%r,*this*r);}
//	pt rot(double a){return rot(pt(sin(a),cos(a)));}
};
//pt ccw90(1,0);
//pt cw90(-1,0);
int sgn2(double x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<EPS;}
	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))-EPS<0;}
	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<EPS;} // 3D
//	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;} // 2D
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection
		if(*this/l)return pt(DINF,DINF,DINF);
		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
		return r;
	}
	double angle(ln l){return pq.angle(l.pq);}
//	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
//	double dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
//	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
//ln bisector(pt p, pt q){ // segment bisector (2D)
//	return ln((p+q)*.5,p).rot(ccw90);
//}

struct plane {
	pt a,n; // n: normal unit vector
	plane(pt a, pt b, pt c):a(a),n(((b-a)^(c-a)).unit()){}
	plane(){}
	bool has(pt p){return abs((p-a)*n)<EPS;}
	double angle(plane w){return acos(n*w.n);}
	double dist(pt p){return abs((p-a)*n);}
	pt proj(pt p){inter(ln(p,p+n),p);return p;}
	bool inter(ln l, pt& r){
		double x=n*(l.p+l.pq-a),y=n*(l.p-a);
		if(abs(x-y)<EPS)return false;
		r=(l.p*x-(l.p+l.pq)*y)/(x-y);
		return true;
	}
	bool inter(plane w, ln& r){
		pt nn=n^w.n;pt v=n^nn;double d=w.n*v;
		if(abs(d)<EPS)return false;
		pt p=a+v*(w.n*(w.a-a)/d);
		r=ln(p,p+nn);
		return true;
	}
};

double randd(){return 1.*rand()/RAND_MAX;}
pt randp(){return pt(randd(),randd(),randd());}

int main(){
	fore(_,0,1000){
		plane w(randp(),randp(),randp());
		ln l(randp(),randp());
		pt r;
		assert(w.inter(l,r));
		assert(l.has(r));
		assert(w.has(r));
	}
	fore(_,0,1000){
		plane w(randp(),randp(),randp());
		plane u(randp(),randp(),randp());
		ln l;
		assert(w.inter(u,l));
		pt p;
		assert(!w.inter(l,p));
		assert(!u.inter(l,p));
		assert(w.has(l.p));
		assert(w.has(l.p+l.pq));
		assert(u.has(l.p));
		assert(u.has(l.p+l.pq));
	}
	fore(_,0,1000){
		plane w(randp(),randp(),randp());
		pt q=randp();
		pt p=w.proj(q);
		assert(w.has(p));
		assert(((p-q)^w.n).norm()<EPS);
		assert(abs(w.dist(q)-(q-p).norm())<EPS);
	}
	return 0;
}




