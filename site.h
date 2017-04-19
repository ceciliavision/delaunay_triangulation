#ifndef _site_H_
#define _site_H_

#define myEPS 1e-6;

class quadEdge;

class site
{
	public:
		float vx;
		float vy;

		site(float x, float y);
		~site(void);

		bool orient2D(site* b, site* c);
		bool inCircle(site* a, site* b, site* c);
		bool rightOf(const quadEdge& edge);
		bool leftOf(const quadEdge& edge);
};

#endif