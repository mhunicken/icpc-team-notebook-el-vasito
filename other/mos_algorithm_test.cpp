// Codeforces 617E - AC
// http://codeforces.com/problemset/problem/617/E
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN 100005

int s[MAXN];
int k;
ll res;

int cnt[1<<21];

void init(){
}

void add(int i){
	res+=cnt[s[i]^k];
	cnt[s[i]]++;
}

void remove(int i){
	cnt[s[i]]--;
	res-=cnt[s[i]^k];
}

ll get_ans(){
	return res;
}

int n,sq,nq; // array size, sqrt(array size), #queries
struct qu{int l,r,id;};
qu qs[MAXN];
ll ans[MAXN]; // ans[i] = answer to ith query
bool qcomp(const qu &a, const qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1?a.r<b.r:a.r>b.r;
}
void mos(){
    fore(i,0,nq)qs[i].id=i;
    sq=sqrt(n)+.5;
    sort(qs,qs+nq,qcomp);
    int l=0,r=0;
    init();
    fore(i,0,nq){
        qu q=qs[i];
        while(l>q.l)add(--l);
        while(r<q.r)add(r++);
        while(l<q.l)remove(l++);
        while(r>q.r)remove(--r);
        ans[q.id]=get_ans();
    }
}

int main(){
	scanf("%d%d%d",&n,&nq,&k);
	fore(i,0,n){
		int a;
		scanf("%d",&a);
		s[i+1]=s[i]^a;
	}
	fore(i,0,nq)scanf("%d%d",&qs[i].l,&qs[i].r),qs[i].l--,qs[i].r++;
	mos();
	fore(i,0,nq)printf("%lld\n",ans[i]);
	return 0;
}
