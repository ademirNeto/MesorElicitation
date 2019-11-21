///roger cook www.tudeupht.com
//#include <boost/math/distributions.hpp>
//using namespace boost::math;
#include "cdflib.h"
#include <string>
#include<iostream>
#include <sstream>
#include <math.h>
#include <algorithm>

#include <time.h>
#include "../../griddyGibbsSampling/engine/BBN_Auxiliar.h"
#include "CalBissecao.h"
#include "CalFirmino.h"
#include "CalibrationInterface.cpp"
#include "cdflib.h"
#include <fstream>
#include <iostream>
#include <map>

#include <windows.h>
using namespace std;
using namespace CalibrationEngine;

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
#include <vector>
#include <string>
#include <sstream>
#include<cstdlib>

const int K_PONTOS = 10000;
const double TOLERANCE = 0;
const int MAX_THREADS = 3;

int nVariable = -1;
map<int,vector<string>> bufferWrite;
stringstream buffer(stringstream::out);
LPCRITICAL_SECTION c_section;
//mutable CRITICAL_SECTION c_s;
//int c_s;
ofstream EBEB_bayesPerformance_out("EBEB_BayesianPerformance.txt", ios::out/*| ios::app*/);

typedef struct MyData {
    int nQuestions;
    int nExperts;
	int curva;
} MYDATA, *PMYDATA;


ofstream calibration_cout("calibration.txt", ios::out);

ofstream best_conjugation("best_conjugation.txt", ios::out);
ofstream best_conjugation_c("best_conjugation_c.txt", ios::out);
//ofstream best_conjugation_u("best_conjugation_u.txt", ios::out);
//ofstream best_conjugation_o("best_conjugation_o.txt", ios::out);

ofstream calibrated_state_table("calibrated_state_table.txt", ios::out);
ofstream loglinear_curve_table("loglinear_curve_table.txt", ios::out);
ofstream underconfident_state_table("underconfident_state_table.txt", ios::out);
ofstream overconfident_state_table("overconfident_state_table.txt", ios::out);
ofstream cal_firm_unif_bern_pdf("cal_firm_unif_bern_pdf.txt", ios::out);
ofstream cal_firm_beta_bern_pdf("cal_firm_beta_bern_pdf.txt", ios::out);
ofstream cal_firm_triangular_bern_pdf("cal_firm_triangular_bern_pdf.txt", ios::out);


struct questao{
	int index;
	int decision;
	int correctAnswer;
	double credibility;
};


void writeToFile(string text){
	//InitializeCriticalSection(c_section);
	//EnterCriticalSection(c_section);

	int id_thread = GetCurrentThreadId();
	bufferWrite[id_thread].push_back(text);
	
	//LeaveCriticalSection(c_section);
	//DeleteCriticalSection(c_section);
}

bool evaluateMiscalibration(Subinterval* subint, const int evidence, const int questionIndex, Subinterval* best){
	bool isToStop = false;
	double error = (subint->spMean - subint->lowerQuantile);///(subint->upperQuantile- subint->lowerQuantile);
	if(error<TOLERANCE){
		subint->isUnderconfident= true;
	}
	else{
		error = (subint->upperQuantile - subint->spMean);///(subint->upperQuantile- subint->lowerQuantile);
		if(error<TOLERANCE){
			subint->isOverconfident = true;
		}
	}
	if(subint->isUnderconfident || subint->isOverconfident){
		isToStop = true;
		//calibration_cout<<"\t"<<questionIndex<<"\t"<<subint->index<<"\t"<<sp<<"\t"<<evidence<<"\t"<<isUnderconfident<<"\t"<<isOverconfident<<endl;
		//if(questionIndex < best->questionId[best->questionId.size()-1])
			//best = subint;
	}
	
	return isToStop;
}
void computeLoglinearCalCurve(Subinterval* subint, string conjugation, int calibrationState){
	double Sx=0, Sx2=0;
	int n = 5, k=3;
	double yi[] = {0,0,0};//Sy[j=0]: Q(2.5%), Sy[j=1]: postMean , Sy[j=2]: Q(97.5%)
	double Sxy[] = {0,0,0};
	double Sy[] = {0,0,0};
	for(int i=0; i<n; i++){
		double xi = log(subint[i].spMean/(1-subint[i].spMean));
		yi[0] = log(subint[i].lowerQuantile/(1-subint[i].lowerQuantile));
		yi[1] = log(subint[i].postMean/(1-subint[i].postMean));
		yi[2] = log(subint[i].upperQuantile/(1-subint[i].upperQuantile));

		Sx += xi;
		Sx2 += (xi*xi);
		for(int j=0; j<3; j++){
			Sy[j]+=yi[j];
			Sxy[j]+=(xi*yi[j]);
		}
	}
	double* a = new double[3];
	double* b = new double[3];
	string stMeasure[] = {"Q(2.5%)", "Mean","Q(97.5%)"};
	loglinear_curve_table<<conjugation.c_str()<<"\t alpha \t beta"<< endl;
	for(int j=0; j<3; j++){
		b[j] = (n*Sxy[j] - Sx*Sy[j])/(n*Sx2 - Sx*Sx);
		a[j] = exp((Sy[j] - b[j]*Sx)/n);
		loglinear_curve_table<<stMeasure[j].c_str()<<"\t"<<a[j]<<"\t "<<b[j]<<endl;
	}
	
}
void elaborateTable(Subinterval& subint, string conjugation, const double mean, const double median, const double mode, const double Q2_5, const double Q97_5, const double var ){

	calibrated_state_table << "["<<subint.min<< "," << subint.max<< ")\t" << conjugation.c_str() << "\t" << (subint.min+subint.max)/2 << "\t" << mean << " \t" << median << " \t" << mode << " \t" << Q2_5 << " \t" << Q97_5 << " \t" << var << endl;

} 

void elaborateHeadTable(string sufix){
	calibrated_state_table << "[min, max)\t conjugation \t middle \t mean_"<< sufix.c_str() <<"\t median"<< sufix.c_str() <<"\t mode "<< sufix.c_str() <<" \t Q2_5"<< sufix.c_str() <<" \t Q97_5 "<< sufix.c_str() <<"\t var "<< sufix.c_str() << endl;
	
}

bool sortfunction(questao a, questao b){
	return a.credibility < b.credibility;
}

void Calculate(){
}

//
int getSubintervalIndex(double credibility){
	int nSubintervals =5;
	double breaks[] = {.5, .6, .7, .8, .9, 1};
	int i = 0;
	while(credibility < breaks[i+1] && i<(nSubintervals-1))
		i++;
	return i;
}
int getSubintervalIndex(double credibility, vector<double> breaks){
	int nSubintervals =breaks.size()-1;
	int i = 0;
	while(credibility >= breaks[i+1] && i<(nSubintervals-1))
		i++;
	return i;
}

