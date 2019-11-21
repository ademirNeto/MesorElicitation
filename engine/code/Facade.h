#include "stdafx.h"

////#ifndef INTERFACE_H
////#define INTERFACE_H
//#include<iostream>
//#include<string>
//#include<vector>
//#include "ET_Node.h"
//#include "FT_Auxiliar.h"
//#include "BBN_Auxiliar.h"
//#include "ET_BDD.h"
//#include "FT_BDD.h"
//#include "FT_Node.h"
//#include "Gamma.h"
//#include "Dirac.h"
//#include "Exponential.h"
//#include "Lognormal.h"
//#include "Uniform.h"
//#include "Triangular.h"
//#include "Weibull.h"
//#include "NonParametricProbabilityDistribution.h"
//
//
//namespace BDD_Engine{
//	typedef vector<string> vec_str;
//
//	class Facade{
//	private:
//		vector<vec_str> cuts;
//		vector<double> probs;
//		ET_Node* initiator;
//		//ET_Node* Failure;
//		string ET_domain;
//		ET_BDD*  et_bdd;
//		vector<ET_Node*> et_nodes, et_nodesToSolveFTs, et_nodesToSolveBBNs, et_endStates;
//		vector<FT_Node*> ft_nodes, ft_nodesToSolveBBNs;//ft_nodesAux1, ft_nodesAux2, ;
//		vector<BBN_DNode*> bbn_nodes;
//		vector<Density*> densities, beDensities;
//		int searchedIndex;
//		bool hasBeenInitialized;
//		bool belongsToBBNNodes(vector<BBN_DNode*>& vec, string nodeLabel);
//		bool belongsToESDNodes(vector<ET_Node*>& vec, string nodeLabel);
//		bool belongsToFTNodes(vector<FT_Node*>& vec, string nodeLabel);
//		bool belongsToDensities(vector<Density*>& vec, string densityLabel);
//		int elaborate_k_out_n_gate(int k, const vector<string> children, vector<string>& andChildren, int* indexes);
//		double getSimulationTime(double tLower, double tUpper, ET_Node* top, const double unreliability);
//		void initializeTerminals();
//		void updateBBNDomain(BBN_DNode* bbn, string domain);
//	public:
//		ET_Node* getET_node(string et_nodeLabel);
//		BBN_DNode* getBBN_node(string bbn_nodeLabel);
//		FT_Node* getFT_node(string ft_nodeLabel);
//		Density* getDensity(string densityLabel);
//		const static int FT_OR = 1;
//		const static int FT_AND = 2;
//		const static int FT_BASIC = 4;
//
//		//DENSITIES CODES
//		static const int	DIRAC_DENSITY = 0;
//		static const int	EXPONENTIAL_DENSITY = 2;
//		static const int	GAMMA_DENSITY = 4;
//		static const int	LOGNORMAL_DENSITY = 6;
//		static const int	NONPARAMETRIC_DENSITY = 10;
//		static const int	NORMAL_DENSITY = 12;
//		static const int	TRIANGULAR_DENSITY = 14;
//		static const int	UNIFORM_DENSITY = 16;
//		static const int	WEIBULL_DENSITY = 18;
//		static const int	NON_PARAMETRIC_DISCRETE_DENSITY = 19;
//
//		vector<string> terminalsLabels;
//		int addBBNNode(const string &BBN_nodeLabel, const vector<string>& states, const vector<string>& parents, const vector<double> &cpt);
//		int addBENode(const string &BE_nodeLabel, const int& DENSITY_CODE, const vector<double>& parameters);
//		int addBENode(const string &BE_nodeLabel, const int& DENSITY_CODE, const vector<string>& parameters);
//		int addBENode(const string &BE_nodeLabel, double FT_nodeProb);
//		int addBENode(const string &BE_nodeLabel, const string &postulatedBBN);
//		int addBENode(const string &BE_nodeLabel, const string &postulatedBBN, const string &BBN_levelNameToLink);
//		int addBlockNode(const string& blockNodeLabel, const vector<string>& nextBlockNodes, const int k_out, const string k_out_n_switchNode);
//		int addDensity(const string& densityLabel, const int& DENSITY_CODE, const vector<double>& parameters);
//		int addESDMultiNode(const string &ESD_nodeLabel, const string &postulatedBBN, const vector<string>& branches);
//		int addESDMultiNode(const string &ESD_nodeLabel, const string &postulatedBBN, const vector<string>& branches, const string BBN_levelNameToLink);
//		int addESDNode(const string& ESD_nodeLabel, const string &postulatedFT, const vector<string>& ESD_nodeBranches);
//		//void addESDNode(string ESD_nodeLabel, vector<string> ESD_nodeBranches, double prob);
//		int addFTNode(const string& FT_nodeLabel,int type, int k, const vector<string>& children);
//		int addNodeParameterDensity(const string &BE_nodeLabel, const int& parameterIndex, const int& DENSITY_CODE, const vector<double>& parameters);
//		int clearAll();
//		int computeLatinHyperCube(const int numberOfSamples, const int intervals
//			, const string ESD_initiator
//			, bool sensitivity);
//		int clearEvidence();
//		int clearEvidence(const string &label);
//		//int createBlockDiagram(string diagramLabel);
//		int computeCutSets(const string &target, int max_cnt, double min_prob, bool dependent);
//		int containsFT(const string &label);
//		int containsBE(const string &BE_label);
//		int containsBBN(const string &BBN_label); 
//		int containsESD(const string &ESD_label);
//		void evaluateTimeProbability(const string& FT_nodeLabel, vector<double>& times, vector<double>& unreliabilities);
//		double getCDF(const int& DENSITY_CODE, const vector<double>& parameters, double time);
//		int getCutCount();
//		vector<string> getCutString(int index);
//		double getCutProbability(int index);
//		double* getBBNNodeDensity(string &BBN_nodeLabel);
//		//double getInverseValue(const string& BE_nodeLabel, const int parameterIndex, const double CDF_value);
//		int getSystemState(const string firstBlockLabel);
//		int fixEvent(const string &ESD_nodeLabel, double ESD_nodeProb);
//		int fixEvent(const string &ESD_nodeLabel, const int& DENSITY_CODE, const vector<string>& parameters );
//		int linkEvent(const string &ESD_nodeLabel, const string &postulatedBBN);
//		int linkESDToBBNNodeLevel(const string &ESD_nodeLabel, const string &postulatedBBN, const string &linkedLevel);
//		double quantify(const string & ESD_targetNodeLabel);
//		int quantifyMeanUncertainty(const string & ESD_targetNodeLabel, double*& x, double*& fx, double*& Fx, double*& percentiles, int& n);
//		//int quantifyVarUncertainty(const string & ESD_targetNodeLabel, double*& x, double*& fx, double*& Fx, int& n);
//		int select(const string &ESD_initiator, const string &ESD_endstate);
//		int selectAll(const string &ESD_initiator);
//		int setCPT(const string &BBN_nodeLabel, const vector<string>& parents, const vector<double> &cpt);
//		int setEventState(const string blockLabel, const int eventState);
//		int setEvidence(const string &label,int state);
//		int setEvidence(const string &label,vector<double>& likelihood);//new
//		int setMissionTime(const double missionTime);//new
//		void solveBBN(const string BBN_nodeLabel);
//		void solveET(const string ESD_initiatorLabel);
//		void solveFT(const string FT_topLabel);
//		//void setESDProb();
//		Facade(void);
//		~Facade(void);
//	};
//}
////#endif