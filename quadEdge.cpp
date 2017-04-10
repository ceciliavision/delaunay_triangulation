#include "quadEdge.h"
#include "dcel.h"


quadEdge::quadEdge(void) : 
	origSite(NULL), 
	eOnext(NULL), 
	orientation(0), 
	orientationEdgeList(new quadEdge*[4])
{
	for (int i=1; i<4; i++){
		orientationEdgeList[i] = 
	}
	m_Onext = this;
	geteRot()->setOnext(geteRotInv());
	geteSym()->setOnext(geteSym());
	geteRotInv()->setOnext(geteRot());
}

quadEdge::~quadEdge(void){

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

