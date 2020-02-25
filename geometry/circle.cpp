struct circle {
	pt o;double r;
	circle(pt o, double r):o(o),r(r){}
	circle(pt x, pt y, pt z){o=bisector(x,y)^bisector(x,z);r=(o-x).norm();}
	bool has(pt p){return (o-p).norm()<=r+EPS;}
	vector<pt> operator^(circle c){ // ccw
		vector<pt> s;
		double d=(o-c.o).norm();
		if(d>r+c.r+EPS||d+min(r,c.r)+EPS<max(r,c.r))return s;
		double x=(d*d-c.r*c.r+r*r)/(2*d);
		double y=sqrt(r*r-x*x);
		pt v=(c.o-o)/d;
		s.pb(o+v*x-v.rot(ccw90)*y);
		if(y>EPS)s.pb(o+v*x+v.rot(ccw90)*y);
		return s;
	}
	vector<pt> operator^(ln l){
		vector<pt> s;
		pt p=l.proj(o);
		double d=(p-o).norm();
		if(d-EPS>r)return s;
		if(abs(d-r)<=EPS){s.pb(p);return s;}
		d=sqrt(r*r-d*d);
		s.pb(p+l.pq.unit()*d);
		s.pb(p-l.pq.unit()*d);
		return s;
	}
	vector<pt> tang(pt p){
		double d=sqrt((p-o).norm2()-r*r);
		return *this^circle(p,d);
	}
	bool in(circle c){ // non strict
		double d=(o-c.o).norm();
		return d+r<=c.r+EPS;
	}
	double intertriangle(pt a, pt b){ // area of intersection with oab
		if(abs((o-a)%(o-b))<=EPS)return 0.;
		vector<pt> q={a},w=*this^ln(a,b);
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.pb(p);
		q.pb(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)swap(q[1],q[2]);
		double s=0;
		fore(i,0,q.size()-1){
			if(!has(q[i])||!has(q[i+1]))s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};
vector<double> intercircles(vector<circle> c){
	vector<double> r(SZ(c)+1); // r[k]: area covered by at least k circles
	fore(i,0,SZ(c)){           // O(n^2 log n) (high constant)
		int k=1;Cmp s(c[i].o);
		vector<pair<pt,int> > p={
			{c[i].o+pt(1,0)*c[i].r,0},
			{c[i].o-pt(1,0)*c[i].r,0}};
		fore(j,0,SZ(c))if(j!=i){
			bool b0=c[i].in(c[j]),b1=c[j].in(c[i]);
			if(b0&&(!b1||i<j))k++;
			else if(!b0&&!b1){
				auto v=c[i]^c[j];
				if(SZ(v)==2){
					p.pb({v[0],1});p.pb({v[1],-1});
					if(s(v[1],v[0]))k++;
				}
			}
		}
		sort(p.begin(),p.end(),
			[&](pair<pt,int> a, pair<pt,int> b){return s(a.fst,b.fst);});
		fore(j,0,SZ(p)){
			pt p0=p[j?j-1:SZ(p)-1].fst,p1=p[j].fst;
			double a=(p0-c[i].o).angle(p1-c[i].o);
			r[k]+=(p0.x-p1.x)*(p0.y+p1.y)/2+c[i].r*c[i].r*(a-sin(a))/2;
			k+=p[j].snd;
		}
	}
	return r;
}
