// ICPC Live Archive 7343 - AC
// https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=5365
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;

typedef ll tp;
#define add(n,s,d,k) fore(i,0,n)(d)[i]+=(s)[i]*k
tp* ini(int n){tp *r=new tp[n];fill(r,r+n,0);return r;}
void karatsura(int n, tp* p, tp* q, tp* r){
	if(n<=0)return;
	if(n<35)fore(i,0,n)fore(j,0,n)r[i+j]+=p[i]*q[j];
	else {
		int nac=n/2,nbd=n-n/2;
		tp *a=p,*b=p+nac,*c=q,*d=q+nac;
		tp *ab=ini(nbd+1),*cd=ini(nbd+1),*ac=ini(nac*2),*bd=ini(nbd*2);
		add(nac,a,ab,1);add(nbd,b,ab,1);
		add(nac,c,cd,1);add(nbd,d,cd,1);
		karatsura(nac,a,c,ac);karatsura(nbd,b,d,bd);
		add(nac*2,ac,r+nac,-1);add(nbd*2,bd,r+nac,-1);
		add(nac*2,ac,r,1);add(nbd*2,bd,r+nac*2,1);
		karatsura(nbd+1,ab,cd,r+nac);
		free(ab);free(cd);free(ac);free(bd);
	}
}
vector<tp> multiply(vector<tp> p0, vector<tp> p1){
	int n=max(p0.size(),p1.size());
	tp *p=ini(n),*q=ini(n),*r=ini(2*n);
	fore(i,0,p0.size())p[i]=p0[i];
	fore(i,0,p1.size())q[i]=p1[i];
	karatsura(n,p,q,r);
	vector<tp> rr(r,r+p0.size()+p1.size()-1);
	free(p);free(q);free(r);
	return rr;
}

#define MOD2 7340033

int pm2(int x, int e){
	int r=1;
	while(e){
		if(e&1)r=(1LL*r*x)%MOD2;
		e>>=1;
		x=(1LL*x*x)%MOD2;
	}
	return r;
}

int inv(int x){
	assert(x);
	return pm2(x,MOD2-2);
}

int f[100005];
int c(int n, int k){
	if(k<0||k>n)return 0;
	int r=(1LL*f[n]*inv(f[k]))%MOD2;
	r=(1LL*r*inv(f[n-k]))%MOD2;
	return r;
}

int n,n1,n2,n3,n4;
vector<ll> p0,p1;

int main(){
	f[0]=1;
	fore(i,1,100005)f[i]=(1LL*f[i-1]*i)%MOD2;
	int tn;
	scanf("%d",&tn);
	fore(tc,1,tn+1){
		printf("Case %d:\n",tc);
		scanf("%d",&n);n1=n2=n3=n4=0;
		fore(i,0,n){
			int x,y;
			scanf("%d%d",&x,&y);
			if(x>0&&y>0)n1++;
			else if(x>0&&y<0)n2++;
			else if(x<0&&y>0)n3++;
			else if(x<0&&y<0)n4++;
			else {assert(0);}
		}
		int m=(n/2)+1;
		p0.resize(m);p1.resize(m);
		fore(i,0,m){
			p0[i]=(1LL*c(n1,i)*c(n4,i))%MOD2;
			p1[i]=(1LL*c(n2,i)*c(n3,i))%MOD2;
		}
		vector<ll> r=multiply(p0,p1);
		fore(i,1,n+1){
			if(i>1)putchar(' ');
			if(i%2==1)printf("0");
			else printf("%lld",r[i/2]%MOD2);
		}
		puts("");
	}
	return 0;
}
