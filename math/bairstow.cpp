double pget(poly<>& p, int k){return k<p.c.size()?p[k]:0;}
poly<> bairstow(poly<> p){ // returns polynomial of degree 2 that
	int n=p.c.size()-1;    // divides p
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
		d=d>0?sqrt(d):0;r.pb((-b-d)/2/a);r.pb((-b+d)/2/a);
	}
}
vector<double> roots(poly<> p){
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	fore(i,0,p.c.size())p[i]/=p.c.back();
	vector<double> r;int n;
	while((n=p.c.size()-1)>=3){
		poly<> q=bairstow(p);addr(r,q);
		p=polydiv(p,q).fst;
		while(p.c.size()>n-1)p.c.pop_back();
	}
	addr(r,p);
	return r;
}
