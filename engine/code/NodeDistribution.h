
#pragma once
#ifndef NodeDistribution_H
#define NODEDISTRIBUTION_H
#include "Method.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Node.h"

namespace Engine{
using namespace std;

class NodeDistribution :	public Method {
private:
	vector<double>lower, upper;
	vector<Node*> nodes;
public:
	Node* root;
	Node* lastParent;
	NodeDistribution();
	NodeDistribution(double min, double max);
	NodeDistribution(Node* root);
	void readLeafs(Node* root);
	int readLeafs(Node*& node, string& xfx, int & nPairs, vector<double>& x, vector<double>& Fx, double parentProb);
	void zoomInto(Node* parent, vector<double> pr, int answer);
	//void updateLastParent(Node*& lastParent);
	~NodeDistribution();
};};

#endif
