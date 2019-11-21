#pragma once
#ifdef NATIVE_EXPORTS
#define NATIVE_API_export __declspec(dllexport)
#else
#define NATIVE_API_import  __declspec(dllimport)
#endif

#ifndef ENGINEFACADE_H
#define ENGINEFACADE_H
//#include "method.h"
#include<iostream>
#include<string>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "Calibration.h"
#include "CalFirmino.h"
#include "CalDireto.h"
#include "CalBissecao.h"
#include "Miscelanices.h"
//#include "Node.h"
//#include "Firmino.h"
//#include "NonParametric.h"

namespace CalibrationEngine{

	using namespace std;
	
	class /*NATIVE_API_export*/ EngineFacade{
		
	private:
		//CalBissecao* calBissecao;
		//CalFirmino* calFirmino;
		//CalDireto* calDireto;	

	public:
		Calibration* calibrationInstance;
		const static int TEST = 1;
		//void	setCalibrationMethod(CalibrationMethod calMethod);
		//void	initializeMethod(CalibrationMethod calMethod);
		//int		MainCalibration();
		string bb_getSubintervalBetaBernoulliParameters();
		void	setSubIntervals(int numberIntervals, double * sizeIntervals);
		void	updateCalibrationDistribution(int decision, int correctAnswer, double credibility);
		string bb_updateSubintervalBetaBernoulli(const double credibility, const int evidence, const int binIndex);
		//bool	updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives);
		int		testMethodFacade(int a, int b);//Metodo para testar
		int		getNumberPointsPDF(void);
		void	setNumberPointsPDF(int number);
		vector<double*> getFx(void);
		double	getMean();
		double	getMedian();
		EngineFacade(const int calMethod);
		~EngineFacade();
	};
};
#endif
