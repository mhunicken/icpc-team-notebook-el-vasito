// Codeforces Extreme Auto Tune - AC
// https://codeforces.com/group/j1UosVRZar/contest/287404/problem/E
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

typedef int tf;
typedef vector<tf> poly;
const tf MOD=998244353,RT=3,LG=16;

tf addmod(tf a, tf b){tf r=a+b;if(r>=MOD)r-=MOD;return r;}
tf submod(tf a, tf b){tf r=a-b;if(r<0)r+=MOD;return r;}
tf mulmod(ll a, ll b){return a*b%MOD;}
tf pm(ll a, ll b){
	ll r=1;
	while(b){
		if(b&1) r=mulmod(r,a); b>>=1;
		a=mulmod(a,a);
	}
	return r;
}
tf inv(tf a){return pm(a,MOD-2);}

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
poly multiply(const poly &as, const poly &bs) {
	static uint32_t v[2<<LG];
	static FFT<uint32_t, uint64_t, 998244353, 3> fft;
	return fft.cv(as, bs, v);
}

// Polynomial division: O(n*log(n))
// Multi-point polynomial evaluation for arbitrarily large points: O(n+k*log^2(k))
// Multi-point polynomial evaluation for all points in [0, MOD): O((n+MOD)*log(n+MOD))
// Polynomial interpolation: O(n*log^2(n))
// Inverse: O(n*log(n))
// Log: O(n*log(n))
// Exp: O(n*log(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(const poly &a, const poly &b){
	int n=SZ(a),m=SZ(b);
	poly ans(max(n,m));
	fore(i,0,max(n,m)) ans[i]=addmod(i<SZ(a)?a[i]:0, i<SZ(b)?b[i]:0);
	while(SZ(ans)>1&&!ans.back())ans.pop_back();
	return ans;
}

// derivative of p
poly derivative(const poly &p){
	poly ans(max(1, SZ(p)-1));
	fore(i,1,SZ(p)) ans[i-1]=mulmod(p[i],i);
	return ans;
}

// integral of p
poly integrate(const poly &p){
	int n=SZ(p);
	poly ans(n+1);
	if(!n) return ans;
	poly pre(n+1); pre[0]=1;
	fore(i,1,n+1) pre[i]=mulmod(pre[i-1],i);
	tf iv=inv(pre[n]);
	for(int i=n;i>=1;i--){
		ans[i]=mulmod(p[i-1], mulmod(iv,pre[i-1]));
		iv=mulmod(iv,i);
	}
	return ans;
}

// p % (x^n)
poly takemod(const poly &p, int n){
	poly res=p;
	res.resize(min(SZ(res),n));
	while(SZ(res)>1&&res.back()==0) res.pop_back();
	return res;
}

// first d terms of 1/p
poly invert(const poly &p, int d){
	assert(p[0]);
	poly res={inv(p[0])};
	int sz=1;
	while(sz<d){
		sz*=2;
		poly pre(p.begin(), p.begin()+min(SZ(p),sz));
		poly cur=multiply(res,pre);
		fore(i,0,SZ(cur)) cur[i]=submod(0,cur[i]);
		cur[0]=addmod(cur[0],2);
		cur=takemod(cur,sz);
		res=multiply(res,cur);
		res=takemod(res,sz);
	}
	res.resize(d);
	return res;
}

// first d terms of log(p)
poly log(const poly &p, int d){
	assert(p[0]==1);
	poly cur=takemod(p,d);
	poly a=invert(cur,d), b=derivative(cur);
	auto res=multiply(a,b);
	res=takemod(res,d-1);
	res=integrate(res);
	return res;
}

