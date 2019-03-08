// Codechef CHN02 - AC
// https://www.codechef.com/problems/CHN02

#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(n) ((int)(n).size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

const double EPS = 1e-7, DINF = 1e100;

struct pt {
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
  pt unit(){return *this/norm();}
  double operator%(pt p){return x*p.y-y*p.x;}
  bool left(pt p, pt q){ // is it to the left of directed line pq?
  return (q-p)%(*this-p)>-EPS;}
};

int sgn2(double x){return x<0?-1:1;}

struct ln {
  pt p,pq;
  ln(pt p, pt q):p(p),pq(q-p){}
  ln(){}
  bool operator/(ln l){return abs(pq.unit()%l.pq.unit())<EPS;}
  pt operator^(ln l){
  if(*this/l)return pt(DINF,DINF);
  pt r=l.p+l.pq*((p-l.p)%pq/(l.pq%pq));
  return r;
  }
};

int sgn(double x){return x<-EPS?-1:x>EPS;}

struct pol {
  int n;vector<pt> p;
  pol(){}
  pol(vector<pt> _p){p=_p;n=p.size();}
  double area(){
    double r=0.;
    for(int i = 0; i < n; i++)r+=p[i]%p[(i+1)%n];
    return abs(r)/2;
  }
};

int sgn3(double d){return abs(d)<EPS?0:(d>0?1:-1);}
struct halfplane:public ln{
    double angle;
    halfplane(){}
    halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
    bool operator<(halfplane b)const{return angle<b.angle;}
};
struct halfplanes {
  int n;
  vector<halfplane> hp;
  halfplanes(vector<halfplane> v):hp(v),n(SZ(v)){}
  halfplanes(){}
  void normalize(){ //removes unnecesary lines and orders by angle
    sort(hp.begin(),hp.end());
    vector<halfplane> v = {hp[0]};
    fore(i,1,n){
      if(sgn3(hp[i].angle-v.back().angle)) v.pb(hp[i]);
      else if(sgn3(v.back().pq%(hp[i].p-v.back().p))>0) v.back()=hp[i];
    }
    hp = v; n = hp.size();
  }
  // polygon intersecting left side of halfplanes
  // may cause problems if EPS is too small
  vector<pt> intersect(){
    vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
    fore(i,0,4) hp.pb(halfplane(bx[i],bx[(i+1)%4]));
    n=SZ(hp);
    normalize();
    int st=0,ed=1;
    vector<int> que(n);
    vector<pt> p1(n);
    que[st]=0; que[ed]=1;
    p1[1]=hp[0]^hp[1];
    for(int i=2; i<n && st <= ed;i++){
      while(st<ed&&sgn3(((hp[i].pq)%(p1[ed]-hp[i].p)))<0)ed--;
      while(st<ed&&sgn3(((hp[i].pq)%(p1[st+1]-hp[i].p)))<0)st++;
      que[++ed]=i;
      if(hp[i]/hp[que[ed-1]]) ed=-1;
      else p1[ed]=hp[i]^hp[que[ed-1]];
    }
    while(st<ed&&sgn3((hp[que[st]].pq)%(p1[ed]-hp[que[st]].p))<0)ed--;
    while(st<ed&&sgn3((hp[que[ed]].pq)%(p1[st+1]-hp[que[ed]].p))<0)st++;
    vector<pt> ans;
    if(st <= ed){
      p1[st]=hp[que[st]]^hp[que[ed]];
      fore(i,st,ed+1) ans.pb(p1[i]);
    }
    if(!SZ(ans)) return ans;
    // change sign of EPS in point.left()
    int f=1; for(auto x : hp) f &= ans[0].left(x.p,x.p+x.pq);
    if(!f) ans.clear();
    return ans;
  }
};

int main(){FIN;
  int n; cin >> n;
  vector<halfplane> v;
  fore(i,0,n){
    int c; cin >> c;
    vector<pt> p(c);
    fore(i,0,c) cin >> p[i].x >> p[i].y;
    fore(i,0,c) v.pb(halfplane(p[i],p[(i+1)%c]));
  }
  pol p(halfplanes(v).intersect());
  cout<<fixed<<setprecision(10)<<p.area()<<"\n";
}
