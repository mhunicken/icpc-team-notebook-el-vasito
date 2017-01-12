// Codeforces 154B - AC
// http://codeforces.com/problemset/problem/154/B
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 100005

int cr[MAXN]; // -1 if prime, some not trivial divisor if not
void init_sieve(){
	memset(cr,-1,sizeof(cr));
	fore(i,2,MAXN)if(cr[i]<0)for(ll j=1LL*i*i;j<MAXN;j+=i)cr[j]=i;
}
map<int,int> fact(int n){  // must call init_cribe before
	map<int,int> r;
	while(cr[n]>=0)r[cr[n]]++,n/=cr[n];
	if(n>1)r[n]++;
	return r;
}

void div_rec(vector<ll>& r, vector<pair<ll,int> >& f, int k, ll c){
	if(k==f.size()){r.pb(c);return;}
	fore(i,0,f[k].snd+1)div_rec(r,f,k+1,c),c*=f[k].fst;
}
vector<ll> divisors(vector<pair<ll,int> > f){
	vector<ll> r;
	div_rec(r,f,0,1);
	return r;
}

bool on[MAXN];
int w[MAXN];
int n,m;

int main(){
	init_sieve();
	scanf("%d%d",&n,&m);
	memset(w,-1,sizeof(w));
	while(m--){
		char s[4];int x;
		scanf("%s%d",s,&x);
		if(s[0]=='+'){
			if(on[x])puts("Already on");
			else {
				map<int,int> f=fact(x);
				vector<ll> d=divisors(vector<pair<ll,int> >(f.begin(),f.end()));
				bool r=true;
				for(ll y:d){
					if(y==1)continue;
					if(w[y]>=0){
						printf("Conflict with %d\n",w[y]);
						r=false;
						break;
					}
				}
				if(r){
					puts("Success");
					on[x]=true;
					for(ll y:d){
						if(y==1)continue;
						w[y]=x;
					}
				}
			}
		}
		else {
			if(!on[x])puts("Already off");
			else {
				puts("Success");
				on[x]=false;
				map<int,int> f=fact(x);
				vector<ll> d=divisors(vector<pair<ll,int> >(f.begin(),f.end()));
				for(ll y:d)w[y]=-1;
			}
		}
	}
	return 0;
}