//Beta-Bernoulli
//Firmino
bool showUpdatedPerformance_BetaBernoulli(Subinterval& subint, const int evidence, bool toPrint){

	subint.alpha += evidence;
	subint.beta -= (evidence-1);

	if(toPrint){
		double gama_ab;
		double gama_a;
		double gama_b;
		Engine::BBN_Auxiliar::setGammaFunction(gama_ab, subint.alpha + subint.beta); 
		Engine::BBN_Auxiliar::setGammaFunction(gama_a, subint.alpha);
		Engine::BBN_Auxiliar::setGammaFunction(gama_b, subint.beta);
		int k = K_PONTOS;
		double* x = new double[k+1];
		double* fx = new double[k+1];
		double* Fx = new double[k+1];
		x[0]=0; fx[0] = 0;Fx[0]=0.0;
		x[k]=1; fx[k] = 0;Fx[k]=1.0;
		double delta = (x[k]-x[0])/k;
		double G = gama_ab/(gama_a*gama_b);
		double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
		double mode = -1000;
		int j=0;
		for(int i=1; i<k; i++){
			x[i] = x[i-1]+delta;
			fx[i] = pow(x[i], subint.alpha-1) * pow(1-x[i], subint.beta-1)*G;
			Fx[i] = Fx[i-1]+fx[i]*delta;
			if(j<=2 && Fx[i]>=Q[j]){
				Q[j]=x[i];
				j++;
			}
			if(fx[i]>mode)
				mode= x[i];

		}
		for(int i=0; i<=k; i++){
			cal_firm_beta_bern_pdf << x[i]<<"\t"<<fx[i]<<endl;
		}
		double Ex = subint.alpha/(subint.alpha +subint.beta);
		double Vx = subint.alpha*subint.beta/(pow(subint.alpha +subint.beta, 2.0)*(subint.alpha +subint.beta+1));
		subint.lowerQuantile = Q[0];
		subint.postMean= Ex;
		subint.upperQuantile = Q[2];
		
		elaborateTable(subint, "Beta-Bernoulli", Ex, Q[1], mode, Q[0], Q[2], Vx);
		
		cal_firm_beta_bern_pdf << endl;
		//cal_firm_beta_bern_pdf <<"Var \t"<<Vx<<endl;
		//cal_firm_beta_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
		//cal_firm_beta_bern_pdf <<"Mean \t"<<Ex<<endl;
		//cal_firm_beta_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
		//cal_firm_beta_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl;

		delete[] x;
		delete[] fx; 
		delete[] Fx; 
	}

	return true;
}
long int getGamma(int x){
	long int result = 1;
	for(int i=2; i<x; i++)
		result*=i;
	return result;
}
bool showUpdatedPerformance_BetaBernoulli_2(Subinterval* subint, const int evidence, int questionIndex, Subinterval* best){
	int n=subint->sp.size();
	double sp = subint->sp[n-1];
	bool isToStop = false;

	subint->alpha += evidence;
	subint->beta -= (evidence-1);
	subint->spMean = ((n-1)*subint->spMean + sp)/n;
	subint->questionId.push_back(questionIndex);
	subint->evidence.push_back((bool)evidence);

	if(subint->sp.size() > 4){
		//double gama_ab = getGamma((int)(subint->alpha + subint->beta)); 
		//double gama_a= getGamma((int)(subint->alpha)); 
		//double gama_b= getGamma((int)(subint->beta)); 
	
		//int k = K_PONTOS;
		//double* x = new double[k+1];
		//double* fx = new double[k+1];
		//double* Fx = new double[k+1];
		//x[0]=0; fx[0] = 0;Fx[0]=0.0;
		//x[k]=1; fx[k] = 0;Fx[k]=1.0;
		//double delta = (x[k]-x[0])/k;
		//double G = gama_ab/(gama_a*gama_b);
		double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
		//double mode = -1000;
		//int j=0;
		//for(int i=1; i<k; i++){
		//	x[i] = x[i-1]+delta;
		//	fx[i] = pow(x[i], subint->alpha-1) * pow(1-x[i], subint->beta-1)*G;
		//	Fx[i] = Fx[i-1]+fx[i]*delta;
		//	if(j<=2 && Fx[i]>=Q[j]){
		//		Q[j]=x[i];
		//		j++;
		//	}
		//	if(fx[i]>mode)
		//		mode= x[i];
		//}
		int which = 2, status=0;
		double trash=0, bound=0,
		q=1-Q[0]; cdfbet(&which, &Q[0], &q, &subint->lowerQuantile,  &trash, &subint->alpha, &subint->beta, &status, &bound);
		q=1-Q[1]; cdfbet(&which, &Q[1], &q, &subint->quantile_50,   &trash, &subint->alpha, &subint->beta, &status, &bound);
		q=1-Q[2]; cdfbet(&which, &Q[2], &q, &subint->upperQuantile, &trash, &subint->alpha, &subint->beta, &status, &bound);
		double Ex = subint->alpha/(subint->alpha +subint->beta);
		double Vx = subint->alpha*subint->beta/(pow(subint->alpha +subint->beta, 2.0)*(subint->alpha +subint->beta+1));
		if(subint->alpha > 1 && subint->beta > 1)
			double Mode = (subint->alpha-1)/(subint->alpha +subint->beta- 2.0);
		subint->postMean= Ex;
		isToStop = evaluateMiscalibration(subint, evidence, questionIndex, best);
											//for(int i=0; i<=k; i++){
	//	cal_firm_beta_bern_pdf << x[i]<<"\t"<<fx[i]<<endl;
	//}
	
	//cal_firm_beta_bern_pdf << endl;
	//cal_firm_beta_bern_pdf <<"Var \t"<<Vx<<endl;
	//cal_firm_beta_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
	//cal_firm_beta_bern_pdf <<"Mean \t"<<Ex<<endl;
	//cal_firm_beta_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
	//cal_firm_beta_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl;
//		delete[] x;
//		delete[] fx; 
//		delete[] Fx; 
	}
//	else{
//		subint->isUnderconfident.push_back(false);
//		subint->isOverconfident.push_back(false);
		//subint->questionId.push_back(questionIndex);
		//subint->evidence.push_back((bool)evidence);
//	}
	return isToStop;
}

//Uniforme-Bernoulli
//Bisseção
bool showUpdatedPerformance_UniformBernoulli(Subinterval& subint, const int evidence, bool toPrint){
	subint.alpha += evidence;
	subint.beta += (1-evidence);
	if(toPrint){
		int k=5000;
		double* x = new double[k+1];
		double* fx = new double[k+1];
		double* Fx = new double[k+1];
		x[0]=0.5; fx[0] = 0;Fx[0]=0.0;
		x[k]=1; fx[k] = 0;Fx[k]=1.0;
		double delta = (x[k]-x[0])/k;
		double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
		int j=0;
		double 	Ex =0, Ex2 =0, sum=0;
		for(int i=0; i<k; i++){
			fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta);//*G;
			x[i+1] = x[i]+delta;
			sum += fx[i];
			Ex += x[i]*fx[i];
			Ex2 += x[i]*x[i]*fx[i];
		}
		sum*=delta;
		Ex *= delta/sum;
		Ex2 *= delta/sum;
		double Vx = (Ex2 - Ex*Ex);
		cal_firm_unif_bern_pdf<<x[0]<<"\t"<<fx[0]/sum<<endl;
		double mode = -1000;
		for(int i=1; i<=k; i++){
			cal_firm_unif_bern_pdf<<x[i]<<"\t"<<fx[i]/sum<<endl;
			Fx[i] = Fx[i-1]+fx[i]*delta/sum;

			if(j<=2 && Fx[i]>=Q[j]){
				Q[j]=x[i];
				j++;
			}
			if(fx[i]>mode)
				mode= x[i];
		}
		//ver como calcula a média, a mediana, a moda e o desvio-padrao da Beta
		//temos que fechar o artigo da EBEB (até Segunda (14/11))...
		subint.lowerQuantile = Q[0];
		subint.postMean= Ex;
		subint.upperQuantile = Q[2];

		elaborateTable(subint, "Uniforme-Bernoulli", Ex, Q[1], mode, Q[0], Q[2], Vx);
		
		cal_firm_unif_bern_pdf<<endl;
		/*cal_firm_unif_bern_pdf <<"Var \t"<<Vx<<endl;
		cal_firm_unif_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
		cal_firm_unif_bern_pdf <<"Mean \t"<<Ex<<endl;
		cal_firm_unif_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
		cal_firm_unif_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl;*/

		delete[] x;
		delete[] fx; 
		delete[] Fx; 
	}
	return true;
}


