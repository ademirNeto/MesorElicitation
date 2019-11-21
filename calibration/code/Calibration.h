#pragma once
#ifndef CALIBRATION_H
#define CALIBRATION_H
#include <math.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include "FLOAT.H"
#include "cdflib.h"
#include "../../griddyGibbsSampling/engine/BBN_Auxiliar.h"
//#include "../../griddyGibbsSampling/engine/General_Auxiliar.h"
#include "Miscelanices.h"
#include "../../griddyGibbsSampling/engine/GGS_Calibration.h"
using namespace std;
//using namespace System;

namespace CalibrationEngine{

	class Calibration
	{
	private:
		int NumberPoints, calibrationPattern, gridSize;
		double* credibilitiesGrid;
		vector<Subinterval*> subintervals, miscalibratedSubintervals;
		double* vec_x;

	protected:
		void updateCalibrationDistributionIntervals(int evidence, double credibility);
		Engine::GGS_Calibration * ggsCalibration;
		
	public:
		//void test();
		const static int	
			CALIBRATED = 1
			, UNDEREXTREMING = 2
			, OVEREXTREMING = 3
			, UNDERPREDICTING= 4
			, OVERPREDICTING = 5
			, UNDERCONFIDENT= 6
			, OVERCONFIDENT = 7
			, MISCALIBRATED = 8;
		const static int K_POINTS_PDF = 100;
		//Gets
		string bb_getCalibrationPattern(Subinterval* subint, const int evidence/*, const int questionIndex*/);
		int bb_getCalibrationPattern();
		void bb_reloadSubintervals(int nSubintervals, double* grid);
		string bb_updateSubintervalBetaBernoulli(const double credibility, const int evidence, const int binIndex/*, int questionIndex*/);
		string bb_getSubintervalBetaBernoulliParameters();
		//void bb_updateCalibration

		vector<Subinterval *> getSubIntervals();
		double* getQuantile(const double quantile);
		double		getMean(void);
		double		getMedian(void);
		double		getVariance(void);
		double		getStandardDesviation(void);
		double		getModa(void);
		//vector<double*>	getFx(void);
		//double *	getX(void);
		int			getNumberPointsPDF(void);
		void		setNumberPointsPDF(int number);
		virtual int			getSubintervalIndex(const double credibility, const int binIndex);
		double*		getVec_x();
		//Sets
		//void	setConfigIntervals(void);

		//virtual void updateCalibrationDistribution(int numCategories, int evidence, double credibility);
		virtual void updateCalibrationDistribution(int decision, int correctAnswer, double credibility);
		/*virtual*/ bool updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives);
		/*virtual*/ char getGGS_CalibrationPattern();
		int getCalibrationPattern();
		//virtual void initializeMethod(CalibrationMethod calMethod);
		bool restartCalibrationStudy();

		void		setVec_x();
		//void	
		double* getCredibilitiesGrid();
		double* getMeanCredibilitiesPerGrid();
		double* getCalibrationCurveLowerQuantiles();
		double* getCalibrationCurveUpperQuantiles();
		int getGridSize();

		Calibration();
		~Calibration(void);
	
	protected:
		int nSubint;
		vector<double*> fx; //Vetor eixo y
		double x[K_POINTS_PDF+1];//Vetor eixo X
		Subinterval* subint;
	private:
		
	};
};
#endif;