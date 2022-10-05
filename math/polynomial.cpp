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
