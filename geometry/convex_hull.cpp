// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	if(SZ(p)<3)return p;
	vector<pt> r; sort(p.begin(),p.end()); // first x, then y
	fore(i,0,p.size()){ // lower hull
		while(SZ(r)>=2&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back(); int k=r.size();
	for(int i=p.size()-1;i>=0;--i){ // upper hull
		while(SZ(r)>=k+2&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back(); return r;
}