// first d terms of exp(p)
poly exp(const poly &p, int d){
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

pair<poly,poly> divslow(const poly &a, const poly &b){
	poly q,r=a;
	tf ib=inv(b.back());
	while(SZ(r)>=SZ(b)){
		q.pb(mulmod(r.back(),ib));
		if(q.back()) fore(i,0,SZ(b)){
			r[SZ(r)-i-1]=submod(r[SZ(r)-i-1],mulmod(q.back(),b[SZ(b)-i-1]));
		}
		r.pop_back();
	}
	reverse(ALL(q));
	return {q,r};
}

pair<poly,poly> divide(const poly &a, const poly &b){	//returns {quotient,remainder}
	int m=SZ(a),n=SZ(b),MAGIC=128;
	if(m<n) return {{0},a};
	if(min(m-n,n)<MAGIC)return divslow(a,b);
	poly ap=a; reverse(ALL(ap));
	poly bp=b; reverse(ALL(bp));
	bp=invert(bp,m-n+1);
	poly q=multiply(ap,bp);
	q.resize(m-n+1,0);
	reverse(ALL(q));
	poly bq=multiply(b,q);
	fore(i,0,SZ(bq)) bq[i]=submod(0,bq[i]);
	poly r=add(a,bq);
	return {q,r};
}

struct EvalTree {
	int k;
	vector<poly> tree;
	EvalTree(const vector<tf> &x): k(SZ(x)), tree(2*max(SZ(x),1)) {
		fore(i,k,2*k) tree[i]={submod(0,x[i-k]),1};
		for(int i=k-1;i;i--) tree[i]=multiply(tree[2*i],tree[2*i+1]);
	}
};

poly mulT(const poly &M, const poly &a, int n){
	poly c=multiply(M,a);
	int m=SZ(M);
	poly res(n);
	fore(j,0,n) res[j]=(j+m-1<SZ(c))?c[j+m-1]:0;
	return res;
}

void downsweep(const EvalTree &et, int v, poly q, vector<tf> &out){
	if(v>=et.k){ out[v-et.k]=q[0]; return; }
	poly ql=mulT(et.tree[2*v+1],q,SZ(et.tree[2*v])-1);
	poly qr=mulT(et.tree[2*v],  q,SZ(et.tree[2*v+1])-1);
	poly().swap(q);
	downsweep(et,2*v,move(ql),out);
	downsweep(et,2*v+1,move(qr),out);
}

vector<tf> evaluate(const poly &a, const EvalTree &et){
	int k=et.k;
	if(!k) return {};
	poly f=SZ(a)>=SZ(et.tree[1])?divide(a,et.tree[1]).snd:a;
	poly rm=et.tree[1]; reverse(ALL(rm));
	poly h=invert(rm,SZ(f));
	poly().swap(rm);
	reverse(ALL(h));
	poly q1=mulT(h,f,SZ(et.tree[1])-1);
	poly().swap(h); poly().swap(f);
	vector<tf> out(k);
	downsweep(et,1,move(q1),out);
	return out;
}

// Multi-point polynomial evaluation for arbitrarily large points
vector<tf> evaluate(const poly &a, const vector<tf> &x){
	if(x.empty()) return {};
	EvalTree et(x);
	return evaluate(a,et);
}

poly upsweep(EvalTree &et, int v, const vector<tf> &c){
	if(v>=et.k) return {c[v-et.k]};
	poly L=upsweep(et,2*v,c), R=upsweep(et,2*v+1,c);
	poly p1=multiply(et.tree[2*v],R);   poly().swap(R);
	poly p2=multiply(et.tree[2*v+1],L); poly().swap(L);
	poly().swap(et.tree[2*v]); poly().swap(et.tree[2*v+1]);
	poly res=add(p1,p2);
	return res;
}

poly interpolate(const vector<tf> &x, const vector<tf> &y){
	int k=SZ(x);
	if(!k) return {0};
	EvalTree et(x);
	vector<tf> d=evaluate(derivative(et.tree[1]),et);
	vector<tf> pre(k+1); pre[0]=1;
	fore(i,0,k) pre[i+1]=mulmod(pre[i],d[i]);
	tf iv=inv(pre[k]);
	vector<tf> c(k);
	for(int i=k-1;i>=0;i--){
		c[i]=mulmod(y[i],mulmod(iv,pre[i]));
		iv=mulmod(iv,d[i]);
	}
	return upsweep(et,1,c);
}

poly interpolate(const vector<tf> &x, const vector<tf> &y){
	EvalTree et(x);
	auto &tree=et.tree;
	poly p=derivative(tree[1]);
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

int main(){FIN;
	int m,k; cin>>m>>k;
	int top=max(k,m)+2;
	vector<int> x,y;
	int ac=0;
	fore(i,0,top){
		ac=addmod(ac,pm(i,k));
		x.pb(i); y.pb(ac);
	}
	poly p=interpolate(x,y);
	vector<int> xs;
	fore(i,0,m){
		ll x; cin>>x; x%=MOD;
		xs.pb(x);
	}
	while(SZ(xs)!=top) xs.pb(0);
	vector<int> ans=evaluate(p,xs);
	fore(i,0,m)cout<<ans[i]<<" ";cout<<"\n";
}
