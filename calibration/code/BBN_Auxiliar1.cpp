#include "stdafx.h"
#include "BBN_Auxiliar1.h"
//Memory Leak Detection Enabling    
#include <stdlib.h>
//#include <crtdbg.h>
#include <fstream>//to print out

#define _CRTDBG_MAP_ALLOC
#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
#ifdef _DEBUG
	#define new DEBUG_NEW
	#undef THIS_FILE
	static char THIS_FILE[] = __FILE__;
#endif
ofstream dataSliceSamplingMatrix_cout("dataSliceSamplingMatrix.csv", ios::out);
ofstream distributionsMatrix_cout("distributionsMatrix.txt", ios::out);
ofstream relatedSampleMatrix_cout("relatedSample.txt", ios::out);
ofstream sample_cout("sample.txt", ios::out);
ofstream blackWell("blackWell.txt", ios::out);

using namespace std;

namespace CalibrationEngine{

	int BBN_Auxiliar::maxGeneration = 6;//test
	double BBN_Auxiliar::BOUNDS_COEFICIENT = 20.0;
	double BBN_Auxiliar::initialSliceSizeMultiplier = -1;
	double BBN_Auxiliar::shrinkingRatio = -100;
	int BBN_Auxiliar::minAutocorrelationStep = 1e10;
	int BBN_Auxiliar::maxAutocorrelationStep = -1e10;
	int BBN_Auxiliar::BBN_id = 0;
	bool BBN_Auxiliar::thereIsModelEstimate = false;
	bool BBN_Auxiliar::booleanKey = true;

	vector<double*> BBN_Auxiliar::dbl_toDelete(0);

