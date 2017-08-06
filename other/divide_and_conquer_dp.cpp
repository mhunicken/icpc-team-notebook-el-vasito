// O(knlogn). For 2D dps, when the position of optimal choice is non-decreasing as the second variable increases
int k,n,f[MAXN],f2[MAXN];
void doit(int s, int e, int s0, int e0, int i){
	// [s,e): range of calculation, [s0,e0): range of optimal choice
	if(s==e)return;
	int m=(s+e)/2,r=INF,rp;
	fore(j,s0,min(e0,m)){
		int r0=something(i,j); // "something" usually depends on f
		if(r0<r)r=r0,rp=j; // position of optimal choice
	}
	f2[m]=r;
	doit(s,m,s0,rp+1,i);doit(m+1,e,rp,e0,i);
}
int doall(){
	init_base_cases();
	fore(i,1,k)doit(1,n+1,0,n,i),memcpy(f,f2,sizeof(f));
	return f[n];
}
