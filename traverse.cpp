#include "traverse.h"
#include "quadEdge.h"
#include "site.h"
#include <iostream>

using namespace std;

traverse::traverse(quadEdge* startedge):
	num_triangle(0)
{
	traversal(startedge);
}

traverse::traverse(quadEdge* startedge, ostream &os):
	num_triangle(0)
{
	os << 0 << "  " << 3 << "  " << 0 << endl;
	traversal_tofile(startedge, os);
}

traverse::~traverse(void)
{
}

void traverse::traversal(quadEdge* startedge)
{
	/// Check if this startedge is already walked
	int num_tri = 0;
	while (pastEdgeDict.count(startedge->getEdgeList()) == 0)
	{
		if( !traversedTri(startedge) )
		{
			cout << startedge->getOrig()->index << "  " 
			<< startedge->geteLnext()->getOrig()->index << "  "
			<< startedge->geteLnext()->geteLnext()->getOrig()->index << endl;
			num_tri ++;
			setNumtri(num_tri);
		}

		pastEdgeDict[startedge->getEdgeList()] = true;
		pastIndDict[startedge->getOrig()->index] = true;

		quadEdge* nextWalked = startedge->geteSym()->geteOnext();
		quadEdge* oNext = startedge->geteOnext();

		traversal(nextWalked);
		startedge = oNext;
	}

	return;
}

void traverse::traversal_tofile(quadEdge* startedge, ostream &os)
{
	/// Check if this startedge is already walked
	int num_tri = 0;
	while (pastEdgeDict.count(startedge->getEdgeList()) == 0)
	{
		if( !traversedTri(startedge) )
		{
			// output to a given file, to a .ele file
			os << "   " << num_tri+1 << "    " << startedge->getOrig()->index << "  " 
			<< startedge->geteLnext()->getOrig()->index << "  "
			<< startedge->geteLnext()->geteLnext()->getOrig()->index << endl;
			num_tri ++;
			setNumtri(num_tri);
		}

		pastEdgeDict[startedge->getEdgeList()] = true;
		pastIndDict[startedge->getOrig()->index] = true;

		quadEdge* nextWalked = startedge->geteSym()->geteOnext();
		quadEdge* oNext = startedge->geteOnext();

		traversal_tofile(nextWalked, os);
		startedge = oNext;
	}

	return;
}

void traverse::setNumtri (int num_tri)
{
	num_triangle = num_tri;
	return;
}

int traverse::getNumtri (void)
{
	return num_triangle;
}

bool traverse::traversedTri (quadEdge* startedge)
{
	bool edge1 = pastIndDict.count(startedge->geteLnext()->getOrig()->index) == 0;
	bool edge2 = pastIndDict.count(startedge->geteLnext()->getOrig()->index) == 0;
	bool edge3 = pastIndDict.count(startedge->geteLnext()->getOrig()->index) == 0;
	return ( edge1 && edge2 && edge3 );
}
