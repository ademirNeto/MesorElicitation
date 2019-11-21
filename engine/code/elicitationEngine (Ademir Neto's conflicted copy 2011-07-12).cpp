#include "stdafx.h"

#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>//to print out
#include ".\Node.h"
#include ".\Firmino.h"
//#include "DLL_Facade.h"

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


using namespace std;
using namespace Engine;


ofstream judgments_cout("judgments.txt", ios::out);
typedef vector<double> vec_dbl;

const int PROBABILITY_ELICITATION = 1;
const int NUMBER_OF_OCCURRENCES_ELICITATION = 2;
const int RATE_ELICITATION = 3;
const int TIME_ELICITATION = 4;

const int MINUTE_TIME_UNIT = 1;
const int HOUR_TIME_UNIT = 2;
const int DAY_TIME_UNIT = 3;
const int MONTH_TIME_UNIT = 4;
const int YEAR_TIME_UNIT = 5;


void addIntervalInOrderedList(double lowerBound, 
							  double upperBound, 
							  double pr,
							  vector<double>& densityLowerBounds, 
							  vector<double>& densityUpperBounds,
							  vector<double>& intervalProbabilities,
							  vector<double>& intervalHeigthInPDF){
	//calculating the interval Heigth in PDF
	double intervalHeigth = pr/(upperBound-lowerBound);
	//searching for the location of the interval
	int nIntervals = densityLowerBounds.size();
	int i=0, nIterations=0;
	bool locationFound = false;
	while(!locationFound && nIterations<nIntervals){
		double upper_i = densityUpperBounds[i];
		if(lowerBound==upper_i){
			locationFound = true;
			i++;
		}
		else if(lowerBound>upper_i)
			i++;
		nIterations++;
	}
	densityLowerBounds.insert(densityLowerBounds.begin()+i, lowerBound);
	densityUpperBounds.insert(densityUpperBounds.begin()+i, upperBound);
	intervalProbabilities.insert(intervalProbabilities.begin()+i, pr);
	intervalHeigthInPDF.insert(intervalHeigthInPDF.begin()+i, intervalHeigth);
}

double* getEqualSpacedProbabilities(int numberOfIntervals, double*& leftIntervalBounds, double*& rigthIntervalBounds, 
									vector<double> leftDensityBounds, vector<double> rigthDensityBounds, vector<double> intervalHeigthInPDF){
	double* equalDensities = new double[numberOfIntervals];
	double min = leftDensityBounds[0];
	double max = rigthDensityBounds[rigthDensityBounds.size()-1];
	double delta = (max-min)/numberOfIntervals;
	for(int i=0; i<numberOfIntervals; i++){
		float left = min+i*delta;
		float rigth = left+delta;
		leftIntervalBounds[i] = left;
		rigthIntervalBounds[i] = rigth;
		equalDensities[i] = 0;
		//searching for the upper limit into respective original density interval
		int r=0;
		while(rigth > rigthDensityBounds[r])
			r++;
		//searching for the lower limit into respective original density interval
		int l=r;
		while(l>=0 && left < leftDensityBounds[l])
			l--;
		//calculating the density into [left, rigth]
		double cumulativePr = 0;
		if(l==r){
			cumulativePr = delta*intervalHeigthInPDF[l];
		}
		else if(l>=0){
			while(l<=r){
				double pr=0;
				if(left>leftDensityBounds[l] && rigth>rigthDensityBounds[l]){
					double basis_l = rigthDensityBounds[l] - left;
					pr = basis_l*intervalHeigthInPDF[l];
					left = rigthDensityBounds[l];
				}
				else if(rigth > rigthDensityBounds[l]){
					double basis_l = rigthDensityBounds[l] - leftDensityBounds[l];
					pr = basis_l*intervalHeigthInPDF[l];
					left = rigthDensityBounds[l];
				}
				else {
					double basis_l = rigth - leftDensityBounds[l];
					pr = basis_l*intervalHeigthInPDF[l];
				}
				cumulativePr += pr;
				l++;
			}
		}
		equalDensities[i] = cumulativePr;
	}
	return equalDensities;
}
double getQuantile(double p, 
				    vector<double>& densityLowerBounds, 
					vector<double>& densityUpperBounds,
					vector<double>& intervalProbabilities){
	double q=0;
	int i=0;
	double F_upper_i = intervalProbabilities[i], F_lower_i = 0;
	while(F_upper_i<p){
		i++;
		F_lower_i = F_upper_i;
		F_upper_i+=intervalProbabilities[i];
	}
	q = densityLowerBounds[i];
	double h = intervalProbabilities[i]/(densityUpperBounds[i]-densityLowerBounds[i]);
	q += (p-F_lower_i)/h;
	return q;
}
double getMode( vector<double>& densityLowerBounds, 
				vector<double>& densityUpperBounds,
				vector<double>& intervalProbabilities,
				vector<double>& intervalHeigthInPDF){
	//CZUBER MODE
	double mode=0;
	int modalInterval=0;
	//double F_upper_i = intervalProbabilities[modalInterval], F_lower_i = 0;
	for(int j=1; j<intervalProbabilities.size(); j++){
		if(intervalHeigthInPDF[modalInterval]<intervalHeigthInPDF[j])
			modalInterval=j;
	}
	mode = densityLowerBounds[modalInterval];
	double modeAmplitude = densityUpperBounds[modalInterval]-densityLowerBounds[modalInterval];
	double delta_a = intervalProbabilities[modalInterval];
	double delta_p = intervalProbabilities[modalInterval];
	if(modalInterval>0)
		delta_a -= modeAmplitude*intervalHeigthInPDF[modalInterval-1];
	if(modalInterval<intervalProbabilities.size()-1)
		delta_p -= modeAmplitude*intervalHeigthInPDF[modalInterval+1];
	mode += modeAmplitude*delta_a/(delta_a+delta_p);
	return mode;
}


//void zoomInto(Node* parent, vec_dbl pr, int answer){
//	static int nAnswers = 0;
//	readLeafs(parent);
//	if(pr[answer]>.5){
//		double answerTime=clock();
//		nAnswers++;
//		double middle = (parent->lower + parent->upper)/2.0;
//		cout<<endl;
//		cout<<nAnswers<<") Eh mais provavel que a variavel pertenca a (0) ["<<parent->lower<<", "<<middle<<"] ou a (1) ["<<middle<<", "<<parent->upper<<"] ? ";
//		cin>>answer	;
//		answerTime=clock();
//		cout<<endl<<"	* Qual nivel de credibilidade voce atribui para sua escolha? ";
//		cin>>pr[answer];
//		pr[1-answer] = 1 - pr[answer];
//		vector<Node*> node(2);
//		node[0] = new Node(parent->lower, middle, pr[0]);
//		node[1] = new Node(middle, parent->upper, pr[1]);
//		parent->addChild(node[0]);
//		parent->addChild(node[1]);
//		zoomInto(node[answer], pr, answer);
//		answerTime-=clock();
//		//judgments_cout<<nAnswers<<") Do you think the quantity most probably belong to (0) ["<<triple[0]<<", "<<triple[1]<<"] or to (1) ["<<triple[1]<<", "<<triple[2]<<"] ?"<<answer;
//		//judgments_cout<<"; answerTime: "<<(-answerTime/CLOCKS_PER_SEC)<<" sec."<<endl;
//		//judgments_cout<<"	, What credibility do you assign to this answer ? "<<pr[answer];		
//		//judgments_cout<<"; answerTime: "<<(-answerTime/CLOCKS_PER_SEC)<<" sec."<<endl;
//	}
//}
void main(){
	//int n = 5;
	//for(double x = 0; x < 10; x+=.05){
	//	long int fat = 1;
	//	double y = 1;
	//	for(int k = 1; k<=n; k++){
	//		fat *= k;
	//		y += pow(x, k)/fat;
	//	}
	//	cout<<x<<"\t"<<y<<endl;
	//}
		char sLower[4000], sUpper[4000], sMiddle[4000];
		double lower_ = -23.0;
		sprintf_s(sLower, "%f" , lower_);
		cout<<sLower<<endl;



	int parameterNature = 0, NUMBER_OF_OPPORTUNITIES=0;
	double unitOfTime = 0;
	cout<<"type the nature of the parameter:"<<endl;
	cout<<"1 for Probability"<<endl;
	cout<<"2 for Number of Occurrences"<<endl;
	cout<<"3 for Rate "<<endl;
	cout<<"4 for Time "<<endl;
	cout<<"5 for General ";
	cin>>parameterNature;
	cout<<endl;
	if(parameterNature == PROBABILITY_ELICITATION){
		judgments_cout<<">>PROBABILITY_ELICITATION"<<endl;
	}
	else if(parameterNature == NUMBER_OF_OCCURRENCES_ELICITATION){
		judgments_cout<<">>NUMBER_OF_OCCURRENCES_ELICITATION"<<endl;
		cout<<"type the number of opportunities: ";
		cin>>NUMBER_OF_OPPORTUNITIES;
		judgments_cout<<">>NUMBER_OF_OPPORTUNITIES = "<<NUMBER_OF_OPPORTUNITIES<<endl;
		cout<<endl;
	}
	else if(parameterNature == RATE_ELICITATION){
		cout<<"type the unit of time: "<<endl;
		cout<<MINUTE_TIME_UNIT<<" for minute"<<endl;
		cout<<HOUR_TIME_UNIT<<" for hour"<<endl;
		cout<<DAY_TIME_UNIT<<" for day "<<endl;
		cout<<MONTH_TIME_UNIT<<" for month "<<endl;
		cout<<YEAR_TIME_UNIT<<" for year ";
		cin>>unitOfTime;
		judgments_cout<<">>RATE_ELICITATION"<<endl;
		judgments_cout<<">>UNIT OF TIME: ";
		if(unitOfTime==MINUTE_TIME_UNIT)
			judgments_cout<<" MINUTE "<<endl;
		else if(unitOfTime==HOUR_TIME_UNIT)
			judgments_cout<<" HOUR "<<endl;
		else if(unitOfTime==DAY_TIME_UNIT)
			judgments_cout<<" DAY "<<endl;
		else if(unitOfTime==MONTH_TIME_UNIT)
			judgments_cout<<" MONTH "<<endl;
		else if(unitOfTime==YEAR_TIME_UNIT)
			judgments_cout<<" YEAR "<<endl;
		cout<<endl;
	}
	else if(parameterNature == TIME_ELICITATION){
		judgments_cout<<">>TIME_ELICITATION"<<endl;
		cout<<"type the unit of time: "<<endl;
		cout<<MINUTE_TIME_UNIT<<" for minute "<<endl;
		cout<<HOUR_TIME_UNIT<<" for hour "<<endl;
		cout<<DAY_TIME_UNIT<<" for day "<<endl;
		cout<<MONTH_TIME_UNIT<<" for month "<<endl;
		cout<<YEAR_TIME_UNIT<<" for year ";
		cin>>unitOfTime;
		judgments_cout<<">>UNIT OF TIME: ";
		if(unitOfTime==MINUTE_TIME_UNIT)
			judgments_cout<<" MINUTE "<<endl;
		else if(unitOfTime==HOUR_TIME_UNIT)
			judgments_cout<<" HOUR "<<endl;
		else if(unitOfTime==DAY_TIME_UNIT)
			judgments_cout<<" DAY "<<endl;
		else if(unitOfTime==MONTH_TIME_UNIT)
			judgments_cout<<" MONTH "<<endl;
		else if(unitOfTime==YEAR_TIME_UNIT)
			judgments_cout<<" YEAR "<<endl;
		cout<<endl;
	}


	double totalTime=clock();

	double lower = 0, upper= 0;
	cout<<"assign the lower bound: "; cin>>lower;
	cout<<"assign the upper bound: "; cin>>upper;		
	int answer = 0;
	vec_dbl pr(2); pr[answer]= 1.0; pr[1-answer] = 1 - pr[answer];//the chose interval was [min, max], with cr=100%
	judgments_cout<<"bounds= ["<<lower<<", "<<upper<<"]"<<endl;
	int nAnswers = 0;
	//Node* root = new Node(lower, upper, pr[0]);
	//Firmino f1(root);

	//zoomInto(parent, pr, answer);


	
	//totalTime-=clock();
	//judgments_cout<<">total time for eliciting: "<<(-totalTime/CLOCKS_PER_SEC)<<" sec."<<endl;

	//cout<<"questao	min	max	pr	partPr	minCpl	maxCpl	prCpl	partPrCpl"<<endl;
	//judgments_cout<<"questão	min	max	pr"<<endl;
	//double partiotionedProb = 1;
	//vector<double> leftDensityBounds(0), rigthDensityBounds(0), probs(0), intervalHeigthInPDF(0);
	//
	//for(int i=0; i<nAnswers && prs[i]>.5; i++){
	//	cout<<(i+1)<<")	"<<lefts[i]<<"	"<<rigths[i]<<"	"<<prs[i]<<"	"<<(partiotionedProb*prs[i])<<"	";
	//	cout<<leftsCpl[i]<<"	"<<rigthsCpl[i]<<"	"<<prsCpl[i]<<"	"<<(partiotionedProb*prsCpl[i])<<endl;

	//	prsCpl[i]*=partiotionedProb;
	//	//ADDING THE COMPLEMENTAR INTERVAL IN AN ORDERED LIST
	//	addIntervalInOrderedList(leftsCpl[i], rigthsCpl[i], prsCpl[i],
	//							leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	//	judgments_cout<<(i+1)<<")	"<<lefts[i]<<"	"<<rigths[i]<<"	"<<prs[i]<<endl;
	//	partiotionedProb *= prs[i];
	//}

	//if(prs[nAnswers-1]<=.5){//removing invalid last answer
	//	//	lefts.erase(lefts.end());
	//	//	rigths.erase(rigths.end());
	//	//	prs.erase(prs.end());
	//	//	leftsCpl.erase(leftsCpl.end());
	//	//	rigthsCpl.erase(rigthsCpl.end());
	//	//	prsCpl.erase(prsCpl.end());
	//	nAnswers--;
	//	//partiotionedProb*=.5;
	//}
	////to update and add the prob of the last valid answer which is not-cpl
	//prs[nAnswers-1]=partiotionedProb;
	//addIntervalInOrderedList(lefts[nAnswers-1], rigths[nAnswers-1], prs[nAnswers-1],
	//						leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	////CALCULATING THE MEAN AND THE VARIANCE
	//double E_X=0, E_X2=0;
	//for(int i=0; i<nAnswers+1; i++){
	//	double v1 = intervalHeigthInPDF[i]/2;
	//	double v2 = pow(rigthDensityBounds[i], 2.0)-pow(leftDensityBounds[i], 2.0);
	//	E_X += v1*v2;
	//	double v3 = intervalHeigthInPDF[i]/3;
	//	double v4 = pow(rigthDensityBounds[i], 3.0)-pow(leftDensityBounds[i], 3.0);
	//	E_X2 += v3*v4;
	//}
	//double VAR_X = E_X2 - pow(E_X, 2.0);
	//double p = .5;
	////CALCULATING THE p QUANTILE
	//double MED_X = getQuantile(p, leftDensityBounds, rigthDensityBounds, probs);
	////saving the MODE
	//double MODE_X = getMode(leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	////PRINTING THE UNDERLING DENSITY
	//judgments_cout<<endl;
	//judgments_cout<<"$$$$ Density $$$$"<<endl;
	//judgments_cout<<"interval	min	max	pr	"<<endl;
	//for(int i=0; i<nAnswers+1; i++){
	//	judgments_cout<<(i+1)<<"\t"<<leftDensityBounds[i]<<"\t"<<rigthDensityBounds[i]<<"\t"<<probs[i]<<endl;
	//}

	////PRINTING THE UNDERLING CDF
	//judgments_cout<<endl;
	//judgments_cout<<"$$$$ CDF $$$$"<<endl;
	//judgments_cout<<"x"<<"\t"<<"Fx"<<endl;
	//double Fx = 0;
	//for(int i=0; i<nAnswers+1; i++){
	//	judgments_cout<<leftDensityBounds[i]<<"\t"<<Fx/*rigthDensityBounds[i]<<"\t"<<probs[i]*/<<endl;
	//	Fx+=probs[i];
	//}
	//judgments_cout<<rigthDensityBounds[nAnswers]<<"\t"<<Fx<<endl;

	////PRINTING THE LOCATION AND SCALING MEASURES
	//judgments_cout<<endl;
	//judgments_cout<<"$$$$ Location and Scaling measures $$$$"<<endl;
	//judgments_cout<<"MEAN"<<"\t"<<"MODE"<<"\t"<<"MEDIAN"<<"\t"<<"DP"<<endl;
	//if(parameterNature == NUMBER_OF_OCCURRENCES_ELICITATION)
	//	judgments_cout<<(E_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(MODE_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(MED_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(pow(VAR_X,.5)/*/(parameterSpaceUppwerBound/100)*/)<<endl;
	//else if(parameterNature == PROBABILITY_ELICITATION)
	//	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	//else if(parameterNature == RATE_ELICITATION){
	//	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	//	judgments_cout<<">> unit of time: "<<unitOfTime<<endl;
	//}
	//else if(parameterNature == TIME_ELICITATION){
	//	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	//}
	//else
	//	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	////PRINTING 95% CREDIBLE INTERVAL
	//cout<<"95% CREDIBLE INTERVAL"<<endl<<getQuantile(.025, leftDensityBounds, rigthDensityBounds, probs)<<'\t';
	//cout<<getQuantile(.975, leftDensityBounds, rigthDensityBounds, probs)<<endl;
	////PERFORMING AGGREGATION OF OPINIONS
	//int numberOfIntervals = 100;
	//double *leftIntervalBounds = new double[numberOfIntervals];
	//double *rigthIntervalBounds = new double[numberOfIntervals];

	//double *equalSpacedDensities = getEqualSpacedProbabilities(numberOfIntervals, leftIntervalBounds, rigthIntervalBounds, 
	//	leftDensityBounds, rigthDensityBounds, intervalHeigthInPDF);

	//judgments_cout<<"$$$$ Equal Spaced Density $$$$"<<endl;
	//judgments_cout<<"interval	min	max	pr	"<<endl;
	//for(int i=0; i<numberOfIntervals; i++){
	//	judgments_cout<<(i+1)<<"\t"<<leftIntervalBounds[i]<<"\t"<<rigthIntervalBounds[i]<<"\t"<<equalSpacedDensities[i]<<endl;
	//}

	//delete (leftIntervalBounds);
	//delete (rigthIntervalBounds);
	//delete (equalSpacedDensities);
	//judgments_cout.close();
	int j;
	  _CrtDumpMemoryLeaks();//to evaluate memory leak
	cin>>j;
}
