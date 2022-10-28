vector<ll> getminlex(vector<ll> s){
	int n=SZ(s),k=0; fore(i,0,n) s.pb(s[i]);
	vector<int> f(2*n,-1);
	fore(j,1,2*n){
		int i=f[j-k-1];
		while(i>=0&&s[j]!=s[k+i+1]){
			if(s[j]<s[k+i+1]) k=j-i-1;
			i=f[i];
		}
		if(s[j]!=s[k+i+1]){
			if(s[j]<s[k])k=j;
			f[j-k]=-1;
		} else f[j-k]=i+1;
	}
	vector<ll> ans; fore(i,0,n) ans.pb(s[k+i]);
	return ans;
}
