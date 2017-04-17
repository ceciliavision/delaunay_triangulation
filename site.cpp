#include "site.h"
#include "quadEdge.h"

site::site(float x, float y):
	vx(x),
	vy(y)
{}

site::~site(void)
{}

bool site::orient2D (site* b, site* c){
	float detleft = (vx - c->vx) * (b->vy - c->vy);
	float detright = (vy - c->vy) * (b->vx - c->vx);
	float det = detleft - detright;
	return det > 0;
}

bool site::inCircle(site* a, site* b, site* c)
{
	float adx = a->vx - vx;
	float ady = a->vy - vy;
	float bdx = b->vx - vx;
	float bdy = b->vy - vy;
	float cdx = c->vx - vx;
	float cdy = c->vy - vy;

	float abdet = adx * bdy - bdx * ady;
	float bcdet = bdx * cdy - cdx * bdy;
	float cadet = cdx * ady - adx * cdy;
	float alift = adx * adx + ady * ady;
	float blift = bdx * bdx + bdy * bdy;
	float clift = cdx * cdx + cdy * cdy;

	float det = alift * bcdet + blift * cadet + clift * abdet;

	return det > 0;
}

bool site::rightOf(const quadEdge& edge)
{
	return orient2D( edge.getDest(), edge.getOrig() );
}

bool site::leftOf(const quadEdge& edge)
{
	return orient2D(edge.getOrig(), edge.getDest());
}