//#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "stdlib.h"
#include <string>
#include "EngineFacade.h"
#include "CalFirmino.h"

using namespace std;

//namespace CalibrationEngine{
//
//	/*public ref */class EngineInterface 
//	{
//		static EngineFacade ef;
//		
//	public:
//		
//		static int Somar(int valor1, int valor2){
//			int resultado = valor1 + valor2;
//			//cout << ef.testMethodFacade();
//			return resultado;
//		}
//
//		static void updateCalibrationDistributionFirmino(int decision, int correctAnswer, double credibility){
//			
//			double intervals[] = {.5, .6, .7, .8, .9, 1};
//			//ef.calFirmino->setSubIntervals(5, intervals);
//			//const int n=6, nSubInt = 5;//questions x
////			questao listaquestoes[n];
////			questao question;
//			
//
//			double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
//			/*subinterval subint [nSubInt];
//			for(int i=0; i < nSubInt; i++){
//				subint[i].index = i;
//				subint[i].min = listaValorMaxClasse[i];
//				subint[i].max = listaValorMaxClasse[i+1];
//				subint[i].alpha = 1;
//				subint[i].beta = 1; 
//			}*/
//			
//			//FOR BETA-BERNOULLI	
//			//for(int i=0; i < n; i++){
//			//question.index = i;
//				//question.decision = decicions[i];
//				//question.correctAnswer = correctAnswers[i];
//				//question.credibility = credibilities[i];
//				//int j = getSubintervalIndex(question.credibility);//index of the subinterval related to the credibility assigned by the expert
//			int evidence = 1 - abs(decision - correctAnswer);//a=0 se errou, a=1 se acertou
//				//showUpdatedPerformance_BetaBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a);
//			//ef.calFirmino->updateCalibrationDistribution(evidence, credibility);
////			listaquestoes[i] = question;
//			//}
//
//			//ef.calFirmino->updateCalibrationDistribution(evidence, credibility);
//
//		}
//
//	/*	static double^* getXFirmino(){
//			return (double^*)ef.calFirmino->getX();
//		}*/
//
//		static void updateCalibrationDistributionDireto(int decision, int correctAnswer, double credibility){
//	
//			double intervals[] = {.1, .2, .3, .4, .5, .6, .7, .8, .9, 1};
//			//ef.calFirmino->setSubIntervals(5, intervals);
//			//const int n=6, nSubInt = 5;//questions x
//
//			//int interval_class[5];
//			double listaValorMaxClasse[] = {.5, .6, .7, .8, .9, 1};//estudar nos paper a melhor disposição dos subintervalos (vai entrar no 1º paper - de revisão. Tem que fechar o 1º artigo até 4ª(09/11))
//			/*subinterval subint [nSubInt];
//			for(int i=0; i < nSubInt; i++){
//				subint[i].index = i;
//				subint[i].min = listaValorMaxClasse[i];
//				subint[i].max = listaValorMaxClasse[i+1];
//				subint[i].alpha = 1;
//				subint[i].beta = 1; 
//			} */
//			
//			//FOR BETA-BERNOULLI	
//			//for(int i=0; i < n; i++){
//			//question.index = i;
//				//question.decision = decicions[i];
//				//question.correctAnswer = correctAnswers[i];
//				//question.credibility = credibilities[i];
//				//int j = getSubintervalIndex(question.credibility);//index of the subinterval related to the credibility assigned by the expert
//			int evidence = 1 - abs(decision - correctAnswer);//a=0 se errou, a=1 se acertou
//				//showUpdatedPerformance_BetaBernoulli(/*chosen subinterval*/subint[j], /*evidence*/a);
//			//ef.calFirmino->updateCalibrationDistribution(evidence, credibility);
////			listaquestoes[i] = question;
//			//}
//
//			//ef.calFirmino->updateCalibrationDistribution(evidence, credibility);
//		}
//
//		static double updateCalibrationDistributionBissecao(int decision, int correctAnswer, double credibility){
//			return 0.2;
//		}
//		
//		//static void 
//
//		//static String^ getQuestionInterface(String^ s, double lower, double upper, double cred, int index){
//		//	
//		//	char c[100000];
//		//	string str = getQuestion(c, lower, upper, cred, index);
//		//	return gcnew String(str.c_str());
//		//}
//
//		//static char* toChar(String^ s){
//		//	
//		//	pin_ptr<const wchar_t> wch = PtrToStringChars(s);
//
//		//	// Convert to a char*
//		//	size_t origsize = wcslen(wch) + 1;
//		//	const size_t newsize = 100;
//		//	size_t convertedChars = 0;
//		//	char nstring[newsize];
//		//	wcstombs_s(&convertedChars, nstring, origsize, wch, _TRUNCATE);
//		//	return nstring;
//		//}
//	};
//}
