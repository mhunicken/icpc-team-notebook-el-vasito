struct plane {
	pt a,n; // n: normal unit vector
	plane(pt a, pt b, pt c):a(a),n(((b-a)^(c-a)).unit()){}
	plane(){}
	bool has(pt p){return abs((p-a)*n)<=EPS;}
	double angle(plane w){return acos(n*w.n);}
	double dist(pt p){return abs((p-a)*n);}
	pt proj(pt p){inter(ln(p,p+n),p);return p;}
	bool inter(ln l, pt& r){
		double x=n*(l.p+l.pq-a),y=n*(l.p-a);
		if(abs(x-y)<=EPS)return false;
		r=(l.p*x-(l.p+l.pq)*y)/(x-y);
		return true;
	}
	bool inter(plane w, ln& r){
		pt nn=n^w.n;pt v=n^nn;double d=w.n*v;
		if(abs(d)<=EPS)return false;
		pt p=a+v*(w.n*(w.a-a)/d);
		r=ln(p,p+nn);
		return true;
	}
};
