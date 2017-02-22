// Codeforces 168B - AC
// http://codeforces.com/problemset/problem/166/B
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-12;

struct pt {  // for 2D ignore z coordinate
	double x,y;int id;
	pt(double x, double y, int id) : x(x),y(y),id(id){}
	pt(double x, double y): x(x),y(y){}
	pt(){}
	double norm(){return sqrt(*this**this);}
//	pt operator+(pt p){return pt(x+p.x,y+p.y);}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
//	pt operator*(double t){return pt(t*x,t*y);}
	double operator*(pt p) {return x*p.x+y*p.y;}
//	pt operator^(pt p){ // only for 3D
//		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
	double operator%(pt p){return x*p.y-y*p.x;} // for 2D
	bool operator<(pt p){ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (p-*this)%(q-*this)>EPS;}
};
// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
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
	return r;
}

int n,m;
vector<pt> p;

int main(){
	scanf("%d",&n);
	fore(i,0,n){
		int x,y;
		scanf("%d%d",&x,&y);
		p.pb(pt(x,y,0));
	}
	scanf("%d",&m);
	fore(i,0,m){
		int x,y;
		scanf("%d%d",&x,&y);
		p.pb(pt(x,y,1));
	}
	vector<pt> c=chull(p);
	for(auto p:c)if(p.id){puts("NO");return 0;}
	puts("YES");
	return 0;
}
