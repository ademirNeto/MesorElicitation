#pragma once
#ifndef ENGINEFACADE_H
#define ENGINEFACADE_H
#include "method.h"
#include<iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Node.h"
//#include "Firmino.h"
#include "NodeDistribution.h"
#include "NonParametric.h"

namespace Engine{

	using namespace std;

	public ref class EngineFacade{
//	private:
		//Firmino* firmino;
	public:
		NodeDistribution* nodeDistribution;
		//Firmino method
		//int initializeFirmino(const double lower, const double upper);
		//int initializeFirmino(Node* root);
		//int getFirminoRoot(Node*& node);
		//int updateFirminoDensity(Node*& node, string& xfx, int & nPairs);

		//General
		int getNode(Node* input, const double lowerKey, const double upperKey, Node*& output);
		//int getNode(Node* input, const double key, Node*& output);
		int getNodeFromSameGeneration(Node* input, const int parentGeneration, Node*& next);
		EngineFacade(void);
		//int initializeNodeDistribution(const double lower, const double upper);
		int initializeNodeDistribution(Node* root);
		int getNodeDistributionRoot(Node*& node);
		int updateNodeDistribution(Node*& node, string& xfx, int & nPairs);
		int updateLastParent(Node*& lastParent);
		int getLastParent(Node*& lastParent);
		int getStatisticalMeasures(vector<double> x, vector<double> Fx, string& xfx, int & nPairs);
		int deleteNews();
	};
};
#endif
