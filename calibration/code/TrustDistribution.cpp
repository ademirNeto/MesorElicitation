// This is the main DLL file.

#include "stdafx.h"

#include "CalibrationWrapper.h"
#include "EngineFacade.h"
#include "Miscelanices.h"
#include "../../griddyGibbsSampling/engine/Binomial.h"
//using namespace  CalibrationEngine;

namespace CalibrationEngine {
	using namespace System;
	using namespace Engine;
	using namespace System::Runtime::InteropServices; // for class Marshal

	public ref class TrustDistributionInterface {
	private:
		static const int POINT_NUMBER = 1000;
		static Binomial * _binomial;
		static Multinomial * _multinomial;
		static const String^ BINOMIAL = "BINOMIAL";
		static const String^ DIRAC = "DIRAC";
		static const String^ MULTINOMIAL = "MULTINOMIAL";
		static const String^ NORMAL = "NORMAL";
		static const String^ LOGNORMAL = "LOGNORMAL";
		static const String^ GEOMETRIC = "GEOMETRIC";
		static const String^ POISSON = "POISSON";
		//EngineFacade * ef;
		///static CalibrationInterface^ _instance;
		//static int calMethod = -1;

	protected:
		array<double>^ multiNomialDist(){
			return gcnew array<double>(2); 
		}

		array<double>^ diracDist(){

			return gcnew array<double>(2); 
		}

		array<double>^ GeometricDist(){
			return gcnew array<double>(2); 
		}

	public:

		static char* toChar(System::String^ str)
		{
			char* str2 = (char*)(void*)Marshal::StringToHGlobalAnsi(str);
			Marshal::FreeHGlobal((System::IntPtr)(void*)str2);
			return str2;
			//printf(str2);
		}

		static array<double>^ getDiracTrueDistribution(int corectAlternative, array<String^>^ alternativas/*, array<array<double^>^> */){
			array<double>^ vec_return = gcnew array<double>(1);//TODO: modify to dinamic...

			return vec_return;
		}

		static void /*array<double>^*/ getBinomialTrueDistribution(String^ st_trueDistribution, array<double>^ grid, int nGrid){

		}

		static  void /*array<double>^*/ getGeometricTrueDistribution(String^ st_trueDistribution, array<double>^ grid, int nGrid){

		}

		static array<double>^ getTrueDistribution(array<String^>^ st_dist, array<double>^ para_dist, int para_dist_length , array<double>^ grid, int nGrid, int method, bool isTraining){
			double probability	=0;
			String^ dist_name = st_dist[0]->ToLower();
			int nPoints = nGrid;
			array<double>^ distribution;// = gcnew array<double>(intervals);

			//for(int i; i < intervals; i++)
			//	vec_return[i] = 0;

			if(st_dist[0]->Equals((String^)BINOMIAL)){
				int n = (int)para_dist[0], x=0, i = 1;//
				double p = para_dist[1];
				if(grid[0]>0){
					nPoints++;
					i--;
				}
				if(grid[nGrid-1]<n){
					nPoints++;
				}
				distribution= gcnew array<double>(nPoints);
				_binomial = new Binomial(n, p);
				
				int j=0;
				//[a-b)
				for(;j < nGrid-1; x++){
					probability += exp(_binomial->get_fx(x));
					if(x >= (int)grid[j]){
						distribution[j+i] = probability;
						j++;
						probability = 0;
					}
				}
				//[a-b]
				for(; x <= grid[j]; x++){
					probability += exp(_binomial->get_fx(x));
				}
				distribution[j] = probability;
				probability = 0;
				//(a-b]
				for(; x <= n; x++){
					probability += exp(_binomial->get_fx(x));
				}
				distribution[nPoints-1]= probability;

				return distribution;
			}
			else if("geometrica" == dist_name){ //TODO: Verificar a questão da probabilidade do intervalo -1 e do intervale n, onde -1 esquerda e n à direita.
				int n = (int)para_dist_length;
				double p = para_dist[0];
				distribution = gcnew array<double>(n-1);
				int j = 0;
				int i = 1;
				//double tmp_fx;
				if(para_dist[i] > 1){
					distribution = gcnew array<double>(n);
					//double xMaiorB = pow((1 - p), (int)para_dist[i]-1);
					double xMaiorB = pow((1 - p), 0);
					distribution[j] = 1 - xMaiorB;
					j++;
				}
				for(; i < (n-1); i++){
					double xMaiorA = pow((1 - p), (int)para_dist[i]-1);
					double xMaiorB = pow((1 - p), (int)para_dist[i+1]);
					para_dist[i+1]= para_dist[i+1]+1;
					distribution[j] = xMaiorA - xMaiorB;
					j++;
				}
				
				distribution[j] = pow((1 - p), (int)para_dist[i]-1);
			}
			else if("dirac" == dist_name){

				int correctAlternative  = (int)para_dist[0]; // CorrectAlternative.
				if(method != BISECTION && isTraining){ //Firmino ou Direto treinamento
					distribution = gcnew array<double>(nPoints);
					distribution[correctAlternative] = 1;
				}
				else{

					distribution = gcnew array<double>(nPoints);
					if(correctAlternative == -2){
						distribution[0] = 1;
					}
					else if(correctAlternative == -1){
						distribution[nPoints-1] = 1;
					}
					else{
						distribution[correctAlternative] = 1;
					}
				}
			}
			else if("multinomial" == dist_name){
				distribution = gcnew array<double>(nPoints);
				int n = ((int)para_dist[0]-1);
				double * p = new double(n);
				for(int i=0; i < n; i++){
					p[i] = para_dist[i+1];
				}
				_multinomial = new Multinomial(1, p);

				for(int x=0; x < n; x++){
					distribution[x] = exp(_multinomial->get_fx(x));
				}
			}
			
			return distribution;
		}
	};
};