ll inv(ll a, ll mod) { //inverse of a modulo mod
	assert(gcd(a,mod)==1);
	pl sol = extendedEuclid(a,mod);
	return ((sol.fst%mod)+mod)%mod;
}