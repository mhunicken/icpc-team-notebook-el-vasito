// CCW order
// Includes collinear points (change sign of EPS in left to exclude)
vector<pt> chull(vector<pt> p){
	if(SZ(p)<3)return p;
	vector<pt> r;
	sort(ALL(p)); // first x, then y
	p.erase(unique(ALL(p)), p.end());
	fore(i,0,SZ(p)){ // lower hull
		while(SZ(r)>=2&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	int k=SZ(r);
	for(int i=SZ(p)-1;i>=0;--i){ // upper hull
		while(SZ(r)>=k+2&&r.back().left(r[SZ(r)-2],p[i]))r.pop_back();
		r.pb(p[i]);
	}
	r.pop_back();
	return r;
}
