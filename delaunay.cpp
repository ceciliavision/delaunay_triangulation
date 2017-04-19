#include "site.h"
#include "quadEdge.h"
#include "delaunay.h"

// construct the delaunay object
delaunay::delaunay (const std::vector<site*>& sites):
	le(NULL),
	re(NULL)
{
	divideConquer(sites, 0, sites.size(), le, re);
}

delaunay::~delaunay (void)
{	
}

void delaunay::divideConquer (const std::vector<site*>& sites, int lstart, int count, quadEdge* &le, quadEdge* &re)
{
	// { let s1, s2 be the two sites, in sorted order. Create an edge a from s1 to s2 }
	if (count == 2){
		site* s1 = sites[lstart];
		site* s2 = sites[lstart+1];
		quadEdge* a = new quadEdge();
		a->setOrig(s1);
		a->setDest(s2);
		le = a;
		re = a->geteSym();
	}

	// { let s1, s2, s3 be the three sites, in sorted order }
	// { create edges a connecting s1 ro s2 and b connecting s2 to s3 }
	else if (count == 3){
		quadEdge* a = new quadEdge();
		quadEdge* b = new quadEdge();
		a->geteSym()->splice(b);
		
		site* s1 = sites[lstart];
		site* s2 = sites[lstart+1];
		site* s3 = sites[lstart+2];
		a->setOrig(s1);
		b->setOrig(s2);
		a->setDest(s2);
		b->setDest(s3);
		
		// { now close the triangle}
		if (s1->orient2D (s2, s3)){
			// quadEdge* c = b->connect(a);
			le = a;
			re = b->geteSym();
			return;
		}
		else if (s1->orient2D(s3, s2)){
			quadEdge* c = b->connect(a);
			le = c->geteSym();
			re = c;
			return;
		}
		else{
			le = a;
			re = b->geteSym();
			return;
		}
	}

	// { L and R be the left and right halves of S. }
	else{
		quadEdge* ldo = NULL;
		quadEdge* ldi = NULL;
		quadEdge* rdi = NULL;
		quadEdge* rdo = NULL;
		int lcount = count/2;
		int rcount = count - lcount;
		int rstart = lstart + lcount;
		divideConquer(sites, lstart, lcount, ldo, ldi);
		divideConquer(sites, rstart, rcount, rdi, rdo);
		
		// { compute the lower common tangent of L and R }
		while(1)
		{
			if (rdi->getOrig()->leftOf(*ldi)){
				ldi = ldi->geteLnext();
			}
			else if (ldi->getOrig()->rightOf(*rdi)){
				rdi = rdi->geteRprev();
			}
			else{
				break;
			}
		}
		
		// { create a first cross edge basel from rdi.org to ldi.org }
		quadEdge* basel = rdi->geteSym()->connect(ldi);
		if (ldi->getOrig() == ldo->getOrig()){
			ldo = basel->geteSym();
		}
		if (rdi->getOrig() == rdo->getOrig()){
			rdo = basel;
		}

		// { merge step }
		// { locate the first L point (lcand.Dest) to be encountered by the rising bubble }
		// { and delete L edges out of basel.Dest that fail the circle test }
		while(1)
		{
			quadEdge* lcand = basel->geteSym()->geteOnext();
			if (isValid (lcand, basel)){
				while (lcand->geteOnext()->getDest()->inCircle(basel->getDest(), basel->getOrig(), lcand->getDest())){
					quadEdge* t = lcand->geteOnext();
					lcand->deleteEdge();
					delete lcand->getEdgeList();
					lcand = t;
				}
			}

			// { symmetrically, locate the first R points to be hit, and delete R edges }
			quadEdge* rcand = basel->geteOprev();
			if (isValid(rcand, basel)){
				while (rcand->geteOprev()->getDest()->inCircle (basel->getDest(), basel->getOrig(), rcand->getDest())){
					quadEdge* t = rcand->geteOprev();
					rcand->deleteEdge();
					delete rcand->getEdgeList();
					rcand = t;
				}
			}

			// { if both lcand and rcand are invalid, then basel is the upper common tangent }
			if (!isValid (lcand, basel) && !isValid(rcand, basel)){
				break;
			}

			// { the next cross edge is to be connected to either lcand.dest or rcand.dest }
			// { if both are valid, then choose the appropriate one using the inCircle test }
			if (!isValid(lcand, basel) || (isValid(rcand, basel) && 
				rcand->getDest()->inCircle( lcand->getDest(), lcand->getOrig(), rcand->getOrig()))){
				// { add cross edge basel from rcand.dest to basel.dest }
				basel = rcand->connect(basel->geteSym());
			}
			else{
				// { add cross edge basel from basel.org to lcand.dest }
				basel = basel->geteSym()->connect(lcand->geteSym());
			}
		}
		le = ldo;
		re = rdo;
	}
}