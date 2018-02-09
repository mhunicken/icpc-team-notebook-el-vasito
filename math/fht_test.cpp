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
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

#define MAXN (1<<10)

ll c1[MAXN+9],c2[MAXN+9];  // MAXN must be power of 2 !!
void fht(ll* p, int n, bool inv, char t){
	for(int l=1;2*l<=n;l*=2){
		for(int i=0;i<n;i+=2*l){
			fore(j,0,l){
				ll u=p[i+j],v=p[i+l+j];
				// XOR
				if(t=='x'){
					if(!inv)p[i+j]=u+v,p[i+l+j]=u-v;
					else p[i+j]=(u+v)/2,p[i+l+j]=(u-v)/2;
				}
				// AND
				else if(t=='a'){
					if(!inv)p[i+j]=v,p[i+l+j]=u+v;
					else p[i+j]=-u+v,p[i+l+j]=u;
				}
				// OR
				else if(t=='o'){
					if(!inv)p[i+j]=u+v,p[i+l+j]=u;
					else p[i+j]=v,p[i+l+j]=u-v;
				}
			}
		}
	}
}
// like polynomial multiplication, but XORing exponents
// instead of adding them (also ANDing, ORing)
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2, char t){
	int n=1<<(32-__builtin_clz(max(SZ(p1),SZ(p2))-1));
	fore(i,0,n)c1[i]=0,c2[i]=0;
	fore(i,0,SZ(p1))c1[i]=p1[i];
	fore(i,0,SZ(p2))c2[i]=p2[i];
	fht(c1,n,false,t);fht(c2,n,false,t);
	fore(i,0,n)c1[i]*=c2[i];
	fht(c1,n,true,t);
	return vector<ll>(c1,c1+n);
}

vector<ll> gen(){
	vector<ll> r;
	fore(_,0,MAXN)r.pb(rand()%2000000-1000000);
	return r;
}

ll t[MAXN];

int main(){
	srand(141414);
	int k=0;
	while(1){
		k++;if(k%100==0)printf("Tested %d random cases\n",k);
		vector<ll> a=gen(),b=gen();
		vector<ll> c=multiply(a,b,'x');
		memset(t,0,sizeof(t));
		fore(i,0,MAXN)fore(j,0,MAXN)t[i^j]+=a[i]*b[j];
		fore(i,0,MAXN)assert(c[i]==t[i]);
		c=multiply(a,b,'a');
		memset(t,0,sizeof(t));
		fore(i,0,MAXN)fore(j,0,MAXN)t[i&j]+=a[i]*b[j];
		fore(i,0,MAXN)assert(c[i]==t[i]);
		c=multiply(a,b,'o');
		memset(t,0,sizeof(t));
		fore(i,0,MAXN)fore(j,0,MAXN)t[i|j]+=a[i]*b[j];
		fore(i,0,MAXN)assert(c[i]==t[i]);
	}
	return 0;
}

