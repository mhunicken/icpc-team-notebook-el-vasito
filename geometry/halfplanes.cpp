int sgn3(double d){return abs(d)<EPS?0:(d>0?1:-1);}

struct halfplane:public ln{
    double angle;
    halfplane(){}
    halfplane(pt a,pt b){p=a; pq=b-a; angle=atan2(pq.y,pq.x);}
    bool operator<(halfplane b)const{return angle<b.angle;}
};

struct halfplanes {
  int n;
  vector<halfplane> hp;
  halfplanes(vector<halfplane> v):hp(v),n(SZ(v)){}
  halfplanes(){}
  void normalize(){ //removes unnecesary lines and orders by angle
    sort(hp.begin(),hp.end());
    vector<halfplane> v = {hp[0]};
    fore(i,1,n){
      if(sgn3(hp[i].angle-v.back().angle)) v.pb(hp[i]);
      else if(sgn3(v.back().pq%(hp[i].p-v.back().p))>0) v.back()=hp[i];
    }
    hp = v; n = hp.size();
  }
  // polygon intersecting left side of halfplanes
  // returns point (0,0) if area of intersection is empty
  pol intersect(){
    vector<pt>bx={{DINF,DINF},{-DINF,DINF},{-DINF,-DINF},{DINF,-DINF}};
    fore(i,0,4) hp.pb(halfplane(bx[i],bx[(i+1)%4]));
    n=SZ(hp);
    normalize();
    int st=0,ed=1;
    vector<int> que(n);
    vector<pt> p1(n);
    que[st]=0; que[ed]=1;
    p1[1]=hp[0]^hp[1];
    for(int i=2; i<n && st <= ed;i++){
      while(st<ed&&sgn3(((hp[i].pq)%(p1[ed]-hp[i].p)))<0)ed--;
      while(st<ed&&sgn3(((hp[i].pq)%(p1[st+1]-hp[i].p)))<0)st++;
      que[++ed]=i;
      if(hp[i]/hp[que[ed-1]]) ed=-1;
      else p1[ed]=hp[i]^hp[que[ed-1]];
    }
    while(st<ed&&sgn3((hp[que[st]].pq)%(p1[ed]-hp[que[st]].p))<0)ed--;
    while(st<ed&&sgn3((hp[que[ed]].pq)%(p1[st+1]-hp[que[ed]].p))<0)st++;
    vector<pt> ans;
    if(st <= ed){
      p1[st]=hp[que[st]]^hp[que[ed]];
      fore(i,st,ed+1) ans.pb(p1[i]);
    }
    double a=pol(ans).area();
    if(a<EPS) return pol({pt(0,0)});
    return ans;
  }
};
