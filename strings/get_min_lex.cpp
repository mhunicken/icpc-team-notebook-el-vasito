vector<ll> getminlex(vector<ll> v){
    int n=SZ(v);
    fore(i,0,n)v.pb(v[i]);
    vector<ll> f(2*n,-1),ans;
    int k=0;
    fore(j,1,2*n){
        ll sj=v[j],i=f[j-k-1];
        while(i>=0&&sj!=v[k+i+1]){
            if(sj<v[k+i+1]) k=j-i-1;
            i=f[i];
        }
        if(sj!=v[k+i+1]){
            if(sj<v[k])k=j;
            f[j-k]=-1;
        }
        else f[j-k]=i+1;
    }
    fore(i,0,n) ans.pb(v[k+i]);
    return ans;
}
