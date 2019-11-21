#pragma once
#ifndef DENSITY_H
#define DENSITY_H
#include<vector>
//#include"BBN_Node.h"
//#include"DBBN_Node.h"
//#include "Calculator.h"
#include "General_Auxiliar.h"
#include "FLOAT.H"
namespace Engine{
	using namespace std;
	class Density {
	protected:
		double locationEstimate, scalingEstimate, derivateIn_x, derivateIn_location, derivateIn_scaling;
		double minLn;
		double minimum;
		double maximum;
		//vector<BBN_Node*> locationParameters, scalingParameters, nominalParameters;
		//vector<Density*> densities;
		double* locationWeights;
		double* scalingWeights;
		bool isItContinuous;
		void isContinuous(bool isItContinuous);
		//Calculator calc;
	public:
		//static const double DOUBLE_MAX = 1.7976931348623158e+308;
		char DENSITY_TYPE;
		double sliceLowerBound, sliceUpperBound, sliceSize, power, sampledLowerBound, sampledUpperBound;
		//bool //isPositiveDensity;
		Density(void);
		virtual ~Density(void);
		virtual void evaluateSliceLowerBound(double& lower) = 0; 
		virtual void evaluateSliceUpperBound(double& upper) = 0; 
		virtual double getLowerBound()=0;
		virtual double getUpperBound()=0;
		virtual double getCDF(double x) = 0; 
		virtual double getDerivate_fx(double x)=0; 
		virtual double getDerivateForLocationParameter(string locationLabel)=0; 
		virtual double getDerivateForScalingParameter(double x)=0; 
		virtual double get_fx(double x)=0; 
		virtual double getMean()=0;
		virtual double getVariance()=0;
		virtual double getQuantile(double p)=0;
		virtual void setParameters(double mean, double variance)=0;
		virtual void updateSliceBounds() = 0;
		double getMaximum();
		double getMinimum();
		//vector<BBN_Node*> getLocationParameters();
		//vector<BBN_Node*> getScalingParameters();
		double getLocationWeight(const int index);
		double getScalingWeight(const int index);
		double getSliceSize();
		//int getKey (vector<BBN_Node*> nominalParameters);
		bool isContinuous();
		//void setMean();
		//void setDistribution(DBBN_Node* node, vector<BBN_Node*> locationParameters, vector<BBN_Node*> scalingParameters);	
		void setMean(double mean);
		//void setLocationParameters(vector<BBN_Node*> locationParameters);
		//void setNominalParameters(vector<BBN_Node*> nominalParameters);
		void setLocationWeights(const vector<double> locationWeights);
		//void setScalingParameters( vector<BBN_Node*> scalingParameters);
		void setScalingWeights(const vector<double> scalingWeights);
		void updateSliceSize(int n, double lowerBound, double upperBound);
		void setSupport(double lowerBound, double upperBound);
	};
}
#endif;