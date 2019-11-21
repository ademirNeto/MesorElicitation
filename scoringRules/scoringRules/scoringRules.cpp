///roger cook www.tudeupht.com
#include<iostream>
#include <sstream>
#include <math.h>
#include <algorithm>
#include <vector>

#include <time.h>
//#include "BBN_Auxiliar.h"
//#include "CalBissecao.h"
//#include "CalFirmino.h"
//#include "cdflib.h"

#include <windows.h>

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
#include <fstream>
#include <iostream>
#include <map>


using namespace std;
ofstream sr_cout("scoring.txt", ios::out);
typedef  vector<double*> vec_dbl;

typedef struct Expert {
    string name;
	int nClasses;
	double* distribution;
    double* trueDistribution;
	bool* trueValue;
	double Q, OQ, L, S, DQ, DL, DS, DC, DK;
};
typedef struct Experiment {
    string name;
	int nExperts;
	vector<Expert*> experts;
};
bool computeScoringRules(Experiment& experiment){
	int nExperts = experiment.nExperts;
	for(int i=0; i<nExperts; i++){
		Expert* expert_i = experiment.experts[i];
		double* p = expert_i->distribution;
		double* g = expert_i->trueDistribution;
		bool* d = expert_i->trueValue;
		double Q = 1, OQ=1, DQ = 1, pd = 0, pg = 0, p2 = 0, DC=0, DK = 0, Pj=0, Dj=0;
		for(int j=0; j<expert_i->nClasses; j++){
			Pj += p[j]; Dj += d[j];
			OQ -= pow(Pj - Dj,2.0);
			Q -= pow(p[j] - d[j],2.0);
			pd += (p[j]*d[j]);
			p2 += (p[j]*p[j]);

			double p_g2 = pow(p[j] - g[j],2.0);
			DQ -= p_g2;
			pg += (p[j]*g[j]);
			DC -= p_g2/g[j];
			if(p[j]>0)
				DK-=g[j]*log(g[j]/p[j]);
			else
				DK-=g[j]*log(g[j]/1e-100);
		}
		double L = log(pd), DL = log(pg);
		double S = pd/sqrt(p2), DS = pg/sqrt(p2);
		expert_i->Q = Q; expert_i->OQ = OQ; expert_i->L = L; expert_i->S=S; expert_i->DQ = DQ; expert_i->DL = DL; expert_i->DS = DS; expert_i->DC = DC;expert_i->DK = DK;
	}

	return true;
}
bool loadExperts(Experiment& experiment, int* nClasses, vector<double*> expertsDistribution, vector<double*> trueDistributions, vector<bool*> trueValues){
	for(int i=0; i<experiment.nExperts; i++){
		experiment.experts[i] = new Expert();
		experiment.experts[i]->nClasses = nClasses[i];
		experiment.experts[i]->distribution = new double[experiment.experts[i]->nClasses];
		experiment.experts[i]->trueDistribution = new double[experiment.experts[i]->nClasses];
		experiment.experts[i]->trueValue= new bool [experiment.experts[i]->nClasses];
		for(int j=0; j<experiment.experts[i]->nClasses;j++){
			experiment.experts[i]->trueValue[j] = trueValues[i][j];
			experiment.experts[i]->trueDistribution[j] = trueDistributions[i][j];
			experiment.experts[i]->distribution[j] = expertsDistribution[i][j];
		}
	}
	experiment.experts[0]->name = "Expert A";
	experiment.experts[1]->name = "Expert B";
	experiment.experts[2]->name = "Expert C";
	return true;
}
bool loadMultinomialExperiment_EBEB2012(Experiment& experiment){
	experiment.name = "MULTINOMIAL";
	experiment.nExperts = 3;
	experiment.experts.resize(experiment.nExperts);// = new Expert[experiment.nExperts];
	bool trueValue[]= {0, 0, 0, 1};
	double trueDistribution[] = {0.07, 0.18, 0.6, 0.15}; 
	int nClasses[] = {4,4,4};
	vector<bool*> trueValues; trueValues.push_back(trueValue);trueValues.push_back(trueValue);trueValues.push_back(trueValue);
	vector<double*> trueDistributions; trueDistributions.push_back(trueDistribution);trueDistributions.push_back(trueDistribution);trueDistributions.push_back(trueDistribution);
	vector<double*> expertsDistribution;
	double expPr0[] = {0.5, 0.3, 0.1, 0.1}; expertsDistribution.push_back(expPr0);
	double expPr1[] = {0.1, 0.3, 0.5, 0.1};expertsDistribution.push_back(expPr1);
	double expPr2[] = {0.25, 0.25, 0.25, 0.25};expertsDistribution.push_back(expPr2);
	loadExperts(experiment,nClasses,expertsDistribution, trueDistributions, trueValues);
	return true;
}
bool loadGeometricExperiment_EBEB2012(Experiment& experiment){
	experiment.name = "GEOMETRIC";
	experiment.nExperts = 3;
	int nClasses[] = {6,6,6};
	experiment.experts.resize(experiment.nExperts);// = new Expert[experiment.nExperts];
	vector<bool *> trueValues (0);
	vector<double*> trueDistributions(0);
	vector<double*> expertsDistribution(0);



	bool d0[]= {1, 0, 0, 0, 0, 0}; trueValues.push_back(d0);
	double g0[] = {0.637956062, 0.240143432, 0.080856501, 0.027224453, 0.013061303, 0.000758249};trueDistributions.push_back(g0);
	double p0[] = {0.45, 0.25, 0.15, 0.1, 0.05, 0};expertsDistribution.push_back(p0);

	bool d1[]= {0, 0, 1, 0, 0, 0}; trueValues.push_back(d1);
	double g1[] = {0.25194799, 0.227640927, 0.268541326, 0.129969251, 0.121722895, 0.000177611};trueDistributions.push_back(g1);
	double p1[] = {0.4, 0.3, 0.2, 0.05, 0.05, 0};expertsDistribution.push_back(p1);

	bool d2[]= {1, 0, 0, 0, 0, 0}; trueValues.push_back(d2);
	double g2[] = {0.811588322, 0.155397645, 0.02722922, 0.004771182, 0.00083602, 0.000177611};trueDistributions.push_back(g2);
	double p2[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0};expertsDistribution.push_back(p2);

	loadExperts(experiment,nClasses,expertsDistribution, trueDistributions, trueValues);
	return true;
}
bool loadGaussianExperiment_EBEB2012(Experiment& experiment){
	experiment.name = "GAUSSIAN";
	experiment.nExperts = 3;
	int nClasses[] = {6,6,6};
	experiment.experts.resize(experiment.nExperts);// = new Expert[experiment.nExperts];
	vector<bool *> trueValues (0);
	vector<double*> trueDistributions(0), expertsDistribution(0);

	bool d0[]= {0, 0, 0, 1, 0, 0}; trueValues.push_back(d0);
	double g0[] = {3.8721E-06, 0.012669787, 0.487326341, 0.487326341, 0.012669787, 3.87212E-06};trueDistributions.push_back(g0);
	double p0[] = {0.01, 0.1, 0.3, 0.54, 0.05, 0};expertsDistribution.push_back(p0);

	bool d1[]= {0, 0, 1, 0, 0, 0}; trueValues.push_back(d1);
	double g1[] = {0.000394243, 0.012275544, 0.119102579, 0.368223761, 0.487326341, 0.012677531};trueDistributions.push_back(g1);
	double p1[] = {0.01, 0.05, 0.2, 0.4, 0.24, 0.1};expertsDistribution.push_back(p1);

	bool d2[]= {0, 0, 0, 1, 0, 0}; trueValues.push_back(d2);
	double g2[] = {4.55445E-05, 0.012628104, 0.275401402, 0.5801487, 0.129181935, 0.002594315};trueDistributions.push_back(g2);
	double p2[] = {0.2, 0.2, 0.2, 0.2, 0.2, 0};expertsDistribution.push_back(p2);
	loadExperts(experiment,nClasses,expertsDistribution, trueDistributions, trueValues);
	return true;
}
bool deleteExperts(Experiment& experiment){
	for (int i=0; i<experiment.experts.size(); i++){
		Expert* ei = experiment.experts[i];
		delete[] ei->distribution;
		delete[] ei->trueDistribution;
		delete[] ei->trueValue;
		delete experiment.experts[i];
	}
	return true;
}
bool printResults(Experiment& experiment){
	sr_cout<<experiment.name;
	for(int i=0; i<experiment.nExperts; i++){
		sr_cout<<"\t"<<experiment.experts[i]->name;
		sr_cout<<"\t"<<experiment.experts[i]->L;
		sr_cout<<"\t"<<experiment.experts[i]->S;
		sr_cout<<"\t"<<experiment.experts[i]->Q;
		sr_cout<<"\t"<<experiment.experts[i]->OQ;
		sr_cout<<"\t"<<experiment.experts[i]->DL;
		sr_cout<<"\t"<<experiment.experts[i]->DS;
		sr_cout<<"\t"<<experiment.experts[i]->DQ;
		sr_cout<<"\t"<<experiment.experts[i]->DC;
		sr_cout<<"\t"<<experiment.experts[i]->DK<<endl;
	}
	return true;
}
void main(){
//	Experiment Multinomial; //loadMultinomialExperiment_EBEB2012(Multinomial);
	Experiment Geometric; loadGeometricExperiment_EBEB2012(Geometric);
//	Experiment Gaussian; loadGaussianExperiment_EBEB2012(Gaussian);

//	computeScoringRules(Multinomial);
	computeScoringRules(Geometric);
//	computeScoringRules(Gaussian);

	sr_cout<<"Experiment \t Expert \t L \t S \t Q \t OQ \t DL \t DS \t DQ \t DC \t DK"<<endl;
//	printResults(Multinomial);
	printResults(Geometric);
//	printResults(Gaussian);
	
//	deleteExperts(Multinomial);
	deleteExperts(Geometric);
//	deleteExperts(Gaussian);


	long time = clock();

	time -= clock();
	cout<<"finished "<<(-time/CLOCKS_PER_SEC)<<endl;
	
	_CrtDumpMemoryLeaks();//Memory Leak Detection Enabling    
	int j;
	cin >> j;
}

