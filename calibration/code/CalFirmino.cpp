#include "Calibration.h"
#include "CalFirmino.h"
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

//ofstream calibration_firmino("calibration_firmino.txt", ios::out);

namespace CalibrationEngine{

	//double* CalFirmino::getQuantile(const double quantile){
	//	double* q = this->ggsCalibration->getGGS_CalibrationParametersQuantile(quantile);
	//	return q;
	//}

	CalFirmino::CalFirmino(){
		int nSubintervals = 10;
		double grid[] = {0.0, .1, .2, .3, .4,  .5, .6, .7, .8, .9, 1.0};
		//vector<double> credibilitiesGrid(0);
		//credibilitiesGrid.insert(credibilitiesGrid.begin(), grid, grid+nSubintervals+1);
		bb_reloadSubintervals(nSubintervals, grid);
		//ggsCalibration = new Engine::GGS_Calibration(10e-6, 10);
		//Engine::GGS_Calibration* ggs_c = new Engine::GGS_Calibration(10e-6, 10);
		
		//subint = new Subinterval[10];
		////subint = new Subinterval(5);
		////subint = (Subinterval*)calloc(nSubint, sizeof(Subinterval));
		//for(int i = 0; i < 5; i++){
		//	subint[i].alpha = 1;
		//	subint[i].alpha = 1;
		//	//subint[i]
		//}
	}

	//CalFirmino::CalFirmino(int nSubint){
	//	subint = (Subinterval*)calloc(nSubint, sizeof(Subinterval));
	//	int * pData;
	//	pData = (int*) calloc (nSubint,sizeof(int));
	//	/*subint[0].alpha = 1;
	//	subint[0].alpha = 1;*/
	//}

	//void CalFirmino::updateCalibrationDistribution(int numCategories, int evidence, double * p_x, double * p_fx){
	void CalFirmino::updateCalibrationDistributionIntervals(Subinterval sub, int evidence, double credibility){
		sub.alpha += evidence; //Caso seja 0 -O especialista errou, 1 -O Especialista acertou
		sub.beta += (1-evidence);
		int k = K_POINTS_PDF;

		double delta = .5/100;
		//x = new double[k+1];
		fx.assign(1,0);
		fx[0] = new double[k+1]; 
		x[0]= 0.5;
		x[k]= 1.0; fx[0][k] = 0;
		//double G = gama_ab/(gama_a * gama_b);
		for(int i=0; i<k; i++){
			fx[0][i] = pow(x[i], sub.alpha) * pow(1-x[i], sub.beta);// * G;
			x[i+1] = x[i]+delta;
		}
		//for(int i=0; i<=k; i++){
			//calibration_firmino << x[i] << "\t" << fx[0][i] << endl;
		//}
		
		//ver como calcula a média, a mediana, a moda e o desvio-padrao da Beta
		//temos que fechar o artigo da EBEB (até Segunda (14/11))...
		//calibration_firmino << endl;
		
		//delete[] x; // New não foi usado para criar esse vetor
		delete[] fx[0];
	}
	
	void CalFirmino::updateCalibrationDistribution(int decision, int correctAnswer, double credibility){
		
		//const int n=6, nSubint = 5;//questions x
		//vector<questao>::iterator it;
		//it = listaQuestoes.begin();

		//double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
		//Subinterval subint [nSubInt];
			
		//FOR BETA-BERNOULLI	
		//int k = 0;
		//for(; it != listaQuestoes.end(); it++, k++){
		int j = this->getSubintervalIndex(credibility, -1);//index of the subinterval related to the credibility assigned by the expert
		int a = 1 - abs(decision - correctAnswer);//a=0 se errou, a=1 se acertou

		updateCalibrationDistributionIntervals(/*chosen subinterval*/subint[j], /*evidence*/a, true);
	}

	void CalFirmino::initializeMethod(){
		for(int i=0; i < nSubint; i++){
			subint[i].index = i;
			subint[i].min = getCredibilitiesGrid()[i];	
			subint[i].max = getCredibilitiesGrid()[i+1];
			subint[i].alpha = 1;
			subint[i].beta = 1; 
			subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
		}
	}

	bool CalFirmino::updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives){
		return ggsCalibration->updateGGS_CalibrationParameters(correctAlternative, credibilities, numberAlternatives);
	}

	/*void CalFirmino::test(){
		ggsCalibration->test();
	}*/

	CalFirmino :: ~CalFirmino(){
		delete subint;
	}
}