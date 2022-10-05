vector<int> cr(MAXN + 1), pr;
void init_sieve() {
	for(int i=2;i<=MAXN;i++){
		if (cr[i] == 0)cr[i] = i,pr.push_back(i);
		for(int j=0;j<SZ(pr)&&pr[j]<=cr[i]&&i*pr[j]<=MAXN;++j) {
			cr[i*pr[j]]=pr[j];
		}
	}
}
