// Timus 1439 - AC
// http://acm.timus.ru/problem.aspx?space=1&num=1439
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
// find_by_order(i) -> iterator to ith element
// order_of_key(k) -> position (int) of lower_bound of k

ordered_set ss;
int n,q;

int find(int x){
	int s=1,e=n+1;
	while(e-s>1){
		int m=(s+e)/2;
		if(m-ss.order_of_key(m)>x)e=m;
		else s=m;
	}
	return s;
}

int main(){
	scanf("%d%d",&n,&q);
	while(q--){
		char c[4];int k;
		scanf("%s%d",c,&k);
		if(c[0]=='D')ss.insert(find(k));
		else printf("%d\n",find(k));
	}
	fore(i,0,ss.size())assert(ss.order_of_key(*ss.find_by_order(i))==i);
	return 0;
}
