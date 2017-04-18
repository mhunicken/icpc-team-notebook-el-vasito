// Codeforces gym 101128J - AC
// http://codeforces.com/gym/101128/problem/J
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

struct pt {  // for 3D add z coordinate
	ll x,y;
	pt(ll x, ll y):x(x),y(y){}
	pt(){}
	pt operator-(pt p){return pt(x-p.x,y-p.y);}
	ll operator%(pt p){return x*p.y-y*p.x;}
	// 2D from now on
	bool operator<(pt p)const{ // for convex hull
		return x<p.x||x==p.x&&y<p.y;}
	bool leftc(pt p, pt q){
		return (q-p)%(*this-p)>=0;}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (q-p)%(*this-p)>0;}
};
// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	vector<pt> r;
	sort(p.begin(),p.end()); // first x, then y
	fore(i,0,p.size()){ // lower hull
		while(r.size()>=2&&r.back().leftc(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(r.size()>=k+2&&r.back().leftc(r[r.size()-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	void normalize(){ // (call before haslog, remove collinear first)
		if(p[2].left(p[0],p[1]))reverse(p.begin(),p.end());
		int pi=min_element(p.begin(),p.end())-p.begin();
		vector<pt> s(n);
		fore(i,0,n)s[i]=p[(pi+i)%n];
		p.swap(s);
	}
	bool haslog(pt q){ // O(log(n)) only CONVEX. Call normalize first
		if(q.left(p[0],p[1])||q.left(p.back(),p[0]))return false;
		int a=1,b=p.size()-1;  // returns true if point on boundary
		while(b-a>1){          // (change sign of EPS in left
			int c=(a+b)/2;     //  to return false in such case)
			if(!q.left(p[0],p[c]))a=c;
			else b=c;
		}
		return !q.left(p[a],p[a+1]);
	}
};

vector<pt> v;
int n;

int main(){
	scanf("%d",&n);
	while(n--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		v.pb(pt(x,y));
	}
	pol p(chull(v));
	p.normalize();
	scanf("%d",&n);
	int r=0;
	while(n--){
		ll x,y;
		scanf("%lld%lld",&x,&y);
		r+=p.haslog(pt(x,y));
	}
	printf("%d\n",r);
	return 0;
}
