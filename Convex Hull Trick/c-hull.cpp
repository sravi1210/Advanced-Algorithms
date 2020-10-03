#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

class Line{
	private:
		ll slope;
		ll intercept;
	public:
		Line(ll slope, ll intercept){
			this->slope = slope;
			this->intercept = intercept;
		}
		ll getIntercept(){
			return this->intercept;
		}
		ll getSlope(){
			return this->slope;
		}
		double intersect(Line L2){
			return (double)(L2.getIntercept() - this->intercept)/(double)(this->slope - L2.getSlope()); 
		}
};

class ConvexHull{
	private:
		vector<Line> hull;
	public:
		ConvexHull(){
			this->hull.clear();
		}

		ll query(ll x){
			ll lo = 0;
			ll hi = this->hull.size()-2;
			ll ans = this->hull.size()-1;
			while(lo<=hi){
				ll mid = (lo+hi)/2;
				Line L = this->hull[mid];
				if(L.intersect(this->hull[mid+1]) >= x){
					ans = mid;
					hi = mid-1;
				}
				else{
					lo = mid+1; 
				}
			}
			if(ans<0){
				return 0;
			}
			ll slope = this->hull[ans].getSlope();
			ll intercept = this->hull[ans].getIntercept();
			return ((slope*x) + intercept);
		}

		void add(ll slope, ll intercept){   //this add only works if slope is present in strictly decreasing manner.
			Line L(slope, intercept);
			ll size = this->hull.size();
			while(size>=2){
				Line L1 = this->hull[size-1];
				Line L2 = this->hull[size-2];
				if(L1.intersect(L2) >= L1.intersect(L)){
					this->hull.pop_back();
					size = this->hull.size();
				}
				else{
					break;
				}
			}
			this->hull.push_back(L);
			return;
		}
};


int main(){
	return 0;
}