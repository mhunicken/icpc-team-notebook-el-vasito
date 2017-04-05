// Kattis pointinpolygon - AC
// https://open.kattis.com/problems/pointinpolygon
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-7;
const double DINF=1e200;

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
//	double angle(pt p){ // redefine acos for values out of range
//		return acos(*this*p/(norm()*p.norm()));}
//	pt unit(){return *this/norm();}
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
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<EPS;} // 3D
//	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;} // 2D
//	bool operator==(ln l){return *this/l&&has(l.p);}
//	pt operator^(ln l){ // intersection
//		if(*this/l)return pt(DINF,DINF);
//		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
//		return r;
//	}
//	double angle(ln l){return pq.angle(l.pq);}
//	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
//	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
//	double dist(ln l){ // only 3D
//		if(*this/l)return dist(l.p);
//		return abs((l.p-p)*(pq^l.pq))/(pq^l.pq).norm();
//	}
//	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
//ln bisector(ln l, ln m){ // angle bisector
//	pt p=l^m;
//	return ln(p,p+l.pq.unit()+m.pq.unit());
//}
//ln bisector(pt p, pt q){ // segment bisector (2D)
//	return ln((p+q)*.5,p).rot(ccw90);
//}

int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	int has(pt q){
		fore(i,0,n)if(ln(p[i],p[(i+1)%n]).seghas(q))return 2; // minor change to distinguish on and in
		int cnt=0;
		fore(i,0,n){
			int j=(i+1)%n;
			int k=sgn((q-p[j])%(p[i]-p[j]));
			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
			if(k>0&&u<0&&v>=0)cnt++;
			if(k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
};

int main(){
	int n;
	while(scanf("%d",&n),n){
		vector<pt> pp;
		double x,y;
		fore(i,0,n){
			scanf("%lf%lf",&x,&y);
			pp.pb(pt(x,y));
		}
		pol p(pp);
		int m;
		scanf("%d",&m);
		while(m--){
			scanf("%lf%lf",&x,&y);
			int r=p.has(pt(x,y));
			if(r==2)puts("on");
			else if(r==1)puts("in");
			else puts("out");
		}
	}
	return 0;
}

