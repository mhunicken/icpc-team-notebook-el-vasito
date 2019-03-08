//returns x such that a^x = b (mod m) or -1 if inexistent
ll discrete_log(ll a,ll b,ll m) {
    a%=m, b%=m;
    if(b == 1) return 0;
    ll tmp=1, cnt=0;
    for(ll g=__gcd(a,m);g!=1;g=__gcd(a,m)) {
        if(b%g) return -1;
        m/=g; b/=g; tmp=tmp*a/g%m; ++cnt;
        if(b == tmp) return cnt;
    }
    map<ll,int> w;
    ll s=ceil(sqrt(m)), base = b;
    fore(i,0,s)w[base]=i, base=base*a%m;
    ll key=tmp;  base=fastpow(a,s,m);
    fore(i,1,s+2){
        key=base*key%m;
        if(w.count(key)) return i*s-w[key]+cnt;
    }
    return -1;
}
