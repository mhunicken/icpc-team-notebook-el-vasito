#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;
const double DINF=numeric_limits<double>::infinity();
const double PI=acos(-1);

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


//int sgn(double x){return x<0?-1:1;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return dist(r)<EPS;}
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
//	int side(pt r){return has(r)?0:sgn(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
	double dist(ln l){ // only 3D
		if(*this/l)return dist(l.p);
		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
	}
//	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){ // angle bisector
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
//ln bisector(pt p, pt q){ // segment bisector (2D)
//	return ln((p+q)*.5,p).rot(ccw90);
//}

#define ITER (1<<23)

double randd(){return 1.*rand()/RAND_MAX;}

pt randp(){return pt(randd(),randd(),randd());}
pt randpinp(pt p0, pt d0, pt d1){
	return p0+d0*(randd()-0.5)*2+d1*(randd()-0.5)*2;
}

void test_has(){
	printf("test has... ");fflush(stdout);
	fore(_,0,ITER){
		pt p=randp(),q=randp();
		pt r=p+(q-p)*(randd()-0.5)*2;
		assert(ln(p,q).has(r));
		assert(ln(q,p).has(r));
		pt n=((q-p)^randp()).unit();
		assert(!ln(p,q).has(r+n*2*EPS));
		assert(!ln(q,p).has(r+n*2*EPS));
	}
	puts("OK");
}
void test_parallel(){
	printf("test parallel... ");fflush(stdout);
	fore(_,0,ITER){
		pt p0=randp(),q0=randp(),p1=randp();
		pt q1=p1+(q0-p0)*randd();
		assert(ln(p0,q0)/ln(p1,q1));
		assert(ln(p0,q0)/ln(q1,p1));
		pt n=((q0-p0)^randp()).unit();
		q1=p1+(q0-p0+n*2*EPS);
		assert(!(ln(p0,q0)/ln(p1,q1)));
		assert(!(ln(q0,p0)/ln(p1,q1)));
	}
	puts("OK");
}
void test_intersection(){
	printf("test intersection... ");fflush(stdout);
	fore(_,0,ITER){
		pt p0=randp(),d0=randp(),d1;
		do d1=randp();while(ln(p0,p0+d0)/ln(p0,p0+d1));
		d0=d0.unit();d1=d1.unit();
		pt a0,b0,a1,b1;
		do {
			a0=randpinp(p0,d0,d1);
			b0=randpinp(p0,d0,d1);
			a1=randpinp(p0,d0,d1);
			b1=randpinp(p0,d0,d1);
		} while(ln(a0,b0)/ln(a1,b1));
		ln l0(a0,b0),l1(a1,b1);
		pt r=l0^l1;
		if(!l0.has(r)){
			printf("%.12lf\n",l0.dist(r));
			printf("%.12lf %.12lf\n",r.x,r.y);
			printf("%.12lf %.12lf\n",d0.x,d0.y);
			printf("%.12lf %.12lf\n",d1.x,d1.y);
			printf("%.12lf\n",l0.angle(l1));
		}
		assert(l0.has(r));assert(l1.has(r));
		r=l1^l0;
		assert(l0.has(r));assert(l1.has(r));

		pt b11=a1+(b0-a0)*randd();
		l1=ln(a1,b11);
		r=l0^l1;
		assert(r.x==DINF&&r.y==DINF&&r.z==DINF);
		r=l1^l0;
		assert(r.x==DINF&&r.y==DINF&&r.z==DINF);

		pt n=(d0^d1).unit();
		a1=a1+n*2*EPS;
		b1=b1+n*2*EPS;
		l1=ln(a1,b1);
		r=l0^l1;
		assert(isnan(r.x)&&isnan(r.y)&&isnan(r.z));
		r=l1^l0;
		assert(isnan(r.x)&&isnan(r.y)&&isnan(r.z));
	}
	puts("OK");
}
void test_proj_distpl(){
	printf("test projection and dist point to line... ");fflush(stdout);
	fore(_,0,ITER){
		pt p=randp(),q=randp();
		pt r=p+(q-p)*(randd()-0.5)*2;
		pt n=((q-p)^randp()).unit();
		double d=randd()+2*EPS;
		pt w=r+n*d;
		assert(r==ln(p,q).proj(w));
		assert(abs(ln(p,q).dist(w)-d)<EPS);
	}
	puts("OK");
}
void test_distll(){
	printf("test dist line to line... ");fflush(stdout);
	fore(_,0,ITER){
		pt p0=randp(),q0=randp();
		pt r=p0+(q0-p0)*(randd()-0.5)*2;
		pt n=((q0-p0)^randp()).unit();
		double d=randd()+2*EPS;
		pt p1=r+n*d;
		pt q1=p1+(n^randp().unit())*randd();
		ln l0(p0,q0),l1(p1,q1);
		assert(abs(l0.dist(l1)-d)<EPS);

		q1=p1+(q0-p0)*(randd()-0.5)*2;
		l1=ln(p1,q1);
		assert(abs(l0.dist(l1)-d)<EPS);
	}
	puts("OK");
}
void test_bisector(){
	printf("test angle bisector... ");fflush(stdout);
	fore(_,0,ITER){
		pt p0=randp(),d0=randp(),d1;
		do d1=randp();while(ln(p0,p0+d0)/ln(p0,p0+d1));
		d0=d0.unit();d1=d1.unit();
		pt a0,b0,a1,b1;
		do {
			a0=randpinp(p0,d0,d1);
			b0=randpinp(p0,d0,d1);
			a1=randpinp(p0,d0,d1);
			b1=randpinp(p0,d0,d1);
		} while(ln(a0,b0)/ln(a1,b1)||ln(a0,b0).angle(ln(a1,b1))>PI-1e-5); // susceptible to error when angle near PI
		ln l0(a0,b0),l1(a1,b1);
		pt r=l0^l1;
		ln l2=bisector(l0,l1);
		assert(l2.has(r));
		assert(abs(l2.angle(l0)-l2.angle(l1))<1e-5); // susceptible to error
		assert(abs(2*l2.angle(l0)-l0.angle(l1))<1e-5);
	}
	puts("OK");
}

int main(){
	srand(123456);
	test_has();
	test_parallel();
	test_intersection();
	test_proj_distpl();
	test_distll();
	test_bisector();
	return 0;
}