bool showUpdatedPerformance_UniformBernoulli_2(Subinterval& subint, const int evidence, int questionIndex, Subinterval& best){
	subint.alpha += evidence;
	subint.beta += (1-evidence);
	//if(toPrint){
	int k=5000;
	double* x = new double[k+1];
	double* fx = new double[k+1];
	double* Fx = new double[k+1];
	x[0]=0.5; fx[0] = 0;Fx[0]=0.0;
	x[k]=1; fx[k] = 0;Fx[k]=1.0;
	double delta = (x[k]-x[0])/k;
	double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
	int j=0;
	double 	Ex =0, Ex2 =0, sum=0;
	for(int i=0; i<k; i++){
		fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta);//*G;
		x[i+1] = x[i]+delta;
		sum += fx[i];
		Ex += x[i]*fx[i];
		Ex2 += x[i]*x[i]*fx[i];
	}
	sum*=delta;
	Ex *= delta/sum;
	Ex2 *= delta/sum;
	double Vx = (Ex2 - Ex*Ex);
	//cal_firm_unif_bern_pdf<<x[0]<<"\t"<<fx[0]/sum<<endl;
	double mode = -1000;
	for(int i=1; i<=k; i++){
		//cal_firm_unif_bern_pdf<<x[i]<<"\t"<<fx[i]/sum<<endl;
		Fx[i] = Fx[i-1]+fx[i]*delta/sum;

		if(j<=2 && Fx[i]>=Q[j]){
			Q[j]=x[i];
			j++;
		}
		if(fx[i]>mode)
			mode= x[i];
	}
	subint.lowerQuantile = Q[0];
	subint.postMean= Ex;
	subint.upperQuantile = Q[2];
	bool isToStop = evaluateMiscalibration(&subint, evidence, questionIndex, &best);

//		elaborateTable(subint, "Uniforme-Bernoulli", Ex, Q[1], mode, Q[0], Q[2], Vx);
	
//		cal_firm_unif_bern_pdf<<endl;
	/*cal_firm_unif_bern_pdf <<"Var \t"<<Vx<<endl;
	cal_firm_unif_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
	cal_firm_unif_bern_pdf <<"Mean \t"<<Ex<<endl;
	cal_firm_unif_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
	cal_firm_unif_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl;*/

	delete[] x;
	delete[] fx; 
	delete[] Fx; 
	return isToStop;
}


//
bool showUpdatedPerformance_DirichiletMultinomial(Subinterval& subint, int evidence){
	double gama_x;
	int sum_x = 0;
	int nQuantiles = 4;

	vector<v_int>::iterator lastUpdate;
	int i, j;
	lastUpdate = subint._alpha.end()-1;
	//subint._alpha.push_back(lastUpdate[0]);
	//updatedParameters = subint._alpha.end()-1;
	//updatedParameters[0][evidence] += 1; //updating the evidence
	v_int updatedParameters;
	updatedParameters = lastUpdate[0];
	if(evidence >= 0)
		updatedParameters[evidence] += 1;
	subint._alpha.push_back(updatedParameters);

	for(j = 0; j < nQuantiles; j++){
		sum_x += updatedParameters[j];
	}

	Engine::BBN_Auxiliar::setGammaFunction(gama_x, sum_x);

	int k=100;
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
		calibration_cout << x[i] << "\t" << fx[0][i] << "\t" << fx[1][i] << "\t" << fx[2][i] << "\t" << fx[3][i] << endl;
	}
	calibration_cout << endl;
	delete[] x;

	for( i = 0; i< nQuantiles; i++){
		delete[] fx[i];
	}

	return true;
}

//Triangular-Bernoulli
bool showUpdatedPerformance_TriangularBernoulli_2 (Subinterval& subint, const int evidence, int questionIndex, double * interval, Subinterval& best){

	subint.alpha += evidence;
	subint.beta -= (evidence - 1);
//	if(toPrint){
	int k=K_PONTOS;
	double* x = new double[k+1];
	double* fx = new double[k+1];
	double* Fx = new double[k+1];
	x[0]=0.5; fx[0] = 0;Fx[0]=0.0;
	x[k]=1; fx[k] = 0;Fx[k]=1.0;
	double delta = (x[k]-x[0])/k;
	double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
	int j=0;
	double 	Ex =0, Ex2 =0, sum=0;
	double b_Menos_a = interval[2] - interval[0];
	double m_Menos_a = interval[1] - interval[0];
	double b_Menos_m = interval[2] - interval[1];
	int i=0;
	for(; x[i] < interval[1]; i++){
		//fx[i] = 1/ProdutorioGama * (2*(x[i]-interval[0])/(b_Menos_a)*m_Menos_a) * pow(x[i], subint.beta) * pow(1-x[i], subint.alpha);
		fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta)*(x[i]-interval[0])/m_Menos_a;
		x[i+1] = x[i]+delta;
		sum += fx[i];
		Ex += x[i]*fx[i];
		Ex2 += x[i]*x[i]*fx[i];
	}

	for(;i < k ; i++){
		//fx[i] = 1/ProdutorioGama * (2*(x[i]-interval[0])/(b_Menos_a)*b_Menos_m) * pow(x[i], subint.beta) * pow(1-x[i], subint.alpha);
		fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta)*(interval[2]-x[i])/b_Menos_m;
		x[i+1] = x[i]+delta;
		sum += fx[i];
		Ex += x[i]*fx[i];
		Ex2 += x[i]*x[i]*fx[i];
	}
	sum*=delta;
	Ex *= delta/sum;
	Ex2 *= delta/sum;
	double Vx = (Ex2 - Ex*Ex);
	//cal_firm_triangular_bern_pdf<<x[0]<<"\t"<<fx[0]/sum<<endl;

	double mode = -1000;
	for(int i=1; i<=k; i++){
		//cal_firm_triangular_bern_pdf<<x[i]<<"\t"<<fx[i]/sum<<endl;
		Fx[i] = Fx[i-1]+fx[i]*delta/sum;

		if(j<=2 && Fx[i]>=Q[j]){
			Q[j]=x[i];
			j++;
		}
		if(fx[i]>mode)
			mode= x[i];
		
	}
	subint.lowerQuantile = Q[0];
	subint.upperQuantile = Q[2];
	subint.postMean= Ex;
	bool isToStop = evaluateMiscalibration(&subint, evidence, questionIndex, &best);

	//elaborateTable(subint, "Triangular-Bernoulli", Ex, Q[1], mode, Q[0], Q[2], Vx);
	//cal_firm_unif_bern_pdf<<endl;
	//cal_firm_triangular_bern_pdf << endl;
	/*cal_firm_triangular_bern_pdf <<"Var \t"<<Vx<<endl;
	cal_firm_triangular_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
	cal_firm_triangular_bern_pdf <<"Mean \t"<<Ex<<endl;
	cal_firm_triangular_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
	cal_firm_triangular_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl<<endl;*/

	delete[] x;
	delete[] fx; 
	delete[] Fx; 
	return isToStop;
}

