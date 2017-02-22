struct pt {  // for 2D ignore z coordinate
	double x,y,z;
	pt(double x, double y, double z):x(x),y(y),z(z){}
	pt(){}
	double norm(){return sqrt(*this**this);}
	pt operator+(pt p){return pt(x+p.x,y+p.y,z+p.z);}
	pt operator-(pt p){return pt(x-p.x,y-p.y,z-p.z);}
	pt operator*(double t){return pt(t*x,t*y,t*z);}
	double operator*(pt p){return x*p.x+y*p.y+z*p.z;}
	pt operator^(pt p){ // only for 3D
		return pt(y*p.z-z*p.y,z*p.x-x*p.z,x*p.y-y*p.x);}
//	double operator%(pt p){return x*p.y-y*p.x;} // for 2D
	bool operator<(pt p){ // for convex hull
		return x<p.x-EPS||(abs(x-p.x)<EPS&&y<p.y-EPS);}
	bool left(pt p, pt q){ // is it to the left of directed line pq?
		return (p-*this)%(q-*this)>EPS;}
};
