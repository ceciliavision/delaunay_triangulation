#ifndef _traverse_H_
#define _traverse_H_

#include <fstream>
#include <map>
using namespace std;

class quadEdge;

class traverse
{
	public:
		traverse(quadEdge* startedge);
		traverse(quadEdge* startedge, ostream &os);
		~traverse(void);

		map<quadEdge*, bool> pastEdgeDict;
		map<int, bool> pastIndDict;
		void traversal_tofile(quadEdge* startedge, ostream &os);
		void traversal(quadEdge* startedge);
		bool traversedTri (quadEdge* startedge);
		void setNumtri (int num_tri);
		int getNumtri (void);

	private:
		int num_triangle;
};

#endif