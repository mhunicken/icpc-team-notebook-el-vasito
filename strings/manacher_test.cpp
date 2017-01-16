// SPOJ PLD - AC
// http://www.spoj.com/problems/PLD/
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

#define MAXN (1<<20)

int d1[MAXN];//d1[i]=max odd palin centered on i
int d2[MAXN];//d2[i]=max even palin centered on i
//s  aabbaacaabbaa
//d1 1111117111111
//d2 20103010010301
void manacher(string& s){
	int l=0,r=-1,n=s.size();
	fore(i,0,n){
		int k=i>r?1:min(d1[l+r-i],r-i);
		while(i+k<n&&i-k>=0&&s[i+k]==s[i-k])k++;
		d1[i]=k--;
		if(i+k>r)l=i-k,r=i+k;
	}
	l=0;r=-1;
	fore(i,0,n){
		int k=i>r?0:min(d2[l+r-i+1],r-i+1);k++;
		while(i+k<=n&&i-k>=0&&s[i+k-1]==s[i-k])k++;
		d2[i]=--k;
		if(i+k-1>r)l=i-k,r=i+k-1;
	}
}

char _s[MAXN];

int main(){
	int k;
	scanf("%d%s",&k,_s);
	string s(_s);
	manacher(s);
	int r=0;
	fore(i,0,s.size()){
		if(k%2==1&&2*d1[i]-1>=k)r++;
		if(k%2==0&&2*d2[i]>=k)r++;
	}
	printf("%d\n",r);
	return 0;
}
