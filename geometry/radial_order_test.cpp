#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

struct pt {
	int x,y;
	pt(int x, int y):x(x),y(y){}
	pt operator-(pt p)const{return pt(x-p.x,y-p.y);}
};

struct Cmp { // IMPORTANT: add const in pt operator -
	pt r;
	Cmp(pt r):r(r){}
	int cuad(const pt &a)const {
		if(a.x>0&&a.y>=0)return 0;
		if(a.x<=0&&a.y>0)return 1;
		if(a.x<0&&a.y<=0)return 2;
		if(a.x>=0&&a.y<0)return 3;
		assert(a.x==0&&a.y==0);
		return -1;
	}
	bool cmp(const pt& p1, const pt& p2)const {
		int c1=cuad(p1),c2=cuad(p2);
		if(c1==c2)return p1.y*p2.x<p1.x*p2.y;
		return c1<c2;
	}
	bool operator()(const pt& p1, const pt& p2)const {
		return cmp(p1-r,p2-r);
	}
};

vector<pt> p;

int main(){
	fore(x,0,9)fore(y,0,9)p.pb(pt(x,y));
	random_shuffle(p.begin(),p.end());
	sort(p.begin(),p.end(),Cmp(pt(4,4)));
	for(pt q:p)printf("%d %d\n",q.x,q.y);
	return 0;
}
