// Input: two dates and the difference between them
// Asserts that the computed difference is correct
// Input generated with data_test_generator.py
// OK
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define fore(i,a,b) for(int i=a,ThxDem=b;i<ThxDem;++i)
using namespace std;
typedef long long ll;

int dateToInt(int y, int m, int d){
	return 1461*(y+4800+(m-14)/12)/4+367*(m-2-(m-14)/12*12)/12-
		3*((y+4900+(m-14)/12)/100)/4+d-32075;
}
void intToDate(int jd, int& y, int& m, int& d){
	int x,n,i,j;
	x=jd+68569;
	n=4*x/146097;
	x-=(146097*n+3)/4;
	i=(4000*(x+1))/1461001;
	x-=1461*i/4-31;
	j=80*x/2447;
	d=x-2447*j/80;
	x=j/11;
	m=j+2-12*x;
	y=100*(n-49)+i+x;
}

int input_date(){
	int y,m,d,yy,mm,dd;
	if(scanf("%d%d%d",&y,&m,&d)==EOF){puts("OK");exit(0);}
	int r=dateToInt(y,m,d);
	intToDate(r,yy,mm,dd);
	assert(m==mm);
	assert(d==dd);
	assert(y==yy);
	return r;
}

int main(){
	int x;
	while(1){
		int d1=input_date();
		int d2=input_date();
		int dist;
		scanf("%d",&dist);
		assert(dist==d2-d1);
	}
	return 0;
}
