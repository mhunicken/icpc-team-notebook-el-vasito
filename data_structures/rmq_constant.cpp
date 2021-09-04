typedef int tf;
struct rmq{
	int n; tf INF=1e9;	//change sign of INF for maximum
	vector<unsigned int> mk; vector<tf> bk,v;
	rmq(){}
	tf op(tf a, tf b){return min(a,b);}	//change for maximum
	int f(int x){return x>>5;}
	rmq(vector<tf> &vv):n(SZ(vv)),mk(n),bk(n,INF),v(vv){
		unsigned int lst=0;
		for(int i=0;i<SZ(v);i++,lst<<=1){
			bk[f(i)]=op(bk[f(i)],v[i]);
			while(lst&&v[i-__builtin_ctz(lst)]>v[i]) lst^=lst&-lst;		//MIN
			//while(lst&&v[i-__builtin_ctz(lst)]<v[i]) lst^=lst&-lst;	//MAX
			mk[i]=++lst;
		}
		for(int k=1,top=f(n);(1<<k)<=top;k++)fore(i,0,top)if(i+(1<<k)<=top)
			bk[top*k+i]=op(bk[top*(k-1)+i], bk[top*(k-1)+i+(1<<k-1)]);
	}
	tf get(int st, int en){
		return v[en-31+__builtin_clz(mk[en]&((1ll<<en-st+1)-1))];
	}
	tf query(int s, int e){	//[s,e]
		int b1=f(s),b2=f(e),top=f(n);
		if(b1==b2) return get(s,e);
		tf ans=op(get(s,(b1+1)*32-1), get(b2*32,e)); s=(b1+1)*32; e=b2*32-1;
		if(s<=e){
			int k=31-__builtin_clz(f(e-s+1));
			ans=op(ans,op(bk[top*k+f(s)],bk[top*k+f(e)-(1<<k)+1]));
		}
		return ans;
	}
};
