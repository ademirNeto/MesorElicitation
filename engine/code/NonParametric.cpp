#include "NonParametric.h"
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
//#include "General_Auxiliar.h"
#include <fstream>//to print out
ofstream distribution_cout("distributionMatrix.txt", ios::out);
namespace Engine{
	//NonParametric::NonParametric(MxBBN_Node* node, int intervalsCount){
	//	this->DENSITY_TYPE = General_Auxiliar::NONPARAMETRIC_DENSITY;
	//	this->sample = node->getSample();
	//	this->intervalsCount = intervalsCount;
	//	this->vec_x = new double[this->intervalsCount];
	//	this->densities = new double[this->intervalsCount];
	//	node->clearSample();
	//	delete node->getDensity();
	//	node->setDensity(this);
	//	this->lowerBound = this->sample[0];
	//	this->upperBound =this->sample[this->sample.size()-1];
	//	this->delta = (this->upperBound - this->lowerBound)/this->intervalsCount;
	//	this->loadDensities();
	//	this->sliceSize = .0000001-lowerBound + upperBound;
	//	this->locationEstimate = (lowerBound + upperBound)/2;
	//}
	void NonParametric::setParameters(double mean, double variance){}
	NonParametric::NonParametric(vector<double> sample){
			//General_Auxiliar::densitiesToDelete.push_back(this);
			this->DENSITY_TYPE = General_Auxiliar::NONPARAMETRIC_DENSITY;
			this->x.clear();
			this->setSample(sample);
			int n= sample.size();
			this->lowerBound = sample[0];
			this->upperBound =sample[n-1];
			double amplitude = (this->upperBound - this->lowerBound);
			this->intervalsCount = pow((double)n, .5);
			this->delta = amplitude/this->intervalsCount;
			this->vec_x = 0;
			this->densities = 0;
			this->cumulativeDensities = 0;
			try{
				double aux = amplitude + this->delta;
				if(amplitude==aux){
					this->mean = sample[0];
					this->variance = 0;

//					throw amplitude;
				}
				else{
					this->evaluateVarAndMean();
				}
//				this->sliceSize = General_Auxiliar::initialSliceSizeMultiplier*amplitude;
				this->locationEstimate = (lowerBound + upperBound)/2;
			}
			catch(double amplitude){
					cout<<"PROBLEM DETECTED: (UPPER - LOWER) NEAR ZERO"<<endl;
					this->goOn = false;
			}
		}
	NonParametric::NonParametric(const vector<double> x, const vector<double> Fx, const int maxIntervalsCount){
			//General_Auxiliar::densitiesToDelete.push_back(this);
			this->DENSITY_TYPE = General_Auxiliar::NONPARAMETRIC_DENSITY;
			this->x = x;
			this->Fx = Fx;
			this->vec_x = 0;
			this->densities = 0;
			this->cumulativeDensities = 0;
			this->lowerBound = x[0];
			this->intervalsCount = x.size();
			this->upperBound =x[this->intervalsCount-1];
			double mass = 1e-200;
			if(this->intervalsCount > maxIntervalsCount){
				this->intervalsCount = maxIntervalsCount;
				mass = 1.0 / maxIntervalsCount;
			}
			this->evaluateParametersAndLeanIntervals(x, Fx, mass);
			try{
			//	this->sliceSize = General_Auxiliar::initialSliceSizeMultiplier*amplitude;
				this->locationEstimate = this->mean;
			}
			catch(double amplitude){
					cout<<"PROBLEM DETECTED: (UPPER - LOWER) NEAR ZERO"<<endl;
					this->goOn = false;
			}
		}
	NonParametric::NonParametric(vector<vec_dbl> samples, const double lowerBound, const double upperBound){
			this->vec_x = 0;
			this->densities = 0;
			this->cumulativeDensities = 0;
			this->DENSITY_TYPE = General_Auxiliar::NONPARAMETRIC_DENSITY;
			this->x.clear();
			int nSamples = (int)samples.size();
			int n = (int)samples[0].size();
			intervalsCount = pow((double)n, .5);
			this->intervalsCount = intervalsCount;
			//this->vec_x = new double[this->intervalsCount];
			//this->densities = new double[this->intervalsCount];
			//this->cumulativeDensities = new double[this->intervalsCount];
			this->sample.clear();
			//int g = sample.size();
			this->lowerBound = lowerBound;
			this->upperBound = upperBound;
			this->delta = (this->upperBound - this->lowerBound)/this->intervalsCount;
//			this->sliceSize = General_Auxiliar::initialSliceSizeMultiplier*(this->upperBound - this->lowerBound);
			this->locationEstimate = (lowerBound + upperBound)/2;
			//this->loadDensities(samples);
		}
	NonParametric::NonParametric(void){
		this->DENSITY_TYPE = General_Auxiliar::NONPARAMETRIC_DENSITY;
		this->lowerBound = 1e100;
		this->upperBound = -1e100;
		this->intervalsCount = -1;
		this->vec_x = 0;
		this->densities = 0;
		this->cumulativeDensities = 0;
	}
	NonParametric::~NonParametric(void){
		if(vec_x!=0){
			delete[]vec_x;
			delete[] densities;
			vec_x=0;
			densities =0;
		}
		if(this->cumulativeDensities !=0){
			delete[] cumulativeDensities;
			cumulativeDensities = 0;
		}
	}
	double NonParametric::getDerivate_fx(double x){
		double result = this->derivateIn_x;
		//int n = this->
		return result;
	}
	double NonParametric::getDerivateForLocationParameter(string locationLabel){
		return 0;
	} 
	double NonParametric::getDerivateForScalingParameter(double x){
		return 0;
	} 
	void NonParametric::evaluateSliceLowerBound(double& lower){
		if(lower < this->lowerBound){
			//double half = (this->lowerBound - lower)/2;
			//lower -= half;
			//upper += half;
			//double diff = (this->lowerBound - lower);
			lower = this->lowerBound;
		}
	} 
	void NonParametric::evaluateSliceUpperBound(double& upper){
		if(upper> this->upperBound){
			//double half = (upper - this->upperBound)/2;
			//lower -= half;
			//upper += half;
			upper = this->upperBound;
		}
	} 
	void NonParametric::evaluateVarAndMean(){
		int n = (int)this->sample.size();
		double sxi = 0.0;
		double sxi2  = 0.0;
		for(int i=0; i<n; i++){
			sxi += this->sample[i];
			sxi2 += pow(this->sample[i], 2.0);
		}
		double S2 = (sxi2 - pow(sxi, 2.0)/n)/(n-1);
		double xBarr = sxi/n;
		this->mean = xBarr;
		this->variance = S2;
		//cout<<"S2: "<<S2<<", xBarr: "<<xBarr<<endl;
	}
	double NonParametric::getMode(){
		return this->mode;
	}
	void NonParametric::evaluateParametersAndLeanIntervals(const vector<double> x, const vector<double> Fx
		, const double minimalMass){
		int n = x.size();
		//calculating mean and variance
		double Ex = 0.0;
		double Ex2  = 0.0;
		double meanDelta = 0;
		for(int i=1; i<n; i++){
			double area = Fx[i] - Fx[i-1];
			double delta = x[i] - x[i-1];
			meanDelta += delta;
			double f = area / delta;
			Ex += f*(pow(x[i], 2.0) - pow(x[i-1], 2.0));
			Ex2 += f*(pow(x[i], 3.0) - pow(x[i-1], 3.0));
		}
		Ex /= 2;
		Ex2 /= 3;
		meanDelta /= (n-1);
		this->mean = Ex;
		this->variance = Ex2 - pow(Ex, 2.0);
		cout<<"S2: "<<variance<<", xBarr: "<<mean<<endl;

		//smothing the distribution
		this->vec_x = new double[n];
		this->cumulativeDensities = new double[n];
		this->densities  = new double[n];
		this->vec_x[0]  = x[0];
		this->cumulativeDensities[0] = Fx[0];
		this->densities[0] = Fx[0];
		int mi = 0; double mlength = x[1] - x[0], fm = densities[0], fb = 0, fp = 0, ml = x[0];
		for(int i=1; i < n; i++){
			double length = x[i] - x[i-1];
			double area = Fx[i] - Fx[i-1];
			vec_x[i] = x[i];
			this->cumulativeDensities[i] = Fx[i];
			this->densities[i] = area / length;
			double diff = densities[i] - fm;
			if(diff>1e-100){
				mlength = length;
				fm = densities[i];
				fb = densities[i-1];
				mi = i;
				ml = x[i-1];
			}else if (diff>=0){
				mlength += length;
				mi = i;
			}
		}
		if(mi<n-1)
			fp = densities[mi+1];
		double db = fm - fb, dp = fm - fp;
		this->mode = ml + mlength*db/(db+dp);

		this->intervalsCount = n;
	}
	void NonParametric::exportDistribution(){
		//cout.precision(100);
//		distribution_cout.precision(100);
		//cout.setf(ios::fixed);
		for(int i=0; i<this->intervalsCount; i++){
			double x = this->vec_x[i];
			double fx = this->densities[i];
			//cout<<x<<", "<<fx<<endl;
			distribution_cout<<x<<"\t";
			distribution_cout<<fx<<endl;
		}
		//distribution_cout<<"JJJJJJ"<<endl;
		distribution_cout<<endl;
	}


