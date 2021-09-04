pair<poly<>,tp> ruffini(poly<> p, tp r){ // returns pair (result,rem)
	int n=p.c.size()-1; vector<tp> b(n); b[n-1]=p[n];
	for(int k=n-2;k>=0;--k)b[k]=p[k+1]+r*b[k+1];
	return {poly<>(b),p[0]+r*b[0]};
}
// only for double polynomials. returns pair (result,rem)
pair<poly<>,poly<> > polydiv(poly<> p, poly<> q){ 
	int n=p.c.size()-q.c.size()+1; vector<tp> b(n);
	for(int k=n-1;k>=0;--k){
		b[k]=p.c.back()/q.c.back();
		fore(i,0,q.c.size())p[i+k]-=b[k]*q[i];
		p.c.pop_back();
	}
	while(!p.c.empty()&&abs(p.c.back())<EPS)p.c.pop_back();
	return {poly<>(b),p};
}
poly<> interpolate(vector<tp> x, vector<tp> y){
	poly<> q={1},S={0};
	for(tp a:x)q=poly<>({-a,1})*q;
	fore(i,0,x.size()){
		poly<> Li=ruffini(q,x[i]).fst;
		Li=Li*(1.0/Li(x[i])); // change for int polynomials
		S=S+Li*y[i];
	}
	return S;
}
