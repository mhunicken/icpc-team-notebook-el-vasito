// Polynomial division: O(n*log(n))
// Multi-point polynomial evaluation for arbitrarily large points: O(n*log^2(n))
// Multi-point polynomial evaluation for all points in [0, MOD): O((n+MOD)*log(n+MOD))
// Polynomial interpolation: O(n*log^2(n))
// Inverse: O(n*log(n))
// Log: O(n*log(n))
// Exp: O(n*log(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=SZ(a),m=SZ(b);
	poly ans(max(n,m));
	fore(i,0,max(n,m)) ans[i]=addmod(i<SZ(a)?a[i]:0, i<SZ(b)?b[i]:0);
	while(SZ(ans)>1&&!ans.back())ans.pop_back();
	return ans;
}

// derivative of p
poly derivate(poly &p){
	poly ans(max(1, SZ(p)-1));
	fore(i,1,SZ(p)) ans[i-1]=mulmod(p[i],i);
	return ans;
}

// integral of p
poly integrate(poly &p){
	poly ans(SZ(p)+1);
	fore(i,0,SZ(p)) ans[i+1]=mulmod(p[i], inv(i+1));
	return ans;
}

// p % (x^n)
poly takemod(poly &p, int n){
	poly res=p;
	res.resize(min(SZ(res),n));
	while(SZ(res)>1&&res.back()==0) res.pop_back();
	return res;
}

// first d terms of 1/p
poly invert(poly &p, int d){
	assert(p[0]);
	poly res={inv(p[0])};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly pre(p.begin(), p.begin()+min(SZ(p),sz));
		poly cur=multiply(res,pre);
		fore(i,0,SZ(cur)) cur[i]=submod(0,cur[i]);
		cur[0]=addmod(cur[0],2);
		res=multiply(res,cur);
		res=takemod(res,sz);
	}
	res.resize(d);
	return res;
}

// first d terms of log(p)
poly log(poly &p, int d){
	assert(p[0]==1);
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivate(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}

// first d terms of exp(p)
poly exp(poly &p, int d){
	assert(!p[0]);
	poly res={1};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly lg=log(res, sz), cur(sz);
		fore(i,0,sz) cur[i]=submod(i<SZ(p)?p[i]:0, i<SZ(lg)?lg[i]:0);
		cur[0]=addmod(cur[0],1);
		res=multiply(res,cur);
		res=takemod(res, sz);
	}
	
	res.resize(d);
	return res;
}

pair<poly,poly> divslow(poly &a, poly &b){
	poly q,r=a;
	while(SZ(r)>=SZ(b)){
		q.pb(mulmod(r.back(),inv(b.back())));
		if(q.back()) fore(i,0,SZ(b)){
			r[SZ(r)-i-1]=submod(r[SZ(r)-i-1],mulmod(q.back(),b[SZ(b)-i-1]));
		}
		r.pop_back();
	}
	reverse(ALL(q));
	return {q,r};
}

pair<poly,poly> divide(poly &a, poly &b){	//returns {quotient,remainder}
	int m=SZ(a),n=SZ(b),MAGIC=750;
	if(m<n) return {{0},a};
	if(min(m-n,n)<MAGIC)return divslow(a,b);
	poly ap=a; reverse(ALL(ap));
	poly bp=b; reverse(ALL(bp));
	bp=invert(bp,m-n+1);
	poly q=multiply(ap,bp);
	q.resize(SZ(q)+m-n-SZ(q)+1,0);
	reverse(ALL(q));
	poly bq=multiply(b,q);
	fore(i,0,SZ(bq)) bq[i]=submod(0,bq[i]);
	poly r=add(a,bq);
	return {q,r};
}

vector<poly> tree;

void filltree(vector<tf> &x){
	int k=SZ(x);
	tree.resize(2*k);
	fore(i,k,2*k) tree[i]={submod(0,x[i-k]),1};
	for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]);
}

// Multi-point polynomial evaluation for arbitrarily large points
vector<tf> evaluate(poly &a, vector<tf> &x){
	filltree(x);
	int k=SZ(x);
	vector<poly> ans(2*k);
	ans[1]=divide(a,tree[1]).snd;
	fore(i,2,2*k) ans[i]=divide(ans[i>>1],tree[i]).snd;
	vector<tf> r; fore(i,0,k) r.pb(ans[i+k][0]);
	return r;
}

int get_primitive_root(int p) {
	if(p==2)return 1;
	int phi=p-1, n=phi;
    vector<int> fact;
	for(int i=2;i*i<=n;i++) if(n%i==0){
		fact.pb(i);
		while(n%i==0) n/=i;
	}
	if(n>1) fact.pb(n);

	fore(res,2,p+1){
		int ok=1;
		for(int f:fact){
			if(fpow(res,phi/f)==1){
				ok=false;
				break;
			}
		}
		if(ok)return res;
    }
    return -1;
}

// Multi-point polynomial evaluation for all points in [0, MOD)
// MOD needs to be a prime number
vector<int> evaluate_all_points(poly& pp) {
	poly p(min(SZ(pp), MOD));
	fore(i,0,SZ(p)) p[i]=pp[i];
	fore(i,MOD,SZ(pp)){
		int e=(i-1)%(MOD-1)+1;
		p[e]=addmod(p[e], pp[i]);
	}

    int g=get_primitive_root(MOD), inv_g=inv(g), n=SZ(p)-1;
	assert(g!=-1);
    poly ap(n+1, 0), bp(n+MOD); 

	fore(i,0,n+MOD-1){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
        if(i<=n) ap[n-i]=mulmod(p[i],fpow(inv_g, exp));
		bp[i]=fpow(g, exp);
    }

    poly cp=multiply(ap, bp);

    vector<int> ans(MOD,pp[0]);
    int gk=1;

	fore(i,0,MOD-1){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
        int val=0;
		if(n+i<SZ(cp)) val=cp[n+i];
		val=mulmod(val, fpow(inv_g,exp));
        ans[gk] = val;
        gk=mulmod(gk,g);
    }

    return ans;
}

poly interpolate(vector<tf> &x, vector<tf> &y){
	filltree(x);
	poly p=derivate(tree[1]);
	int k=SZ(y);
	vector<tf> d=evaluate(p,x);
	vector<poly> intree(2*k);
	fore(i,k,2*k) intree[i]={mulmod(y[i-k],inv(d[i-k]))};
	for(int i=k-1;i;i--){
		poly p1=multiply(tree[2*i],intree[2*i+1]);
		poly p2=multiply(tree[2*i+1],intree[2*i]);
		intree[i]=add(p1,p2);
	}
	return intree[1];
}
