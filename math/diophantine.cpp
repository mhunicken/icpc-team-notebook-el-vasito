pl extendedEuclid (ll a, ll b){ //a * x + b * y = gcd(a,b)
	ll x,y;
	if (b==0) return mp(1,0);
	pl p=extendedEuclid(b,a%b);
	x=p.snd;
	y=p.fst-(a/b)*x;
	if(a*x+b*y==-gcd(a,b)) x=-x, y=-y;
	return mp(x,y);
}

pair<pl,pl> diophantine(ll a,ll b, ll r) { //a*x+b*y=r donde r es multiplo de gcd(a,b);
	ll d=gcd(a,b);
	a/=d; b/=d; r/=d;
	pl p = extendedEuclid(a,b);
	p.fst*=r; p.snd*=r;
	assert(a*p.fst+b*p.snd==r);
	return mp(p,mp(-b,a)); // las sols de la eq son las de la forma p+t*ans.snd;
}