bool showUpdatedPerformance_TriangularBernoulli (Subinterval& subint, const int evidence, bool toPrint, double * interval, double ProdutorioGama){

	subint.alpha += evidence;
	subint.beta -= (evidence - 1);
	if(toPrint){
		int k=K_PONTOS;
		double* x = new double[k+1];
		double* fx = new double[k+1];
		double* Fx = new double[k+1];
		x[0]=0.5; fx[0] = 0;Fx[0]=0.0;
		x[k]=1; fx[k] = 0;Fx[k]=1.0;
		double delta = (x[k]-x[0])/k;
		double Q[] = {.025,.5,.975};//quantiles 2.5%, 50%, 97.5%
		int j=0;
		double 	Ex =0, Ex2 =0, sum=0;
		double b_Menos_a = interval[2] - interval[0];
		double m_Menos_a = interval[1] - interval[0];
		double b_Menos_m = interval[2] - interval[1];
		int i=0;
		for(; x[i] < interval[1]; i++){
			//fx[i] = 1/ProdutorioGama * (2*(x[i]-interval[0])/(b_Menos_a)*m_Menos_a) * pow(x[i], subint.beta) * pow(1-x[i], subint.alpha);
			fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta)*(x[i]-interval[0])/m_Menos_a;
			x[i+1] = x[i]+delta;
			sum += fx[i];
			Ex += x[i]*fx[i];
			Ex2 += x[i]*x[i]*fx[i];
		}

		for(;i < k ; i++){
			//fx[i] = 1/ProdutorioGama * (2*(x[i]-interval[0])/(b_Menos_a)*b_Menos_m) * pow(x[i], subint.beta) * pow(1-x[i], subint.alpha);
			fx[i] = pow(x[i], subint.alpha) * pow(1-x[i], subint.beta)*(interval[2]-x[i])/b_Menos_m;
			x[i+1] = x[i]+delta;
			sum += fx[i];
			Ex += x[i]*fx[i];
			Ex2 += x[i]*x[i]*fx[i];
		}
		sum*=delta;
		Ex *= delta/sum;
		Ex2 *= delta/sum;
		double Vx = (Ex2 - Ex*Ex);
		cal_firm_triangular_bern_pdf<<x[0]<<"\t"<<fx[0]/sum<<endl;

		double mode = -1000;
		for(int i=1; i<=k; i++){
			cal_firm_triangular_bern_pdf<<x[i]<<"\t"<<fx[i]/sum<<endl;
			Fx[i] = Fx[i-1]+fx[i]*delta/sum;

			if(j<=2 && Fx[i]>=Q[j]){
				Q[j]=x[i];
				j++;
			}
			if(fx[i]>mode)
				mode= x[i];
			
		}
		//ver como calcula a média, a mediana, a moda e o desvio-padrao da Beta
		//temos que fechar o artigo da EBEB (até Segunda (14/11))...
		subint.lowerQuantile = Q[0];
		subint.postMean= Ex;
		subint.upperQuantile = Q[2];
		elaborateTable(subint, "Triangular-Bernoulli", Ex, Q[1], mode, Q[0], Q[2], Vx);
		//cal_firm_unif_bern_pdf<<endl;
		cal_firm_triangular_bern_pdf << endl;
		/*cal_firm_triangular_bern_pdf <<"Var \t"<<Vx<<endl;
		cal_firm_triangular_bern_pdf <<"Q(2.5%)\t"<<Q[0]<<endl;
		cal_firm_triangular_bern_pdf <<"Mean \t"<<Ex<<endl;
		cal_firm_triangular_bern_pdf <<"Q(50%)\t"<<Q[1]<<endl;
		cal_firm_triangular_bern_pdf <<"Q(97.5%)\t"<<Q[2]<<endl<<endl;*/

		delete[] x;
		delete[] fx; 
		delete[] Fx; 
	}
	return true;
}

//BY NIELSON
bool uniformeBernoulliUpdatePerformace (Subinterval& subint, const int evidence){

	double G = 2;//Priori information

	int k = 50;//O intervalo da integral da bernoli será 0.5 a 1
	double delta = .01;
	double* x = new double[k+1];
	double* fx = new double[k+1];
	x[0]=.5; fx[0] = 0;
	x[k]=1; fx[k] = 0;

	for(int i=1; i<k; i++){
		x[i] = x[i-1] + delta;
		fx[i] = pow(x[i], evidence) * pow(1-x[i], evidence-1)*G;
	}
	for(int i=0; i<=k; i++){
		cout << x[i] << "\t" << fx[i] << endl;
	}

	//ver como calcula a média, a mediana, a moda e o desvio-padrao da Beta
	//temos que fechar o artigo da EBEB (até Segunda (14/11))...
	cout<<endl;
	delete[] x;
	delete[] fx; 

	return true;
}

//Firmino
void main_betaBernoulli( vector<questao> listaQuestoes){
	const int n=6, nSubInt = 5;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	Subinterval subint [nSubInt];
	for(int i=0; i < nSubInt; i++){
		subint[i].index = i;
		subint[i].min = listaValorMaxClasse[i];
		subint[i].max = listaValorMaxClasse[i+1];
		subint[i].alpha = 1;
		subint[i].beta = 1; 
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	} 	
	//FOR BETA-BERNOULLI	
	int k = 0;
	for(; it != listaQuestoes.end(); it++, k++){
		int j = getSubintervalIndex((*it).credibility);//index of the subinterval related to the credibility assigned by the expert
		int a = 1 - abs((*it).decision - (*it).correctAnswer);//a=0 se errou, a=1 se acertou
		if((k+1) % nVariable == 0  ){
			showUpdatedPerformance_BetaBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, true);
		}
		else
			showUpdatedPerformance_BetaBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, false);
	}
	computeLoglinearCalCurve(subint, "BB", 0);
}
void main_betaBernoulli_2( vector<questao> listaQuestoes, Subinterval& best){
	const int n=6, nSubintervals = 10;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	vector<double> breaks (nSubintervals+1);//= {0, .1, .2, .3, .4, .5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	breaks[0]=0.0;
	Subinterval subint [nSubintervals];
	for(int i=0; i < nSubintervals; i++){
		breaks[i+1]=breaks[i]+.1;
		subint[i].index = i;
		subint[i].min = breaks[i];
		subint[i].max = breaks[i+1];
		subint[i].alpha = 1;
		subint[i].beta = 1; 
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	} 	
	//FOR BETA-BERNOULLI	
	int k = 0, nAlternatives = 2;
	bool isToStop = false;
	for(; it != listaQuestoes.end() && !isToStop; it++, k++){
		double aux = (*it).credibility, cred[] = {aux, 1-aux};
		int correctAlternative = (*it).correctAnswer, correctDirac[] = {1-correctAlternative, correctAlternative};
		for(int i=0; i<nAlternatives; i++){
			int j = getSubintervalIndex(cred[i], breaks);//index of the subinterval related to the credibility assigned by the expert
			subint[j].sp.push_back(cred[i]);
			//int a = 1 - abs((*it).decision - correctAlternative);//a=0 se errou, a=1 se acertou
			isToStop = showUpdatedPerformance_BetaBernoulli_2(/*chosen subinterval*/&subint[j], /*evidence*/correctDirac[i], k, &best);
		}
	}
	//computeLoglinearCalCurve(subint, "BB", 0);
}
void main_uniformBernoulli_2(vector<questao> listaQuestoes, Subinterval& best){
	const int n=10, nSubInt = 5;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	Subinterval subint [nSubInt];
	for(int i=0; i < nSubInt; i++){
		subint[i].index = i;
		subint[i].min = listaValorMaxClasse[i];
		subint[i].max = listaValorMaxClasse[i+1];
		subint[i].alpha =0;
		subint[i].beta = 0;
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	}

	//int decicions[] =		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//n decisions between two alternatives (0 and 1)
	////int correctAnswers[] =	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//n uncertainty measures
	////int correctAnswers[] =	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//n uncertainty measures
	//int correctAnswers[] =	{1, 1, 1, 1, 1, 0, 0, 0, 0, 0};//n uncertainty measures
	//double credibilities[] ={.5, .8, .6, .9, 1, .7, .6, .9, 1, .7};//n uncertainty measures (between .5 and 1)	

	//FOR UNIFORM-BERNOULLI
	int k = 0;
	bool isToStop = false;
	for(; it != listaQuestoes.end() && !isToStop; it++, k++){
		int j = getSubintervalIndex((*it).credibility);//index of the subinterval related to the credibility assigned by the expert
		subint[j].sp.push_back((*it).credibility);
		int a = 1 - abs((*it).decision - (*it).correctAnswer);//a=0 se errou, a=1 se acertou
		isToStop= showUpdatedPerformance_UniformBernoulli_2(/*chosen subinterval*/subint[j], /*evidence*/a, k, best);
	}

	//for(int i=0; i < n-1; i++){
	//	question.index = i;
	//	question.decision = decicions[i];
	//	question.correctAnswer = correctAnswers[i];
	//	question.credibility = credibilities[i];
	//	int j = getSubintervalIndex(question.credibility);//index of the subinterval related to the credibility assigned by the expert
	//	int a = 1 - abs(question.decision - question.correctAnswer);//a=0 se errou, a=1 se acertou
	//	showUpdatedPerformance_UniformBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a);
	//	listaquestoes[i] = question;
	//}
	//int k , h = 0 ; 
	/*1. elaborate the sets of credibilities
	2. compute Bayesian updates*/
	//computeLoglinearCalCurve(subint, "UB", 0);
}



