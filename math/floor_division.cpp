void floordiv(ll x, ll y, ll& q, ll& r) { // (for negative x)
	q=x/y;r=x%y;
	if((r!=0)&&((r<0)!=(y<0)))q--,r+=y;
}
