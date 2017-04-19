#include <stdio.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include <iostream>

#include "quadEdge.h"
#include "site.h"
#include "delaunay.h"

// TODO
// assignment and comparison between sites and quadEdges
// the constructor and destructor
// files and parse, and sort
// output
// add timer

using namespace std;

int main(int argc, char** argv)
{
	ifstream infile(argv[1]);
	int num_v, num_dim, num_attr, boundary_marker;
	infile >> num_v >> num_dim >> num_attr >> boundary_marker;

	if (num_v <=0 ){
		cout << "No points to process\n" << endl;
		return 0;
	}
	else{
		printf(" Reading file %s, in total %d vertices to process\n", argv[1], num_v);
	}

	vector<site*> sites;
	int vid;
	float p1, p2;
	for (int i = 0; i < num_v; ++i)
	{
		infile >> vid >> p1 >> p2;
		sites.push_back(new site(p1, p2));
	}

	// delaunay delaunay(sites);

	//
	vector<site*>::iterator site_s = sites.begin();
	vector<site*>::iterator site_e = sites.end();
	while (site_s != site_e)
	{
		delete *site_s;
		site_s++;
	}

	return 0;
}