void main_triangularBernoulli_2(vector<questao> listaQuestoes, Subinterval& best){
	const int n=10, nSubInt = 5;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	Subinterval subint [nSubInt];
	vector<double*> intervals (5);
	for(int i=0; i < nSubInt; i++){
		subint[i].index = i;
		subint[i].min = listaValorMaxClasse[i];
		subint[i].max = listaValorMaxClasse[i+1];
		subint[i].alpha = 0;
		subint[i].beta = 0;
		intervals[i] = new double[3];
		intervals[i][0] = 0.5;
		intervals[i][1] = (subint[i].min+subint[i].max)/2.0;
		intervals[i][2] = 1.0;
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	}

	//FOR TRIANGULAR-BERNOULLI
	int k = 0;
	bool isToStop = false;
	for(; it != listaQuestoes.end() && !isToStop; it++, k++){
		int j = getSubintervalIndex((*it).credibility);//index of the subinterval related to the credibility assigned by the expert
		subint[j].sp.push_back((*it).credibility);
		int a = 1 - abs((*it).decision - (*it).correctAnswer);//a=0 se errou, a=1 se acertou
		isToStop = showUpdatedPerformance_TriangularBernoulli_2(/*chosen subinterval*/subint[j], /*evidence*/a, k, intervals[j], best);
	}
//	computeLoglinearCalCurve(subint, "TB", 0);
	for(int i=0; i < nSubInt; i++){
		delete[] intervals[i];
	}
}



void main_uniformBernoulli(vector<questao> listaQuestoes){
	const int n=10, nSubInt = 5;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	Subinterval subint [nSubInt];
	for(int i=0; i < nSubInt; i++){
		subint[i].index = i;
		subint[i].min = listaValorMaxClasse[i];
		subint[i].max = listaValorMaxClasse[i+1];
		subint[i].alpha =0;
		subint[i].beta = 0;
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	}

	//int decicions[] =		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//n decisions between two alternatives (0 and 1)
	////int correctAnswers[] =	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1};//n uncertainty measures
	////int correctAnswers[] =	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};//n uncertainty measures
	//int correctAnswers[] =	{1, 1, 1, 1, 1, 0, 0, 0, 0, 0};//n uncertainty measures
	//double credibilities[] ={.5, .8, .6, .9, 1, .7, .6, .9, 1, .7};//n uncertainty measures (between .5 and 1)	

	//FOR UNIFORM-BERNOULLI
	int k = 0;
	for(; it != listaQuestoes.end(); it++, k++){
		int j = getSubintervalIndex((*it).credibility);//index of the subinterval related to the credibility assigned by the expert
		int a = 1 - abs((*it).decision - (*it).correctAnswer);//a=0 se errou, a=1 se acertou
		if((k+1) % nVariable == 0  ){
			showUpdatedPerformance_UniformBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, true);
		}
		else
			showUpdatedPerformance_UniformBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, false);
	}

	//for(int i=0; i < n-1; i++){
	//	question.index = i;
	//	question.decision = decicions[i];
	//	question.correctAnswer = correctAnswers[i];
	//	question.credibility = credibilities[i];
	//	int j = getSubintervalIndex(question.credibility);//index of the subinterval related to the credibility assigned by the expert
	//	int a = 1 - abs(question.decision - question.correctAnswer);//a=0 se errou, a=1 se acertou
	//	showUpdatedPerformance_UniformBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a);
	//	listaquestoes[i] = question;
	//}
	//int k , h = 0 ; 
	/*1. elaborate the sets of credibilities
	2. compute Bayesian updates*/
	computeLoglinearCalCurve(subint, "UB", 0);
}



//
void main_dirichletMultinomial(vector<questao> listaQuestoes){
	const int n=10, nSubInt = 5;//questions x
	//questao listaquestoes[n];

	Subinterval subint [nSubInt];
	double evidence[] = {0, 1, 2, 3, 3, 0, 1, 2, 3, 3};//evidenced quartile (0-quartile 1, etc)
	v_int prioriParameters(4,1);//it is considered a hipercube (uniform distribution)
	subint[0]._alpha.push_back(prioriParameters);
	
	for(int i=0; i < n; i++){
		int j = 0;//getSubintervalIndex(question.credibility);//index of the subinterval related to the credibility assigned by the expert
		//int a = 1 - abs(question.decision - question.correctAnswer);//a=0 se errou, a=1 se acertou

		showUpdatedPerformance_DirichiletMultinomial(subint[j], evidence[i]);
		//bissecao.updateCalibrationDistribution(4, evidence[i]);
		int a = 1;

		//	listaquestoes[i] = question;
	}
	//int k , h = 0 ; 
	/*1. elaborate the sets of credibilities
	2. compute Bayesian updates*/
}

