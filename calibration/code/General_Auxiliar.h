#ifndef GENERAL_AUXILIAR_H
#define GENERAL_AUXILIAR_H
#include<vector>
#include<iostream>
#include <math.h>


using namespace std;
namespace CalibrationEngine{
		class General_Auxiliar{
		
		public:
		static const char	DBBN_NODE= 'D', 
							CBBN_NODE= 'C',
							NORMAL_DENSITY = '0',
							LOGNORMAL_DENSITY = '1',
							GAMMA_DENSITY = '2',
							UNIFORM_DENSITY = '3',
							NONPARAMETRIC_DENSITY = '4',
							Inverse_DENSITY = '5',
							POISSON_DENSITY = '6',
							BINOMIAL_DENSITY = '7',
							DIRAC_DENSITY = '8',
							BETA_DENSITY = '9',
							MIXED_DENSITY = 'B',
							NOMINAL_DISTRIBUTION = 'E',
							EXPONENTIAL_DISTRIBUTION = 'C',
							TRIANGULAR_DENSITY= 'A',
							TRANSFORMED_BETA_DENSITY = 'F',
							BGIW_DENSITY = 'G';
		static int id, maxGeneration;

		static vector<int*> intsToDelete;
		static vector<double*> doublesToDelete;

		static bool addSortedDouble(vector<double>& vec, double value);
		static void setMeanAndVariance(vector<double> x, double & mean,double& var);
		General_Auxiliar(void);
		~General_Auxiliar(void);
		};
}
#endif
