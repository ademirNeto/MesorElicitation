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


namespace CalibrationEngine {

	EngineFacade::EngineFacade(const int calMethod){
		if(calMethod == FIRMINO){
			calibrationInstance = new CalFirmino();
		}
		else if(calMethod == DIRECT){
			calibrationInstance = new CalDireto();
		}
		else if(calMethod == BISECTION){
			calibrationInstance = new CalBissecao();
		}
		/*calFirmino = new CalFirmino();
		calDireto = new CalDireto();
		calBissecao = new CalBissecao();*/
	}
	string EngineFacade::bb_getSubintervalBetaBernoulliParameters(){
		return calibrationInstance->bb_getSubintervalBetaBernoulliParameters();
	}
	
	/*void EngineFacade::setCalibrationMethod(CalibrationMethod calMethod ){
		if(calMethod == Firmino){
			calibrationInstance = calFirmino;
		}
		else if(calMethod == Direto){
			calibrationInstance = calDireto;
		}
		else if(calMethod == Bissecao){
			calibrationInstance = calBissecao;
		}
	}*/

	/*void EngineFacade::initializeMethod(CalibrationMethod calMethod ){
		if(calMethod == Firmino){
			delete calFirmino;
			calFirmino =  new CalFirmino();
			calibrationInstance = calFirmino;
		}
		else if(calMethod == Direto){
			delete calDireto;
			calDireto =  new CalDireto();
			calibrationInstance = calDireto;
		}
		else if(calMethod == Bissecao){
			delete calBissecao;
			calBissecao =  new CalBissecao();
			calibrationInstance = calBissecao;
		}
	}*/
	
	int EngineFacade::testMethodFacade(int a, int b){
		return a+b;
	}

	void EngineFacade::setSubIntervals(int numberIntervals, double * sizeIntervals){
		//calibrationInstance->setSubIntervals(numberIntervals, sizeIntervals);
	}
	string EngineFacade::bb_updateSubintervalBetaBernoulli(const double credibility, const int evidence, const int binIndex){
		string ret = calibrationInstance->bb_updateSubintervalBetaBernoulli(credibility, evidence, binIndex);
		return ret;
	}
	/*void EngineFacade::updateCalibrationDistribution(int decision, int correctAnswer, double credibility){
		calibrationInstance->updateCalibrationDistribution(decision,correctAnswer,credibility);
	}*/

	void EngineFacade::setNumberPointsPDF(int number){
		//this->calibrationInstance->
	}

	int  EngineFacade::getNumberPointsPDF(){
		return 1;
	}

	//vector<double*> EngineFacade::getFx(void){
	//	return this->calibrationInstance->getFx();
	//}

	double EngineFacade::getMean(){
		return 0;
	}

	double EngineFacade::getMedian(){
		return 0;
	}
}
