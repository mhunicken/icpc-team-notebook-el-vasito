// Library checker: counting_primes - AC
// https://judge.yosupo.jp/problem/counting_primes
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

// Count number of primes in [1,n]
// O(n^(2/3)) time
// O(sqrt(n)) memory
ll prime_count(ll n) {
    if (n <= 1) return 0;
    int v = sqrtl(n), s = (v+1)>>1, pc=0;
    vector<int> smalls(s), roughs(s), skip(v+1);
    vector<ll> larges(s);
    fore(i,0,s){
        smalls[i]=i;
        roughs[i]=2*i+1;
        larges[i]=(n/roughs[i]-1)>>1;
    }
    for(int p=3;p<=v;p+=2) if(!skip[p]){
        int q=p*p;
        if(1ll*q*q>n) break;
        skip[p]=1;
        for(int i=q;i<=v;i+=2*p) skip[i]=1;
        int ns=0;
        fore(k,0,s){
            int i=roughs[k];
            if(skip[i]) continue;
            ll d=1ll*i*p;
            larges[ns]=larges[k]-(d<=v?larges[smalls[d>>1]-pc]:smalls[(n/d-1)>>1])+pc;
            roughs[ns++]=i;
        }
        s=ns;
        for(int i=(v-1)>>1, j=((v/p)-1)|1; j>=p; j-=2){
            int c=smalls[j>>1]-pc;
            for(int e=(j*p)>>1;i>=e;i--) smalls[i]-=c;
        }
        pc++;
    }
    larges[0]+=1ll*(s+2*(pc-1))*(s-1)>>1;
    fore(k,1,s) larges[0]-=larges[k];
    fore(l,1,s){
        int q=roughs[l];
        ll m=n/q, t=0;
        int e=smalls[(m/q-1)>>1]-pc;
        if(e<l+1)break;
        fore(k,l+1,e+1) t+=smalls[(m/roughs[k]-1)>>1];
        larges[0]+=t-1ll*(e-l)*(pc+l-1);
    }
    return larges[0]+1;
}

int main(){FIN;
  ll n; cin>>n;
  cout<<prime_count(n)<<"\n";
}