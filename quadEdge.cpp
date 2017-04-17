#include "quadEdge.h"

quadEdge::quadEdge(void): 
	origSite(0), 
	eOnext(NULL), 
	orientEdge(e_IDEN), 
	orientationEdgeList(new quadEdge*[4])
{
	// pre-allocate space
	for (int i=0; i<4; i++){
		orientationEdgeList[i] = this;
	}
	eOnext = this;

	// actually assign quad edge
	for (int i=1; i<4; i++){
		orientationEdgeList[i] = new quadEdge(orientationEdgeList, (orientEdge)i);
	}
	
	geteRot()->setOnext(geteRotInv());
	geteSym()->setOnext(geteSym());
	geteRotInv()->setOnext(geteRot());
}

quadEdge::quadEdge(quadEdge** orientationEdgeList, orientEdge orientation):
	origSite(0), 
	eOnext(NULL), 
	orientEdge(orientation), 
	orientationEdgeList(orientationEdgeList)
{
}

quadEdge::~quadEdge(void){
	if (orientation==e_IDEN){
		for (int i=1; i<4; i++){
			quadEdge* this_edge = orientationEdgeList[i];
			delete[] this_edge;
		}
		delete[] orientationEdgeList[0];
	}
}

void quadEdge::setOrig(site* orig){
	origSite = orig;
}

void quadEdge::setDest(site* dest){
	geteSym()->setOrig(dest);
}

void quadEdge::seteOnext(quadEdge* onext){
	eOnext = onext;
}

site* quadEdge::getOrig(void) const{
	return origSite;
}

site* quadEdge::getDest(void) const{
	return geteSym()->getOrig();
}

quadEdge** getEdgeList(void) const{
	return orientationEdgeList;
}

// pointers
quadEdge* quadEdge::geteSym(void) const{
	int id = (int(orientation)+e_SYM) % 4;
	return orientationEdgeList[id]
}

quadEdge* quadEdge::geteRot(void) const{
	int id = (int(orientation)+e_ROT) % 4;
	return orientationEdgeList[id]
}

quadEdge* quadEdge::geteRotInv(void) const{
	int id = (int(orientation)+e_ROTINV) % 4;
	return orientationEdgeList[id]
}

quadEdge* quadEdge::geteRnext(void) const{
	return geteRot()->geteOnext()->geteRotInv();
}

quadEdge* quadEdge::geteRprev(void) const{
	return geteSym()->geteOnext();
}

quadEdge* quadEdge::geteLnext(void) const{
	return geteRotInv()->geteOnext()->geteRot();
}

quadEdge* quadEdge::geteLprev(void) const{
	return geteOnext()->geteSym();
}

quadEdge* quadEdge::geteOnext(void) const{
	return eOnext;
}

quadEdge* quadEdge::geteOprev(void) const{
	return eteRot()->geteOnext()->geteRot();
}

quadEdge* quadEdge::geteDnext(void) const{
	return geteSym()->geteOnext()->geteSym();
}

quadEdge* quadEdge::geteDprev(void) const{
	return geteRotInv()->geteOnext()->geteRotInv();
}

void quadEdge::splice(quadEdge* b){
	quadEdge* alpha = geteOnext()->geteRot();
	quadEdge* beta = b->geteOnext()->geteRot();

	quadEdge* aonext_new = b->geteOnext();
	quadEdge* bonext_new = geteOnext();
	seteOnext(aonext_new);
	b->seteOnext(bonext_new);

	quadEdge* alphaonext_new beta->geteOnext();
	quadEdge* betaonext_new alpha->geteOnext();
	alpha->seteOnext(alphaonext_new);
	beta->seteOnext(betaonext_new);
}

quadEdge* quadEdge::connect(quadEdge* b){
	quadEdge* e = new quadEdge();
	site* dest_a = getDest();
	e->setOrig(dest_a);
	site* orig_b = getOrig(b);
	e->setDest(orig_b);
	e->splice(geteLnext());
	e->geteSym()->splice(b);
}

void quadEdge::deleteEdge(void){
	splice(geteOprev());
	quadEdge* eSym = geteSym();
	eSym->splice(eSym->geteOprev());
}

bool isValid(quadEdge* edge, quadEdge* basel)
{
	return edge->getDest()->rightOf(*basel);
}

