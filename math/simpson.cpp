double integrate(double f(double), double a, double b, int n=10000){
	double r=0,h=(b-a)/n,fa=f(a),fb;
	fore(i,0,n){fb=f(a+h*(i+1));r+=fa+4*f(a+h*(i+0.5))+fb;fa=fb;}
	return r*h/6.;
}
