// ICPC Live Archive 4671 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=2672
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

// MAXN must be power of 2 !!
// MOD-1 needs to be a multiple of MAXN !!
// big mod and primitive root for NTT:
typedef int tf;
typedef vector<tf> poly;
const tf MAXN=1<<19;
// FFT
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
// NTT
/*
struct CD {
	tf x;
	CD(tf x):x(x){}
	CD(){}
};
CD operator*(const CD& a, const CD& b){return CD(mulmod(a.x,b.x));}
CD operator+(const CD& a, const CD& b){return CD(addmod(a.x,b.x));}
CD operator-(const CD& a, const CD& b){return CD(submod(a.x,b.x));}
vector<int> rts(MAXN+9,-1);
CD root(int n, bool inv){
	int r=rts[n]<0?rts[n]=pm(RT,(MOD-1)/n):rts[n];
	return CD(inv?pm(r,MOD-2):r);
}
*/
CD cp1[MAXN+9],cp2[MAXN+9];
int R[MAXN+9];
void dft(CD* a, int n, bool inv){
	fore(i,0,n)if(R[i]<i)swap(a[R[i]],a[i]);
	for(int m=2;m<=n;m*=2){
		double z=2*pi/m*(inv?-1:1); // FFT
		CD wi=CD(cos(z),sin(z)); // FFT
		// CD wi=root(m,inv); // NTT
		for(int j=0;j<n;j+=m){
			CD w(1);
			for(int k=j,k2=j+m/2;k2<j+m;k++,k2++){
				CD u=a[k];CD v=a[k2]*w;a[k]=u+v;a[k2]=u-v;w=w*wi;
			}
		}
	}
	if(inv)fore(i,0,n)a[i]/=n; // FFT
	//if(inv){ // NTT
	//	CD z(pm(n,MOD-2)); // pm: modular exponentiation
	//	fore(i,0,n)a[i]=a[i]*z;
	//}
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
	fore(i,0,n)res.pb((ll)floor(cp1[i].real()+0.5)); // FFT
	//fore(i,0,n)res.pb(cp1[i].x); // NTT
	return res;
}

#define P 1777771

int MOD[]={999727999,1070777777};
int PI[]={325255434,10018302};

int ns,nt,k;

char s[200005];
char t[200005];
int p[200005][2];
int pis[200005][2];
int h[200005][2];

set<pair<int,int> > w;

int gh(int _, int s, int e){
	return ((1LL*(h[e][_]+MOD[_]-h[s][_])%MOD[_])*pis[s][_])%MOD[_];
}

int main(){
	fore(_,0,2){
		p[0][_]=pis[0][_]=1;
		fore(i,1,200005){
			p[i][_]=(1LL*p[i-1][_]*P)%MOD[_];
			pis[i][_]=(1LL*pis[i-1][_]*PI[_])%MOD[_];
		}
	}
	int tc=1;
	while(scanf("%d",&k),k>=0){
		scanf("%s%s",s,t);ns=strlen(s);nt=strlen(t);
		if(nt>ns){printf("Case %d: 0\n",tc++);continue;}
		fore(_,0,2){
			h[0][_]=0;
			fore(i,0,ns){
				h[i+1][_]=(h[i][_]+(1LL*s[i]*p[i][_]))%MOD[_];
			}
		}
		vector<int> S,T,R;
		w.clear();
		fore(i,0,ns)S.pb(s[i]=='a'?1:-1);
		fore(i,0,nt)T.pb(t[i]=='a'?1:-1);
		reverse(T.begin(),T.end());
		R=multiply(S,T);
		int q=nt-2*k,r=0;
		fore(i,nt-1,ns){
			if(R[i]>=q){
				w.insert({gh(0,i-nt+1,i+1),gh(1,i-nt+1,i+1)});
			}
		}
		printf("Case %d: %d\n",tc++,(int)w.size());
	}
	return 0;
}
