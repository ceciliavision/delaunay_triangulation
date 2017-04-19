#ifndef _quadEdge_H_
#define _quadEdge_H_

class site;

#define e_IDEN 0
#define e_ROT 1
#define e_SYM 2
#define e_ROTINV 3

class quadEdge
{
	public:
		// Constructor & destructor
		quadEdge(void);
		~quadEdge(void);

		// members
		site* getOrig(void) const;
		site* getDest(void) const;
		quadEdge* getEdgeList(void) const;
		void setOrig(site* orig);
		void setDest(site* dest);
		void seteOnext(quadEdge* onext);

		// pointers
		quadEdge* geteSym(void) const;
		quadEdge* geteRot(void) const;
		quadEdge* geteRotInv(void) const;
		quadEdge* geteRnext(void) const;
		quadEdge* geteRprev(void) const;
		quadEdge* geteLnext(void) const;
		quadEdge* geteLprev(void) const;
		quadEdge* geteOnext(void) const;
		quadEdge* geteOprev(void) const;
		quadEdge* geteDnext(void) const;
		quadEdge* geteDprev(void) const;
		
		// Basic topological operators
		void deleteEdge(void);
		void splice(quadEdge* b);
		quadEdge* connect(quadEdge* b);


	private:
		quadEdge(quadEdge** orientationEdgeList, int orientation);
		site* origSite;
		quadEdge* eOnext;
		int orientation;
		quadEdge** orientationEdgeList;

};

bool isValid(quadEdge* edge, quadEdge* basel);

#endif