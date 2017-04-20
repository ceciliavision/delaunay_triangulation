#ifndef _delaunay_H_
#define _delaunay_H_

#include <vector>

class site;
class quadEdge;

using namespace std;

class delaunay
{
	public:
		delaunay (const vector<site*>& sites);
		~delaunay (void);
		quadEdge* le;
		quadEdge* re;
		void divideConquer (const vector<site*>& s, int lstart, int lcount, quadEdge* &le, quadEdge* &re);
};
 
#endif