	char BBN_Auxiliar::INF_TYPE = BBN_Auxiliar::UPDATE_INF;

void BBN_Auxiliar::addSortedSample(vector<double>& sample, double value){
	bool indexFound = false;
	int size = sample.size();
	int upper = size;
	//upper = (upper>0?upper--:upper);
	int lower = 0;
	int mid=0;
	while(!indexFound && lower!=upper){
		mid = (int) (upper+lower)/2;
		if(sample[mid]==value)
			indexFound = true;
		else{
			if(upper-lower<=1){
				if (value>sample[mid]){
					mid++;
					lower = upper;
				}else{
					mid--;
					upper = lower;
				}
			}else{
				if (value>sample[mid])
					lower = mid;
				else
					upper = mid;
			}
		}
	}
	if(mid<0)
		mid=0;
	sample.insert(sample.begin()+mid, value);
}

//void BBN_Auxiliar::deleteBTNews()	{
//	int n=bt_nodesToDelete.size();
//	for(int i=0; i<n; i++){
//		delete bt_nodesToDelete[i];
//	}
//	bt_nodesToDelete.clear();
//	//int n = cNodesToDelete.size();
//	//for(int i=n-1; i>=0; i--){
//	//	MxBBN_Node* node = cNodesToDelete[i];
//	//	if(node->getDensity()!=NULL)
//	//		delete (node->getDensity());
//	//	if(node->getNonParametricDistribution()!=NULL)
//	//		delete (node->getNonParametricDistribution());
//	//	delete(node);
//	//}
//}

//void BBN_Auxiliar::exportDistributionsMatrix(vector<double*> distributionsMatrix, int nIntervals){
//	int nDist = distributionsMatrix.size();
//	int sampleSize = nIntervals;
//	for(int i=0; i<sampleSize; i++){
//		for(int j=0; j<nDist; j++){
//			distributionsMatrix_cout<<distributionsMatrix[j][i]<<"\t";
//		}
//		distributionsMatrix_cout<<endl;
//	}
//}
//
//void BBN_Auxiliar::exportSample(vector<double> sample){
//	int n = sample.size();
//	for(int i=0; i<n; i++){
//		sample_cout<<sample[i]<<endl;
//	}
//	sample_cout<<"JJJJJJJ"<<endl<<endl;
//}
//
////void BBN_Auxiliar::exportSamples(vector<vecDouble> samplesMatrix){
////	int nVar = allDNodes.size();
////	int nCol = nVar;
////	//for (nCol = 0; BBN_Auxiliar::allDNodes[nCol]->getParentsCount()==0; nCol++) 
////	//	true;
////	int nSamples = samplesMatrix[0].size();
////	for(int i=0; i<nSamples; i++){
////		for(int j=0; j<nCol; j++){
////			//MxBBN_Node* nj = (MxBBN_Node*) BBN_Auxiliar::allDNodes[j];
////			//if(!nj->isEvidenced)
////				dataSliceSamplingMatrix_cout<<samplesMatrix[j][i]<<"\t";
////			//else
////			//	dataSliceSamplingMatrix_cout<<nj-><<"\t";
////		}
////		dataSliceSamplingMatrix_cout<<endl;
////	}
////	dataSliceSamplingMatrix_cout<<"JJJJJJJ"<<endl<<endl;
////}
//
//double BBN_Auxiliar::getSpectralStatistic(const vector<double*> sample, const int index, const double pr1, const double pr2){
//	double const PI = 3.14159265358979;
//	int N = sample.size();
//	int* lower = new int[2];
//	int* upper = new int[2];
//	double* mean = new double[2];
//	double* spD0 = new double[2]; //spectral density at 0 for sample i
//	int* n = new int[2];
//	lower[0] = 0;
//	upper[0] = pr1*N-1;
//	lower[1] = N - pr2*N;
//	upper[1] = N-1;
//	for(int i = 0; i<2; i++){
//		n[i] = upper[i] - lower[i]+1;
//		double sxi = 0.0;
//		for(int j=lower[i]; j<=upper[i]; j++){
//			sxi += sample[j][index];
//		}
//		mean[i] = sxi / n[i];
//
//		double sp = 0.0;
//		for(int lag = 0; lag < n[i]; lag++){
//			for(int t=lower[i]+lag; t<=upper[i]; t++)
//				sp+= (sample[t][index] - mean[i])*(sample[t-lag][index] - mean[i]);
//		}
//		spD0[i] = sp/n[i];
//		spD0[i] /= (2*PI);
//	}
//	double statistic = mean[0] - mean[1];
//	double sd = pow(spD0[0]/n[0] + spD0[1]/n[1], .5);
//	if(sd == 0)
//		sd = 1e-30;
//	statistic /= sd;
//	delete[]mean;
//	delete[]spD0;
//	delete[]n;
//	delete[]lower;
//	delete[]upper;
//
//	return statistic;
//}
//
//double BBN_Auxiliar::getSpectralStatistic(vector<double> sample, double pr1, double pr2){
//	double const PI = 3.14159265358979;
//	int N = sample.size();
//	int* lower = new int[2];
//	int* upper = new int[2];
//	double* mean = new double[2];
//	double* spD0 = new double[2]; //spectral density at 0 for sample i
//	int* n = new int[2];
//	lower[0] = 0;
//	upper[0] = pr1*N-1;
//	lower[1] = N - pr2*N;
//	upper[1] = N-1;
//	for(int i = 0; i<2; i++){
//		n[i] = upper[i] - lower[i]+1;
//		double sxi = 0.0;
//		for(int j=lower[i]; j<=upper[i]; j++){
//			sxi += sample[j];
//		}
//		mean[i] = sxi / n[i];
//
//		double sp = 0.0;
//		for(int lag = 0; lag < n[i]; lag++){
//			for(int t=lower[i]+lag; t<=upper[i]; t++)
//				sp+= (sample[t] - mean[i])*(sample[t-lag] - mean[i]);
//		}
//		spD0[i] = sp/n[i];
//		spD0[i] /= (2*PI);
//	}
//	double statistic = mean[0] - mean[1];
//	double sd = pow(spD0[0]/n[0] + spD0[1]/n[1], .5);
//	if(sd == 0)
//		sd = 1e-30;
//	statistic /= sd;
//	delete[]mean;
//	delete[]spD0;
//	delete[]n;
//	delete[]lower;
//	delete[]upper;
//
//	return statistic;
//}
//
//double BBN_Auxiliar::getAutocorrelationStatisticForOneStep(vector<double> sample){
//	int n = sample.size();
//	double sxi = 0.0;
//	double sxi2  = 0.0;
//	for(int i=0; i<n; i++){
//		sxi += sample[i];
//		sxi2 += pow(sample[i], 2.0);
//	}
//	double S2_numerator = (sxi2 - pow(sxi, 2.0)/n);
//	double mean = sxi/n;
//
//	double r = 0.0;
//	for(int t=1; t<n; t++)
//		r+= (sample[t] - mean)*(sample[t-1] - mean);
//	r /= S2_numerator;
//	if(r<0)
//		r = abs(r);
//	double statistic = r*pow((double)n-2, .5);
//	statistic /= pow(1-r*r, .5);
//	//if(statistic>1.96)
//	//	cout<<" ( t= "<<statistic<<" ) ";
//	//IF statistic >= 1.96, THERE IS AUTOCORRELATION
//	return statistic;
//}

