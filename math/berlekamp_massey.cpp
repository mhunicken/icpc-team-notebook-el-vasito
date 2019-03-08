typedef vector<int> vi;
vi BM(vi x){
	vi ls,cur;int lf,ld;
  fore(i,0,SZ(x)){
		ll t=0;
    fore(j,0,SZ(cur))t=(t+x[i-j-1]*(ll)cur[j])%MOD;
		if((t-x[i])%MOD==0)continue;
    if(!SZ(cur)){cur.resize(i+1);lf=i;ld=(t-x[i])%MOD;continue;}
		ll k=-(x[i]-t)*fast_pow(ld,MOD-2)%MOD;
		vi c(i-lf-1);c.pb(k);
    fore(j,0,SZ(ls))c.pb(-ls[j]*k%MOD);
    if(SZ(c)<SZ(cur))c.resize(SZ(cur));
    fore(j,0,SZ(cur))c[j]=(c[j]+cur[j])%MOD;
    if(i-lf+SZ(ls)>=SZ(cur))ls=cur,lf=i,ld=(t-x[i])%MOD;
		cur=c;
	}
  fore(i,0,SZ(cur))cur[i]=(cur[i]%MOD+MOD)%MOD;
	return cur;
}
