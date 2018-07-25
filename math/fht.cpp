ll c1[MAXN+9],c2[MAXN+9];  // MAXN must be power of 2 !!
void fht(ll* p, int n, bool inv){
	for(int l=1;2*l<=n;l*=2)for(int i=0;i<n;i+=2*l)fore(j,0,l){
		ll u=p[i+j],v=p[i+l+j];
		if(!inv)p[i+j]=u+v,p[i+l+j]=u-v; // XOR
		else p[i+j]=(u+v)/2,p[i+l+j]=(u-v)/2;
		//if(!inv)p[i+j]=v,p[i+l+j]=u+v; // AND
		//else p[i+j]=-u+v,p[i+l+j]=u;
		//if(!inv)p[i+j]=u+v,p[i+l+j]=u; // OR
		//else p[i+j]=v,p[i+l+j]=u-v;
	}
}
// like polynomial multiplication, but XORing exponents
// instead of adding them (also ANDing, ORing)
vector<ll> multiply(vector<ll>& p1, vector<ll>& p2){
	int n=1<<(32-__builtin_clz(max(SZ(p1),SZ(p2))-1));
	fore(i,0,n)c1[i]=0,c2[i]=0;
	fore(i,0,SZ(p1))c1[i]=p1[i];
	fore(i,0,SZ(p2))c2[i]=p2[i];
	fht(c1,n,false);fht(c2,n,false);
	fore(i,0,n)c1[i]*=c2[i];
	fht(c1,n,true);
	return vector<ll>(c1,c1+n);
}
