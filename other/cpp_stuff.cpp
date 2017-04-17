// double inf
const double DINF=numeric_limits<double>::infinity();

// Custom comparator for set/map
struct comp {
	bool operator()(const double& a, const double& b) const {
		return a+EPS<b;}
};
set<double,comp> w; // or map<double,int,comp>

// Iterate over non empty subsets of bitmask
for(int s=m;s;s=(s-1)&m)
