//https://open.kattis.com/problems/generalchineseremainder
#include <bits/stdc++.h>
#define fst first
#define snd second
#define pb push_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pl;

ll gcd(ll a, ll b){while(b){ll t=a%b;a=b;b=t;}return a;}
pl extendedEuclid (ll a, ll b){ //a * x + b * y = gcd(a,b)
	ll x,y;
	if (b==0) return mp(1,0);
	pl p=extendedEuclid(b,a%b);
	x=p.snd;
	y=p.fst-(a/b)*x;
	if(a*x+b*y==-gcd(a,b)) x=-x, y=-y;
	return mp(x,y);
}
pair<pl,pl> diophantine(ll a,ll b, ll r) { //a*x+b*y=r donde r es multiplo de gcd(a,b);
	ll d=gcd(a,b);
	a/=d; b/=d; r/=d;
	pl p = extendedEuclid(a,b);
	p.fst*=r; p.snd*=r;
	assert(a*p.fst+b*p.snd==r);
	return mp(p,mp(-b,a)); // las sols de la eq son las de la forma p+t*ans.snd;
}
ll inv(ll a, ll m) {
	assert(gcd(a,m)==1);
	ll x = diophantine(a,m,1).fst.fst;
	return ((x%m)+m)%m;
}



#define mod(a,m) (((a)%m+m)%m)
pl sol(tuple<ll,ll,ll> c){ //requires inv, extEuclid, diophantine, gcd
    ll a=get<0>(c), x1=get<1>(c), m=get<2>(c), d=gcd(a,m);
    if(d==1) return mp(mod(x1*inv(a,m),m), m);
    else return x1%d ? mp(-1LL,-1LL) : sol(make_tuple(a/d,x1/d,m/d));
}
pl teocochino(vector< tuple<ll,ll,ll> > cond) {
	if(cond.size()==1) return sol(cond[0]);
	ll a1,x1,m1,a2,x2,m2,n=cond.size();
	tie(a1,x2,m1)=cond[n-1]; tie(a2,x2,m2)=cond[n-2];
	tie(x1,m1)=sol(cond[n-1]); tie(x2,m2)=sol(cond[n-2]);
	cond.pop_back();cond.pop_back();
	if((x1-x2)%gcd(m1,m2)) return mp(-1,-1);
	else if(m1==m2) cond.pb(make_tuple(1,x1,m1));
	else {
		ll k=diophantine(m2,-m1,x1-x2).fst.snd;
		ll mcm=m1*(m2/gcd(m1,m2)), x=mod((__int128)m1*k+x1,mcm);
		cond.pb(make_tuple(1,x,mcm));
	}
	return teocochino(cond);
} //cond[i]={ai,bi,mi} ai*xi=bi (mi); assumes lcm fits in ll 



int main(){
    int T; cin >> T;
    while(T--){
        #define mt make_tuple
        int a, n, b, m; cin >> a >> n >> b >> m;
        vector<tuple<ll,ll,ll> > cond = {mt(1,a,n),mt(1,b,m)};
        pl ans = teocochino(cond);
        if(ans.fst==-1&&ans.snd==-1)cout<<"no solution\n";
        else cout<<ans.fst<<" " <<ans.snd << "\n";
    }
}
