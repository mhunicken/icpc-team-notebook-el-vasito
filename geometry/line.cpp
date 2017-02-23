int sgn(double x){if(x<-EPS)return -1;return x>EPS;}
struct ln {
	pt p,pq;
	ln(pt p, pt q):p(p),pq(q-p){}
	ln(){}
	bool has(pt r){return abs((r-p)%pq)<EPS;}
	bool operator/(ln l){return abs(pq%l.pq)<EPS;}
	bool operator==(ln l){return *this/l&&has(l.p);}
	pt operator^(ln l){ // intersection (2D)
		double s=l.pq%pq;
		if(abs(s)<EPS)return pt(DINF,DINF);
		return l.p+l.pq*((p-l.p)%pq/s);
	}
	double angle(ln l){return pq.angle(l.pq);}
	int side(pt r){return sgn(pq%(r-p));} // 2D
	pt proj(pt r){return p+pq*((r-p)*pq/pq.norm2());}
	pt ref(pt r){return proj(r)*2-r;}
	double dist(pt r){return (r-proj(r)).norm();}
	ln rot(auto a){return ln(p,p+pq.rot(a));} // 2D
};
ln bisector(ln l, ln m){
	pt p=l^m;
	return ln(p,p+l.pq.unit()+m.pq.unit());
}