//
void main_triangularBernoulli(vector<questao> listaQuestoes){
	const int n=10, nSubInt = 5;//questions x
	vector<questao>::iterator it;
	it = listaQuestoes.begin();

	double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
	Subinterval subint [nSubInt];
	vector<double*> intervals (5);
	for(int i=0; i < nSubInt; i++){
		subint[i].index = i;
		subint[i].min = listaValorMaxClasse[i];
		subint[i].max = listaValorMaxClasse[i+1];
		subint[i].alpha = 0;
		subint[i].beta = 0;
		intervals[i] = new double[3];
		intervals[i][0] = 0.5;
		intervals[i][1] = (subint[i].min+subint[i].max)/2.0;
		intervals[i][2] = 1.0;
		subint[i].spMean = (subint[i].min + subint[i].max)/2.0;
	}

	//FOR TRIANGULAR-BERNOULLI
	int k = 0;
	double produtorio = 0;
	double tmpGama = 0;
	for(; it != listaQuestoes.end(); it++, k++){
		int j = getSubintervalIndex((*it).credibility);//index of the subinterval related to the credibility assigned by the expert
		int a = 1 - abs((*it).decision - (*it).correctAnswer);//a=0 se errou, a=1 se acertou
		//double interval[] = {0.5, (subint[j].min+subint[j].max)/2, 1};
		//BBN_Auxiliar::setGammaFunction(tmpGama, (subint[j].alpha + a) + 1);
		//produtorio *= tmpGama;
		if((k+1) % nVariable == 0  ){
			showUpdatedPerformance_TriangularBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, true, intervals[j], produtorio);
			produtorio = 0;
		}
		else
			showUpdatedPerformance_TriangularBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a, false, intervals[j], produtorio);
	}
	computeLoglinearCalCurve(subint, "TB", 0);
	for(int i=0; i < nSubInt; i++){
		delete[] intervals[i];
	}
}



//
void EBEB2012(int sampleSize, CurvaCalibracao curva){
	int n, categ;
	n = nVariable = sampleSize;
	categ = 5;
	int numberMethodToTest = 3;
	vector<int*> nCorrects(3);
	if(n==10){
		int Vc[] = {5, 7, 7, 8, 10}; 
		int Vu[] = {6, 8, 9, 10, 10}; 
		int Vo[] = {7, 5, 5, 7, 9};//n=10, Calibrated, Underconf, Overconf
		nCorrects[0] = Vc; nCorrects[1] = Vu;nCorrects[2] = Vo;
	} else if(n==20){
		int Vc[] = {10, 15, 14, 18, 20};//Calibrated
		int Vu[] = {13, 15, 17, 20, 20};//Underconf
		int Vo[] = {9, 12, 14, 12, 17}; //Overconf
		nCorrects[0] = Vc; nCorrects[1] = Vu;nCorrects[2] = Vo;
	}else if(n==30){
		int Vc[] = {15, 18, 23, 24, 30};
		int Vu[] = {17, 21, 28, 30, 30};
		int Vo[] = {12, 12, 15, 21, 22};//Calibrated, Underconf, Overconf
		nCorrects[0] = Vc; nCorrects[1] = Vu;nCorrects[2] = Vo;
	}

	double credibles[] = {.55,.65,.75,.85,.95};
	vector<vector<questao>> listaquestoes;
	questao tmp;
	
	for(int k=0; k < numberMethodToTest; k++){
		listaquestoes.push_back(vector<questao>());
		for(int j=0; j < categ; j++){
			int i=0;
			for(; i < nCorrects[k][j]; i++){
				tmp.decision = 1;
				tmp.correctAnswer = 1;
				tmp.credibility = credibles[j];
				listaquestoes[k].push_back(tmp);
			}
			for(; i < n; i++){
				tmp.decision = 0;
				tmp.correctAnswer = 1;
				tmp.credibility = credibles[j];
				listaquestoes[k].push_back(tmp);
			}
		}
	}

	elaborateHeadTable("_BB");
	main_betaBernoulli(listaquestoes[(int)curva]);
	elaborateHeadTable("_UB");
	main_uniformBernoulli(listaquestoes[(int)curva]);
	elaborateHeadTable("_TB");
	main_triangularBernoulli(listaquestoes[(int)curva]);
}

void EBEB2012_2(int nQuestions, CurvaCalibracao curva, int nExperts){
	
	int n, categ;
	n = nVariable = nQuestions;
	categ = 5;
	int numberMethodToTest = 3;
	double A = -1, B = -1;
	string condition = "C";
	if(curva==Calibrated){
		A = 1.0; B = 1.0;
	}else if(curva==Underconfident){
		condition = "U";
		A = 2.0; B = 2.0;
	}else if(curva==Overconfident){
		condition = "O";
		A = 1.0; B = 0.5;
	}
	
	writeToFile("\niter \t condition \t bestConjugation \t questionIndex \t subint.index \t sp \t evidence\t isUnderconfident \t isOverconfident\n");
	best_conjugation<<endl<<"iter \t condition \t bestConjugation \t questionIndex \t subint.index \t sp \t evidence\t isUnderconfident \t isOverconfident"<<endl;
	
	for(int t=1; t<=nExperts; t++){
		double* p = new double[n];//p: assessed (and public) probability
		double* g = new double[n];//g: true (and private) probabilty
		bool* isCorrect = new bool[n];
		for(int i=0; i<n; i++){
			double u = (double)(rand())/RAND_MAX;
			p[i] = 0.5 +u*.5;
			double ratio = p[i]/(1-p[i]);
			double aux = A*pow(ratio, B);
			g[i] = aux/(1+aux);
			aux = (double)(rand())/RAND_MAX;
			if(aux<=g[i])
				isCorrect[i] = 1;
			else
				isCorrect[i] = 0;
		}
		vector<vector<questao>> listaquestoes;
		questao tmp;
		
//		for(int k=0; k < numberMethodToTest; k++){
		listaquestoes.push_back(vector<questao>());
		for(int i=0; i < n; i++){
			tmp.decision = 0;
			tmp.correctAnswer = 1-isCorrect[i];
			tmp.credibility = p[i];
			listaquestoes[0].push_back(tmp);
		}
//		}

		vector<Subinterval> best(3);
		vector<string> str_best(0);
		int l=0; 
		for (; l<3; l++){
			best[l].questionId.push_back(n+1);
			best[l].index = -1;
			best[l].sp.push_back(-1);
//			best[l].isUnderconfident.push_back(false);
//			best[l].isOverconfident.push_back(false);
		}
		vector<Subinterval> aux(0);

		//calibration_cout<<endl<<condition.c_str()<<"+BB \t questionIndex \t subint.index \t sp \t evidence\t isUnderconfident \t isOverconfident"<<endl;
		l=0; main_betaBernoulli_2(listaquestoes[0], best[l]); int min1 = best[l].questionId[best[l].questionId.size()-1];str_best.push_back("BB");
		aux.push_back(best[l]);
		int min2 = 1000;

		//calibration_cout<<endl<<condition.c_str()<<"+UB \t questionIndex \t subint.index \t sp \t evidence\t isUnderconfident \t isOverconfident"<<endl;
		//l++; main_uniformBernoulli_2(listaquestoes[0], best[l]);min2 = best[l].questionId[best[l].questionId.size()-1];//hasAlarmed
		//if(min2<min1){//hasAlarmed
		//	min1=min2; //hasAlarmed
		//	aux.clear(); //hasAlarmed 
		//	str_best.clear(); //hasAlarmed
		//	aux.push_back(best[l]); //hasAlarmed
		//	str_best.push_back("UB"); //hasAlarmed
		//}//hasAlarmed
		//else if(min2==min1){//hasAlarmed
		//	aux.push_back(best[l]); //hasAlarmed
		//	str_best.push_back("UB"); //hasAlarmed
		//}//hasAlarmed

		//calibration_cout<<endl<<condition.c_str()<<"+TB \t questionIndex \t subint.index \t sp \t evidence\t isUnderconfident \t isOverconfident"<<endl;
		l++; main_triangularBernoulli_2(listaquestoes[0], best[l]);min2 = best[l].questionId[best[l].questionId.size()-1];
		if(min2<min1){
			aux.clear(); 
			str_best.clear();
			aux.push_back(best[l]);
			str_best.push_back("TB");
		}
		else if(min2==min1){
			aux.push_back(best[l]);
			str_best.push_back("TB");
		}
		best = aux; //firstToStop
		//str_best.clear(); str_best.push_back("BB");str_best.push_back("UB");str_best.push_back("TB");//for hasAlarmed

		int m=best[0].sp.size()-1;
		if(m>0){
			for (int l=0; l<best.size(); l++){
				m = best[l].sp.size()-1;
				//stringstream s;
				//if(m>0){//for hasAlarmed
					best_conjugation<<t<<"\t"<<condition.c_str()<<"\t"<<str_best[l].c_str()<<"\t"<<best[l].questionId[m]<<"\t"<<best[l].index<<"\t"<<best[l].sp[m]<<"\t"<<best[l].evidence[m]<<"\t"<<best[l].isUnderconfident<<"\t"<<best[l].isOverconfident<<endl;
					buffer<<t<<"\t"<<condition.c_str()<<"\t"<<str_best[l].c_str()<<"\t"<<best[l].questionId[m]<<"\t"<<best[l].index<<"\t"<<best[l].sp[m]<<"\t"<<best[l].evidence[m]<<"\t"<<best[l].isUnderconfident<<"\t"<<best[l].isOverconfident<<endl;
					writeToFile(buffer.str());
					buffer.str("");
				//}
			}
		}else{
			best_conjugation<<t<<"\t"<<condition.c_str()<<"\t NO_STOP"<<endl;
			buffer <<t<<"\t"<<condition.c_str()<<"\t NO_STOP"<<endl;
			writeToFile(buffer.str());
		}
		delete[] g;
		delete[] p;
		delete[] isCorrect;
		
		//adicionado
		buffer.str("");
	}

}

