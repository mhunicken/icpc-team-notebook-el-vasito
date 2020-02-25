#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

const double EPS=1e-14;

typedef double tp; // type of polynomial
template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	poly(vector<T>& c):c(c){}
	poly(initializer_list<T> c):c(c){}
	poly(int k):c(k){}
	poly(){}
	poly operator+(poly<T> o){
		int m=c.size(),n=o.c.size();
		poly res(max(m,n));
		fore(i,0,m)res[i]=res[i]+c[i];
		fore(i,0,n)res[i]=res[i]+o.c[i];
		return res;
	}
	poly operator*(tp k){
		poly res(c.size());
		fore(i,0,c.size())res[i]=c[i]*k;
		return res;
	}
	poly operator*(poly o){
		int m=c.size(),n=o.c.size();
		poly res(m+n-1);
		fore(i,0,m)fore(j,0,n)res[i+j]=res[i+j]+c[i]*o.c[j];
		return res;
	}
	poly operator-(poly<T> o){return *this+(o*-1);}
	T operator()(tp v){
		T sum(0);
		for(int i=c.size()-1;i>=0;--i)sum=sum*v+c[i];
		return sum;
	}
	void print(){
		while(!c.empty()&&abs(c.back())<EPS)c.pop_back();
		if(c.empty())puts(" 0");
		else {
			for(auto x:c)printf(" %.6lf",x);
			puts("");
		}
	}
};
// only for double polynomials
pair<poly<>,poly<> > polydiv(poly<> p, poly<> q){ // returns pair (result,rem)
	int n=p.c.size()-q.c.size()+1;
	vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		fore(i,0,q.c.size())p[i+k]-=b[k]*q[i];
		p.c.pop_back();
	}
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	return {poly<>(b),p};
}

#define ITER 250

double pget(poly<>& p, int k){return k<p.c.size()?p[k]:0;}
poly<> bairstow(poly<> p){
	int n=p.c.size()-1;
	assert(n>=3&&abs(p.c.back())>EPS);
	double u=p[n-1]/p[n],v=p[n-2]/p[n];
	fore(_,0,ITER){
		auto w=polydiv(p,{v,u,1});
		poly<> q=w.fst,r0=w.snd;
		poly<> r1=polydiv(q,{v,u,1}).snd;
		double c=pget(r0,1),d=pget(r0,0),g=pget(r1,1),h=pget(r1,0);
		double det=1/(v*g*g+h*(h-u*g)),uu=u;
		u-=det*(-h*c+g*d);v-=det*(-g*v*c+(g*uu-h)*d);

	}
	return {v,u,1};
}
void addr(vector<double>& r, poly<>& p){
	assert(p.c.size()<=3);
	if(p.c.size()<=1)return;
	if(p.c.size()==2)r.pb(-p[0]/p[1]);
	if(p.c.size()==3){
		double a=p[2],b=p[1],c=p[0];
		double d=b*b-4*a*c;
		if(d<-0.1)return; // huge epsilon because of bad precision
		d=d>0?sqrt(d):0;
		r.pb((-b-d)/2/a);
		r.pb((-b+d)/2/a);
	}
}
vector<double> roots(poly<> p){
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	fore(i,0,p.c.size())p[i]/=p.c.back();
	vector<double> r;int n;
	while((n=p.c.size()-1)>=3){
		poly<> q=bairstow(p);
		addr(r,q);
		p=polydiv(p,q).fst;
		while(p.c.size()>n-1)p.c.pop_back();
	}
	addr(r,p);
	return r;
}

int main(){
	int n;
	while(scanf("%d",&n)!=EOF){
		/*vector<double> v;
		fore(i,0,n+1){
			double x;
			scanf("%lf",&x);
			v.pb(x);
		}
		poly<> p(v);
		*/
		poly<> p={1};
		fore(i,0,n){
			double x;
			scanf("%lf",&x);
			p=p*poly<>({-x,1});
		}
		for(double x:roots(p))printf(" %.6lf",x);puts("");
	}
	return 0;
}