	double BBN_Auxiliar::getExp(double x){
		double result=0;
		if(x > BBN_Auxiliar::ZERO_EXP){
			if(x < BBN_Auxiliar::INF_EXP)
				result = exp(x);
			else{
				result = DBL_MAX;
				//cout<<"::DANGER: EXP(X)=INF!!"<<endl;
			}
		}
		return result;
	}

	double BBN_Auxiliar::getLog(double x){
		double result=LOG_ZERO;
		if(x > 0){
			result = log(x);
		}
		return result;
	}

	int BBN_Auxiliar::getPointLocationByBinarySearch(const vector<double*> sample, const vector<int> ordered_indexes, const int var_index, const double value, int lower, int upper){
		bool indexFound = false;
		//int nComp = 0;
		//static int max_nComp = 0;
		int mid=0;
		int min = lower;
		int max = upper;//(upper>0?upper-1:0);
		while(!indexFound && lower!=upper){
			mid = (int) (upper+lower)/2;
			int aux = ordered_indexes[mid];
			double sampleKey = sample[aux][var_index];
			if(value==sampleKey)
				indexFound = true;
			else{
				if(upper-lower>1){
					if (value>sampleKey)
						lower = mid;
					else
						upper = mid;
				}else{
					if (value>sampleKey){
						mid++;
						lower = upper;
					}else{
						mid--;
						upper = lower;
					}
				}
			}
		}
		//if(nComp > max_nComp){
		//	max_nComp = nComp;
		//	cout<<"max_nComp = "<<max_nComp<<endl;
		//}
		//cout<<nComp<<endl;
		if(mid<min)
			mid=min;
		else if(mid > max)
			mid = max;
		return mid;
	}

	int BBN_Auxiliar::getPointLocationByBinarySearch(vector<double*> & sample, int col, double value, int lower, int upper){
		bool indexFound = false;
		//int nComp = 0;
		//static int max_nComp = 0;
		int mid=0;
		int min = lower;
		int max = upper;//(upper>0?upper-1:0);
		while(!indexFound && lower!=upper){
			mid = (int) (upper+lower)/2;
			double sampleKey = sample[mid][col];
			if(value==sampleKey)
				indexFound = true;
			else{
				if(upper-lower>1){
					if (value>sampleKey)
						lower = mid;
					else
						upper = mid;
				}else{
					if (value>sampleKey){
						mid++;
						lower = upper;
					}else{
						mid--;
						upper = lower;
					}
				}
			}
		}
		//if(nComp > max_nComp){
		//	max_nComp = nComp;
		//	cout<<"max_nComp = "<<max_nComp<<endl;
		//}
		//cout<<nComp<<endl;
		if(mid<min)
			mid=min;
		else if(mid > max)
			mid = max;
		return mid;
	}

	double BBN_Auxiliar::getFx(const vector<double> x, const vector<double> Fx, const double value){
		int n = x.size();
		int i = BBN_Auxiliar::getPointLocationByBinarySearch(x, value, 1, n-1);
		double intervalBasis = x[i] - x[i-1];
		double intervalArea = Fx[i] - Fx[i-1];
		double height = intervalArea / intervalBasis;
		double pBase = value -x[i-1];
		double pArea = pBase*height;
		double result = Fx[i-1] + pArea;
		return result;

	
	}



