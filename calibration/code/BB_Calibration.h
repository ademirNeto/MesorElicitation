#pragma once
#ifndef BB_Calibration_H
#define BB_Calibration_H
#include "Uniform.h"
#include "Lichtenstein.h"
#include "Multinomial.h"
#include "Dirac.h"
#include "Facade.h"
#include "Density.h"
#include "NumericApproximation.h"
#include"General_Auxiliar.h"
#include"Overrelaxation.h"
#include "MxBBN_Node.h"

namespace Engine{
	using namespace std;
	class BB_Calibration{
		private:
			//int t;
			Density* dA; Density* dB;
			void updateCalibraitonPattern();
		public:
			char BB_Calibration_PATTERN;
			Facade* manager;
			BB_Calibration(const double lower, const double upper);
			bool updateBB_CalibrationParameters(const int correctAlternative, double* assignedCredibilities, const int numberOfAlternatives);
			//double* getBB_CalibrationParametersMean();
			//double* getBB_CalibrationParametersVar();
			double* getBB_CalibrationParametersQuantile(const double quantile);
			char getBB_CalibrationPattern();
			bool restartCalibrationStudy();
			void printMarginals(const int gridSize);
			~BB_Calibration();
	};
};
#endif;
