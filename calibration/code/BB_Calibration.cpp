#include "BB_Calibration.h"
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
namespace Engine{
	BB_Calibration::BB_Calibration(const double lower, const double upper){
		this->BB_Calibration_PATTERN = General_Auxiliar::CALIBRATED;
		this->dA = new Uniform(lower, upper); 	
		//this->dA = new Dirac(1.0); 	
		this->dB = new Uniform(lower, upper);
		this->manager = new Facade();
	}

	bool BB_Calibration::updateBB_CalibrationParameters(const int correctAlternative, double* assignedCredibilities, const int numberOfAlternatives){
		int evidence = correctAlternative;
		//AVOIDING DIVISION PER ZERO
		for(int i=0; i<numberOfAlternatives; i++){
			if(assignedCredibilities[i]==1.0)
				assignedCredibilities[i] = 1-BBN_Auxiliar::ZERO_PROB;
			else if (assignedCredibilities[i]==0.0)
				assignedCredibilities[i] = BBN_Auxiliar::ZERO_PROB;
		}

		MxBBN_Node* A = new MxBBN_Node();	MxBBN_Node* B = new MxBBN_Node(); MxBBN_Node* P_ev = new MxBBN_Node();	
		A->setDensity(this->dA);
		B->setDensity(this->dB);
		Lichtenstein* dP_ev = new Lichtenstein(A, B);
		P_ev->setDensity(dP_ev);

		A->isToPrint = true; B->isToPrint = true;
		string stP = "P", /*stE = "E", */stA = "A", stB = "B"; 
		/*E->setLabel(stE); */A->setLabel(stA); B->setLabel(stB);
		P_ev->addParent(A);	P_ev->addParent(B);	

		char ch[10];
		_itoa(evidence,  ch, 10); 
		string stP_ev = stP;  stP_ev += "_"; stP_ev += ch;
		P_ev->setLabel(stP_ev); 
		double likelihood = assignedCredibilities[evidence];
		P_ev->setEmpiricalEvidence(likelihood);
		//E->addParent(P_ev);
		//}else{//IF THE EVIDENCE IS ON THE LAST BIN (FOR WHICH THE EXPERT HAS NOT ASSIGNED A PROBABILITY)
		//	st_gt = "1";
		//vector<MxBBN_Node*> P(numberOfAlternatives);
		//string st_normalizingConstant="(0";
		//string* st_gt = new string[numberOfAlternatives];
		//for(int i=0; i<numberOfAlternatives; i++){
		//	P[i] = new MxBBN_Node();
		//	_itoa(i,  ch, 10);
		//	string stP_i = stP;  stP_i += "_"; stP_i += ch;
		//	P[i]->setLabel(stP_i); 
		//	string aux = "pow((1-"; aux+= stP_i; aux+=")/";aux+= stP_i; aux+=(", "+stB+")/"+stA);
		//	//string aux = stA; aux+= "*pow("; aux+=stP_i; aux+="/(1-"; aux+=stP_i; aux+="),";aux+=stB; aux+=")";
		//	st_gt[i]=""; st_gt[i] += aux; st_gt[i]+="/(";st_gt[i]+="1+";st_gt[i]+=aux;st_gt[i]+=")";
		//	st_normalizingConstant+=" + "; st_normalizingConstant+=st_gt[i];
		//	lc.push_back(P[i]);
		//	double likelihood_i = assignedCredibilities[i];
		//	Dirac* dP_i = new Dirac(likelihood_i);
		//	P[i]->setDensity(dP_i);
		//	P[i]->setEmpiricalEvidence(likelihood_i);
		//	E->addParent(P[i]);
		//}
		//}
		//st_normalizingConstant +=")";
		//st_gt[evidence] +="/"; st_gt[evidence] +=st_normalizingConstant; st_gt[evidence] +=";";
		//SUMULATION RUNNING
		A->loadForest();
		int MC_size = 1000;//to be changed to 2000
		Overrelaxation ov(MC_size, 1, 0, 1e-3);
		double time=clock();
		ov.samplingByOrderedOverrelaxation(0, 1000);
		time-=clock();
		cout<<". > total time for sampling( "<<MC_size<<") "<<(-time/CLOCKS_PER_SEC)<<" sec."<<endl;
		this->dA = A->getMarginal();	
		this->dB = B->getMarginal();
		this->updateCalibraitonPattern();

		A->setMarginal(NULL); 
		B->setMarginal(NULL);
		this->manager->clearAll();
		return true;

	}
	void BB_Calibration::updateCalibraitonPattern(){
		double alpha=1.0/100;
		if(((NumericApproximation*)this->dB)->getInverse(alpha/2) > 1){
			this->BB_Calibration_PATTERN=General_Auxiliar::UNDEREXTREMING;
		}
		else if (((NumericApproximation*)this->dB)->getInverse(1-alpha/2) < 1) {
			this->BB_Calibration_PATTERN=General_Auxiliar::OVEREXTREMING;
		}
		else if(((NumericApproximation*)this->dA)->getInverse(alpha/4) > 1){
				this->BB_Calibration_PATTERN=General_Auxiliar::UNDERPREDICTING;
		} 
		else if (((NumericApproximation*)this->dA)->getInverse(1-alpha/4) < 1) {
				this->BB_Calibration_PATTERN=General_Auxiliar::OVERPREDICTING;
		}

	}
	double* BB_Calibration::getBB_CalibrationParametersQuantile(const double quantile){
		double qA = ((NumericApproximation*)this->dA)->getInverse(quantile);
		double qB = ((NumericApproximation*)this->dB)->getInverse(quantile);
		double* quantiles = new double[2];
		BBN_Auxiliar::dbl_toDelete.push_back(quantiles);
		quantiles[0] = qA; quantiles[1] = qB; 
		return quantiles;
	}
	void BB_Calibration::printMarginals(const int gridSize){
		((NumericApproximation*)this->dA)->computeRaoBlackwellEstimate(gridSize);
		((NumericApproximation*)this->dB)->computeRaoBlackwellEstimate(gridSize);
	}
	bool BB_Calibration::restartCalibrationStudy(){
		this->BB_Calibration_PATTERN = 1;//this->General_Auxiliar::CALIBRATED=1;
		delete this->dA;
		delete this->dB;
		double lower = 1e-5, upper = 10;
		this->dA = new Uniform(lower, upper); 	this->dB = new Uniform(lower, upper);
		return true;
	}
	char BB_Calibration::getBB_CalibrationPattern(){
		return this->BB_Calibration_PATTERN;
	}
	BB_Calibration::~BB_Calibration(){
		this->manager->clearAll();
		delete this->manager;
		delete this->dA;
		delete this->dB;
	}
}
