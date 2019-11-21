#include "Density.h"
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

	void Density::setSupport(double lowerBound, double upperBound){
		this->sampledLowerBound = lowerBound;
		this->sampledUpperBound = upperBound;
	}
	Density::Density(void){
		this->isItContinuous = true;
		this->sampledLowerBound = 1e200;
		this->sampledUpperBound = -this->sampledLowerBound;
		this->minLn = -1e200;
		this->locationWeights=0;
		this->scalingWeights=0;
	}

	Density::~Density(void){
		if(this->locationWeights!=0){
			delete[] this->locationWeights;
			this->locationWeights=0;
		}
		if(this->scalingWeights!=0){
			delete[] this->scalingWeights;
			this->scalingWeights = 0;
		}
	}
	double Density::getLocationWeight(const int index){
		return this->locationWeights[index];
	}
	double Density::getMaximum(){
		return this->maximum;
	}
	double Density::getMinimum(){
		return this->minimum;
	}
	double Density::getScalingWeight(const int index){
		return this->scalingWeights[index];
	}
	//int Density::getKey (vector<BBN_Node*> nominalParameters){
	//	int index = 0;
	//	for(int i=0; i<n; i++){//the parents oredering in the CPT must be equal to the ordering in the nominalPar vector
	//		MxBBN_Node* ni = (MxBBN_Node*)this->nominalParameters [i];
	//		int evidence = ni->getSimulatedEvidence();
	//		index += evidence*nominalPeriods[i];
	//	}
	//	return index;
	//}

	//vector<BBN_Node*> Density::getLocationParameters(){
	//	return this->locationParameters;
	//}
	//vector<BBN_Node*> Density::getScalingParameters(){
	//	return this->scalingParameters;
	//}
	bool Density::isContinuous(){
		return this->isItContinuous;
	}

	void Density::isContinuous(bool isItContinuous){
		this->isItContinuous = isItContinuous;
	}

	double Density::getSliceSize(){
		return this->sliceSize;
	}

	void Density::setMean(double mean){
		this->locationEstimate = mean;
	}
	//void Density::setLocationParameters(vector<BBN_Node*> locationParameters){
	//	this->locationParameters = locationParameters;
	//	int n=this->locationParameters.size();
	//	this->locationWeights = new double[n];
	//	for(int i=0;i<n; i++)
	//		this->locationWeights[i] = 1;
	//}
	void Density::setLocationWeights(const vector<double> locationWeights){
		int n=locationWeights.size();
		for(int i=0;i<n; i++)
			this->locationWeights[i] = locationWeights[i];
	}
	//void Density::setNominalParameters(vector<BBN_Node*> nominalParameters){
	//	this->nominalParameters = nominalParameters;
	//	int n = nominalParameters.size();
	//	this->nominalPeriods = new int[n];
	//	this->nominalPeriods[n-1] = 1;
	//	for(int i=n-2;i>=0; i--){
	//		MxBBN_Node* next = (MxBBN_Node*)nominalParameters [i+1];
	//		Nominal* d = (Nominal*) next->getDensity();
	//		int nLevels = d->getLevelsCount();
	//		this->nominalPeriods[i] = this->nominalPeriods[i+1]*nLevels;
	//	}
	//}
	//void Density::setScalingParameters(vector<BBN_Node*> scalingParameters){
	//	this->scalingParameters = scalingParameters;
	//	int n=this->scalingParameters.size();
	//	this->scalingWeights = new double[n];
	//	for(int i=0;i<n; i++)
	//		this->scalingWeights[i] = 1;
	//}
	void Density::setScalingWeights(const vector<double> scalingWeights){
		int n=scalingWeights.size();
		for(int i=0;i<n; i++)
			this->scalingWeights[i] = scalingWeights[i];
	}
	void Density::updateSliceSize(int n, double lowerBound, double upperBound){
		double dif = upperBound - lowerBound;
		this->sliceSize = (this->
			sliceSize*(n-1) + dif )/n;
	}

}
