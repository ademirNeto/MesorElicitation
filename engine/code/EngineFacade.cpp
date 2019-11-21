
#include "EngineFacade.h"

//Memory Leak Detection Enabling    
#include <stdlib.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace Engine{
	EngineFacade::EngineFacade(void){
		this->nodeDistribution = NULL;
	}
	//int EngineFacade::initializeFirmino(const double lower, const double upper){
	//	this->firmino = new Firmino(lower, upper);
	//	return 1;
	//}
	//int EngineFacade::getFirminoRoot(Node*& node){
	//	node= this->firmino->root;	
	//	return 1;
	//}
	//int EngineFacade::initializeFirmino(Node* root){
	//	this->firmino = new Firmino(root);	
	//	return 1;
	//}
	//int EngineFacade::updateFirminoDensity(Node*& root, string& xfx, int & nPairs){
	//	xfx="";
	//	nPairs=0;
	//	vector<double> x(1), Fx(1);
	//	x[0] = root->lower; Fx[0] = 0;
	//	double parentProb = 1;
	//	this->firmino->readLeafs(root, xfx, nPairs, x, Fx, parentProb);	
	//	this->getStatisticalMeasures(x, Fx, xfx, nPairs);
	//	//NonParametric* np = new NonParametric(x, Fx, nPairs);
	//	//double Ex = np->getMean();
	//	//double Md = np->getQuantile(.5);
	//	//double Mo = np->getMode();
	//	//double Vx = np->getVariance();
	//	//char st[4000];
	//	//sprintf_s(st, "%f", Ex); xfx+=st; xfx+=";";
	//	//sprintf_s(st, "%f", Md); xfx+=st; xfx+=";";
	//	//sprintf_s(st, "%f", Mo); xfx+=st; xfx+=";";
	//	//sprintf_s(st, "%f", Vx); xfx+=st; xfx+=";";

	//	//if(root->density != NULL)
	//	//	deleted root->density ;
	//	//root->density = np;
	//	return 1;
	//}
	int EngineFacade::getStatisticalMeasures(vector<double> x, vector<double> Fx, string& xfx, int & nPairs){
		//xfx="";
		NonParametric np (x, Fx, nPairs);
		double Ex = np.getMean();
		double Md = np.getQuantile(.5);
		double Mo = np.getMode();
		double Vx = np.getVariance();
		char st[4000];
		sprintf_s(st, "%f", Ex); xfx+=st; xfx+=";";
		sprintf_s(st, "%f", Md); xfx+=st; xfx+=";";
		sprintf_s(st, "%f", Mo); xfx+=st; xfx+=";";
		sprintf_s(st, "%f", Vx); xfx+=st; xfx+=";";

		//if(root->density != NULL)
		//	deleted root->density ;
		//root->density = np;
		return 1;
	}
	int EngineFacade::getNodeFromSameGeneration(Node* input, const int parentGeneration, Node*& next){
		if(next == 0 || input->getGeneration()<next->getGeneration()){
			if(input->getChildrenCount()==0)
				next = input;
			else{
				getNodeFromSameGeneration(input->getChild(0), parentGeneration, next);
				getNodeFromSameGeneration(input->getChild(1), parentGeneration, next);
			}
		}
		
		return 1;	
	}

	int EngineFacade::getNode(Node* input, const double lowerKey, const double upperKey, Node*& output){
		float tolerance = 0;
		//double diff = key - input->center;
		//if(diff< -tolerance)
		//	getNode(input->getChild(0), key, output);
		//else if(diff > tolerance)
		//	getNode(input->getChild(1), key, output);
		//else
		//	output = input;
		if(upperKey - input->center <= -tolerance)
			getNode(input->getChild(0), lowerKey, upperKey, output);
		else if(lowerKey - input->center >= tolerance)
			getNode(input->getChild(1), lowerKey, upperKey, output);
		else
			output = input;

		return 1;	
	}

	int EngineFacade::deleteNews(){
		delete this->nodeDistribution;	
		return 1;
	}
	int EngineFacade::initializeNodeDistribution(Node* root){
		this->nodeDistribution = new NodeDistribution(root);	

		return 1;
	}
	int EngineFacade::updateNodeDistribution(Node*& root, string& xfx, int & nPairs){
		xfx="";
		nPairs=0;
		vector<double> x(1), Fx(1);
		x[0] = root->lower; Fx[0] = 0;
		double parentProb = 1;
		this->nodeDistribution->readLeafs(root, xfx, nPairs, x, Fx, parentProb);	
		this->getStatisticalMeasures(x, Fx, xfx, nPairs);
		return 1;
	}
	int EngineFacade::getNodeDistributionRoot(Node*& node){
		node= this->nodeDistribution->root;	
		return 1;
	}
	int EngineFacade::updateLastParent(Node*& lastParent){
		this->nodeDistribution->lastParent = lastParent;
		return 1;
	}
	int EngineFacade::getLastParent(Node*& lastParent){
		lastParent = this->nodeDistribution->lastParent;
		return 1;
	}

}
