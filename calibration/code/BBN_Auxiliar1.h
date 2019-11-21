#ifndef BBN_AUXILIAR_H
#define BBN_AUXILIAR_H
#include <math.h>
#include<vector>
#include<iostream>
#include "FLOAT.H"
#include "cdflib.h"

using namespace std;

namespace CalibrationEngine
{
	typedef vector<double> vecDouble;
	typedef vector<double*> vecPontDouble;
	class BBN_Auxiliar { //: public General_Auxiliar{

	public:
		static int maxGeneration;
		static vector<double*> dbl_toDelete;
		static double BOUNDS_COEFICIENT;
		const static int ADDITIVE_ERROR_MODEL = 1;
		const static int MULTIPLICATIVE_ERROR_MODEL = 2;
		const static int ZERO_EXP = -708;
		const static int LOG_ZERO = -742;
		const static int INF_EXP = 710;
		const static char PIECEWISE_TRAPEZOIDAL= 'L';
		const static char PIECEWISE_UNIFORM= 'U';
		//SINGLE MODEL VARIABLES ID FOR HOMOGENEOUS DATA
		const static int UNKNOWN_ID = 1;
		const static int ERROR_LOCATION_ID = 2;//id for: mean or median (location implies in mean or median)
		const static int ERROR_SCALING_ID = 3;//id for: error factor
		const static int ERROR_ID = 4;
		const static int UESTIMATE_ID = 5;

		//SINGLE MODEL VARIABLES ID FOR NON-HOMOGENEOUS DATA
		const static int LOCATION_LOCATION_ID = 6;//id for: location of the location 
		const static int SCALING_LOCATION_ID = 7;//id for: scaling of the location (error factor of the mean/median)
		const static int LOCATION_SCALING_ID = 8;//id for: location of the scaling
		const static int SCALING_SCALING_ID = 9;//id for: scaling of the scaling (error factor of the variance)

		//SINGLE MODEL VARIABLES ID FOR NON-HOMOGENEOUS DATA WITH CONFIDENCE FACTOR
		const static int LOCATION_SCALING_SCALING_ID = 10;//id for: location of the scaling of the scaling (median of the variance of the variance)

		//SINGLE MODEL VARIABLES ID FOR HOMOGENEOUS DATA WITH APPLICABILITY FACTOR
		const static int BETA_ERROR_ID = 11;
		const static int FINAL_ERROR_ID = 12;
		const static int LOCATION_BETA_ERROR_ID = 13;
		const static int SCALING_BETA_ERROR_ID = 14;
		const static int LOCATION_SCALING_BETA_ERROR_ID = 15;

		static double initialSliceSizeMultiplier;
		static double shrinkingRatio;
		static int minAutocorrelationStep;
		static int maxAutocorrelationStep;
		static int BBN_id;
		static bool thereIsModelEstimate, booleanKey;
		static char INF_TYPE;
		static const char	NO_CHANGE_INF= 'N', 
			UPDATE_INF= 'U', 
			RETRACTION_INF= 'R',
			LOG_XOR= 'X',
			LOG_SIMPLE='S',
			LOG_NOR='N';
		static const char	LOCATION_NODE= 'L', 
			SCALING_NODE= 'S';

		static void addSortedSample(vector<double>& sample, double value);

		static double getExp(double x);
		static double getLog(double x);

		static void exportSamples(vector<vecDouble> samplesMatrix);
		static void exportSample(vector<double> sample);
		static void exportDistributionsMatrix(vector<double*> distributionsMatrix, int nIntervals);
		static double getAutocorrelationStatisticForOneStep(vector<double> sample);
		static double getSpectralStatistic(vector<double> sample, double pr1, double pr2);
		static double getSpectralStatistic(const vector<double*> sample, const int index, const double pr1, const double pr2);
		static int getPointLocationByBinarySearch(vector<double*> & sample, int col, double value, int lower, int upper);
		static int getPointLocationByBinarySearch(const vector<double*> sample, const vector<int> ordered_indexes, const int var_index, const double value, int lower, int upper);
		static int getPointLocationByBinarySearch(const vector<double> sample, const double value, int lower, int upper);
		static void inicializeVariables();

		static void removeAutocorrelation(vector<double>& sample, double maxAutocorrelation);
		static void setGammaFunction(double& gamma_x, const double x);
		static void updatePrioris();
		static double getQuantile(const vector<double> x, const vector<double> Fx, double p);
		static double getFx(const vector<double> x, const vector<double> Fx, double value);

		BBN_Auxiliar(void);
		~BBN_Auxiliar(void);
	};
};
#endif;
