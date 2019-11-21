// This is the main DLL file.

#include "stdafx.h"

#include "CalibrationWrapper.h"
#include "EngineFacade.h"
#include "Miscelanices.h"
using namespace  CalibrationEngine;

namespace calibrationWrapper {//THE NEW DLL
	using namespace System;
	//using namespace Engine;

	public ref class CalibrationInterface {
	private:
		EngineFacade * ef;
		static CalibrationInterface^ _instance;
		static int calMethod = -1;

		array<double>^ updateCalibrationCurveDistribution(int correctAlternative, array<double>^ credibilities, int numberAlternatives){
			double * _credibilities = new double[numberAlternatives];
			double QSR=1, RQSR = 1;//RQSR: the ranked quadratic scoring rule
			double Pi=0; int Di = 0;
			for(int i = 0; i < numberAlternatives; i++){
				_credibilities[i] = credibilities[i];
				int di=0;
				if(i==correctAlternative)
					di=1;
				QSR -= pow(credibilities[i] - di, 2.0);

				Pi+=credibilities[i];
				Di+=di;
				RQSR -= pow(Pi - Di, 2.0);
			}

			this->ef->calibrationInstance->updateCalibrationCurveDistribution(correctAlternative, _credibilities, numberAlternatives);

			delete [] _credibilities;
			array<double>^ scores = gcnew array<double>(2);
			scores[0] = QSR;
			scores[1] = RQSR;
			return scores;
		}

		void computeGoodnesOfFitSRs(array<double>^  credibilities, array<double>^  trueProbabilities, int nBins){
			this->sr_shiquadrado=1; this->sr_kullback = 1;
			double Ci=0, Ti=0, Di=0;
			for(int i=0; i<nBins; i++){
				this->sr_shiquadrado -= pow(credibilities[i] - trueProbabilities[i], 2.0)/trueProbabilities[i];
				this->sr_kullback -= trueProbabilities[i]*log(trueProbabilities[i]/credibilities[i]);
			}
		}
		void computeSphericalSRs(array<double>^  credibilities, array<double>^  trueProbabilities, array<double>^  diracProbabilities, int nBins){
			this->sr_t_esferico=0; this->sr_t_esfericoOrdenado = 0;
			this->sr_esferico=0;this->sr_esfericoOrdenado=0;
			double Ci=0, Ti=0, Di=0, sumCT=0, sumCD=0, sumC2=0, sumCT_ordered=0, sumCD_ordered=0, sumC2_ordered=0;
			for(int i=0; i<nBins; i++){
				//NOT ORDERED VERSION
				sumCD+=(credibilities[i]*diracProbabilities[i]);
				sumCT+=(credibilities[i]*trueProbabilities[i]);
				sumC2+=(credibilities[i]*credibilities[i]);
				//ORDERED VERSION
				Ci+=credibilities[i];
				Di+=diracProbabilities[i];
				Ti+=trueProbabilities[i];
				sumCD_ordered+=(Ci*Di);
				sumCT_ordered+=(Ci*Ti);
				sumC2_ordered+=(Ci*Ci);
			}
			this->sr_t_esferico=sumCD/pow(sumC2, 0.5);
			this->sr_t_esfericoOrdenado = sumCD_ordered/pow(sumC2_ordered, 0.5);
			this->sr_esferico= sumCT/pow(sumC2, 0.5);
			this->sr_esfericoOrdenado= sumCT_ordered/pow(sumC2_ordered, 0.5);
		}
		void computeLogarithmSRs(array<double>^  credibilities, array<double>^  trueProbabilities, array<double>^  diracProbabilities, int nBins){
			this->sr_t_logaritimico=0; this->sr_t_logaritimicoOrdenado = 0;
			this->sr_logaritimico=0;this->sr_logaritimicoOrdenado=0;
			double Ci=0, Ti=0, Di=0, sumCT=0, sumCD=0, sumCT_ordered=0, sumCD_ordered=0;
			for(int i=0; i<nBins; i++){
				//NOT ORDERED VERSION
				sumCD+=(credibilities[i]*diracProbabilities[i]);
				sumCT+=(credibilities[i]*trueProbabilities[i]);
				//ORDERED VERSION
				Ci+=credibilities[i];
				Di+=diracProbabilities[i];
				Ti+=trueProbabilities[i];
				sumCD_ordered+=(Ci*Di);
				sumCT_ordered+=(Ci*Ti);
			}
			this->sr_t_logaritimico=log(sumCD);
			this->sr_t_logaritimicoOrdenado = log(sumCD_ordered);
			this->sr_logaritimico=log(sumCT);
			this->sr_logaritimicoOrdenado=log(sumCT_ordered);
		}
		void computeQuadractSRs(array<double>^  credibilities, array<double>^  trueProbabilities, array<double>^  diracProbabilities, int nBins){
			this->sr_quadratico=1; this->sr_quadratico_ordenado = 1;
			this->sr_t_quadratico=1;this->sr_t_quadraticoOrdenado=1;
			double Ci=0, Ti=0, Di=0;
			for(int i=0; i<nBins; i++){
				//NOT ORDERED VERSION
				this->sr_quadratico -= pow(credibilities[i] - trueProbabilities[i], 2.0);
				this->sr_t_quadratico -= pow(credibilities[i] - diracProbabilities[i], 2.0);
				//ORDERED VERSION
				Ci+=credibilities[i];
				Ti+=trueProbabilities[i];
				Di+=diracProbabilities[i];
				this->sr_quadratico_ordenado -= pow(Ci - Ti, 2.0);
				this->sr_t_quadraticoOrdenado -= pow(Ci - Di, 2.0);
			}
		}
	protected:
		CalibrationInterface(const int calMethod){
			ef = new EngineFacade(calMethod);
		}
	public:
		static double	sr_t_quadratico	 =-1	;
		static double	sr_t_quadraticoOrdenado	 =-1	;
		static double	sr_t_logaritimico	 =-1	;
		static double	sr_t_logaritimicoOrdenado	 =-1	;
		static double	sr_t_esferico	 =-1	;
		static double	sr_t_esfericoOrdenado	 =-1	;
		static double	sr_quadratico	 =-1	;
		static double	sr_quadratico_ordenado	 =-1	;
		static double	sr_shiquadrado	 =-1	;
		static double	sr_kullback	 =-1	;
		static double	sr_logaritimico	 =-1	;
		static double	sr_logaritimicoOrdenado	 =-1	;
		static double	sr_esferico	 =-1	;
		static double	sr_esfericoOrdenado	 =-1	;
		ref class MethodType {
			public:
				static const int FIRMINO = 1;
				static const int DIRECT = 2;
				static const int BISECTION = 3;
		};
		ref class Score {
			/*static*/	double	sr_quadratico	;
			/*static*/	double	sr_quadratico_ordenado	;
			/*static*/	double	sr_shiquadrado	;
			/*static*/	double	sr_kullback	;
			/*static*/	double	sr_logaritimico	;
			/*static*/	double	sr_esferico	;
			/*static*/	double	sr_t_quadratico	;
			/*static*/	double	sr_t_quadraticoOrdenado	;
			/*static*/	double	sr_t_logaritimico	;
			/*static*/	double	sr_t_esferico	;
			//public Score::Score(){
			//	sr_quadratico	 =-1	;
			//	sr_quadratico_ordenado	 =-1	;
			//	sr_shiquadrado	 =-1	;
			//	sr_kullback	 =-1	;
			//	sr_logaritimico	 =-1	;
			//	sr_esferico	 =-1	;
			//	sr_t_quadratico	 =-1	;
			//	sr_t_quadraticoOrdenado	 =-1	;
			//	sr_t_logaritimico	 =-1	;
			//	sr_t_esferico	 =-1	;
			//}
		};
		static CalibrationInterface^ Instance(const int calMethod){
			if(_instance && _instance->calMethod != calMethod){
				delete _instance;
				_instance = nullptr;
			}
			if(!_instance) {
				_instance = gcnew CalibrationInterface(calMethod);
				_instance->calMethod = calMethod;
			}

			return _instance;
		}

		/*
		the  scores are returned
		*/
		void updateCalibrationCurveDistribution(int correctAlternative, array<double>^ trueProbabilities, array<double>^ credibilities, int numberAlternatives){
			double * _credibilities = new double[numberAlternatives];
			array<double>^ diracProbabilities =  gcnew array<double>(numberAlternatives);
			for(int i = 0; i < numberAlternatives; i++){
				_credibilities[i] = credibilities[i];
				diracProbabilities[i] = 0;
				if(i==correctAlternative)
					diracProbabilities[i]=1;
			}
			this->computeQuadractSRs(credibilities, trueProbabilities, diracProbabilities, numberAlternatives);
			this->computeLogarithmSRs(credibilities, trueProbabilities, diracProbabilities, numberAlternatives);
			this->computeSphericalSRs(credibilities, trueProbabilities, diracProbabilities, numberAlternatives);
			this->computeGoodnesOfFitSRs(credibilities, trueProbabilities, numberAlternatives);
			this->ef->calibrationInstance->updateCalibrationCurveDistribution(correctAlternative, _credibilities, numberAlternatives);//THE ISSUE OF USING realProbabilites FOR CALIBRATING MUST BE STUDIED YET

			delete [] _credibilities;
			array<double>^ scores = gcnew array<double>(2);
			//return scores;
		}

		array<double>^ getGGS_CalibrationParametersQuantile(const double quantile){
			double* q = this->ef->calibrationInstance->getQuantile(quantile);
			array<double>^ quantiles = gcnew array<double>(2);
			for(int i=0; i<2; i++)
				quantiles[i] = q[i];
			return quantiles;
		}

		//int deleteNews(){
		//	//IMPLEMENTAR
		//	delete this->ef->calibrationInstance->;
		//	return 1;
		//}

		char getGGS_CalibrationPattern(){
			//IMPLEMENTAR...
			return this->ef->calibrationInstance->getGGS_CalibrationPattern();
		}
		bool restartCalibrationStudy(){
			return this->ef->calibrationInstance->restartCalibrationStudy();
		}

		//static void getMeasuresFromPDF(array<double>^ grid, array<double>^ cumulative){
		//	int k=nPoints; //double* _x = new double; double* _Fx = cumulative;
		//	
		//	vector<double> x(k), Fx(k);
		//	this->ef->CredibilitysGrid
		//	for(int i=0; i<k; i++){
		//		
		//		//x[i]=grid[i]; Fx[i] = cumulative[i];
		//	}
		//	ef.getStatisticalMeasures(x, Fx, q, k); 
		//}

		//private char* toChar(String^ s){

		//	pin_ptr<const wchar_t> wch = PtrToStringChars(s);

		//	// Convert to a char*
		//	size_t origsize = wcslen(wch) + 1;
		//	const size_t newsize = 100;
		//	size_t convertedChars = 0;
		//	char nstring[newsize];
		//	wcstombs_s(&convertedChars, nstring, origsize, wch, _TRUNCATE);
		//	return nstring;
		//}
	};
};