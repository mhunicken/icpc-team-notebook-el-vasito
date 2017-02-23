// double inf
const double DINF=numeric_limits<double>::infinity();

// Custom comparator for set/map
struct comp {
	bool operator()(const double& a, const double& b) const {
		return a+EPS<b;}
};
set<double,comp> w; // or map<double,int,comp>
