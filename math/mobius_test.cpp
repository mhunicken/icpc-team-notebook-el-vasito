// Codeforces gym 101055C - AC
// http://codeforces.com/gym/101055/problem/C
#include <bits/stdc++.h>
#define fore(i,a,n) for(int i = a,qwer = n;i<qwer;i++)
#define fst first
#define snd second
#define pb push_back
#define mp make_pair

using namespace std;

typedef long long ll;
const int MAXN = 1500000;

short mu[MAXN] = {0,1};
void mobius(){
	fore(i,1,MAXN)if(mu[i])for(int j=i+i;j<MAXN;j+=i)mu[j]-=mu[i];
}

ll fun(ll N) {
	ll ans=0;
	for(ll i=1;i*i<=N;i++) {
		ans+=mu[i]*(N/(i*i));
	}
	return ans;
}

int main() {
	mobius();
	int q; scanf("%d",&q);
	while(q--) {
		ll N;
		scanf("%lld",&N);
		ll mn=0; ll mx = 1500000000000LL;
		// fun(mn)==N-1 fun(mn+1)==N
		while(mx-mn>1) {
			ll md = (mx+mn)/2;
			if(fun(md)>=N) mx = md;
			else {
				mn=md;
			}
		}
		printf("%lld\n",mx);
	}
	return 0;
}