	double NonParametric::getLowerBound(){
		return this->lowerBound;
	}
	double NonParametric::getVariance(){
		return this->variance;
	}

	double NonParametric::getUpperBound(){
		return this->upperBound;
	}
	//double NonParametric::get_fx(double x){
	//	double result = 0.0;
	//	if(x>=this->lowerBound && x<= this->upperBound){
	//		double realIndex= (x - this->lowerBound)/this->delta; 
	//		int flooIndex = realIndex;
	//		double xxxx = this->vec_x[flooIndex];
	//		result = this->densities[flooIndex];
	//		//evaluating the derivate
	//		int otherIntervalLevel = flooIndex+1;
	//		if(flooIndex == this->intervalsCount)
	//			otherIntervalLevel = flooIndex-1;
	//		double oppositeCatet = abs(result-this->densities[otherIntervalLevel]);
	//		double adjacentCatet = abs(x-this->vec_x[otherIntervalLevel]);
	//		this->derivateIn_x = oppositeCatet/adjacentCatet;
	//	}
	//	if(result>0)
	//		return log(result);
	//	else
	//		return this->minLn;
	//}
	double NonParametric::get_fx(double x){
		double result = this->minLn;
		if(x>=this->lowerBound && x<= this->upperBound){
			int n= (int)this->sample.size();
			int i = General_Auxiliar::getPointLocationByBinarySearch(this->sample, x, 0, n);
			double l = x-this->delta/2;
			double u = x+this->delta/2;
			int i_l = -1;
			int i_u = -1;

			if(l < this->lowerBound){
				l = this->lowerBound;
				u = l+this->delta;
				i_l = 0;
				i_u = General_Auxiliar::getPointLocationByBinarySearch(this->sample, u, 0, n);
			}
			else if(u > this->upperBound){
				u = this->upperBound;
				l = u-this->delta;
				i_u = n-1;
				i_l = General_Auxiliar::getPointLocationByBinarySearch(this->sample, l, 0, i_u);

			}
			else{
				i_l = General_Auxiliar::getPointLocationByBinarySearch(this->sample, l, 0, i);
				i_u = General_Auxiliar::getPointLocationByBinarySearch(this->sample, u, i, n);
			}

			//i_l = i;
			//i_u = i;
			//while(i_l>0 && this->sample[i_l]>l)
			//	i_l--;
			//while(i_u<n-1 && this->sample[i_u]<u)
			//	i_u++;

			int oppositeCatet = i_u - i_l+1;
			if(oppositeCatet<=0)
				cout<<"negative oppositeCatet in NonParametric::get_fx(...)"<<endl;
			result = log((double)oppositeCatet);
		}
		return result;
	}
	double NonParametric::getCDF(double x){
		return 0.0;
	}

