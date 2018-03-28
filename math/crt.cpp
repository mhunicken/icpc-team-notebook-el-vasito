#define mod(a,m) (((a)%m+m)%m)
pl sol(tuple<ll,ll,ll> c){ //requires inv, extEuclid, diophantine, gcd
    ll a=get<0>(c), x1=get<1>(c), m=get<2>(c), d=gcd(a,m);
    if(d==1) return mp(mod(x1*inv(a,m),m), m);
    else return x1%d ? mp(-1LL,-1LL) : sol(make_tuple(a/d,x1/d,m/d));
}
pl teocochino(vector< tuple<ll,ll,ll> > cond) {
	if(cond.size()==1) return sol(cond[0]);
	ll a1,x1,m1,a2,x2,m2,n=cond.size();
	tie(a1,x2,m1)=cond[n-1]; tie(a2,x2,m2)=cond[n-2];
	tie(x1,m1)=sol(cond[n-1]); tie(x2,m2)=sol(cond[n-2]);
	cond.pop_back();cond.pop_back();
	if((x1-x2)%gcd(m1,m2)) return mp(-1,-1);
	else if(m1==m2) cond.pb(make_tuple(1,x1,m1));
	else {
		ll k=diophantine(m2,-m1,x1-x2).fst.snd;
		ll mcm=m1*(m2/gcd(m1,m2)), x=mod((__int128)m1*k+x1,mcm);
		cond.pb(make_tuple(1,x,mcm));
	}
	return teocochino(cond);
} //cond[i]={ai,bi,mi} ai*xi=bi (mi); assumes lcm fits in ll 
