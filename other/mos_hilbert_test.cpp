// Codeforces 617E - AC
// http://codeforces.com/problemset/problem/617/E

#include <bits/stdc++.h>

using namespace std;

#define fore(i, a, b) for(ll i = a, bella = b; i < bella; i++)
#define mset(a, b) memset(a, b, sizeof(a))
#define ALL(a) a.begin(), a.end()
#define SZ(a) ll(a.size())
#define fst first 
#define snd second
#define pb push_back
#define FIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0)

typedef long double ld;
typedef long long ll;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;

const int MAXN = 100005;
int s[MAXN], k; ll res;
int cnt[1 << 21];

void init() {}
void add(int i) {
    res += cnt[s[i] ^ k];
    cnt[s[i]]++;
}
void remove(int i) {
    cnt[s[i]]--;
    res -= cnt[s[i] ^ k];
}
ll get_ans() { return res; }

int n,sq,nq; // size, sqrt(size), #queries
struct qu{int l,r,id; ll ord;}; // HILT -> ll ord;
qu qs[MAXN]; ll ans[MAXN]; // ans[i] = answer to ith query

const int HOLG = 18, HON = 1 << HOLG; // HON*HON is the size of the square (HON >= MAXN)
ll hilbertOrder(int x, int y){
  ll rx, ry, s, d = 0;
  for(s=HON/2; s>0; s/=2){
    rx = (x&s)>0, ry = (y&s)>0;
    d += s*s*((3*rx)^ry);
    if(!ry){
      if(rx) x = HON-1-x, y = HON-1-y;
      swap(x, y);
    }
  }
  return d;
}
bool qcomp(const qu &a, const qu &b) { return a.ord < b.ord; }

void mos(){
  fore(i,0,nq)qs[i].id=i, qs[i].ord = hilbertOrder(qs[i].l, qs[i].r); // HILT -> qs[i].ord = hilbertOrder(qs[i].l, qs[i].r);
  sq=sqrt(n)+.5; sort(qs,qs+nq,qcomp); int l=0,r=0; init();
  fore(i,0,nq){
    qu q=qs[i];
    while(l>q.l)add(--l);
    while(r<q.r)add(r++);
    while(l<q.l)remove(l++);
    while(r>q.r)remove(--r);
    ans[q.id]=get_ans();
  }
}

int main() { FIO;

    cin >> n >> nq >> k;
    fore(i, 0, n) {
        int a; cin >> a;
        s[i + 1] = s[i] ^ a;
    }
    fore(i, 0, nq) cin >> qs[i].l >> qs[i].r, qs[i].l--, qs[i].r++;
    mos();
    fore(i, 0, nq) cout << ans[i] << '\n';

    return 0;
}