int sgn(double x){return x<-EPS?-1:x>EPS;}
struct pol {
	int n;vector<pt> p;
	pol(){}
	pol(vector<pt> _p){p=_p;n=p.size();}
	double area(){
		double r=0.;
		fore(i,0,n)r+=p[i]%p[(i+1)%n];
		return abs(r)/2; // negative if CW, positive if CCW
	}
	pt centroid(){ // (barycenter)
		pt r(0,0);double t=0;
		fore(i,0,n){
			r=r+(p[i]+p[(i+1)%n])*(p[i]%p[(i+1)%n]);
			t+=p[i]%p[(i+1)%n];
		}
		return r/t/3;
	}
	bool has(pt q){
		fore(i,0,n)if(ln(p[i],p[(i+1)%n]).seghas(q))return true;
		int cnt=0;
		fore(i,0,n){
			int j=(i+1)%n;
			int k=sgn((q-p[j])%(p[i]-p[j]));
			int u=sgn(p[i].y-q.y),v=sgn(p[j].y-q.y);
			if(k>0&&u<0&&v>=0)cnt++;
			if(k<0&&v<0&&u>=0)cnt--;
		}
		return cnt!=0;
	}
	pol cut(ln l){   // cut CONVEX polygon by line l
		vector<pt> q;  // returns part at left of l.pq
		fore(i,0,n){
			int d0=sgn(l.pq%(p[i]-l.p)),d1=sgn(l.pq%(p[(i+1)%n]-l.p));
			if(d0>=0)q.pb(p[i]);
			ln m(p[i],p[(i+1)%n]);
			if(d0*d1<0&&!(l/m))q.pb(l^m);
		}
		return pol(q);
	}
	double intercircle(circle c){ // area of intersection with circle
		double r=0.;
		fore(i,0,n){
			int j=(i+1)%n;double w=c.intertriangle(p[i],p[j]);
			if((p[j]-c.o)%(p[i]-c.o)>0)r+=w;
			else r-=w;
		}
		return abs(r);
	}
};
