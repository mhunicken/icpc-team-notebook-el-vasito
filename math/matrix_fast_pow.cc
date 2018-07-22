typedef vector<vector<int> > Matrix;
int mod=1e9+7;
Matrix ones(int n) {
	Matrix r(n,vector<int>(n));
	fore(i,0,n)r[i][i]=1;
	return r;
}
Matrix operator*(Matrix &a, Matrix &b) {
	int n=SZ(a),m=SZ(b[0]),z=SZ(a[0]);
	Matrix r(n,vector<int>(m));
	fore(i,0,n)fore(j,0,m)fore(k,0,z)r[i][j]+=a[i][k]*b[k][j],r[i][j]%=mod;
	return r;
}
Matrix be(Matrix b, ll e) {
	Matrix r=ones(SZ(b));
	while(e){if(e&1LL)r=r*b;b=b*b;e/=2;}
	return r;
}