//


//DWORD WINAPI MyThreadFunction( LPVOID lpParam );
DWORD WINAPI MyThreadFunction_C(LPVOID lpParameter){
	PMYDATA pData = (PMYDATA)lpParameter;
	int id_thread = GetCurrentThreadId();

	bufferWrite[id_thread] = vector<string>();

	EBEB2012_2(pData[0].nQuestions, Calibrated, pData[0].nExperts);
	return 0;
}

DWORD WINAPI MyThreadFunction_O(LPVOID lpParameter){
	PMYDATA pData = (PMYDATA)lpParameter;
	int id_thread = GetCurrentThreadId();

	bufferWrite[id_thread] = vector<string>();

	EBEB2012_2(pData[0].nQuestions, Overconfident, pData[0].nExperts);
	return 0;
}

DWORD WINAPI MyThreadFunction_U(LPVOID lpParameter)
{
	PMYDATA pData = (PMYDATA)lpParameter;
	int id_thread = GetCurrentThreadId();

	bufferWrite[id_thread] = vector<string>();

	EBEB2012_2(pData[0].nQuestions, Underconfident, pData[0].nExperts);
	return 0;
}

int main_thread( int nExperts , int  nQuestions){

	HANDLE  hThreadArray[MAX_THREADS];
	DWORD   dwThreadIdArray[MAX_THREADS];
	MYDATA pData;
	pData.nExperts = nExperts;
	pData.nQuestions = nQuestions;
	hThreadArray[0] = CreateThread(NULL,0,MyThreadFunction_C, &pData, 0, &dwThreadIdArray[0]); 
	hThreadArray[1] = CreateThread(NULL,0,MyThreadFunction_U, &pData, 0, &dwThreadIdArray[1]); 
	hThreadArray[2] = CreateThread(NULL,0,MyThreadFunction_O, &pData, 0, &dwThreadIdArray[2]); 

	WaitForMultipleObjects(MAX_THREADS, hThreadArray, TRUE, INFINITE);
	
	//WaitForSingleObject(hThreadArray[0],INFINITE);

	//int id_thread = GetCurrentThreadId();
	map<int,vector<string>>::iterator it;
	vector<string>::iterator itv;
	it = bufferWrite.begin();
	
	
	for(;it != bufferWrite.end(); it++){
		
		for(itv = bufferWrite[(*it).first].begin(); itv < bufferWrite[(*it).first].end(); itv++){
			buffer << (*itv);
		}
	}
	best_conjugation_c << buffer.str();
	best_conjugation_c.flush();
	return 0;
}

