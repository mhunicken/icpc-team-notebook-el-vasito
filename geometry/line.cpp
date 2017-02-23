int sgn(double x){if(x<-EPS)return -1;return x>EPS;}
struct ln {
	pt p,q;
	ln(pt p, pt q):p(p),q(q){}
	ln(){}
	bool has(pt r){return abs((r-p)%(q-p))<EPS;}
	bool operator/(ln l){return abs((q-p)%(l.q-l.p))<EPS;}
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection (2D)
		double s=(l.q-l.p)%(q-p);
		if(abs(s)<EPS)return pt(DINF,DINF);
		return l.p+(l.q-l.p)*((p-l.p)%(q-p)/s);
	}
	double angle(ln l){return (q-p).angle(l.q-l.p);}
	int side(pt r){return sgn((q-p)%(r-p));}
	pt proj(pt r){return p+(q-p)*((r-p)*(q-p)/(q-p).norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
	ln rot(auto a){return ln(p,p+(q-p).rot(a));} // 2D
};
ln bisector(ln l, ln m){
	pt p=l^m;
	return ln(p,p+(l.q-l.p).unit()+(m.q-m.p).unit());
}
