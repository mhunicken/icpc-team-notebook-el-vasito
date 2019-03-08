#include <bits/stdc++.h>
#ifdef DEMETRIO
#define deb(...) fprintf(stderr,__VA_ARGS__)
#define deb1(x) cerr << #x << " = " << x << endl
#else
#define deb(...) 0
#define deb1(x) 0
#endif
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)(x).size())
#define mset(a,v) memset(a,v,sizeof(a))
#define mcopy(a,b) memcpy(a,b,sizeof(a))
#define MOD 998244353
using namespace std;
typedef long long ll;

#define RT 3
#define MAXN (1<<18)
ll mulmod(ll a, ll b){
	return (a*b)%MOD;
	/*ll r=0;
	while(b){
		if(b&1)r=(r+a)%MOD;
		b>>=1;a=(a+a)%MOD;
	}
	return r;*/
}
ll pm(ll a, ll e){
	ll r=1;
	while(e){
		if(e&1)r=mulmod(r,a);
		e>>=1;a=mulmod(a,a);
	}
	return r;
}
ll inv(ll a){return pm(a,MOD-2);}
// big mod and primitive root for NTT:
//#define MOD 2305843009255636993
//#define RT 5
struct CD {
	ll x;
	CD(ll x):x(x){}
	CD(){}
	ll get()const{return x;}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD((a.x+b.x)%MOD);}
CD operator-(const CD& a, const CD& b){return CD((a.x+MOD-b.x)%MOD);}
CD cp1[MAXN+9],cp2[MAXN+9];  // MAXN must be power of 2 !!
int R[MAXN+9];
CD root(int n, bool inv){ // NTT
	ll r=pm(RT,(MOD-1)/n); // pm: modular exponentiation
	return CD(inv?pm(r,MOD-2):r);
}
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
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2){
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
	vector<ll> res;
	n-=2;
	fore(i,0,n)res.pb((ll)floor(cp1[i].get())); // change for NTT
	return res;
}

vector<ll> p;
ll f[100005],fi[100005];
int n;ll m;

void doit(vector<ll>& p, bool asd){
	fore(i,0,n)p[i]=mulmod(p[i],f[i]);
	vector<ll> q;
	fore(i,0,n)q.pb(fi[n-1-i]);
	if(asd)for(int i=n-2;i>=0;i-=2)q[i]=MOD-q[i];
	vector<ll> v=multiply(p,q);
	p.clear();
	fore(i,0,n)p.pb(v[i+n-1]);
	fore(i,0,n)p[i]=mulmod(p[i],fi[i]);
}

int main(){
	f[0]=1;
	fore(i,1,100005)f[i]=mulmod(f[i-1],i);
	fore(i,0,100005)fi[i]=inv(f[i]);
	scanf("%d%lld",&n,&m);n++;
	fore(i,0,n){
		int x;
		scanf("%d",&x);
		p.pb(x);
	}
	doit(p,false);
	fore(i,0,n)p[i]=mulmod(p[i],pm(inv(i+1),m));
	doit(p,true);
	fore(i,0,n)printf("%lld%c",p[i]," \n"[i==n-1]);
	return 0;
}
