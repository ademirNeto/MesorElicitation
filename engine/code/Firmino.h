
#pragma once
#ifndef FIRMINO_H
#define FIRMINO_H
#include "method.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Node.h"

namespace Engine{
using namespace std;

class Firmino :	public Method {
private:
	vector<double>lower, upper;
	vector<Node*> nodes;
public:
	Node* root;
	Firmino();
	Firmino(double min, double max);
	Firmino(Node* root);
	void readLeafs(Node* root);
	int readLeafs(Node*& node, string& xfx, int & nPairs, vector<double>& x, vector<double>& Fx, double& parentProb);
	void zoomInto(Node* parent, vector<double> pr, int answer);
	~Firmino();
};};

#endif
