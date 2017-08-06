struct event {
	double x;int t;
	event(double x, int t):x(x),t(t){}
	bool operator <(const event &o)const{return x<o.x;}
};
int n;
double proc(vector<event>& v){
	sort(v.begin(),v.end());
	double r=0.,lx=((v.empty())?0.0:v[0].x);
	int count=0;
	for(auto e:v){
		// count: number of circles that cover
		if(count==n-1)r+=e.x-lx; // (if(count>0) gives area of union)
		count+=e.t;lx=e.x;
	}
	return r;
}
// Primitive of sqrt(r*r-x*x) (as function of x)
inline double prim(double x, double r){
	if(x>=r)return r*r*PI/4.;
	if(x<=-r)return -r*r*PI/4.;
	double a=sqrt(r*r-x*x);
	return 0.5*(x*a+r*r*atan(x/a));
}
double interCircle(vector<circle>& v) { // O(n^3)
	vector<double> p;p.reserve(v.size()*(v.size()+2));
	for(auto c:v)p.pb(c.o.x+c.r),p.pb(c.o.x-c.r);
	fore(i,0,v.size())fore(j,0,i){
		circle a=v[i],b=v[j];
		double d=(a.o-b.o).norm();
		if(abs(a.r-b.r)<d&&d<a.r+b.r){
			double g=acos((a.r*a.r+d*d-b.r*b.r)/(2*d*a.r));
			pt w=(b.o-a.o)*(a.r/d);
			p.pb((a.o+w.rot(g)).x);p.pb((a.o+w.rot(-g)).x);
		}
	}
	sort(p.begin(),p.end());
	double r=0.;
	fore(i,0,p.size()-1){
		double A=p[i],B=p[i+1];
		vector<event> ve;ve.reserve(2*v.size());
		for(auto c:v){
			double a=prim(B-c.o.x,c.r)-prim(A-c.o.x,c.r),b=c.o.y*(B-A);
			ve.pb(event(b+a,-1));ve.pb(event(b-a,1));
		}
		r+=proc(ve);
	}
	return r;
}
