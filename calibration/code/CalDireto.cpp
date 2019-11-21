#include "Calibration.h"
#include "CalDireto.h"
//Memory Leak Detection Enabling    
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
//#include "BBN_Auxiliar.h"

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

//ofstream calibration_out2("calibration.txt", ios::out);

namespace CalibrationEngine{

//int CalDireto::getSubintervalIndex(const double credibility, const int binIndex){
//	return binIndex;
//}

	CalDireto::CalDireto(){
		int nSubintervals = 10;
		double grid[] = {0.0, .1, .2, .3, .4,  .5, .6, .7, .8, .9, 1.0};
		//vector<double> credibilitiesGrid(0);
		//credibilitiesGrid.insert(credibilitiesGrid.begin(), grid, grid+nSubintervals+1);
		bb_reloadSubintervals(nSubintervals, grid);
		//ggsCalibration = new Engine::GGS_Calibration(10e-6, 10);
		////Engine::GGS_Calibration* ggs_c = new Engine::GGS_Calibration(10e-6, 10);
		//
		//subint = new Subinterval[10];
		////subint = new Subinterval(5);
		////subint = (Subinterval*)calloc(nSubint, sizeof(Subinterval));
		//for(int i = 0; i < 5; i++){
		//	subint[i].alpha = 1;
		//	subint[i].alpha = 1;
		//	//subint[i]
		//}
		
	}
	
	void CalDireto::updateCalibrationDistribution(int decision, int correctAnswer, double credibility){
		
	}

	bool CalDireto::updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives){
		return ggsCalibration->updateGGS_CalibrationParameters(correctAlternative, credibilities, numberAlternatives);
	}

	CalDireto :: ~CalDireto(){
	}

}