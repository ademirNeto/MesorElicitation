//Memory Leak Detection Enabling
#include "Calibration.h"
#include <stdlib.h>
#include <crtdbg.h>
//#include "BBN_Auxiliar.h"

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace CalibrationEngine{
	vector<Subinterval *> Calibration::getSubIntervals(){
		return this->subintervals;
	}

	double* Calibration::getQuantile(const double quantile){
		double* q = this->ggsCalibration->getGGS_CalibrationParametersQuantile(quantile);
		return q;
	}

	char Calibration::getGGS_CalibrationPattern(){

		return this->ggsCalibration->GGS_Calibration_PATTERN;
	}
	int Calibration::getCalibrationPattern(){
		return this->calibrationPattern;
		//return this->ggsCalibration->GGS_Calibration_PATTERN;
	}

	Calibration :: Calibration(){
		//Setting Default size sub intervals
		//double sizeIntervals[] = {.1,.2,.3,.4,.5,.6,.7,.8,.9, 1};
		//this->setSubIntervals(10, sizeIntervals);
		//
		//this->NumberPoints = 1000;
		this->calibrationPattern = Calibration::CALIBRATED;
		this->credibilitiesGrid=NULL;
	}

int Calibration::getSubintervalIndex(const double credibility, const int binIndex){
	int nSubintervals =gridSize-1;
	int i = 0;
	while(credibility >= this->credibilitiesGrid[i+1] && i<(nSubintervals-1))
		i++;
	return i;
}

void Calibration::bb_reloadSubintervals(int nSubintervals, double* grid){
	this->calibrationPattern = Calibration::CALIBRATED;
	int actual_n = this->gridSize-1;
	this->miscalibratedSubintervals.clear();
	for(int i=0; i<actual_n; i++){
		delete this->subintervals[i];
	}
	this->gridSize = nSubintervals+1;
	if(this->credibilitiesGrid != grid){
		if(this->credibilitiesGrid!=NULL)
			delete[] this->credibilitiesGrid;
		this->credibilitiesGrid = new double[nSubintervals+1];
		for(int i=0; i<=nSubintervals; i++){
			this->credibilitiesGrid[i] = grid[i];
		}
	}
	this->subintervals.clear();
	this->subintervals.resize(nSubintervals);
	//credibilitiesGrid.insert(credibilitiesGrid.begin(), grid, grid+nSubintervals+1);
	for(int i=0; i<nSubintervals; i++){
		subintervals[i] = new Subinterval();
		subintervals[i]->isUnderconfident = false;
		subintervals[i]->isOverconfident = false;
		subintervals[i]->index = i;
		subintervals[i]->min = grid[i];
		subintervals[i]->max = grid[i+1];
		subintervals[i]->alpha = 1;
		subintervals[i]->beta = 1; 
		subintervals[i]->spMean = (subintervals[i]->min + subintervals[i]->max)/2.0;
		subintervals[i]->lowerQuantile  = 0;
		subintervals[i]->upperQuantile = 1;
	}
	if(nSubintervals > 4){
		//if(subintervals[i]->min == .9 || subintervals[i]->max == .1)
		//for(int i=0; i<nSubintervals; i++)
		//	subintervals[i]->sp.push_back(subintervals[i]->spMean);
		int middle = (int)nSubintervals/2;
		for(int i=0; i<middle; i++)
			subintervals[i]->sp.push_back(subintervals[i]->max);
		for(int i=middle; i<nSubintervals; i++)
			subintervals[i]->sp.push_back(subintervals[i]->min);
		//subintervals[0]->sp[0] = .09;
		//subintervals[nSubintervals-1]->sp[0] = .91;
	} else{//for bissection method
		int i=0; subintervals[i]->sp.push_back(.05); subintervals[i]->spMean = .05;
		i++; subintervals[i]->sp.push_back(.5); subintervals[i]->spMean = .5;
		i++; subintervals[i]->sp.push_back(.5); subintervals[i]->spMean = .5;
		i++; subintervals[i]->sp.push_back(.05); subintervals[i]->spMean = .05;
	}
}
string Calibration::bb_getCalibrationPattern(Subinterval* subint, const int evidence/*, const int questionIndex*/){
	string pattern = "CALIBRATED";
	double error = (subint->spMean - subint->lowerQuantile);///(subint->upperQuantile- subint->lowerQuantile);
	if(error<0){
		subint->isUnderconfident= true;
		pattern = "UNDERCONFIDENT";
	}
	else{
		error = (subint->upperQuantile - subint->spMean);///(subint->upperQuantile- subint->lowerQuantile);
		if(error<0){
			subint->isOverconfident = true;
			pattern = "OVERCONFIDENT";
		}
	}
	if(pattern != "CALIBRATED"){
		int i=0, nMisc=this->miscalibratedSubintervals.size();
		for(i=0; i<nMisc; i++){
			int index_i = this->miscalibratedSubintervals[i]->index;
			if(subint->index < index_i)
				break;
		}
		this->miscalibratedSubintervals.insert(this->miscalibratedSubintervals.begin()+i, subint);
		this->calibrationPattern = Calibration::MISCALIBRATED;
		//calibration_cout<<"\t"<<questionIndex<<"\t"<<subint->index<<"\t"<<sp<<"\t"<<evidence<<"\t"<<isUnderconfident<<"\t"<<isOverconfident<<endl;
		//if(questionIndex < best->questionId[best->questionId.size()-1])
			//best = subint;
	}
	std::ostringstream oss_min, oss_max, oss_alpha, oss_beta;
	oss_min << subint->min; oss_max << subint->max; oss_alpha << subint->alpha; oss_beta << subint->beta;
	string ret = "["; ret+=oss_min.str(); ret+=", "; ret+= oss_max.str(); 
	if(subint->max==this->credibilitiesGrid[this->gridSize-1])
		ret+= "]";
	else
		ret+= ")";
	ret+=";"; ret+=pattern; ret+="; "; ret+=oss_alpha.str(); ret+="; "; ret+=oss_beta.str(); ret+="|";

	return ret;
	//return "[min, max); pattern; alpha; beta;"
}
int Calibration::bb_getCalibrationPattern(){
	//string pattern = "CALIBRATED";
	int nMisc = this->miscalibratedSubintervals.size();
	if(nMisc > 0){
		int i=0;
		Subinterval* subint_i = this->miscalibratedSubintervals[i];
		if(subint_i->isUnderconfident)
			this->calibrationPattern = Calibration::UNDERPREDICTING;
		else if (subint_i->isOverconfident)
			this->calibrationPattern = Calibration::OVERPREDICTING;
		for(i=1; i<nMisc; i++){
			Subinterval* subint_i = this->miscalibratedSubintervals[i];
			if(this->calibrationPattern == Calibration::UNDERPREDICTING && subint_i->isOverconfident){
				this->calibrationPattern = Calibration::OVEREXTREMING;break;
			}
			else if(this->calibrationPattern == Calibration::OVERPREDICTING && subint_i->isUnderconfident){
				this->calibrationPattern = Calibration::UNDEREXTREMING;break;
			}
		}
	}
	return this->calibrationPattern;
}
string Calibration::bb_updateSubintervalBetaBernoulli(const double credibility, const int evidence, const int binIndex/*, int questionIndex*/){
	int subint_index = this->getSubintervalIndex(credibility, binIndex);
	Subinterval* subint = this->subintervals[subint_index];
	subint->sp.push_back(credibility);
	int n = subint->sp.size();
	string patternInfo = "";

	subint->alpha += evidence;
	subint->beta += (1-evidence);
	subint->spMean = ((n-1)*subint->spMean + credibility)/n;
	subint->questionId.push_back(/*questionIndex*/-1);
	subint->evidence.push_back(evidence);

//	if(subint->sp.size() > 4){
		double Q[] = {.01,.5,.99};//quantiles 2.5%, 50%, 97.5%
		int which = 2, status=0;
		double trash=0, bound=0,
		q=1-Q[0]; cdfbet(&which, &Q[0], &q, &subint->lowerQuantile,  &trash, &subint->alpha, &subint->beta, &status, &bound);
		q=1-Q[1]; cdfbet(&which, &Q[1], &q, &subint->quantile_50,   &trash, &subint->alpha, &subint->beta, &status, &bound);
		q=1-Q[2]; cdfbet(&which, &Q[2], &q, &subint->upperQuantile, &trash, &subint->alpha, &subint->beta, &status, &bound);
		double Ex = subint->alpha/(subint->alpha +subint->beta);
		//double Vx = subint->alpha*subint->beta/(pow(subint->alpha +subint->beta, 2.0)*(subint->alpha +subint->beta+1));
		//if(subint->alpha > 1 && subint->beta > 1)
			//double Mode = (subint->alpha-1)/(subint->alpha +subint->beta- 2.0);
		subint->postMean= Ex;
		patternInfo = bb_getCalibrationPattern(subint, evidence/*, questionIndex*/);
	//}
	return patternInfo;
}
/**/
string Calibration::bb_getSubintervalBetaBernoulliParameters(){
	int nSubintervals = this->subintervals.size();
	string ret = "";
	for(int i=0; i<nSubintervals; i++){
		std::ostringstream oss_alpha, oss_beta;
		Subinterval* subint = this->subintervals[i];
		oss_alpha << subint->alpha; oss_beta << subint->beta;
		ret+=oss_alpha.str(); ret+="; "; ret+=oss_beta.str(); ret+="; ";
	}
	return ret;//it is returned the pairs (alpha[i], beta[i]), separeted by semmi-colons
}



	void Calibration::updateCalibrationDistributionIntervals(int evidence, double credibility){
		
	}

	void Calibration::updateCalibrationDistribution(int decision, int correctAnswer, double credibility){
		
	}

	bool Calibration::updateCalibrationCurveDistribution(int correctAlternative, double * credibilities, int numberAlternatives){
		ggsCalibration->updateGGS_CalibrationParameters(correctAlternative, credibilities, numberAlternatives);
		return true;
		
	}
	bool Calibration::restartCalibrationStudy(){
		//ggsCalibration->restartCalibrationStudy();
		this->bb_reloadSubintervals(this->gridSize-1, this->credibilitiesGrid);
		return true;
	}


	/*vector<double*> Calibration::getFx(void){
		return this->fx;
	}*/

	double Calibration::getMean(){
		return 0;
	}

	double Calibration::getMedian(){
		return 0;
	}

	void Calibration::setNumberPointsPDF(int number){
		this->NumberPoints = number;
	}

	int  Calibration::getNumberPointsPDF(){
		return this->NumberPoints;
	}

	double* Calibration::getCredibilitiesGrid(){
		return this->credibilitiesGrid;
	}
	double* Calibration::getCalibrationCurveLowerQuantiles(){
		int nPoints = this->subintervals.size();
		double* q = new double[nPoints];
		for(int i=0; i<nPoints; i++){
			Subinterval* subint_i = this->subintervals[i];
			q[i] = subint_i->lowerQuantile;
		}
		return q;
	}
	double* Calibration::getCalibrationCurveUpperQuantiles(){
		int nPoints = this->subintervals.size();
		double* q = new double[nPoints];
		for(int i=0; i<nPoints; i++){
			Subinterval* subint_i = this->subintervals[i];
			q[i] = subint_i->upperQuantile;
		}
		return q;
	}
	double* Calibration::getMeanCredibilitiesPerGrid(){
		int nPoints = this->subintervals.size();
		double* q = new double[nPoints];
		for(int i=0; i<nPoints; i++){
			Subinterval* subint_i = this->subintervals[i];
			q[i] = subint_i->spMean;
		}
		return q;
	}
	int Calibration::getGridSize(){
		return this->gridSize;
	}

	void test(){

	}

	Calibration :: ~Calibration(){
		if(this->credibilitiesGrid != NULL){
			delete this->credibilitiesGrid;
			this->credibilitiesGrid = NULL;
		}
		for(int i=0; i<this->subintervals.size(); i++){
			delete this->subintervals[i];
		}
		this->subintervals.clear();
	}
}