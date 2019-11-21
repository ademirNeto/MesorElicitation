
#ifndef GENERAL_AUXILIAR_H
#define GENERAL_AUXILIAR_H
#include<vector>
#include<iostream>
#include"Node.h"
#include <math.h>


using namespace std;

namespace Engine{

	typedef vector<Node*> vecNodes;
	class General_Auxiliar{

	public:
		static const int ZERO_EXP = -708;
		static const int LOG_ZERO = -742;
		static const int INF_EXP = 710;
		//static const double DBL_MAX = 1.7976931348623158e+308;

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
		//static vector<Node*> nodesToDelete;
		static vector<int*> intsToDelete;
		static vector<double*> doublesToDelete;
		static vector<Node*> rootNodes;
		static vector<Node*> leafNodes;
		static vector<Node*> allNodes;

		static double getLog(double x);
		static double getExp(double x);
		static int getPointLocationByBinarySearch(const vector<double> sample, const double value, int lower, int upper);
		static bool addSortedNodes(vector<Node*>& vec, Node* node);
		static bool addSortedDouble(vector<double>& vec, double value);
		static void deleteNews();
		static void eliminateAllNodes();
		static void inicializeVariables();
		static	void readDensities();
		static void readVecNodes();
		static void readVecClonedUNodes();
		static bool removeSortedNodes(vector<Node*>& vec, Node* node);
		static void setMeanAndVariance(vector<double> x, double & mean,double& var);
		General_Auxiliar(void);
		~General_Auxiliar(void);
	};
}
#endif
