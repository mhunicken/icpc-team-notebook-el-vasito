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

// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
typedef int tf;
typedef vector<tf> poly;
const tf MOD=998244353,RT=3,MAXN=1<<16;

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
// FFT
/*
struct CD {
	double r,i;
	CD(double r=0, double i=0):r(r),i(i){}
	double real()const{return r;}
	void operator/=(const int c){r/=c, i/=c;}
};
CD operator*(const CD& a, const CD& b){
	return CD(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
CD operator+(const CD& a, const CD& b){return CD(a.r+b.r,a.i+b.i);}
CD operator-(const CD& a, const CD& b){return CD(a.r-b.r,a.i-b.i);}
const double pi=acos(-1.0);
*/
// NTT
struct CD {
	tf x;
	CD(tf x):x(x){}
	CD(){}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<tf> rts(MAXN+9,-1);
CD root(int n, bool inv){
	tf r=rts[n]<0?rts[n]=pm(RT,(MOD-1)/n):rts[n];
	return CD(inv?pm(r,MOD-2):r);
}
CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		//double z=2*pi/m*(inv?-1:1); // FFT
		//CD wi=CD(cos(z),sin(z)); // FFT
		CD wi=root(m,inv); // NTT
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	//if(inv)fore(i,0,n)a[i]/=n; // FFT
	if(inv){ // NTT
		CD z(pm(n,MOD-2)); // pm: modular exponentiation
		fore(i,0,n)a[i]=a[i]*z;
	}
}
poly multiply(poly& p1, poly& p2){
	int n=p1.size()+p2.size()+1;
	int m=1,cnt=0;
	while(m<=n)m+=m,cnt++;
	fore(i,0,m){R[i]=0;fore(j,0,cnt)R[i]=(R[i]<<1)|((i>>j)&1);}
	fore(i,0,m)cp1[i]=0,cp2[i]=0;
	fore(i,0,p1.size())cp1[i]=p1[i];
	fore(i,0,p2.size())cp2[i]=p2[i];
	dft(cp1,m,false);dft(cp2,m,false);
	fore(i,0,m)cp1[i]=cp1[i]*cp2[i];
	dft(cp1,m,true);
	poly res;
	n-=2;
	//fore(i,0,n)res.pb((tf)floor(cp1[i].real()+0.5)); // FFT
	fore(i,0,n)res.pb(cp1[i].x); // NTT
	return res;
}

//Polynomial division: O(n*log(n))
//Multi-point polynomial evaluation: O(n*log^2(n))
//Polynomial interpolation: O(n*log^2(n))

//Works with NTT. For FFT, just replace addmod,submod,mulmod,inv
poly add(poly &a, poly &b){
	int n=SZ(a),m=SZ(b);
	poly ans(max(n,m));
	fore(i,0,max(n,m)){
		if(i<n) ans[i]=addmod(ans[i],a[i]);
		if(i<m) ans[i]=addmod(ans[i],b[i]);	
	}
	while(SZ(ans)>1&&!ans.back())ans.pop_back();
	return ans;
}

poly invert(poly &b, int d){
 poly c = {inv(b[0])};
 while(SZ(c)<=d){
 	int j=2*SZ(c);
  auto bb=b; bb.resize(j);
  poly cb=multiply(c,bb);
  fore(i,0,SZ(cb)) cb[i]=submod(0,cb[i]);
  cb[0]=addmod(cb[0],2);
  c=multiply(c,cb);
  c.resize(j);
 }
 c.resize(d+1);
 return c;
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
	bp=invert(bp,m-n);
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

vector<tf> evaluate(poly &a, vector<tf> &x){
	filltree(x);
	int k=SZ(x);
	vector<poly> ans(2*k);
	ans[1]=divide(a,tree[1]).snd;
	fore(i,2,2*k) ans[i]=divide(ans[i>>1],tree[i]).snd;
	vector<tf> r; fore(i,0,k) r.pb(ans[i+k][0]);
	return r;
}

poly derivate(poly &p){
	poly ans(SZ(p)-1);
	fore(i,1,SZ(p)) ans[i-1]=mulmod(p[i],i);
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