	double BBN_Auxiliar::getQuantile(const vector<double> x, const vector<double> Fx, const double p){
		int n = x.size();
		int l = BBN_Auxiliar::getPointLocationByBinarySearch(Fx, p, 0, n);
		double v=0;
		if(l>0){
			double x_ = x[l-1];
			double y = x[l];
			double F_x = Fx[l-1];
			double Fy = Fx[l];
			double f = (Fy - F_x)/(y-x_);
			v = x_;
			v += (p-F_x)/f;
		}
		else{
			if(x[0]/x[n-1]-1< 10e-100)
				v = x[0];
			else
				v = p*x[0] / Fx[0];
		}
		return v;
	}



int BBN_Auxiliar::getPointLocationByBinarySearch(const vector<double> sample, const double value, int lower, int upper){
		bool indexFound = false;
		int mid=0;
		int min = lower;
		int max = upper;
		while(!indexFound && lower!=upper){
			mid = (int) (upper+lower)/2;
			double sampleKey = sample[mid];
			if(value==sampleKey)
				indexFound = true;
			else{
				if(upper-lower>1){
					if (value>sampleKey)
						lower = mid;
					else
						upper = mid;
				}else{
					if (value>sampleKey){
						mid++;
						lower = upper;
					}else{
						mid--;
						upper = lower;
					}
				}
			}
		}
		//if(nComp > max_nComp){
		//	max_nComp = nComp;
		//	cout<<"max_nComp = "<<max_nComp<<endl;
		//}
		//cout<<nComp<<endl;
		if(mid<min)
			mid=min;
		else if(mid > max)
			mid = max;
		return mid;
}

void BBN_Auxiliar::removeAutocorrelation(vector<double>& sample, double maxAutocorrelation){
	int n = sample.size();
	double sxi = 0.0;
	double sxi2  = 0.0;
	for(int i=0; i<n; i++){
		sxi += sample[i];
		sxi2 += pow(sample[i], 2.0);
	}
	double S2_numerator = (sxi2 - pow(sxi, 2.0)/n);
	double mean = sxi/n;

	bool indexFound = false;
	int upper = n;
	//upper = (upper>0?upper--:upper);
	int lower = 0;
	int k=0, nCalculations=0;
	double r_k = 1.0;
	while(maxAutocorrelation<abs(r_k)){
		nCalculations++;
		k ++;
		r_k = 0.0;
		for(int t=k; t<n; t++)
			r_k+= (sample[t] - mean)*(sample[t-k] - mean);
		r_k /=S2_numerator;
	}
	//cout<<"autocorrelation for k= "<<k<<": "<<r_k<<endl;//" (with "<<nCalculations<<" calculations)"<<endl;
	cout<<" (k= "<<k<<") ";
	vector<double> newSample(0);
	if(k==0)
		k++;
	if(k<minAutocorrelationStep)
		minAutocorrelationStep = k;
	if(k>maxAutocorrelationStep)
		maxAutocorrelationStep = k;
	for(int i=n-1; i>=0; i-=k){
		BBN_Auxiliar::addSortedSample(newSample, sample[i]);
	}
	sample = newSample;
}


void BBN_Auxiliar::setGammaFunction(double& gamma_x, const double x){
	gamma_x  =0;
	double v = x;
	if(v > 100){
		int upper = x+.5;
		for(double k = 2; k<=upper; k++)
			gamma_x += log(k);
	}
	else if (v>0)
		gamma_x = (Xgamm(&v));
}

void BBN_Auxiliar::updatePrioris(){
	/*int size = BBN_Auxiliar::rootDNodes.size();
	for(int i=0; i<size; i++){
		DBBN_Node* di = NULL;
		if(rootDNodes[i]->NODE_TYPE == General_Auxiliar::DBBN_NODE){
			di = (DBBN_Node*)BBN_Auxiliar::rootDNodes[i];
		}
		vector<double> diProbs = di->getDensity();
		int nLevels = di->getLevelsCount();
		for(int j=0; j<nLevels; j++){
			di->setProb(0,j,diProbs[j]);
		}
	}*/
}


BBN_Auxiliar::~BBN_Auxiliar(){}

BBN_Auxiliar::BBN_Auxiliar(){}
}