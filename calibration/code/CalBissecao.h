#pragma once
#ifndef CAL_BISSECAO_H
#define CAL_BISSECAO_H
#include "Calibration.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include "BBN_Auxiliar.h"
#include "../../griddyGibbsSampling/engine/BBN_Auxiliar.h"

namespace CalibrationEngine{

	using namespace std;

	class CalBissecao : virtual public Calibration{

		public:
			//double* getQuantile(const double quantile);
			CalBissecao();
		
			void updateCalibrationDistribution(int decision, int correctAnswer, double credibility);
			bool updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives);
			void initializeMethod(CalibrationMethod calMethod);

			~CalBissecao();

		protected:
			void CalBissecao::updateCalibrationDistributionIntervals(Subinterval sub,int evidence, double credibility);
			int			getSubintervalIndex(const double credibility, const int binIndex);
	};
};

#endif
