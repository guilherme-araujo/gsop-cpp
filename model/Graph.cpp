#pragma once

#include <vector>
#include "GsopNode.cpp"

class GsopGraph{

    public:

    vector<GsopNode> nodes;

    vector< vector<int> > adjMatrix;

	int size(){
		return nodes.size();
	}
};
