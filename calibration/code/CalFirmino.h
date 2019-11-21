#pragma once
#ifndef CAL_FIRMINO_H
#define CAL_FIRMINO_H
#include "Calibration.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "BBN_Auxiliar.h"
//#include "../../griddyGibbsSampling/engine/BBN_Auxiliar.h"

namespace CalibrationEngine{

	using namespace std;

	class CalFirmino : public virtual Calibration{
		
	protected:
		void updateCalibrationDistributionIntervals(Subinterval sub ,int evidence, double credibility);
	public:
		//double* getQuantile(const double quantile);
		CalFirmino();
		//CalFirmino(int nSubint);
		void updateCalibrationDistribution(int decision, int correctAnswer, double credibility);
		bool updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives);
		void initializeMethod();
		~CalFirmino();	
	};
};

#endif