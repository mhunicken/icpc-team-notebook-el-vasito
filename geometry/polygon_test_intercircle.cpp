// Codeforces gym 101208J - AC
// http://codeforces.com/gym/101208/problem/J
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
const double PI=acos(-1);

struct pt {  // for 3D add z coordinate
	double x,y;
	pt(double x, double y):x(x),y(y){}
	pt(){}
	double norm2(){return *this**this;}
	double norm(){return sqrt(norm2());}
//	bool operator==(pt p){return abs(x-p.x)<EPS&&abs(y-p.y)<EPS;}
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
//	bool has(pt r){return dist(r)<EPS;}
//	bool seghas(pt r){return has(r)&&(r-p)*(r-(p+pq))-EPS<0;}
//	bool operator /(ln l){return (pq.unit()^l.pq.unit()).norm()<EPS;} // 3D
//	bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;} // 2D
//	bool operator==(ln l){return *this/l&&has(l.p);}
//	pt operator^(ln l){ // intersection
//		if(*this/l){return pt(DINF,DINF);}
//		pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
//		if(!has(r)){return pt(NAN,NAN,NAN);} // check only for 3D
//		return r;
//	}
//	double angle(ln l){return pq.angle(l.pq);}
//	int side(pt r){return has(r)?0:sgn2(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
//	pt ref(pt r){return proj(r)*2-r;}
//	double dist(pt r){return (r-proj(r)).norm();}
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

struct circle {
	pt o;double r;
	circle(pt o, double r):o(o),r(r){}
//	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<r+EPS;}
//	vector<pt> operator^(circle c){
//		vector<pt> s;
//		double d=(o-c.o).norm();
//		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
//		double x=(d*d-c.r*c.r+r*r)/(2*d);
//		double y=sqrt(r*r-x*x);
//		pt v=(c.o-o)/d;
//		s.pb(o+v*x+v.rot(ccw90)*y);
//		if(y>EPS)s.pb(o+v*x-v.rot(ccw90)*y);
//		return s;
//	}
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
//	vector<pt> tang(pt p){
//		double d=sqrt((p-o).norm2()-r*r);
//		return *this^circle(p,d);
//	}
	double intertriangle(pt a, pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<EPS)return 0.;
		vector<pt> q={a},w=*this^ln(a,b);
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.pb(p);
		q.pb(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)swap(q[1],q[2]);
		double s=0;
		fore(i,0,q.size()-1){
			if(!has(q[i])||!has(q[i+1]))s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};

//int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
//	double area(){
//		double r=0.;
//		fore(i,0,n)r+=p[i]%p[(i+1)%n];
//		return abs(r)/2; // negative if CW, positive if CCW
//	}
//	pt centroid(){ // (barycenter)
//		pt r(0,0);double t=0;
//		fore(i,0,n){
//			r=r+(p[i]+p[(i+1)%n])*(p[i]%p[(i+1)%n]);
//			t+=p[i]%p[(i+1)%n];
//		}
//		return r/t/3;
//	}
//	bool has(pt q){
//		fore(i,0,n)if(ln(p[i],p[(i+1)%n]).seghas(q))return true;
//		int cnt=0;
//		fore(i,0,n){
//			int j=(i+1)%n;
//			int k=sgn((q-p[j])%(p[i]-p[j]));
//			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
//			if(k>0&&u<0&&v>=0)cnt++;
//			if(k<0&&v<0&&u>=0)cnt--;
//		}
//		return cnt!=0;
//	}
//	pol cut(ln l){   // cut CONVEX polygon by line l
//		vector<pt> q;  // returns part at left of l.pq
//		fore(i,0,n){
//			int d0=sgn(l.pq%(p[i]-l.p)),d1=sgn(l.pq%(p[(i+1)%n]-l.p));
//			if(d0>=0)q.pb(p[i]);
//			ln m(p[i],p[(i+1)%n]);
//			if(d0*d1<0&&!(l/m))q.pb(l^m);
//		}
//		return pol(q);
//	}
	double intercircle(circle c){ // area of intersection with circle
		double r=0.;
		fore(i,0,n){
			int j=(i+1)%n;double w=c.intertriangle(p[i],p[j]);
			if((p[j]-c.o)%(p[i]-c.o)>0)r+=w;
			else r-=w;
		}
		return abs(r);
	}
};

int main(){
	int n;double r;
	scanf("%d%lf",&n,&r);
	vector<pt> pp;
	fore(i,0,n){
		double x,y;
		scanf("%lf%lf",&x,&y);
		pp.pb(pt(x,y));
	}
	printf("%.12lf\n",pol(pp).intercircle(circle(pt(0,0),r)));
	return 0;
}

