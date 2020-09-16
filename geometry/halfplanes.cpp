// polygon intersecting left side of halfplanes
struct halfplane:public ln{
	double angle;
	halfplane(){}
	halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
	bool operator<(halfplane b)const{return angle<b.angle;}
};
vector<pt> intersect(vector<halfplane> &v){
	vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
	fore(i,0,4) v.pb(halfplane(bx[i],bx[(i+1)%4]));
	sort(ALL(v));
	int first=0,last=0,n=SZ(v);
	vector<pt> p(n);
	vector<halfplane> q(n);
	q[first]=v[0];
	fore(i,1,n){
		while(first<last&&v[i].side(p[last-1])<0) last--;
		while(first<last&&v[i].side(p[first])<0) first++;
		q[++last]=v[i];
		if(abs(q[last].pq%q[last-1].pq)<EPS){
			last--;
			if(q[last].side(v[i].p)>=0) q[last]=v[i];
		}
		if(first<last) p[last-1]=q[last-1]^q[last];
	}
	while(first<last&&q[first].side(p[last-1])<0) last--;
	if(last-first<=1) return {};
	p[last]=q[last]^q[first];
	vector<pt> ans;
	fore(i,first,last+1) ans.pb(p[i]);
	return ans;
}
