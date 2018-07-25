// ICPC Live Archive 6135 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=4146
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

double integrate(double f(double), double a, double b, int n=10000){
	double r=0,h=(b-a)/n,fa=f(a),fb;
	fore(i,0,n){fb=f(a+h*(i+1));r+=fa+4*f(a+h*(i+0.5))+fb;fa=fb;}
	return r*h/6.;
}

typedef double tp; // type of polynomial
template<class T=tp>
struct poly {  // poly<> : 1 variable, poly<poly<>>: 2 variables, etc.
	vector<T> c;
	T& operator[](int k){return c[k];}
	T operator()(tp v){
		T sum(0);
		for(int i=c.size()-1;i>=0;--i)sum=sum*v+c[i];
		return sum;
	}
};

double w,d,a;
int k;
poly<> p1,q1,p2,q2;
double h;

double f(double x){
	return max(p1(x)/q1(x)-max(p2(x)/q2(x),h),0.);
}

double doit(double _h){
	h=-_h;
	return integrate(f,0,w);
}

int main(){
	while(scanf("%lf%lf%lf%d",&w,&d,&a,&k)!=EOF){
		p1.c.clear();q1.c.clear();
		p2.c.clear();q2.c.clear();
		fore(_,0,k+1){int x;scanf("%d",&x);p1.c.pb(x);}
		fore(_,0,k+1){int x;scanf("%d",&x);q1.c.pb(x);}
		fore(_,0,k+1){int x;scanf("%d",&x);p2.c.pb(x);}
		fore(_,0,k+1){int x;scanf("%d",&x);q2.c.pb(x);}
		double s=0.,e=d;
		while(e-s>1e-8){
			double m=(s+e)/2;
			if(doit(m)<a)s=m;
			else e=m;
		}
		printf("%.5lf\n",s);
	}
	return 0;
}
