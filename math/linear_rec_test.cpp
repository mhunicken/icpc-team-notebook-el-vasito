//Codechef CROWD
//https://www.codechef.com/problems/CROWD

#include <bits/stdc++.h>
#ifdef DBP
#define deb(...) fprintf(stderr,__VA_ARGS__)
#else
#define deb(...) 0
#endif
#define fst first
#define snd second
#define fore(x,a,b) for(int x=(a), qwerty=(b); x<qwerty; x++)
#define pb push_back
#define mset(a,v) memset((a),(v),sizeof(a))
#define ALL(a) (a).begin(), (a).end()
#define SZ(a) int((a).size())
#define FIN ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
using namespace std;
typedef long long ll;

//init O(n^2log) query(n^2 logk)
//input: terms: first n term; trans: transition function; MOD; LOG=mxlog of k
//output calc(k): kth term mod MOD
//example: {1,1} {2,1} an=2*a_(n-1)+a_(n-2); calc(3)=3 calc(10007)=71480733
const ll MOD=1e9+7;const int LOG=62;
struct LinearRec{
    typedef vector<ll> vi;
    int n; vi terms, trans; vector<vi> bin;
    vi add(vi &a, vi &b){
        vi res(n*2+1);
        fore(i,0,n+1)fore(j,0,n+1)res[i+j]=(res[i+j]*1LL+(ll)a[i]*b[j])%MOD;
        for(int i=2*n; i>n; --i){
            fore(j,0,n)res[i-1-j]=(res[i-1-j]*1LL+(ll)res[i]*trans[j])%MOD;
            res[i]=0;
        }
        res.erase(res.begin()+n+1,res.end());
        return res;
    }
    LinearRec(vi &terms, vi &trans):n(SZ(terms)),terms(terms),trans(trans){
        vi a(n+1);a[1]=1;
        bin.pb(a);
        fore(i,1,LOG)bin.pb(add(bin[i-1],bin[i-1]));
    }
    int calc(ll k){
        vi a(n+1);a[0]=1;
        fore(i,0,LOG)if((k>>i)&1)a=add(a,bin[i]);
        int ret=0;
        fore(i,0,n)ret=((ll)ret+(ll)a[i+1]*terms[i])%MOD;
        return ret;
    }
};

ll add(ll a,ll b){if(a>=MOD)a%=MOD;if(b>=MOD)b%=MOD;a+=b;if(a>=MOD)a-=MOD;return a;}
ll sub(ll a,ll b){if(a>=MOD)a%=MOD;if(b>=MOD)b%=MOD;a-=b;if(a<0)a+=MOD;return a;}
ll be(ll b, ll e){
    ll r=1;
    while(e)if(e&1)e^=1,r=(r*b)%MOD; else e>>=1,b=(b*b)%MOD;
    return r;
}

int main(){FIN;
    int T; cin >> T;
    vector<ll> terms={0,1,1}, trans = {1,1,1};
    LinearRec lr(terms,trans);
    while(T--){
        ll n;cin>>n;
        cout<<sub(be(2,n),lr.calc(n+3))<<"\n";
    }
}
