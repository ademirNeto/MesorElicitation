#pragma once
#ifndef CAL_DIRETO_H
#define CAL_DIRETO_H
#include "Calibration.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "BBN_Auxiliar.h"

namespace CalibrationEngine{

	using namespace std;
	
	class CalDireto : public virtual Calibration{

	protected:
		void updateCalibrationDistributionIntervals(int evidence, double credibility);
	public:
		CalDireto();
		//double* getQuantile(const double quantile);

		void updateCalibrationDistribution(int decision, int correctAnswer, double credibility);
		bool updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives);
		void initializeMethod(CalibrationMethod calMethod);

		~CalDireto();
	};
};
#endif;