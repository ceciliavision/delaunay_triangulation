
class site;

class orient;

class quadEdge
{
	public:
		// Constructor & destructor
		quadEdge(void);
		~quadEdge(void);

		//
		site* getOrig(void) const;
		site* getDest(void) const;
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
		void deleteEdge(quadEdge* a);
		void splice(quadEdge* b);
		quadEdge* connect(quadEdge* b);


	private:
		site* origSite;
		quadEdge* eOnext;

};
