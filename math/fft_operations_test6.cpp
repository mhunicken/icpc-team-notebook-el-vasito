// Test for multi-point evaluation for all points in range [0,MOD)
// Manual randomized brute force - AC
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

const int MAXN=10001;
int MOD;

int addmod(int a, int b){a+=b;if(a>=MOD)a-=MOD;return a;}
int submod(int a, int b){a-=b;if(a<0)a+=MOD;return a;}
int mulmod(ll a, ll b){return a*b%MOD;}
int fpow(int a, ll b){
	int r=1;
	while(b){if(b&1)r=mulmod(r,a); b>>=1; a=mulmod(a,a);}
	return r;
}
int inv(int a){
	return fpow(a,MOD-2);
}

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

// For modular convolutions modulo an arbitrary 32-bit modulus.
// Slightly slower than above versions, because it performs two calls to fft
poly multiply(const poly v1, const poly v2, ll m=MOD) {
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

// Given any number g, perform multi-point polynomial evaluation
// for all points of the form g^i, for each i in [0, k)
// in O((n+k) * log(n+k))
vector<int> chirpTransform(poly& p, int g, int k) {
	int inv_g=inv(g), n=SZ(p)-1, sz=min(k,MOD-1), gk=1;
	poly ap(n+1), bp(n+sz);

	fore(i,0,n+sz){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
		if(i<=n) ap[n-i]=mulmod(p[i],fpow(inv_g, exp));
		bp[i]=fpow(g, exp);
	}

	poly cp=multiply(ap, bp);
	vector<int> ans(k);

	fore(i,0,sz){
		ll exp=1ll*i*(i-1)/2%(MOD-1);
		int val=0;
		if(n+i<SZ(cp)) val=cp[n+i];
		val=mulmod(val, fpow(inv_g,exp));
		ans[i]=val;
		gk=mulmod(gk,g);
	}
	fore(i,sz,k) ans[i]=ans[i-MOD+1];
	return ans;
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
vector<int> evaluate_all_points(poly& p) {
	int g=get_primitive_root(MOD), gk=1;
	assert(g!=-1);

	vector<int> ch=chirpTransform(p,g,MOD-1), ans(MOD, p[0]);
	
	fore(i,0,MOD-1){
		ans[gk]=ch[i];
		gk=mulmod(gk,g);
	}
	return ans;
}

auto rnd=bind(uniform_int_distribution<int>(0,1e9), mt19937(time(0)));

int getRand(int l, int r){
	return l+rnd()%(r-l+1);
}

int eval(poly &p, int x){
	int pw=1, ans=0;
	for(auto a:p){
		ans=addmod(ans, mulmod(pw, a));
		pw=mulmod(pw, x);
	}
	return ans;
}

int main(){FIN;
	vector<int> spf(MAXN), pr;
	fore(i,2,MAXN) if(!spf[i]){
		pr.pb(i);
		for(int j=i;j<MAXN;j+=i) if(!spf[j]) spf[j]=i;
	}

	int it=100;

	while(it--){
		MOD=pr[getRand(0,SZ(pr)-1)];
		int n=10000;
		poly p(n+1);
		fore(i,0,n+1) p[i]=getRand(0,MOD-1);

		auto res=evaluate_all_points(p);
		vector<int> brute(MOD);
		fore(i,0,MOD) brute[i]=eval(p,i);

		cout<<"checking polynomial of degree "<<n<<" for MOD = "<<MOD<<": ";
		cout<<(res==brute)<<endl;
	}
}
