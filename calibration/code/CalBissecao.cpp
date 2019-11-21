#include "Calibration.h"
#include "CalBissecao.h"
//Memory Leak Detection Enabling
#include <stdlib.h>
#include <crtdbg.h>
#include <vector>
//#include "BBN_Auxiliar.h"
#include "../../griddyGibbsSampling/engine/BBN_Auxiliar.h"

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;


ofstream calibration_out("calibration.txt", ios::out);

namespace CalibrationEngine{
	CalBissecao::CalBissecao(){
		int nSubintervals = 4;
		//the grid[] represent in this order the true 0%, the experts' 0%, 50%, 100%, and true 100% quantiles. 
		//It is because the true value must be outside the [min, max] bounds setted by the expert
		double grid[] = {0.0, 0.0, .5, 1.0, 1.0};
		//vector<double> credibilitiesGrid(0);
		//credibilitiesGrid.insert(credibilitiesGrid.begin(), grid, grid+nSubintervals+1);
		bb_reloadSubintervals(nSubintervals, grid);
		//ggsCalibration = new Engine::GGS_Calibration(10e-6, 10);
		//Engine::GGS_Calibration* ggs_c = new Engine::GGS_Calibration(10e-6, 10);
		
		//subint = new Subinterval[1];
		//subint[0]._alpha.push_back( v_int(4,1) );
	}


	//int Calibration::getSubintervalIndex(double credibility){

	//	int indexResult = 0;
	//	int i, numIntervalos;
	//	vector<double>::iterator it;
	//	numIntervalos = CredibilitysGrid.size();
	//	//		for(
	//	//.begin();
	//	//printf("%d" , i);
	//	//for(i = 0; i < 

	//	return indexResult;
	//}

int CalBissecao::getSubintervalIndex(const double credibility, const int binIndex){
	return binIndex;
}

	void CalBissecao::updateCalibrationDistributionIntervals(Subinterval sub,int evidence, double credibility){
		double gama_x;
		int i, j;
		int sum_x = 0;
		int nQuantiles = 4; //Neste método de edução, serão usados 4 quantiles.

		vector<v_int>::iterator lastUpdate;

		lastUpdate = sub._alpha.end()-1; //Obtem o útimo elemento do vetor alpha

		v_int updatedParameters;

		updatedParameters = lastUpdate[0];
		//Lança exceção caso evidence não esteja entre 0 e 4;
		if(evidence > -1 && evidence < 4)
			updatedParameters[evidence] += 1;
		//getFx();

		sub._alpha.push_back(updatedParameters);

		for(j = 0; j < nQuantiles; j++){
			sum_x += updatedParameters[j];
		}

		//BBN_Auxiliar::setGammaFunction(gama_x, sum_x);


		int k=getNumberPointsPDF();
		double delta = .01;
		double* x = new double[k+1];
		vector<double*> fx(nQuantiles);

		for( i = 0; i< nQuantiles; i++){
			fx[i] =  new double[k+1];
		}

		x[0]=0.0;
		x[k]=1.0; fx[0][k] = 0;
		fx[1][k] = 0; fx[2][k] = 0; fx[3][k] = 0;


		for(int j=0; j<nQuantiles; j++){
			int betaParameter = sum_x - updatedParameters[j];
			x[0]=0.0;
			for(int i=0; i<k; i++){
				fx[j][i] = pow(x[i], updatedParameters[j]-1) * pow(1-x[i], betaParameter -1) * gama_x;
				x[i+1] = x[i]+delta;
			}
		}

		for(int i=0; i<k; i++){
			//calibration_out << x[i] << "\t" << fx[0][i] << "\t" << fx[1][i] << "\t" << fx[2][i] << "\t" << fx[3][i] << endl;
		}
		calibration_out << endl;
		delete[] x;

		for( i = 0; i< nQuantiles; i++){
			delete[] fx[i];
		}
	}
	void CalBissecao::updateCalibrationDistribution(int decision, int correctAnswer, double credibility){
			
		int j = this->getSubintervalIndex(credibility, -1);//index of the subinterval related to the credibility assigned by the expert
		int a = 1 - abs(decision - correctAnswer);//a=0 se errou, a=1 se acertou
		
		updateCalibrationDistributionIntervals(/*chosen subinterval*/subint[j], /*evidence*/a,credibility);

	}

	bool CalBissecao::updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives){
		return ggsCalibration->updateGGS_CalibrationParameters(correctAlternative, credibilities, numberAlternatives);
	}

	CalBissecao :: ~CalBissecao(){}

}