bool calibrationMonitoringFacade(const int expert, const int nQuestions, const string TRUE_CONDITION, const double A, const double B, const double* sr, vector<double> breaks, vector<Subinterval*> subintervals){
	
//	EBEB_bayesPerformance_out<<expert<<"\t"<<TRUE_CONDITION<<"\t"<<CURVE[estimatedPattern]<<"\t"<<(q+1)<<"\t"<<A<<"\t"<<q50[0]<<"\t"<<B<<"\t"<<q50[1]<<endl;
	//string CURVE[6]={"", "CALIBRATED", "UNDEREXTREMING", "OVEREXTREMING", "UNDERPREDICTING", "OVERPREDICTING"};
	double* assignedCredibilities = new double[2];
	int nAlternatives=2, q=0, k=0, diracCorrect []= {1, 0};
	string estimatedPattern = "CALIBRATED";//General_Auxiliar::CALIBRATED;
	//int q=0;
	double* q01;
	double* q50;
	double* q99;
	//int k=0;
	vector<Subinterval*> miscalibratedSubintervals(0);
	for(q=0; miscalibratedSubintervals.size()==0 && q < nQuestions; q++){
		assignedCredibilities[0]=sr[q];assignedCredibilities[1]=1-sr[q];
		for(int i=0; i<nAlternatives; i++){
			int j = getSubintervalIndex(assignedCredibilities[i], breaks);//index of the subinterval related to the credibility assigned by the expert
			subintervals[j]->sp.push_back(assignedCredibilities[i]);
			bool isMiscalibrated= showUpdatedPerformance_BetaBernoulli_2(subintervals[j], diracCorrect[i], (q+1), 0);
			if(isMiscalibrated){
				miscalibratedSubintervals.push_back(subintervals[j]);
			}
		}
		//main_betaBernoulli_2(listaquestoes[0], best[l]); 
		//if(estimatedPattern!=General_Auxiliar::CALIBRATED){
		//	q01 = ggs_c->getGGS_CalibrationParametersQuantile(0.01);
		//	q50 = ggs_c->getGGS_CalibrationParametersQuantile(0.5);
		//	q99 = ggs_c->getGGS_CalibrationParametersQuantile(0.99);
		//	ggs_c->restartCalibrationStudy();
		//}
	}
	if(miscalibratedSubintervals.size()==1){
//		int lastIndex = miscalibratedSubintervals[0]->isUnderconfident.size()-1;
		if (miscalibratedSubintervals[0]->isUnderconfident)
			estimatedPattern = "UNDERPREDICTING";
		else
			estimatedPattern = "OVERPREDICTING";
	} 
	else if (miscalibratedSubintervals.size()==2){
		//int lastIndex = miscalibratedSubintervals[0]->isUnderconfident.size()-1;
		if (miscalibratedSubintervals[0]->isUnderconfident && miscalibratedSubintervals[1]->isUnderconfident)
			estimatedPattern = "UNDERPREDICTING";
		else if(miscalibratedSubintervals[0]->isOverconfident && miscalibratedSubintervals[1]->isOverconfident)
			estimatedPattern = "OVERPREDICTING";
		else {
			Subinterval* first = miscalibratedSubintervals[0];
			Subinterval* second = miscalibratedSubintervals[1];
			if(first->min > second->min){
				first = miscalibratedSubintervals[1];
				second = miscalibratedSubintervals[0];
			}
			if(first->isOverconfident && second->isUnderconfident)
				estimatedPattern = "UNDEREXTREMING";
			else if (first->isUnderconfident && second->isOverconfident)
				estimatedPattern = "OVEREXTREMING";
		}
	}
	if(q>=nQuestions)
		q = nQuestions-1;
	q50 = new double[2];
	q50[0]=-1; q50[1]=-1;
	EBEB_bayesPerformance_out<<expert<<"\t"<<TRUE_CONDITION<<"\t"<<estimatedPattern<<"\t"<<(q+1)<<"\t"<<A<<"\t"<<q50[0]<<"\t"<<B<<"\t"<<q50[1]<<endl;
	//string var[] = {"A","B"};
	//cout<<"Pattern>> "<<estimatedPattern<<", question = "<<(q+1)<<endl;
	//ios::left;
	//cout<<"var \t q01 \t q50 \t q99"<<endl;
	//for (int i=0;i<2;i++){
	//	ios::left;
	//	cout<<var[i]<<" \t "<<q01[i]<<"\t"<<q50[i]<<"\t"<<q99[i]<<endl;
	//}
	delete[] assignedCredibilities ;
	delete[] q50 ;
	return true;
}
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
    std::string item;
    while(std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    return split(s, delim, elems);
}
void restartSubintervals(vector<Subinterval*>& subintervals, const vector<double> breaks){
	int nSubintervals = subintervals.size();
	for(int i=0; i < nSubintervals; i++){
		delete subintervals[i];
		subintervals[i] = new Subinterval();
		subintervals[i]->isUnderconfident = false;
		subintervals[i]->isOverconfident = false;
		subintervals[i]->index = i;
		subintervals[i]->min = breaks[i];
		subintervals[i]->max = breaks[i+1];
		subintervals[i]->alpha = 1;
		subintervals[i]->beta = 1; 
		subintervals[i]->spMean = (subintervals[i]->min + subintervals[i]->max)/2.0;
	} 	
}
void calibrationBayesianMonitoring(){
	const int nSubintervals = 10;//questions x
	vector<double> breaks (nSubintervals+1); 
	breaks[0]=0.0;
	vector<Subinterval*> subintervals (nSubintervals);
	for(int i=0; i < nSubintervals; i++){
		breaks[i+1]=breaks[i]+.1;
		subintervals[i] = new Subinterval();
		subintervals[i]->isUnderconfident = false;
		subintervals[i]->isOverconfident = false;
		subintervals[i]->index = i;
		subintervals[i]->min = breaks[i];
		subintervals[i]->max = breaks[i+1];
		subintervals[i]->alpha = 1;
		subintervals[i]->beta = 1; 
		subintervals[i]->spMean = (subintervals[i]->min + subintervals[i]->max)/2.0;
	} 	
	string line;
	EBEB_bayesPerformance_out<<"expert \t true_condition \t diagnostic \t question_index \t true_alpha \t estimated_alpha \t true_beta \t estimated_beta"<<endl;
	ifstream performance_in ("_performance.txt");
	if (performance_in.is_open()){
		int i=0;
		while ( performance_in.good() ){
		  getline (performance_in,line);
		  if(i>0){
			std::vector<std::string> sample = split(line, '\t');
			int n = sample.size(), nQuestions=50, j=0;
			int expert = atoi(sample[j].c_str());j++;
			string true_condition = sample[j];j++;
			if(true){
				double alpha = atof(sample[j].c_str());j++;
				double beta = atof(sample[j].c_str());j++;
				double* sr = new double[nQuestions];
				for(int q=0; q<nQuestions; q++){
					sr[q] = atof(sample[q+j].c_str());
				}
				calibrationMonitoringFacade(expert, nQuestions, true_condition, alpha, beta, sr, breaks, subintervals);
				delete[] sr;
				restartSubintervals(subintervals, breaks);
			}
			//cout << line << endl;
		  }
		  i++;
		}
		performance_in.close();
	 }
	else cout << "Unable to open file"; 
	for(int i=0; i < nSubintervals; i++){
		delete subintervals[i];
	}
}




void main(){

	long time = clock();
	//CalibrationInterface^ calInterface = CalibrationInterface::Instance(BISECTION);
	//int correctAlternative = 0, numberAlternatives=2;
	//array<double>^ credibilities = gcnew array<double>(numberAlternatives);
	//array<double>^ trueProbabilities = gcnew array<double>(numberAlternatives);
	//credibilities[0] = .5; credibilities[1] = .5; //credibilities[2] = .1;
	//trueProbabilities[0] = .5; trueProbabilities[1] = .5; //trueProbabilities[2] = 0;
	//int pattern = Calibration::CALIBRATED;
	//while(pattern == Calibration::CALIBRATED){
	//	String ^ ret = calInterface->updateCalibrationCurveDistribution(0, trueProbabilities, credibilities, numberAlternatives, true);
	//	pattern = calInterface->getCalibrationPattern();
	//}
	//if(pattern != Calibration::CALIBRATED){
	//	int gridZise = calInterface->getGridSize();
	//	array<double>^ gridMean = calInterface->getMeanCredibilitiesPerGrid(gridZise-1);
	//	array<double>^ q_lower = calInterface->getCalibrationCurveLowerQuantiles(gridZise-1);
	//	array<double>^ q_upper = calInterface->getCalibrationCurveUpperQuantiles(gridZise-1);
	//	cout<<"q_lower \t gridMean \t q_upper"<<endl;
	//	for(int i=0; i<gridZise-1; i++){
	//		cout<<q_lower[i]<<"\t"<<gridMean[i]<<"\t"<<q_upper[i]<<endl;
	//	}
	//	int g=0;
	//}
	//calInterface->deleteNews();
	//array<String^>^ list = ret->Split('|');
	//vector<array<String^>^> miscBins(0);
	//int nUpdates = list->Length-1;
	//for(int i=0; i<nUpdates; i++){
	//	String^ Str_i = list[i];
	//	array<String^>^ list_i = Str_i->Split(';');
	//	String^ pattern = list_i[1];
	//	if(pattern!="CALIBRATED"){
	//		String^ actualBin = list_i[0];
	//		int nMiscBins = miscBins.size(), index = 0;
	//		for (index; index < nMiscBins; index++){
	//			//miscBins[index][0]<actualBin
	//		}
	//	}
	//}

	//array<String^>^ list2 = Array::sort(list); 
	//decisoes.push_back((int*)(12, 12, 15, 21, 22));
	int nQuestions=50, nExperts=2;

	calibrationBayesianMonitoring();
	//CalibrationEngine::TrustDistributionInterface.getComulativeTrueDistribution("dirac; test");

	//main_thread(nExperts ,nQuestions);
	
	EBEB2012_2(nQuestions, CurvaCalibracao::Calibrated, nExperts);
	cout<<"Calibrated"<<endl;
	EBEB2012_2(nQuestions, CurvaCalibracao::Underconfident, nExperts);
	cout<<"Underconfident"<<endl;
	EBEB2012_2(nQuestions, CurvaCalibracao::Overconfident, nExperts);

	time -= clock();
	cout<<"Overconfident finished "<<(-time/CLOCKS_PER_SEC)<<endl;
	
	_CrtDumpMemoryLeaks();//Memory Leak Detection Enabling    
	int j;
	cin >> j;

}
