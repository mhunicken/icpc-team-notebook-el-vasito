vector<int> z_function(string& s){
	vector<int> z(s.size(),0); // z[i] = max k: s[0,k) == s[i,i+k)
	int l=0,r=0;
	fore(i,1,n){
		if(i<=r)z[i]=min(r-i+1,z[i-l]);
		while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
		if(i+z[i]-1>r)l=i,r=i+z[i]-1;
	}
	return z;
}
