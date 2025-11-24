// Codeforces 104288G - AC
// https://codeforces.com/gym/104288/problem/G
#include <bits/stdc++.h>
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define pb push_back
#define ALL(s) s.begin(),s.end()
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define SZ(s) int(s.size())
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

// The maximum length of the resulting convolution vector is 2^LG
const int LG = 20;
typedef vector<ll> poly;

template<class u, class uu, u p, u root>
struct FFT {
	u r[1+(2<<LG)];
	constexpr u m(u a, u b) {
		uu k = uu(a)*b;
		#define op(g) g*(g*p+2)
		k += u(k) * (op(op(op(op(op(-p)))))) * uu(p);
		#undef op
		return u(k>>(8*sizeof(u)));
	}
	constexpr u red(u k, u a){return a-k*(a>=k);}
	FFT() {
		u k=r[2<<LG]=-p%p, b=root, e=p>>LG;
		for(;e;e/=2,b=m(b,b)) if(e&1) k=m(k,b);
		for(int i=(2<<LG)-1;i>=0;i--) r[i]=red(p, m(r[i+1], k)), i&(i-1)?0:k=m(k,k);
	}
	poly cv(const poly &as, const poly &bs, u *v) {
		int c=max(SZ(as)+SZ(bs)-1, 0), n=1;
		assert(c <= (1<<LG));
		u h=u(uu(-p)*-p%p), a=m(h, p/2+1), x, y;
		while(n<c) n*=2, h=red(p, m(h, a));
		fore(i,0,n){
			v[i]=i<SZ(as)?u(as[i]):0,
			v[i+n]=i<SZ(bs)?u(bs[i]):0;

		}
		for(auto s:{v,v+n}) for(int j=n;j>=2;j--) for(int k=j&-j; k/=2;) fore(i,j-k,j){
			x=s[i], y=s[i-k];
			s[i-k] = red(2*p, x+y);
			s[i] = m(2*p+y-x, r[3*k-j+i]);
		}
		fore(i,0,n) v[i]=m(v[i], v[i+n]);
		fore(j,2,n+1) for(int k=1; !(k&j); k*=2) fore(i,j-k,j){
			x = m(v[i], r[3*k+j-i]);
			y = red(2*p, v[i-k]);
			v[i-k]=x+y, v[i]=2*p+y-x;
		}
		fore(i,0,c) v[i]=red(p, m(v[i], h));
		return poly(v, v+c);
	}
};

// For modular convolutions modulo 998244353.
// Replace with any NTT-friendly mod by doing:
// FFT<uint32_t, uint64_t, MOD, primitiveRoot(MOD)>
poly conv_small(const poly &as, const poly &bs) {
	static uint32_t v[2<<LG];
	static FFT<uint32_t, uint64_t, 998244353, 3> fft;
	return fft.cv(as, bs, v);
}

// For modular convolutions modulo a 62 bit prime.
poly conv_big(const poly &as, const poly &bs) {
	static uint64_t v[2<<LG];
	static FFT<uint64_t, __uint128_t, (1ull<<62)-(18ull<<32)+1, 3> fft;
	return fft.cv(as, bs, v);
}

// For modular convolutions modulo an arbitrary 32-bit modulus.
// Slightly slower than above versions, because it performs two calls to fft
poly conv_sunzi(const poly &v1, const poly &v2, ll m) {
	const uint64_t inv = 2703402103339935109ull,
		mod1 = (1ull<<62)-(18ull<<32)+1,
		mod2 = (1ull<<62)-(76ull<<32)+1;
	static uint64_t v[2<<LG];
	static FFT<uint64_t, __uint128_t, mod1, 3> fft1;
	static FFT<uint64_t, __uint128_t, mod2, 17> fft2;
	auto as=fft1.cv(v1, v2, v), bs=fft2.cv(v1, v2, v);
	fore(i,0,SZ(as)){
		auto d = fft1.m(mod1+as[i]-bs[i], inv);
		d -= mod1*(d >= mod1); d %= m;
		as[i] = (bs[i] + mod2%m*d)%m;
	}
	return as;
}

poly add(poly p, poly q){
	int n=SZ(p),m=SZ(q);
	poly ans(max(n,m));
	fore(i,0,n) ans[i]+=p[i];
	fore(i,0,m) ans[i]+=q[i];
	return ans;
}
 
poly sub(poly p, poly q){
	int n=SZ(p),m=SZ(q);
	poly ans(max(n,m));
	fore(i,0,n) ans[i]+=p[i];
	fore(i,0,m) ans[i]-=q[i];
	return ans;
}
 
int main(){FIN;
	int n1,m1; cin>>n1>>m1;
	vector<vector<int>> a(n1,vector<int>(m1));
	fore(i,0,n1) fore(j,0,m1) cin>>a[i][j];
	
	int n2,m2; cin>>n2>>m2;
	vector<vector<int>> b(n2,vector<int>(m2));
	fore(i,0,n2) fore(j,0,m2) cin>>b[i][j];
	
	
	poly p;
	fore(i,0,n1){
		fore(j,0,m1) p.pb(a[i][j]);
		if(i!=n1-1) fore(j,0,m2-m1) p.pb(0);
	}
	
	poly q;
	fore(i,0,n2) fore(j,0,m2) q.pb(b[i][j]);
	
	// (p-q)^2 = p^2 - 2*p*q + q^2
	
	ll sum2=0;
	for(auto &x:p) sum2+=x*x;
	auto sq=q;
	for(auto &x:sq) x=x*x;
	fore(i,1,SZ(sq)) sq[i]+=sq[i-1];
	
	poly qr=p;
	reverse(ALL(qr));
	
	poly now=conv_big(q,qr);
	poly me;
	fore(i,0,SZ(q)-SZ(p)+1){
	  ll val=sq[i+SZ(p)-1]; if(i) val-=sq[i-1];
	  val-=2ll*now[SZ(p)+i-1];
	  val+=sum2;
	  me.pb(val);
	}
	
	//(p0*q^2)
	poly p0=p;
	for(auto &x:p0) x=x==0;
	for(auto &x:q) x=x*x;
	reverse(ALL(p0));
	poly now2=conv_big(p0,q);
	poly he;
	fore(i,0,SZ(q)-SZ(p0)+1) he.pb(now2[SZ(p)+i-1]);
 
	// (p-q)^2 - (p0*q^2)
	poly ans=sub(me,he);
	
	vector<ii> res;
	
	fore(i,0,n2) fore(j,0,m2) if(i+n1<=n2 && j+m1<=m2 && ans[m2*i+j]==0){
		res.pb({i,j});
	}
	
	cout<<SZ(res)<<"\n";
	for(auto x:res)cout<<x.fst+1<<" "<<x.snd+1<<"\n";
}