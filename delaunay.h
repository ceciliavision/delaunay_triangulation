#ifndef _delaunay_H_
#define _delaunay_H_

#include <vector>

class site;
class quadEdge;

class delaunay
{
	delaunay (const std::vector<site*>& sites);
	~delaunay (void);
	public:
		quadEdge* le;
		quadEdge* re;
		divideConquer (const std::vector<Site*>& S, int lstart, int lcount, quadEdge* &le, quadEdge* &re);
}

#endif