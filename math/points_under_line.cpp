// # of lattice points s.t. ax+by<=c, x,y>0 (a,b is positive integer)
ll f(ll a, ll b, ll c){
	if(c<=0) return 0;
	if(a<b) swap(a, b);
	ll m=c/a, k=(a-1)/b, h=(c-a*m)/b;
	if(a==b) return m*(m-1)/2;
	return f(b,a-b*k,c-b*(k*m+h))+k*m*(m-1)/2+m*h;
}
// # of lattice points s.t. ax+by<=c, 0<x<=X, 0<y<=Y (a,b integers > 0)
ll g(ll a, ll b, ll c, ll X, ll Y){
	if(a*X+b*Y<=c) return X*Y;
	return f(a,b,c)-f(a,b,c-a*X)-f(a,b,c-b*Y)+f(a,b,c-a*X-b*Y);
}
