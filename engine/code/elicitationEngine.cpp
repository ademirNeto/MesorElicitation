#include "stdafx.h"

#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>//to print out
#include ".\Node.h"
#include ".\Firmino.h"
#include ".\DLL_Facade.cpp"

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
ofstream cout_questions("questions.txt", ios::out);
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

//struct UF{
//	string nome;	string região;	string capital;	int população_2010;	double area;	double densidDemogr;	
//	int nMunicipios;	double latitude;	double longitude;
//
//	void loadData(string p_nome,	string p_região,	string p_capital,	int p_população_2010,	double p_area,
//				double p_densidDemogr,	int p_nMunicipios,	double p_latitude,	double p_longitude){
//		nome=p_nome;	região=p_região; capital=p_capital; população_2010=p_população_2010;	area=p_area;
//		densidDemogr=p_densidDemogr; nMunicipios=p_nMunicipios; latitude=p_latitude; longitude=p_longitude;
//	}
//};
//
struct Mcomp{
	string sn;//Name of the series
	int n;//The number of observations in the time series
	int h;//The number of required forecasts
	double* x;//A time series of length n (the historical data)
	double* xx;//A time series of length h (the future data)
};
void loadForecastingQuestions(){
	//the states and districts are in increasing order, for every variable
	Mcomp N0113;
//	N0113.h
}
void loadQuestions(string key, const int nStates, const int nQuestions, char* states[]){
	static int questionIndex=0;
	int begin = 0, end = 26, distance = 1, middle = nStates/2, m2 = end/2, m1 = m2, aux1=-1, aux2=1;
	vector<string> question(nQuestions);
	for(int i=0; i<nQuestions; i++){
		vector<int> index(nStates);
		for(int j=0; j<middle; j++){
			index[j]=begin;
			index[nStates-j-1] = end;
			if (nStates==3){
				if(i%2==0){
					if(m1+aux1<=begin || m1+aux1>=end){
						aux1*=(-1);
					}
					m1+=aux1; index[middle] = m1; 
				}else{
					if(m2+aux2<=begin || m2+aux2>=end){
						aux2*=(-1);
					}
					m2+=aux2; index[middle] = m2; 
				}
			}
			begin += distance;
			end -= distance;
		}
		question[i] = key; 
		int indMax = -1;
		for(int j=0; j<nStates; j++){
			double u = ((double)rand()/RAND_MAX);
			int sortedIndex = u*index.size(); 
			question[i] += "\t"; question[i] += states[index[sortedIndex]]; 
			if(index[sortedIndex] > indMax)
				indMax = index[sortedIndex];
			cout<<index[sortedIndex]<<", ";
			index.erase(index.begin()+sortedIndex);
		}
		questionIndex++; cout_questions<<questionIndex<<"\t "<<question[i]<<"\t<answer: "<<states[indMax]<<">"<<endl;			
		cout<<endl;
		index.clear();
	}
}
void loadQuestions(){
	//the states and districts are in increasing order, for every variable
	char* population []= {"Roraima", "Amapa", "Acre", "Tocantins", "Rondonia", "Sergipe", "Mato Grosso do Sul", "Distrito Federal", "Mato Grosso", "Piaui", "Alagoas", "Rio Grande do Norte", "Amazonas", "Espirito Santo", "Paraiba", "Goias", "Santa Catarina", "Maranhao", "Para", "Ceara", "Pernambuco", "Parana", "Rio Grande do Sul", "Bahia", "Rio de Janeiro", "Minas Gerais", "Sao Paulo"};
	char* area []= {"Distrito Federal", "Sergipe", "Alagoas", "Rio de Janeiro", "Espirito Santo", "Rio Grande do Norte", "Paraiba", "Santa Catarina", "Pernambuco", "Amapa", "Ceara", "Acre", "Parana", "Roraima", "Rondonia", "Sao Paulo", "Piaui", "Rio Grande do Sul", "Tocantins", "Maranhao", "Goias", "Mato Grosso do Sul", "Bahia", "Minas Gerais", "Mato Grosso", "Para", "Amazonas"};
	char* nMunic[] = {"Distrito Federal", "Roraima", "Amapa", "Acre", "Rondonia", "Amazonas", "Sergipe", "Espirito Santo", "Mato Grosso do Sul", "Rio de Janeiro", "Alagoas", "Tocantins", "Mato Grosso", "Para", "Rio Grande do Norte", "Ceara", "Pernambuco", "Maranhao", "Paraiba", "Piaui", "Goias", "Santa Catarina", "Parana", "Bahia", "Rio Grande do Sul", "Sao Paulo", "Minas Gerais"};
	char* latitude []= {"Porto Alegre (Rio Grande do Sul)", "Florianopolis (Santa Catarina)", "Curitiba (Parana)", "Sao Paulo (Sao Paulo)", "Rio de Janeiro (Rio de Janeiro)", "Campo Grande (Mato Grosso do Sul)", "Vitoria (Espirito Santo)", "Belo Horizonte (Minas Gerais)", "Goiânia (Goias)", "Brasilia (Distrito Federal)", "Cuiaba (Mato Grosso)", "Salvador (Bahia)", "Aracaju (Sergipe)", "Palmas (Tocantins)", "Rio Branco (Acre)", "Maceio (Alagoas)", "Porto Velho (Rondonia)", "Recife (Pernambuco)", "Joao Pessoa (Paraiba)", "Natal (Rio Grande do Norte)", "Teresina (Piaui)", "Fortaleza (Ceara)", "Manaus (Amazonas)", "Sao Luis (Maranhao)", "Belém (Para)", "Macapa (Amapa)", "Boa Vista (Roraima)"};
	char* longititude[] = {"Rio Branco (Acre)", "Porto Velho (Rondonia)", "Boa Vista (Roraima)", "Manaus (Amazonas)", "Cuiaba (Mato Grosso)", "Campo Grande (Mato Grosso do Sul)", "Porto Alegre (Rio Grande do Sul)", "Macapa (Amapa)", "Curitiba (Parana)", "Goiânia (Goias)", "Florianopolis (Santa Catarina)", "Belém (Para)", "Palmas (Tocantins)", "Brasilia (Distrito Federal)", "Sao Paulo (Sao Paulo)", "Sao Luis (Maranhao)", "Belo Horizonte (Minas Gerais)", "Rio de Janeiro (Rio de Janeiro)", "Teresina (Piaui)", "Vitoria (Espirito Santo)", "Fortaleza (Ceara)", "Salvador (Bahia)", "Aracaju (Sergipe)", "Maceio (Alagoas)", "Natal (Rio Grande do Norte)", "Recife (Pernambuco)", "Joao Pessoa (Paraiba)"};

	string keyBinPopulation = "Qual dos Estados eh mais populoso? Qual nivel de credibilidade voce atribui a sua resposta?";
	string keyBinArea = "Qual dos Estados tem maior area? Qual nivel de credibilidade voce atribui a sua resposta?";
	string keyBinNMun = "Qual dos Estados tem mais municipios? Qual nivel de credibilidade voce atribui a sua resposta?";
	string keyBinLat = "Qual das Capitais eh mais ao Norte? Qual nivel de credibilidade voce atribui a sua resposta?";
	string keyBinLong = "Qual das Capitais eh mais ao Leste? Qual nivel de credibilidade voce atribui a sua resposta?";

	string keyMultPopulation = "Para cada um dos Estados, atribua a sua credibilidade sobre ele ser o mais populoso do grupo:";
	string keyMultArea = "Para cada um dos Estados, atribua a sua credibilidade sobre ele ser o com maior area do grupo:";
	string keyMultNMun = "Para cada um dos Estados, atribua a sua credibilidade sobre ele ser o com mais municípios do grupo:";
	string keyMultLat = "Para cada uma das Capitais, atribua a sua credibilidade sobre ela ser a mais ao Norte do grupo:";
	string keyMultLong = "Para cada uma das Capitais, atribua a sua credibilidade sobre ela ser a mais ao Leste do grupo:";

	int nQuestions = 13;

	loadQuestions(keyBinPopulation, 2, nQuestions, population);
	loadQuestions(keyBinArea, 2, nQuestions, area);
	loadQuestions(keyBinNMun, 2, nQuestions, nMunic);
	loadQuestions(keyBinLat, 2, nQuestions, latitude);
	loadQuestions(keyBinLong, 2, nQuestions, longititude);

	loadQuestions(keyMultPopulation, 3, nQuestions, population);
	loadQuestions(keyMultArea, 3, nQuestions, area);
	loadQuestions(keyMultNMun, 3, nQuestions, nMunic);
	loadQuestions(keyMultLat, 3, nQuestions, latitude);
	loadQuestions(keyMultLong, 3, nQuestions, longititude);

}

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
void testBinary(const char METHOD){
	double x[] = {0, 1};
	double center = (x[0]+x[1])/2.0;
	int answer = 0, n=1;
	String^ q1 = EngineInterface::getNextBinaryQuestion(x[0], center, x[1], 1, -1, METHOD);
	if(METHOD==EngineInterface::FIRMINO){
		for (int i=0; i<n; i++){
			int index = i%2+1;
			double center = (x[0]+x[1])/2;
			q1 = EngineInterface::getNextBinaryQuestion(x[0], center, x[1], .51, index, METHOD);
			//string st = EngineInterface::toChar(q1);
			//cout<<st<<endl;
			x[1-index] = center;
		}
		EngineInterface::deleteChildren(.5, .75, 1); //não deve mais ser chamado da interface
		q1 = EngineInterface::getNextBinaryQuestion(0, .5, 1, .51, 0, METHOD);
	}
	else if (METHOD==EngineInterface::BISECTION){
		srand((int)clock());
		float u = 0;
		wchar_t comma = ';';
		for (int i=0; i<3; i++){
			u = .5;//(float)rand()/RAND_MAX;
			center = x[0] + u*(x[1]-x[0]);
			q1 = EngineInterface::getNextBinaryQuestion(x[0], center, x[1], 0.5, 2, METHOD);
			//cli::array<System::String^>^ list = q1->Split(comma);
			//for(int j=0; j<2; j++)
				//x[j] = System::Convert::ToDouble(list[j]);
			x[0] = EngineInterface::nextLower;
			x[1] = EngineInterface::nextUpper;
		}
		EngineInterface::deleteChildren(.5, .75, 1);
		EngineInterface::deleteChildren(.0, .25, .5);
	}

	EngineInterface::deleteNews();

	//String^ q = "T";
	//String^ q1 = EngineInterface::getFirminoQuestion(lower, upper, 1, -1);
	////string st = EngineInterface::toChar(q1);
	////cout<<st<<endl;

	//lower = (lower+upper)/2.0;
	//String^ q2 = EngineInterface::getFirminoQuestion(lower, upper, .8, 1);
	////st = EngineInterface::toChar(q2);
	////cout<<st<<endl;

	//lower = (lower+upper)/2.0;
	//String^ q3 = EngineInterface::getFirminoQuestion(lower, upper, .8, 1);
	////st = EngineInterface::toChar(q3);
	////cout<<st<<endl;




	////int parameterNature = 0, NUMBER_OF_OPPORTUNITIES=0;
	////double unitOfTime = 0;
	////cout<<"type the nature of the parameter:"<<endl;
	////cout<<"1 for Probability"<<endl;
	////cout<<"2 for Number of Occurrences"<<endl;
	////cout<<"3 for Rate "<<endl;
	////cout<<"4 for Time "<<endl;
	////cout<<"5 for General ";
	////cin>>parameterNature;
	////cout<<endl;
	////if(parameterNature == PROBABILITY_ELICITATION){
	////	judgments_cout<<">>PROBABILITY_ELICITATION"<<endl;
	////}
	////else if(parameterNature == NUMBER_OF_OCCURRENCES_ELICITATION){
	////	judgments_cout<<">>NUMBER_OF_OCCURRENCES_ELICITATION"<<endl;
	////	cout<<"type the number of opportunities: ";
	////	cin>>NUMBER_OF_OPPORTUNITIES;
	////	judgments_cout<<">>NUMBER_OF_OPPORTUNITIES = "<<NUMBER_OF_OPPORTUNITIES<<endl;
	////	cout<<endl;
	////}
	////else if(parameterNature == RATE_ELICITATION){
	////	cout<<"type the unit of time: "<<endl;
	////	cout<<MINUTE_TIME_UNIT<<" for minute"<<endl;
	////	cout<<HOUR_TIME_UNIT<<" for hour"<<endl;
	////	cout<<DAY_TIME_UNIT<<" for day "<<endl;
	////	cout<<MONTH_TIME_UNIT<<" for month "<<endl;
	////	cout<<YEAR_TIME_UNIT<<" for year ";
	////	cin>>unitOfTime;
	////	judgments_cout<<">>RATE_ELICITATION"<<endl;
	////	judgments_cout<<">>UNIT OF TIME: ";
	////	if(unitOfTime==MINUTE_TIME_UNIT)
	////		judgments_cout<<" MINUTE "<<endl;
	////	else if(unitOfTime==HOUR_TIME_UNIT)
	////		judgments_cout<<" HOUR "<<endl;
	////	else if(unitOfTime==DAY_TIME_UNIT)
	////		judgments_cout<<" DAY "<<endl;
	////	else if(unitOfTime==MONTH_TIME_UNIT)
	////		judgments_cout<<" MONTH "<<endl;
	////	else if(unitOfTime==YEAR_TIME_UNIT)
	////		judgments_cout<<" YEAR "<<endl;
	////	cout<<endl;
	////}
	////else if(parameterNature == TIME_ELICITATION){
	////	judgments_cout<<">>TIME_ELICITATION"<<endl;
	////	cout<<"type the unit of time: "<<endl;
	////	cout<<MINUTE_TIME_UNIT<<" for minute "<<endl;
	////	cout<<HOUR_TIME_UNIT<<" for hour "<<endl;
	////	cout<<DAY_TIME_UNIT<<" for day "<<endl;
	////	cout<<MONTH_TIME_UNIT<<" for month "<<endl;
	////	cout<<YEAR_TIME_UNIT<<" for year ";
	////	cin>>unitOfTime;
	////	judgments_cout<<">>UNIT OF TIME: ";
	////	if(unitOfTime==MINUTE_TIME_UNIT)
	////		judgments_cout<<" MINUTE "<<endl;
	////	else if(unitOfTime==HOUR_TIME_UNIT)
	////		judgments_cout<<" HOUR "<<endl;
	////	else if(unitOfTime==DAY_TIME_UNIT)
	////		judgments_cout<<" DAY "<<endl;
	////	else if(unitOfTime==MONTH_TIME_UNIT)
	////		judgments_cout<<" MONTH "<<endl;
	////	else if(unitOfTime==YEAR_TIME_UNIT)
	////		judgments_cout<<" YEAR "<<endl;
	////	cout<<endl;
	////}


	////double totalTime=clock();

	////totalTime-=clock();
	////judgments_cout<<">total time for eliciting: "<<(-totalTime/CLOCKS_PER_SEC)<<" sec."<<endl;

	////cout<<"questao	min	max	pr	partPr	minCpl	maxCpl	prCpl	partPrCpl"<<endl;
	////judgments_cout<<"questão	min	max	pr"<<endl;
	////double partiotionedProb = 1;
	////vector<double> leftDensityBounds(0), rigthDensityBounds(0), probs(0), intervalHeigthInPDF(0);
	////
	////for(int i=0; i<nAnswers && prs[i]>.5; i++){
	////	cout<<(i+1)<<")	"<<lefts[i]<<"	"<<rigths[i]<<"	"<<prs[i]<<"	"<<(partiotionedProb*prs[i])<<"	";
	////	cout<<leftsCpl[i]<<"	"<<rigthsCpl[i]<<"	"<<prsCpl[i]<<"	"<<(partiotionedProb*prsCpl[i])<<endl;

	////	prsCpl[i]*=partiotionedProb;
	////	//ADDING THE COMPLEMENTAR INTERVAL IN AN ORDERED LIST
	////	addIntervalInOrderedList(leftsCpl[i], rigthsCpl[i], prsCpl[i],
	////							leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	////	judgments_cout<<(i+1)<<")	"<<lefts[i]<<"	"<<rigths[i]<<"	"<<prs[i]<<endl;
	////	partiotionedProb *= prs[i];
	////}

	////if(prs[nAnswers-1]<=.5){//removing invalid last answer
	////	//	lefts.erase(lefts.end());
	////	//	rigths.erase(rigths.end());
	////	//	prs.erase(prs.end());
	////	//	leftsCpl.erase(leftsCpl.end());
	////	//	rigthsCpl.erase(rigthsCpl.end());
	////	//	prsCpl.erase(prsCpl.end());
	////	nAnswers--;
	////	//partiotionedProb*=.5;
	////}
	//////to update and add the prob of the last valid answer which is not-cpl
	////prs[nAnswers-1]=partiotionedProb;
	////addIntervalInOrderedList(lefts[nAnswers-1], rigths[nAnswers-1], prs[nAnswers-1],
	////						leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	//////CALCULATING THE MEAN AND THE VARIANCE
	////double E_X=0, E_X2=0;
	////for(int i=0; i<nAnswers+1; i++){
	////	double v1 = intervalHeigthInPDF[i]/2;
	////	double v2 = pow(rigthDensityBounds[i], 2.0)-pow(leftDensityBounds[i], 2.0);
	////	E_X += v1*v2;
	////	double v3 = intervalHeigthInPDF[i]/3;
	////	double v4 = pow(rigthDensityBounds[i], 3.0)-pow(leftDensityBounds[i], 3.0);
	////	E_X2 += v3*v4;
	////}
	////double VAR_X = E_X2 - pow(E_X, 2.0);
	////double p = .5;
	//////CALCULATING THE p QUANTILE
	////double MED_X = getQuantile(p, leftDensityBounds, rigthDensityBounds, probs);
	//////saving the MODE
	////double MODE_X = getMode(leftDensityBounds, rigthDensityBounds, probs, intervalHeigthInPDF);

	//////PRINTING THE UNDERLING DENSITY
	////judgments_cout<<endl;
	////judgments_cout<<"$$$$ Density $$$$"<<endl;
	////judgments_cout<<"interval	min	max	pr	"<<endl;
	////for(int i=0; i<nAnswers+1; i++){
	////	judgments_cout<<(i+1)<<"\t"<<leftDensityBounds[i]<<"\t"<<rigthDensityBounds[i]<<"\t"<<probs[i]<<endl;
	////}

	//////PRINTING THE UNDERLING CDF
	////judgments_cout<<endl;
	////judgments_cout<<"$$$$ CDF $$$$"<<endl;
	////judgments_cout<<"x"<<"\t"<<"Fx"<<endl;
	////double Fx = 0;
	////for(int i=0; i<nAnswers+1; i++){
	////	judgments_cout<<leftDensityBounds[i]<<"\t"<<Fx/*rigthDensityBounds[i]<<"\t"<<probs[i]*/<<endl;
	////	Fx+=probs[i];
	////}
	////judgments_cout<<rigthDensityBounds[nAnswers]<<"\t"<<Fx<<endl;

	//////PRINTING THE LOCATION AND SCALING MEASURES
	////judgments_cout<<endl;
	////judgments_cout<<"$$$$ Location and Scaling measures $$$$"<<endl;
	////judgments_cout<<"MEAN"<<"\t"<<"MODE"<<"\t"<<"MEDIAN"<<"\t"<<"DP"<<endl;
	////if(parameterNature == NUMBER_OF_OCCURRENCES_ELICITATION)
	////	judgments_cout<<(E_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(MODE_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(MED_X/*/NUMBER_OF_OPPORTUNITIES*/)<<"\t"<<(pow(VAR_X,.5)/*/(parameterSpaceUppwerBound/100)*/)<<endl;
	////else if(parameterNature == PROBABILITY_ELICITATION)
	////	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	////else if(parameterNature == RATE_ELICITATION){
	////	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	////	judgments_cout<<">> unit of time: "<<unitOfTime<<endl;
	////}
	////else if(parameterNature == TIME_ELICITATION){
	////	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	////}
	////else
	////	judgments_cout<<(E_X)<<"\t"<<(MODE_X)<<"\t"<<(MED_X)<<"\t"<<(pow(VAR_X,.5))<<endl;
	//////PRINTING 95% CREDIBLE INTERVAL
	////cout<<"95% CREDIBLE INTERVAL"<<endl<<getQuantile(.025, leftDensityBounds, rigthDensityBounds, probs)<<'\t';
	////cout<<getQuantile(.975, leftDensityBounds, rigthDensityBounds, probs)<<endl;
	//////PERFORMING AGGREGATION OF OPINIONS
	////int numberOfIntervals = 100;
	////double *leftIntervalBounds = new double[numberOfIntervals];
	////double *rigthIntervalBounds = new double[numberOfIntervals];

	////double *equalSpacedDensities = getEqualSpacedProbabilities(numberOfIntervals, leftIntervalBounds, rigthIntervalBounds, 
	////	leftDensityBounds, rigthDensityBounds, intervalHeigthInPDF);

	////judgments_cout<<"$$$$ Equal Spaced Density $$$$"<<endl;
	////judgments_cout<<"interval	min	max	pr	"<<endl;
	////for(int i=0; i<numberOfIntervals; i++){
	////	judgments_cout<<(i+1)<<"\t"<<leftIntervalBounds[i]<<"\t"<<rigthIntervalBounds[i]<<"\t"<<equalSpacedDensities[i]<<endl;
	////}

	////delete (leftIntervalBounds);
	////delete (rigthIntervalBounds);
	////delete (equalSpacedDensities);
	////judgments_cout.close();
}
void testDirectMethod(){
	double lower = 0, upper= 1; 
	int k = 6;
	array<double>^ x=   {0, .2, .4, .6, .8, 1};
	array<double>^ Fx = {0, 0, .3, .6, .9, 1};
	String^ q = EngineInterface::getMeasuresFromPDF(x, Fx, k);
	int hj=4;
}
//void composingQuestionnaire(){
//	vector<string> key(7);
//	string q1 = "Qual das capitais ";
//	int i=-1;
//	i++;key[i] = "é mais populosa?";
//	i++;key[i] = "é maior em área?";
//	i++;key[i] = "é mais ao Norte?";
//	i++;key[i] = "é mais ao Oeste?";
//	vector<UF> estado (27);
//	estado[0].loadData("Sergipe","Nordeste","Aracaju",2068017,21918.354, 94.35 ,75,-10.54,-37.04);
//	estado[1].loadData("Pará","Norte","Belém",7581051,1247950.003, 6.07 ,143,-1.27,-48.3);
//	estado[2].loadData("Minas Gerais","Sudeste","Belo Horizonte",19597330,586520.368, 33.41 ,853,-19.55,-43.56);
//	estado[3].loadData("Roraima","Norte","Boa Vista",450479,224301.04, 2.01 ,15,2.49,-60.4);
//	estado[4].loadData("Distrito Federal","Centro-Oeste","Brasília",2570160,5787.784, 444.07 ,1,-15.46,-47.55);
//	estado[5].loadData("Mato Grosso do Sul","Centro-Oeste","Campo Grande",2449024,357145.836, 6.86 ,78,-20.26,-54.38);
//	estado[6].loadData("Mato Grosso","Centro-Oeste","Cuiabá",3035122,903329.7, 3.36 ,141,-15.35,-56.05);
//	estado[7].loadData("Paraná","Sul","Curitiba",10444526,199316.694, 52.40 ,399,-25.25,-49.16);
//	estado[8].loadData("Santa Catarina","Sul","Florianópolis",6248436,95703.487, 65.29 ,293,-27.35,-48.32);
//	estado[9].loadData("Ceará","Nordeste","Fortaleza",8452381,148920.538, 56.76 ,184,-3.43,-38.32);
//	estado[10].loadData("Goiás","Centro-Oeste","Goiânia",6003788,340103.467, 17.65 ,246,-16.4,-49.15);
//	estado[11].loadData("Paraíba","Nordeste","João Pessoa",3766528,56469.466, 66.70 ,223,-7.06,-34.51);
//	estado[12].loadData("Amapá","Norte","Macapá",669526,142827.897, 4.69 ,16,0.02,-51.03);
//	estado[13].loadData("Alagoas","Nordeste","Maceió",3120494,27779.343, 112.33 ,102,-9.39,-35.44);
//	estado[14].loadData("Amazonas","Norte","Manaus",3483985,1559161.682, 2.23 ,62,-3.06,-60.01);
//	estado[15].loadData("Rio Grande do Norte","Nordeste","Natal",3168027,52810.699, 59.99 ,167,-5.47,-35.12);
//	estado[16].loadData("Tocantins","Norte","Palmas",1383445,277621.858, 4.98 ,139,-10.12,-48.21);
//	estado[17].loadData("Rio Grande do Sul","Sul","Porto Alegre",10693929,268781.896, 39.79 ,496,-30.01,-51.13);
//	estado[18].loadData("Rondônia","Norte","Porto Velho",1562409,237590.864, 6.58 ,52,-8.45,-63.54);
//	estado[19].loadData("Pernambuco","Nordeste","Recife",8796448,98146.315, 89.63 ,185,-8.03,-34.52);
//	estado[20].loadData("Acre","Norte","Rio Branco",733559,164122.28, 4.47 ,22,-9.58,-67.48);
//	estado[21].loadData("Rio de Janeiro","Sudeste","Rio de Janeiro",15989929,43780.157, 365.23 ,92,-22.54,-43.12);
//	estado[22].loadData("Bahia","Nordeste","Salvador",14016906,564830.859, 24.82 ,417,-12.58,-38.3);
//	estado[23].loadData("Maranhão","Nordeste","São Luis",6574789,331935.507, 19.81 ,217,-2.31,-44.18);
//	estado[24].loadData("São Paulo","Sudeste","São Paulo",41262199,248196.96, 166.25 ,645,-23.32,-46.38);
//	estado[25].loadData("Piauí","Nordeste","Teresina",3118360,251576.644, 12.40 ,224,-5.05,-42.48);
//	estado[26].loadData("Espírito Santo","Sudeste","Vitória",3514952,46098.571, 76.25 ,78,-20.19,-40.2);
//	}
void main(){
	//	composingQuestionnaire();
	//estado[0].area = ;estado[0].capital=; estado[0].densidDemogr; estado[0].index; estado[0].latitude; estado[0].longitude; estado[0].nMunicipios; estado[0].nome; estado[0].população_2010; estado[0].região
	//int n=3;
	//array<double>^ x = {0, .5, 1};//String^ xFx="0;1;2;3;4;5"; int n=3;
	//EngineInterface::getMeasuresFromCDF(xFx, n);
	//loadQuestions();

	//testDirectMethod();
	//testBinary(EngineInterface::BISECTION/*, .8*/);

	//	testBinary(EngineInterface::FIRMINO);
	double x[] = {0, 1};
	int answer = 0, n=1;
	String^ q1 = EngineInterface::getNextBinaryQuestion(x[0], .5, x[1], 1, -1, EngineInterface::BISECTION);
	q1 = EngineInterface::getNextBinaryQuestion(x[0], .25, x[1], 1, 0, EngineInterface::BISECTION);
	EngineInterface::deleteChildren(0, .125, .25); //não deve mais ser chamado da interface
	q1 = EngineInterface::getNextBinaryQuestion(x[0], .35, x[1], 1, 0, EngineInterface::BISECTION);

	int gj;
	_CrtDumpMemoryLeaks();//to evaluate memory leak
	cin >> gj;
}
