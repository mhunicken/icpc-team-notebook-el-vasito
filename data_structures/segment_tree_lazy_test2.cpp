// CSES Range Updates and Sums - AC
// https://cses.fi/problemset/task/1735
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

struct Lazy {
	bool set; // if true set, if false add
	ll v;

	Lazy() : set(false), v(0) {}
	Lazy(bool set, ll v) : set(set), v(v) {}

	bool operator==(Lazy o) const {
		return set==o.set && v==o.v;
	}
};

const Lazy lneut = {false, 0};
struct STree { // example: range sum with range addition
	typedef ll T; typedef Lazy L; // T: data type, L: lazy type
	constexpr static T tneut = 0; // neutrals
	T oper(T a, T b){return a+b;}
	T apply(T v, L l, int s, int e) {
		if (l.set) return l.v*(e-s);
		return v+l.v*(e-s);
	} // new st according to lazy
	L prop(L a, L b) {
		if (b.set) return b;
		return L(a.set, a.v+b.v);
	} // cumulative effect of lazy

	vector<T> st;vector<L> lazy;int n;
	STree(int n): st(4*n+5,tneut), lazy(4*n+5,lneut), n(n) {}
	void init(int k, int s, int e, const vector<T>& a){
		lazy[k]=lneut;
		if(s+1==e){st[k]=a[s];return;}
		int m=(s+e)/2;
		init(2*k,s,m,a);init(2*k+1,m,e,a);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	void push(int k, int s, int e){
		if(lazy[k] == lneut)return; // if neutral, nothing to do
		st[k]=apply(st[k], lazy[k], s, e);
		if(s+1<e){ // propagate to children
			lazy[2*k]=prop(lazy[2*k],lazy[k]);
			lazy[2*k+1]=prop(lazy[2*k+1],lazy[k]);
		}
		lazy[k]=lneut; // clear node lazy
	}
	void upd(int k, int s, int e, int a, int b, L v){
		push(k,s,e);
		if(s>=b||e<=a)return;
		if(s>=a&&e<=b){
			lazy[k]=prop(lazy[k], v); // accumulate lazy
			push(k,s,e);return;
		}
		int m=(s+e)/2;
		upd(2*k,s,m,a,b,v);upd(2*k+1,m,e,a,b,v);
		st[k]=oper(st[2*k],st[2*k+1]);
	}
	T query(int k, int s, int e, int a, int b){
		if(s>=b||e<=a)return tneut;
		push(k,s,e);
		if(s>=a&&e<=b)return st[k];
		int m=(s+e)/2;
		return oper(query(2*k,s,m,a,b),query(2*k+1,m,e,a,b));
	}
	void init(const vector<T>& a){init(1,0,n,a);}
	void upd(int a, int b, L v){upd(1,0,n,a,b,v);}
	T query(int a, int b){return query(1,0,n,a,b);}
}; // usage: STree rmq(n);rmq.init(x);rmq.upd(s,e,v);rmq.query(s,e);

int main(){
	ll n,q;
	cin>>n>>q;
	vector<ll> ts(n);
	fore(i,0,n) cin>>ts[i];
	STree t(n);t.init(ts);
	while(q--) {
		ll ty,a,b,x;
		cin>>ty>>a>>b;
		if(ty==1) {
			cin>>x;
			t.upd(a-1,b,{false,x});
		}
		else if(ty==2) {
			cin>>x;
			t.upd(a-1,b,{true,x});
		}
		else cout<<t.query(a-1,b)<<'\n';
	}
	return 0;
}