	int NonParametric::getIntervalsCount(){
		return this->intervalsCount;
	}
	double NonParametric::getMean(){
		return this->mean;
	}
	double NonParametric::getQuantile(double p){
		double result = 0;
		int n = this->x.size(); //redo...
		if(n>0){
			int l = General_Auxiliar::getPointLocationByBinarySearch(Fx, p, 0, n);
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
			result=v;
		}
		else{
			int index = (int)this->sample.size()*p;
			result  = this->sample[index];
		}
		return result;

	
	}


	bool NonParametric::loadDensities(){
		if(!goOn)
			return false;
		double delta = this->delta;
		int intervalsCount = this->intervalsCount;
		delete [] this->vec_x;
		delete [] this->densities;
		delete [] this->cumulativeDensities ;
		this->vec_x = new double[intervalsCount];
		this->densities = new double[intervalsCount];
		this->cumulativeDensities = new double[intervalsCount];


		int n = (int)this->sample.size();
		double x = this->lowerBound;
		int i=0, j=0; 
		double maxDensity = -1e200;
		while(i<n && j<intervalsCount){
			this->densities[j] = 0;
			double aux = x;
			x = this->lowerBound + (j+1)*delta;
			try{
				if(x==aux)
					throw delta;
			}
			catch(double delta){
				cout<<"PROBLEM DETECTED: (UPPER - LOWER) NEAR ZERO"<<endl;
				return false;
			}
			while(i<n && this->sample[i] < x){
				i++;
				this->densities[j]++;
			}
			this->vec_x[j] = x;// - delta/2;
			this->densities[j] /= n;
			if(this->densities[j]>maxDensity){
				maxDensity = this->densities[j];
				this->locationEstimate = this->vec_x[j];
			}
			this->cumulativeDensities[j] = (double)i/n;
			j++;
		}
		for(j; j<intervalsCount; j++){
			this->densities[j] = 0;
			this->cumulativeDensities[j] = 1;
		}
		return true;
	}
	bool NonParametric::loadDensities(const int intervalsCount){
		if(!goOn)
			return false;
		double delta = (this->upperBound - this->lowerBound)/intervalsCount;
		if(this->vec_x!=0){
			delete [] this->vec_x;
			delete [] this->densities;
			delete [] this->cumulativeDensities ;
		}
		this->vec_x = new double[intervalsCount];
		this->densities = new double[intervalsCount];
		this->cumulativeDensities = new double[intervalsCount];

		int n = (int)this->sample.size();
		double x = this->lowerBound;
		int i=0, j=0; 
		double maxDensity = -1e200;
		while(i<n && j<intervalsCount){
			this->densities[j] = 0;
			double aux = x;
			x = this->lowerBound + (j+1)*delta;
			try{
				if(x==aux)
					throw delta;
			}
			catch(double delta){
				cout<<"PROBLEM DETECTED: (UPPER - LOWER) NEAR ZERO"<<endl;
				return false;
			}
			while(i<n && this->sample[i] < x){
				i++;
				this->densities[j]++;
			}
			this->vec_x[j] = x;// - delta/2;
			this->densities[j] /= n;
			if(this->densities[j]>maxDensity){
				maxDensity = this->densities[j];
				this->locationEstimate = this->vec_x[j];
			}
			this->cumulativeDensities[j] = (double)i/n;
			j++;
		}
		for(j; j<intervalsCount; j++){
			this->densities[j] = 0;
			this->cumulativeDensities[j] = 1;
		}
		return true;
	}
	bool NonParametric::loadDensities(vector<vec_dbl> samples){
		int nS = (int)samples.size();
		int n = (int)samples[0].size();
		double x = this->lowerBound + delta;
		//int cumulative_i = 0; 
		unsigned int* j = new unsigned int[nS];
		//unsigned int* actual_n = new unsigned int[nS];
		double ln_pot = nS*log((double)n);
		for(int i=0; i<nS; i++){
			j[i] = 0;
		}
		int interval_index = 0;
		//int maxCumulative = n*nS;
		while(interval_index<this->intervalsCount/* cumulative_i<maxCumulative*/){
			this->densities[interval_index] = 0;
			this->cumulativeDensities[interval_index] =0;
			bool goOn = true;
			for(int i = 0; goOn && i<nS; i++){
				int actual_n=0; 
				vec_dbl sample = samples[i];
				while(j[i]<n && sample[j[i]] <= x){
					j[i]++;
					actual_n++;
				}
				if(actual_n>0){
					this->cumulativeDensities[interval_index] += log((double)j[i]);
					this->densities[interval_index]+= log((double)actual_n);
					//cumulative_i+=actual_n;
				}
				else{
					this->densities[interval_index] = -1e200;
					this->cumulativeDensities[interval_index] = -1e200;
					goOn = false;
				}
			}
			this->vec_x[interval_index] = x;
			interval_index++;
			x += this->delta;
		}
		delete j;
		double dividend = 0;
		double maxDensity = -1e200;
		for(int i=0; i<this->intervalsCount; i++){
			dividend += General_Auxiliar::getExp(this->densities[i]-ln_pot);
		}
		try{
			if(dividend==0)
				throw dividend;
			for(int i=0; i<this->intervalsCount; i++){
				if(this->densities[i]>maxDensity){
					maxDensity = this->densities[i];
					this->locationEstimate = this->vec_x[i];
				}
				this->densities[i] = General_Auxiliar::getExp(this->densities[i]-ln_pot)/dividend;
				//dividend += this->densities[i];
				this->cumulativeDensities[i] = General_Auxiliar::getExp(this->cumulativeDensities[i]-ln_pot);
			}
			return true;
		}catch(double dividend){
		//else{
			cout<<"PROBLEM DETECTED: NULL DENSITY!"<<endl;
			return false;
			
		}
	}
	double* NonParametric::getVec_x(){
		return this->vec_x;
	}
	double* NonParametric::getVec_xCumulativeProbabilities(){
		return this->cumulativeDensities;
	}
	double* NonParametric::getVec_xProbabilities(){
		return this->densities;
	}
	void NonParametric::performeAdherenceTestByChiSquare(Density* density, double &pValue, double &cValue){
		
		cValue = 0.0;
		pValue = 0.0;
		int 
			n = (int)this->sample.size(),
			k = this->intervalsCount,
			i = 0;
		double 
			//diff = this->upperBound - this->lowerBound,
			xi = this->lowerBound + this->delta,// + 1/pow(diff, 2.0),
			Fxi_1 = 0.0;
		while( i <k){
			double Fxi = density->getCDF(xi);
			double fxi =  Fxi - Fxi_1;
			Fxi_1 = Fxi;
			double fxi_observed = this->densities[i];
			cValue += pow(fxi - fxi_observed, 2.0)/fxi;
			i++;
			xi += this->delta;
		}
		cValue *= n;
		if(cValue<=1.7976931348623158e+308){
			double bound = 0.0, p = 0.0, k_1 = k-1.0; 
			int which = 1, status=0;
			cdfchi(&which, &p, &pValue, &cValue, &k_1, &status, &bound);
		}else
			pValue = 0.0;
		cout<<">>by Chi-Square|| n= "<<n<<", DF= "<<(k-1)<<" and a cValue= "<<cValue<<". The pValue is "<<pValue<<endl;
	}
	void NonParametric::performeAdherenceTestByKolmogorovSmirnov(Density* density, double alfa, double &cValue, double &tValue)
{
		int n = (int)this->sample.size();
		if(n>0){
			int i=0;
			double 
				Sxi = 0.0, 
				Sxi_1 = 0.0, 
				Fxi = 0.0,
				xi = this->sample[i],
				max = -1;

			while( i <n){
				while( i <n && this->sample[i] <= xi)
					i++;
				Sxi_1 = Sxi;
				Sxi =(double)i/n;
				Fxi = density->getCDF(xi);
				double absFxi_Sxi = abs(Fxi-Sxi);
				double absFxi_Sxi_1 = abs(Fxi-Sxi_1);
	//			double localMax = absFxi_Sxi;
				double localMax = absFxi_Sxi > absFxi_Sxi_1 ? absFxi_Sxi : absFxi_Sxi_1;
				if(localMax > max)
					max = localMax;
				if(i<n)
					xi = this->sample[i];
			}
			cValue = max;
			double tDiv = pow(1.0*n, .5);
			if(alfa==.01)
				tValue = 1.63;
			else if(alfa == .05)
				tValue = 1.36;
			tValue /= tDiv;
			cout<<"by K-S|| n= "<<n<<", cValue = "<<cValue<<" and tValue= "<<tValue<<endl;
		}
		else {
			n = this->intervalsCount;
			int i=-1;
			double 
				Sxi = 0.0, 
				Sxi_1 = 0.0, 
				Fxi = 0.0,
				max = -1;

			while( i <n){
				i++;
				double xi = this->vec_x[i],
				Sxi_1 = Sxi;
				Sxi =(double)this->cumulativeDensities[i];
				Fxi = density->getCDF(xi);
				double absFxi_Sxi = abs(Fxi-Sxi);
				double absFxi_Sxi_1 = abs(Fxi-Sxi_1);
	//			double localMax = absFxi_Sxi;
				double localMax = absFxi_Sxi > absFxi_Sxi_1 ? absFxi_Sxi : absFxi_Sxi_1;
				if(localMax > max)
					max = localMax;
			}
			cValue = max;
			double tDiv = pow(1.0*n, .5);
			if(alfa==.01)
				tValue = 1.63;
			else if(alfa == .05)
				tValue = 1.36;
			tValue /= tDiv;
			cout<<"by K-S|| n= "<<n<<", cValue = "<<cValue<<" and tValue= "<<tValue<<endl;
		}

	}
	void NonParametric::performeAdherenceTestByLilliefors(Density* density, double alfa, double &cValue, double &tValue){
		int n = (int)this->sample.size();
		if(n==0){
			n = this->intervalsCount;
			density->setParameters(this->mean, this->variance);
			int i=-1;
			double 
				Sxi = 0.0, 
				Sxi_1 = 0.0, 
				Fxi = 0.0,
				max = -1;

			while( i <n){
				i++;
				double xi = this->vec_x[i],
				Sxi_1 = Sxi;
				Sxi =(double)this->cumulativeDensities[i];
				Fxi = density->getCDF(xi);
				double absFxi_Sxi = abs(Fxi-Sxi);
				double absFxi_Sxi_1 = abs(Fxi-Sxi_1);
	//			double localMax = absFxi_Sxi;
				double localMax = absFxi_Sxi > absFxi_Sxi_1 ? absFxi_Sxi : absFxi_Sxi_1;
				if(localMax > max)
					max = localMax;
			}
			cValue = max;
			double tDiv = pow(1.0*n, .5);
			if(alfa==.01)
				tValue = 1.63;
			else if(alfa == .05)
				tValue = 1.36;
			tValue /= tDiv;
			cout<<"by K-S|| n= "<<n<<", cValue = "<<cValue<<" and tValue= "<<tValue<<endl;
		}
	}
	void NonParametric::removeOutliers(){
		int n = (int)this->sample.size(), j=n-1;
		double Q_25 = this->sample[n/4];//wrong (correct only for Uniform density)
		double Q_75 = this->sample[n-n/4];
		double interquartileInterval = Q_75 - Q_25;
		while(this->sample[j] > Q_75 + 1.5*interquartileInterval){
			this->sample.erase(this->sample.end()-1);
			j--;
		}
		while(this->sample[0] < Q_25 - 1.5*interquartileInterval)
			this->sample.erase(this->sample.begin());
	}
	void NonParametric:: setIntervalsCount(int intervalsCount){
		this->intervalsCount = intervalsCount;
	}
	void NonParametric::setSample(const vector<double> sample){
		int n = (int)sample.size();
		this->sample.resize(0);
		this->sample.push_back(sample[0]);
		for(int i=1; i<n; i++){
			double value = sample[i];
			int index = General_Auxiliar::getPointLocationByBinarySearch(this->sample, value, 0, i);
			this->sample.insert(this->sample.begin()+index, value);
		}
	}
	void NonParametric::setVec_x(double* x){
		this->vec_x = x;
	}
	void NonParametric::setVec_fx(double* fx){
		this->densities = fx;
	}
	void NonParametric::updateBounds(const double lower, const double upper){
		if(lower < this->lowerBound)
			this->lowerBound = lower;
		if(upper > this->upperBound)
			this->upperBound = upper;
	}
	void NonParametric::updateGridSize(const int count, const int n){
		//this->intervalsCount = (this->intervalsCount*(n-1) + count)/n;
		int aux = count -1;
		if(this->intervalsCount < aux)
			this->intervalsCount = aux;
	}
	void NonParametric::updateSliceBounds(){
		this->sliceLowerBound = this->sample[0];
		this->sliceUpperBound = this->sample[(int)this->sample.size()-1];
	}
}
