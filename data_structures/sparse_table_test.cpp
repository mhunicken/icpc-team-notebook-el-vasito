// SPOJ RMQSQ - AC
// http://www.spoj.com/problems/RMQSQ/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define K 17

#define oper min
int st[K][1<<K];int n;  // K such that 2^K>n
void st_init(int *a){
	fore(i,0,n)st[0][i]=a[i];
	fore(k,1,K)fore(i,0,n-(1<<k)+1)
		st[k][i]=oper(st[k-1][i],st[k-1][i+(1<<(k-1))]);
}
int st_query(int s, int e){
	int k=31-__builtin_clz(e-s);
	return oper(st[k][s],st[k][e-(1<<k)]);
}

int x[1<<K];

int main(){
	scanf("%d",&n);
	fore(i,0,n)scanf("%d",x+i);
	st_init(x);
	int q;
	scanf("%d",&q);
	while(q--){
		int i,j;
		scanf("%d%d",&i,&j);j++;
		printf("%d\n",st_query(i,j));
	}
	return 0;
}
