#include <stdio.h>
#include <assert.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctime>

#include "quadEdge.h"
#include "site.h"
#include "delaunay.h"

// TODO
// assignment and comparison between sites and quadEdges
// the constructor and destructor
// files and parse, and sort
// output

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

	// use std::sort, with self-defined sorting scheme
	sort(sites.begin(), sites.end(), siteLessPredicate);

	clock_t start = clock();
	// delaunay delaunay(sites);
	double duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    cout<<"Delaunay Triangulation takes (in s): "<< duration <<'\n';

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