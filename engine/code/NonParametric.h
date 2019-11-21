#pragma once

#ifndef NONPARAMETRIC_H
#define NONPARAMETRIC_H
#include<iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
//#include "BBN_Node.h"
#include "cdflib.h"
#include "Density.h"

namespace Engine{
	using namespace std;
	class NonParametric :public Density{
	typedef vector<double> vec_dbl;
	private:
		double* vec_x, * densities, *cumulativeDensities;
		int intervalsCount;
		double lowerBound, upperBound, delta, mean, variance, mode;
		vector<double> sample, x, Fx;
		void setParameters(double mean, double variance);

	public:
		bool goOn;
		bool loadDensities(const int intervalsCount);
		bool loadDensities();
		//NonParametric(MxBBN_Node* node, int intervalsCount=100);
		bool loadDensities(vector<vec_dbl> samples);
		NonParametric();
		NonParametric(vector<double> sample);
		NonParametric(const vector<double> x, const vector<double> Fx, const int maxIntervalsCount);
		NonParametric(vector<vec_dbl> samples, const double lowerBound, const double upperBound);
		~NonParametric(void);
		void evaluateSliceLowerBound(double& lower); 
		void evaluateSliceUpperBound(double& upper); 
		void evaluateVarAndMean();
		void evaluateParametersAndLeanIntervals(const vector<double> x, const vector<double> Fx, const double minimalMass);
		void exportDistribution();
		double getLowerBound();
		double getUpperBound();
		double getCDF(double x);
		double getDerivate_fx(double x);
		double getDerivateForLocationParameter(string locationLabel); 
		double getDerivateForScalingParameter(double x); 
		double get_fx(double x);
		int getIntervalsCount();
		double getMean();
		double getQuantile(double p);
		double getVariance();
		double getMode();
		double* getVec_x();
		double* getVec_xProbabilities();
		double* getVec_xCumulativeProbabilities();
		void performeAdherenceTestByChiSquare(Density* density, double &pValue, double &cValue);
		void performeAdherenceTestByKolmogorovSmirnov(Density* density, double alfa, double &cValue, double &tValue);
		void performeAdherenceTestByLilliefors(Density* density, double alfa, double &cValue, double &tValue);
		void removeOutliers();
		void updateBounds(const double lower, const double upper);
		void updateGridSize(const int count, const int n);
		void setIntervalsCount(int intervalsCount);
		void setSample(const vector<double> sample);
		void setVec_x(double * x);
		void setVec_fx(double * fx);
		void updateSliceBounds();
	};
}
#endif;
