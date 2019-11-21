#include "stdafx.h"
//#include ".\Facade.h"
//#include "crtdbg.h"
////Memory Leak Detection Enabling    
//#include <stdlib.h>
//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//#define DEBUG_NEW new(_NORMAL_BLOCK, THIS_FILE, __LINE__)
//#ifdef _DEBUG
//	#define new DEBUG_NEW
//	#undef THIS_FILE
//	static char THIS_FILE[] = __FILE__;
//#endif
//namespace BDD_Engine{
//
//int Facade::addBBNNode(const string &BBN_nodeLabel, 
//							const vector<string>& states, 
//							const vector<string>& parents, 
//							const vector<double> &cpt){
//		
//	if(!this->belongsToBBNNodes(this->bbn_nodes, BBN_nodeLabel)){
//		BBN_DNode* bbn_node = new BBN_DNode();
//		this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, bbn_node);
//		bbn_node->setAdded(true);
//		bbn_node->setLabel(BBN_nodeLabel);
//		int nLevels = states.size();
//		bbn_node->setLevelsCount(nLevels);
//		for(int i=0; i<nLevels; i++)
//			bbn_node->setLevelName(i, states[i]);
//		int nPar = parents.size();
//		for(int i=0; i<nPar; i++){
//			string strPari = parents[i];
//			if(!this->belongsToBBNNodes(this->bbn_nodes, strPari)){
//				BBN_DNode* pari = new BBN_DNode();
//				this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, pari);
//				pari->setLabel(strPari);
//				pari->addChild(bbn_node);
//			}else{
//				BBN_DNode* pari = this->bbn_nodes[this->searchedIndex];
//				pari->addChild(bbn_node);
//			}
//			//if(bbn_node->domain !="")
//		}
//		int nRows = cpt.size()/nLevels;
//		int k=0;
//		bbn_node->generateCPT(nRows, nLevels);
//		for(int i=0; i<nRows; i++)
//			for(int j=0; j<nLevels; j++){
//				bbn_node->setProb(i, j, cpt[k]);
//				k++;
//			}
//	}
//	else if(!this->bbn_nodes[this->searchedIndex]->isAdded()){
//		BBN_DNode * bbn_node = this->bbn_nodes[this->searchedIndex];
//		bbn_node->setAdded(true);
//		if (bbn_node->getParentsCount()==0){//it is a signal that the node was included by the addESDMultiNode method
//			int nLevels = states.size();
//			bbn_node->setLevelsCount(nLevels);
//			for(int i=0; i<nLevels; i++)
//				bbn_node->setLevelName(i, states[i]);
//			int nPar = parents.size();
//			for(int i=0; i<nPar; i++){
//				string strPari = parents[i];
//				if(!this->belongsToBBNNodes(this->bbn_nodes, strPari)){
//					BBN_DNode* pari = new BBN_DNode();
//					this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, pari);
//					pari->setLabel(strPari);
//					pari->addChild(bbn_node);
//				}else{
//					BBN_DNode* pari = this->bbn_nodes[this->searchedIndex];
//					pari->addChild(bbn_node);
//				}
//			}
//			//this->updateBBNDomain(bbn_node, bbn_node->domain);
//			int nRows = cpt.size()/nLevels;
//			int k=0;
//			bbn_node->generateCPT(nRows, nLevels);
//			for(int i=0; i<nRows; i++)
//				for(int j=0; j<nLevels; j++){
//					bbn_node->setProb(i, j, cpt[k]);
//					k++;
//				}
//		}
//	}
//	return 0;
//}
//
//int Facade::addBENode(const string &BE_nodeLabel, const int& DENSITY_CODE, const vector<double>& parameters){
//	FT_Node* node = getFT_node(BE_nodeLabel);
//	if (node == NULL) {
//		node = new FT_Node(FT_Auxiliar::LOG_NULL);
//		node->setLabel(BE_nodeLabel);
//		this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, node);
//	}
//	else
//		delete (node->getDensity());
//	node->setAdded(true);
//	if(DENSITY_CODE == this->DIRAC_DENSITY){//PROBABILITY
//		Dirac* density = new Dirac(parameters[0]);
//		node->setDensity(density);
//		node->setProb(parameters[0]);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->EXPONENTIAL_DENSITY){//SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Exponential* density = new Exponential(parameters[0]);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->GAMMA_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Gamma* density = new Gamma(parameters[0], parameters[1]);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->NON_PARAMETRIC_DISCRETE_DENSITY){//(x0, f_x0), (x1, f_x1),... (each pair of values implies in one value and its respective probability)
//		int n = parameters.size()/2;
//		double* x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		double* F_x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		for(int i=0; i<n; i+=2){
//			x[i] = parameters[i];
//			F_x[i] = parameters[i+1];
//		}
//		NonParametricProbabilityDistribution* density = new NonParametricProbabilityDistribution(x, F_x, n);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->LOGNORMAL_DENSITY){//MEDIAN, STANDARD DEVIATION
//		Lognormal* density = new Lognormal(parameters[0], pow(parameters[1], 2.0));
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->WEIBULL_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Weibull* density = new Weibull(parameters[0], parameters[1]);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->TRIANGULAR_DENSITY){//LOWER, MODE, UPPER
//		Triangular* density = new Triangular(parameters[0], parameters[1],parameters[2]);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->UNIFORM_DENSITY){//LOWER, UPPER
//		Uniform* density = new Uniform(parameters[0], parameters[1]);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	node->getDensity()->setNumberOfParametersDensities(parameters.size());
//
//	return 0;
//}
//int Facade::addBENode(const string &BE_nodeLabel, const int& DENSITY_CODE, const vector<string>& parameters){
//	FT_Node* node = getFT_node(BE_nodeLabel);
//	if (node == NULL) {
//		node = new FT_Node(FT_Auxiliar::LOG_NULL);
//		node->setLabel(BE_nodeLabel);
//		this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, node);
//	}
//	else
//		delete (node->getDensity());
//	node->setAdded(true);
//	if(DENSITY_CODE == this->DIRAC_DENSITY){//PROBABILITY
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Dirac* density = new Dirac(p1);
//		node->setDensity(density);
//		node->setProb(density->getMean());
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->EXPONENTIAL_DENSITY){//SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Density* p1 = Facade::getDensity(parameters[0]);
//		//double scaling = 1.0/p1->getMean();
//		//p1->setScaling(scaling);
//		//char aux [20];
//		//int id=1;
//		//_itoa( id, aux, 10 );
//		//label="newD";
//		//label+= *aux;
//		Exponential* density = new Exponential(p1);
//		beDensities.push_back(density);
//		node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->GAMMA_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Density* p2 = Facade::getDensity(parameters[1]);
//		Gamma* density = new Gamma(p1, p2);
//		beDensities.push_back(density);
//		node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->NON_PARAMETRIC_DISCRETE_DENSITY){//(x0, f_x0), (x1, f_x1),... (each pair of values implies in one value and its respective probability)
//		Density* p1 = Facade::getDensity(parameters[0]);
//		//Dirac* density = new Dirac(p1);
//		int n = ((NonParametricProbabilityDistribution*)p1)->get_n();
//		double* x = ((NonParametricProbabilityDistribution*)p1)->get_vec_x();
//		double* F_x = ((NonParametricProbabilityDistribution*)p1)->get_vec_Fx();
//		NonParametricProbabilityDistribution* density = new NonParametricProbabilityDistribution(x, F_x, n);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->LOGNORMAL_DENSITY){//MEDIAN, STANDARD DEVIATION
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Density* p2 = Facade::getDensity(parameters[1]);
//		Lognormal* density = new Lognormal(p1, p2);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->WEIBULL_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Density* p2 = Facade::getDensity(parameters[1]);
//		Weibull* density = new Weibull(p1, p2);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->TRIANGULAR_DENSITY){//LOWER, MODE, UPPER
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Density* p2 = Facade::getDensity(parameters[1]);
//		Density* p3 = Facade::getDensity(parameters[2]);
//		Triangular* density = new Triangular(p1, p2, p3);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	else if(DENSITY_CODE == this->UNIFORM_DENSITY){//LOWER, UPPER
//		Density* p1 = Facade::getDensity(parameters[0]);
//		Density* p2 = Facade::getDensity(parameters[1]);
//		Uniform* density = new Uniform(p1, p2);
//		node->setDensity(density);
//		beDensities.push_back(density);
//	}
//	//node->getDensity()->setNumberOfParametersDensities(parameters.size());
//
//	return 0;
//}
//int Facade::addBENode(const string &BE_nodeLabel, double FT_nodeProb){
//	vector<double> prob(0);
//	prob.push_back(FT_nodeProb);
//	this->addBENode(BE_nodeLabel, this->DIRAC_DENSITY, prob);
//	//FT_Node* node = getFT_node(FT_nodeLabel);
//	//if (node == NULL) {
//	//	node = new FT_Node(FT_Auxiliar::LOG_NULL);
//	//	node->setLabel(FT_nodeLabel);
//	//	this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, node);
//	//}
//	//node->setAdded(true);
//	////node->bdd= node;
//	//node->setProb(FT_nodeProb);
//	return 0;
//}
//int Facade::addBENode(const string &BE_nodeLabel, const string &postulatedBBN){
//	FT_Node* ft_be = getFT_node(BE_nodeLabel);
//	BBN_DNode* bbn_node = getBBN_node(postulatedBBN);
//	if(bbn_node ==NULL){
//		bbn_node = new BBN_DNode(ft_be->getET_Domain());
//		bbn_node->setLabel(postulatedBBN);
//		this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, bbn_node);
//	}
//	else
//		this->updateBBNDomain(bbn_node, ft_be->getET_Domain());
//	ft_be->setAdded(true);
//	//bbn_node->setAdded(true);//dobt
//	ft_be->BBN_effect = bbn_node;
//	this->ft_nodesToSolveBBNs.push_back(ft_be);
//
//	vector<double> prob(0);
//	prob.push_back(0.0);
//	this->addBENode(BE_nodeLabel, this->DIRAC_DENSITY, prob);
//
//	return 0;
//}
//
//int Facade::addBENode(const string &BE_nodeLabel, const string &postulatedBBN, const string &BBN_levelNameToLink){
//	FT_Node* ft_be = getFT_node(BE_nodeLabel);
//	BBN_DNode* bbn_node = getBBN_node(postulatedBBN);
//	if(bbn_node ==NULL){
//		bbn_node = new BBN_DNode(ft_be->getET_Domain());
//		bbn_node->setLabel(postulatedBBN);
//		this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, bbn_node);
//	}
//	else
//		this->updateBBNDomain(bbn_node, ft_be->getET_Domain());
//	ft_be->setAdded(true);
//	//bbn_node->setAdded(true);//dobt
//	ft_be->BBN_effect = bbn_node;
//	this->ft_nodesToSolveBBNs.push_back(ft_be);
//
//	bool levelFound = false;
//	int i=0;
//	while(!levelFound){
//		if(bbn_node->getLevelName(i)==BBN_levelNameToLink){
//			levelFound = true;
//			bbn_node->linkedESDIndex = i;
//		}
//		i++;
//	}
//
//	vector<double> prob(0);
//	prob.push_back(0.0);
//	this->addBENode(BE_nodeLabel, this->DIRAC_DENSITY, prob);
//
//	return 0;
//}
//
//int Facade::addNodeParameterDensity(const string &BE_nodeLabel, const int& parameterIndex, const int& DENSITY_CODE, const vector<double>& parameters){
//	FT_Node* node = getFT_node(BE_nodeLabel);
//	//if (node == NULL) {
//	//	node = new FT_Node(FT_Auxiliar::LOG_NULL);
//	//	node->setLabel(BE_nodeLabel);
//	//	this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, node);
//	//}
//	//else
//	//	delete (node->getDensity());
//	//node->setAdded(true);
//	Density* density = NULL;
//	if(DENSITY_CODE == this->DIRAC_DENSITY){//PROBABILITY
//		density = new Dirac(parameters[0]);
//	}
//	else if(DENSITY_CODE == this->EXPONENTIAL_DENSITY){//SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		density = new Exponential(parameters[0]);
//	}
//	else if(DENSITY_CODE == this->NON_PARAMETRIC_DISCRETE_DENSITY){//(x0, f_x0), (x1, f_x1),... (each pair of values implies in one value and its respective probability)
//		int i, j, n = parameters.size()/2;
//		double* x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		double* F_x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		for(i=0, j = 0; i<n; i++, j++){
//			x[i] = parameters[i + j];
//			F_x[i] = parameters[i + j +1];//modified
//		}
//		density = new NonParametricProbabilityDistribution(x, F_x, n);
//	}
//	else if(DENSITY_CODE == this->UNIFORM_DENSITY){//LOWER, UPPER
//		density = new Uniform(parameters[0], parameters[1]);
//	}
//	else if(DENSITY_CODE == this->GAMMA_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		density = new Gamma(parameters[0], parameters[1]);
//	}
//	else if(DENSITY_CODE == this->LOGNORMAL_DENSITY){//MEDIAN, STANDARD DEVIATION
//		density = new Lognormal(parameters[0], pow(parameters[1], 2.0));
//	}
//	else if(DENSITY_CODE == this->WEIBULL_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		density = new Weibull(parameters[0], parameters[1]);
//	}
//	else if(DENSITY_CODE == this->TRIANGULAR_DENSITY){//LOWER, MODE, UPPER
//		density = new Triangular(parameters[0], parameters[1],parameters[2]);
//	}
//	node->getDensity()->setParameterDensity(parameterIndex, density);
//	return 0;
//}
//int Facade::addBlockNode(const string& blockNodeLabel, const vector<string>& nextBlockNodes, const int k_out, const string k_out_n_switchNode){
//	//static int counter = 0;
//	//counter ++;
//	//char aux [20];
//	//_itoa( counter, aux, 10 );
//	//label="newG";
//	//label+= *aux;
//	vector<string> children(0);
//	this->addFTNode(blockNodeLabel, FT_Auxiliar::LOG_NULL, 0, children);
//	if(nextBlockNodes.size()>0){
//		FT_Node* top = this->getFT_node(blockNodeLabel);
//		FT_Node* actualBlock = NULL;
//		this->addFTNode(nextBlockNodes[0], FT_Auxiliar::LOG_NULL, 0, children);
//		actualBlock = this->getFT_node(nextBlockNodes[0]);
//		if(k_out_n_switchNode != ""){//the switch node is a series with the k out n subsystem
//			this->addFTNode(k_out_n_switchNode, FT_Auxiliar::LOG_NULL, 0, children);
//			FT_Node* switchNode = this->getFT_node(k_out_n_switchNode);
//			if(top->getChildrenCount()==0)//evaluating if the sucess child of the top was already added
//				top->setVertices(FT_Auxiliar::t0, switchNode);
//			else
//				top->setVertices(top->getChild(0), switchNode);
//			switchNode->setVertices(FT_Auxiliar::t0, actualBlock);
//		}
//		else{
//			if(top->getChildrenCount()==0)//evaluating if the sucess child of the top was already added
//				top->setVertices(FT_Auxiliar::t0, actualBlock);
//			else
//				top->setVertices(top->getChild(0), actualBlock);
//		}
//		
//		//defining the k out n incomplete BDD
//		vector<FT_Node*> vi(0);
//		vi.push_back(actualBlock);
//		for(int i=1; i<k_out; i++){
//			this->addFTNode(nextBlockNodes[i], FT_Auxiliar::LOG_NULL, 0, children);
//			FT_Node* node_i =  this->getFT_node(nextBlockNodes[i]);
//			vi.push_back(node_i);
//		}
//		int nLoops = nextBlockNodes.size() - k_out;
//		for(int i=0; i<nLoops; i++){
//			vector<FT_Node*> viP1(0);
//			for(int j=i+1; j<k_out+i; j++){
//				FT_Node* node_j = this->getFT_node(nextBlockNodes[j]);
//				FT_Node* clone_node_j = node_j->getClone(NULL);
//				viP1.push_back(clone_node_j);
//			}
//			this->addFTNode(nextBlockNodes[i+k_out], FT_Auxiliar::LOG_NULL, 0, children);
//			FT_Node* lastNodeOf_viP1 = this->getFT_node(nextBlockNodes[i+k_out]);
//			viP1.push_back(lastNodeOf_viP1);
//
//			int l=0;
//			FT_Node* nil = NULL;
//			for(l=0; l<k_out-1; l++){
//				nil = vi[l];
//				nil->setVertices(viP1[l], vi[l+1]);
//			}
//			nil = vi[l];
//			nil->setVertices(viP1[l], FT_Auxiliar::t1);
//			vi = viP1;
//		}
//		for(int i=0; i<k_out-1; i++){
//			FT_Node* node = vi[i];
//			node->setVertices(FT_Auxiliar::t0, vi[i+1]);
//		}
//		FT_Node* node = vi[k_out-1];
//		node->setVertices(FT_Auxiliar::t0, FT_Auxiliar::t1);
//	}
//	else{
//		FT_Node* top = this->getFT_node(blockNodeLabel);
//		top->setVertices(FT_Auxiliar::t0, FT_Auxiliar::t1);
//	}
//	return 0;
//}
//int Facade::addDensity(const string& densityLabel, const int& DENSITY_CODE, const vector<double>& parameters){
//	Density* density = getDensity(densityLabel);
//	if (density == NULL) {
//		if(DENSITY_CODE == this->DIRAC_DENSITY){//PROBABILITY
//			density = new Dirac(parameters[0]);
//			//node->setDensity(density);
//			//node->setProb(parameters[0]);
//		}
//		else if(DENSITY_CODE == this->EXPONENTIAL_DENSITY){//SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//			density = new Exponential(parameters[0]);
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->GAMMA_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//			density = new Gamma(parameters[0], parameters[1]);
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->NON_PARAMETRIC_DISCRETE_DENSITY){//(x0, f_x0), (x1, f_x1),... (each pair of values implies in one value and its respective probability)
//			int n = parameters.size()/2;
//			double* x = FT_Auxiliar::getNewDouble(n);//new double[n];
//			double* F_x = FT_Auxiliar::getNewDouble(n);//new double[n];
//			for(int i=0, j = 0; i<n; i++, j++){
//				x[i] = parameters[i + j];
//				F_x[i] = parameters[i + j +1];//modified
//			}
//			density = new NonParametricProbabilityDistribution(x, F_x, n);
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->LOGNORMAL_DENSITY){//MEDIAN, STANDARD DEVIATION
//			density = new Lognormal(parameters[0], pow(parameters[1], 2.0));
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->WEIBULL_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//			density = new Weibull(parameters[0], parameters[1]);
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->TRIANGULAR_DENSITY){//LOWER, MODE, UPPER
//			density = new Triangular(parameters[0], parameters[1],parameters[2]);
//			//node->setDensity(density);
//		}
//		else if(DENSITY_CODE == this->UNIFORM_DENSITY){//LOWER, UPPER
//			density = new Uniform(parameters[0], parameters[1]);
//			//node->setDensity(density);
//		}
//		density->setLabel(densityLabel);
//		Facade::densities.insert(Facade::densities.begin()+Facade::searchedIndex, density);
//	}
//	return 0;
//}
//
//int Facade::addESDMultiNode(const string &ESD_nodeLabel, 
//							   const string &postulatedBBN, 
//							   const vector<string>& ESD_node_branches){
//	ET_Node* ESD_node = NULL;
//	ET_Node* ESD_v0 = NULL;
//	ET_Node* ESD_v1 = NULL;
//	if(!this->belongsToESDNodes(this->et_nodes, ESD_nodeLabel)){
//		//this->ET_domain = ESD_nodeLabel;
//		ESD_node = new ET_Node(ESD_nodeLabel);
//		ESD_node->setAdded(true);
//		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_node);
//	}else
//		ESD_node = this->et_nodes[this->searchedIndex];
//
//	if(postulatedBBN!=""){
//		if(!this->belongsToBBNNodes(this->bbn_nodes, postulatedBBN)){
//			ESD_node->BBN_effect= new BBN_DNode();
//			ESD_node->BBN_effect->setLabel(postulatedBBN);
//			this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, ESD_node->BBN_effect);
//		} else
//			ESD_node->BBN_effect= this->bbn_nodes[this->searchedIndex];
//		et_nodesToSolveBBNs.push_back(ESD_node);
//	}
//
//	if(ESD_node_branches.size()!=0){
//		if(ESD_node_branches[0]!=""){//childS
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[0])){
//				ESD_v0 = new ET_Node(ESD_node_branches[0]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v0);
//			}else
//				ESD_v0 = this->et_nodes[this->searchedIndex];
//		}
//		if(ESD_node_branches[1]!=""){//childF
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[1])){
//				ESD_v1 = new ET_Node(ESD_node_branches[1]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v1);
//			}else
//				ESD_v1 = this->et_nodes[this->searchedIndex];
//		}
//		else{//childF
//			string label = "_INO";
//			vector<string> branches(0);
//			this->addESDNode(label, "", branches);
//			this->et_endStates.erase(this->et_endStates.begin()+this->et_endStates.size()-1);
//			ESD_v1 = this->getET_node(label);
//		}
//		ESD_node->setChildS(ESD_v0);
//		ESD_node->setChildF(ESD_v1);
//	}
//	else{
//		ESD_node->isTerminal = true;
//		this->et_endStates.push_back(ESD_node);
//	}
//	return 0;
//
//}
//
//int Facade::addESDMultiNode(   const string &ESD_nodeLabel, 
//							   const string &postulatedBBN, 
//							   const vector<string>& ESD_node_branches,
//							   const string BBN_levelNameToLink){
//	ET_Node* ESD_node = NULL;
//	ET_Node* ESD_v0 = NULL;
//	ET_Node* ESD_v1 = NULL;
//	if(!this->belongsToESDNodes(this->et_nodes, ESD_nodeLabel)){
//		//this->ET_domain = ESD_nodeLabel;
//		ESD_node = new ET_Node(ESD_nodeLabel);
//		ESD_node->setAdded(true);
//		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_node);
//	}else
//		ESD_node = this->et_nodes[this->searchedIndex];
//
//	if(postulatedBBN!=""){//there will be problem if the bbn_node there is not...
//		if(!this->belongsToBBNNodes(this->bbn_nodes, postulatedBBN)){
//			ESD_node->BBN_effect= new BBN_DNode();
//			ESD_node->BBN_effect->setLabel(postulatedBBN);
//			this->bbn_nodes.insert(this->bbn_nodes.begin()+this->searchedIndex, ESD_node->BBN_effect);
//		} else{
//			ESD_node->BBN_effect= this->bbn_nodes[this->searchedIndex];
//			bool levelFound = false;
//			int i=0;
//			while(!levelFound){
//				if(ESD_node->BBN_effect->getLevelName(i)==BBN_levelNameToLink){
//					levelFound = true;
//					ESD_node->BBN_effect->linkedESDIndex = i;
//				}
//				i++;
//			}
//		}
//		et_nodesToSolveBBNs.push_back(ESD_node);
//	}
//
//	if(ESD_node_branches.size()!=0){
//		if(ESD_node_branches[0]!=""){//childS
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[0])){
//				ESD_v0 = new ET_Node(ESD_node_branches[0]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v0);
//			}else
//				ESD_v0 = this->et_nodes[this->searchedIndex];
//		}
//		if(ESD_node_branches[1]!=""){//childF
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[1])){
//				ESD_v1 = new ET_Node(ESD_node_branches[1]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v1);
//			}else
//				ESD_v1 = this->et_nodes[this->searchedIndex];
//		}
//		else{//childF
//			string label = "_INO";
//			vector<string> branches(0);
//			this->addESDNode(label, "", branches);
//			this->et_endStates.erase(this->et_endStates.begin()+this->et_endStates.size()-1);
//			ESD_v1 = this->getET_node(label);
//		}
//		ESD_node->setChildS(ESD_v0);
//		ESD_node->setChildF(ESD_v1);
//	}
//	else{
//		ESD_node->isTerminal = true;
//		this->et_endStates.push_back(ESD_node);
//	}
//	return 0;
//
//}
//
//int Facade::addESDNode(const string& ESD_nodeLabel, 
//					   const string &postulatedFT, 
//					   const vector<string>& ESD_node_branches){
//	ET_Node* ESD_node = NULL;
//	ET_Node* ESD_v0 = NULL;
//	ET_Node* ESD_v1 = NULL;
//	if(!this->belongsToESDNodes(this->et_nodes, ESD_nodeLabel)){
//		//this->ET_domain = ESD_nodeLabel;
//		ESD_node = new ET_Node(ESD_nodeLabel);
//		ESD_node->setAdded(true);
//		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_node);
//	}else
//		ESD_node = this->et_nodes[this->searchedIndex];
//
//	if(!this->belongsToFTNodes(this->ft_nodes, postulatedFT)){
//		if(postulatedFT!=""){
//			if(ESD_node->FT_TopEvent!=0)
//				delete ESD_node->FT_TopEvent;
//			ESD_node->FT_TopEvent = new FT_Node('?', ESD_node->getET_Domain());
//			ESD_node->FT_TopEvent->setLabel(postulatedFT);
//			this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, ESD_node->FT_TopEvent);
//			et_nodesToSolveFTs.push_back(ESD_node);
//		}
//	}else{
//		ESD_node->FT_TopEvent = this->ft_nodes[this->searchedIndex];
//		//ESD_node->setProb(this->ft_nodes[this->searchedIndex]->getProb());
//	}
//
//	if(ESD_node_branches.size()!=0){
//		if(ESD_node_branches[0]!=""){//childS
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[0])){
//				ESD_v0 = new ET_Node(ESD_node_branches[0]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v0);
//			}else
//				ESD_v0 = this->et_nodes[this->searchedIndex];
//		}
//		if(ESD_node_branches[1]!=""){//childF
//			if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[1])){
//				ESD_v1 = new ET_Node(ESD_node_branches[1]);
//				this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v1);
//			}else
//				ESD_v1 = this->et_nodes[this->searchedIndex];
//		}
//		else{//childF
//			string label = "_INO";
//			vector<string> branches(0);
//			this->addESDNode(label, "", branches);
//			this->et_endStates.erase(this->et_endStates.begin()+this->et_endStates.size()-1);
//			ESD_v1 = this->getET_node(label);
//		}
//		ESD_node->setChildS(ESD_v0);
//		ESD_node->setChildF(ESD_v1);
//	}
//	else{
//		ESD_node->isTerminal = true;
//		this->et_endStates.push_back(ESD_node);
//	}
//	return 0;
//}
////void Facade::addESDNode(string ESD_nodeLabel, vector<string> ESD_node_branches, double prob){
////	ET_Node* ESD_node = NULL;
////	ET_Node* ESD_v0 = NULL;
////	ET_Node* ESD_v1 = NULL;
////	if(!this->belongsToESDNodes(this->et_nodes, ESD_nodeLabel)){
////		ESD_node = new ET_Node(ESD_nodeLabel);
////		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_node);
////	}else
////		ESD_node = this->et_nodes[this->searchedIndex];
////
////	if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[0])){
////		ESD_v0 = new ET_Node(ESD_node_branches[0]);
////		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v0);
////	}else
////		ESD_v0 = this->et_nodes[this->searchedIndex];
////
////	if(!this->belongsToESDNodes(this->et_nodes, ESD_node_branches[1])){
////		ESD_v1 = new ET_Node(ESD_node_branches[1]);
////		this->et_nodes.insert(this->et_nodes.begin()+this->searchedIndex, ESD_v1);
////	}else
////		ESD_v1 = this->et_nodes[this->searchedIndex];
////
////	ESD_node->setProb(prob);
////	ESD_v0->setProb(prob);
////	ESD_v1->setProb(prob);
////	ESD_node->setChildS(ESD_v0);
////	ESD_node->setChildF(ESD_v1);
////}
//int Facade::addFTNode(const string& FT_nodeLabel,int type, int k, const vector<string>& children){
//	char LOG_TYPE = FT_Auxiliar::LOG_NULL;
//	if(type == this->FT_OR)
//		LOG_TYPE = FT_Auxiliar::LOG_OR;
//	else if(type == this->FT_AND)
//		LOG_TYPE = FT_Auxiliar::LOG_AND;
//		
//	FT_Node* FT_node = NULL;
//	if(!this->belongsToFTNodes(this->ft_nodes, FT_nodeLabel)){//it never will ocurr
//		FT_node = new FT_Node(LOG_TYPE, this->ET_domain);
//		FT_node->setAdded(true);
//		FT_node->setLabel(FT_nodeLabel);
//		this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, FT_node);
//
//	}else{
//		FT_node = this->ft_nodes[this->searchedIndex];
//		FT_node->setAdded(true);
////		FT_node->bdd = NULL;
////		FT_node->removeChildren();
//		FT_Node* parent = FT_node->getParent();
//		if(parent!=NULL){//it guarantes the separation between BEs and gates
//			parent->removeChild(FT_node);
//			FT_node->setLogic(LOG_TYPE);
//			parent->addChild(FT_node);
//		}else
//			FT_node->setLogic(LOG_TYPE);
//	}
//	vector<string> localChildren = children;
//	if(k > 1){//is k out n?
//		FT_node->setLogic(FT_Auxiliar::LOG_OR);
//		int* indexes = new int[k];
//		for(int i=0; i<k; i++){
//			indexes[i] = i;
//		}
//		vector<string> andChildren(0);
//		this->elaborate_k_out_n_gate(k, children, andChildren, indexes);
//		localChildren = andChildren;
//		delete[]indexes;
//		//FT_Auxiliar::readTree(getFT_node(FT_nodeLabel));
//		//cout<<endl;
//	}
//	//else{
//		int n = localChildren.size();
//		for(int i=0; i<n; i++){
//			string sti = localChildren[i];
//
//			FT_Node* childi = NULL;
//			if(!this->belongsToFTNodes(this->ft_nodes, sti)){
//				childi = new FT_Node(FT_Auxiliar::LOG_NULL, FT_node->getET_Domain());
//				childi->setLabel(sti);
//				this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, childi);
//			}
//			else{
//				FT_Node* original = this->ft_nodes[this->searchedIndex];
//				childi = original->getClone(NULL);	
//			}
//			FT_node->addChild(childi);
//			//FT_Auxiliar::readTree(getFT_node("A_FT"));
//		}
//	//}
//	if(LOG_TYPE!=FT_Auxiliar::LOG_NULL){
//		int nClones = FT_node->clones.size();
//		for(int i=0; i<nClones; i++){
//			FT_Node* cli = FT_node->clones[i];
//			cli->bdd = NULL;
//			cli->removeChildren();
//			FT_Node* parent = cli->getParent();
//			//cli->setLogic(FT_node->getLogic());
//			parent->removeChild(cli);
////			if(cli->getLogic()!=FT_node->getLogic())
////				parent->firstGateIndex--;
//			cli = FT_node->getClone(NULL);
//			//FT_node->clones[i] = cli;
//			parent->addChild(cli);
//		}
//	}
//	//FT_Auxiliar::readTree(getFT_node("A_FT"));
//	return 0;
//}
//bool Facade::belongsToBBNNodes(vector<BBN_DNode*>& vec, string nodeLabel){
//	bool indexFound = false;
//	int size = vec.size();
//	int upper = size;
//	upper = (upper>0?upper--:upper);
//	int lower = 0;
//	int mid=0;
//	while(!indexFound && lower!=upper){
//		mid = (int) (upper+lower)/2;
//		BBN_DNode* bbn_node = vec[mid];
//		if(nodeLabel==vec[mid]->getLabel())
//			indexFound = true;
//		else{
//			if(upper-lower<=1){
//				if (nodeLabel>vec[mid]->getLabel()){
//					mid++;
//					lower = upper;
//				}else{
//					mid--;
//					upper = lower;
//				}
//			}else{
//				if (nodeLabel>vec[mid]->getLabel())
//					lower = mid;
//				else
//					upper = mid;				
//			}
//		}
//	}
//	for(int i=0; i<vec.size(); i++){
//		BBN_DNode* bbn_node = vec[i];
//		int j=i;
//	}
//	if(mid<0)
//		mid=0;
//	searchedIndex = mid;
//	return indexFound;
//}
//bool Facade::belongsToESDNodes(vector<ET_Node*>& vec, string nodeLabel){
//	bool indexFound = false;
//	int size = vec.size();
//	int upper = size;
//	upper = (upper>0?upper--:upper);
//	int lower = 0;
//	int mid=0;
//	//vec[0]->readVecET_Nodes(vec);
//	while(!indexFound && lower!=upper){
//		mid = (int) (upper+lower)/2;
//		if(nodeLabel==vec[mid]->getLabel())
//			indexFound = true;
//		else{
//			if(upper-lower<=1){
//				if (nodeLabel>vec[mid]->getLabel()){
//					mid++;
//					lower = upper;
//				}else{
//					mid--;
//					upper = lower;
//				}
//			}else{
//				if (nodeLabel>vec[mid]->getLabel())
//					lower = mid;
//				else
//					upper = mid;
//			}
//		}
//	}
//	if(mid<0)
//		mid=0;
//	searchedIndex = mid;
//	return indexFound;
////	readNodeVector(vec);
//}
//bool Facade::belongsToFTNodes(vector<FT_Node*>& vec, string nodeLabel){
//	bool indexFound = false;
//	int size = vec.size();
//	int upper = size;
//	upper = (upper>0?upper--:upper);
//	int lower = 0;
//	int mid=0;
//	while(!indexFound && lower!=upper){
//		mid = (int) (upper+lower)/2;
//		if(nodeLabel==vec[mid]->getLabel())
//			indexFound = true;
//		else{
//			if(upper-lower<=1){
//				if (nodeLabel>vec[mid]->getLabel()){
//					mid++;
//					lower = upper;
//				}else{
//					mid--;
//					upper = lower;
//				}
//			}else{
//				if (nodeLabel>vec[mid]->getLabel())
//					lower = mid;
//				else
//					upper = mid;
//			}
//		}
//	}
//	if(mid<0)
//		mid=0;
//	searchedIndex = mid;
//	return indexFound;
////	readNodeVector(vec);
//}
//bool Facade::belongsToDensities(vector<Density*>& vec, string densityLabel){
//	bool indexFound = false;
//	int size = vec.size();
//	int upper = size;
//	upper = (upper>0?upper--:upper);
//	int lower = 0;
//	int mid=0;
//	while(!indexFound && lower!=upper){
//		mid = (int) (upper+lower)/2;
//		if(densityLabel==vec[mid]->getLabel())
//			indexFound = true;
//		else{
//			if(upper-lower<=1){
//				if (densityLabel>vec[mid]->getLabel()){
//					mid++;
//					lower = upper;
//				}else{
//					mid--;
//					upper = lower;
//				}
//			}else{
//				if (densityLabel>vec[mid]->getLabel())
//					lower = mid;
//				else
//					upper = mid;
//			}
//		}
//	}
//	if(mid<0)
//		mid=0;
//	searchedIndex = mid;
//	return indexFound;
////	readNodeVector(vec);
//}
//int Facade::clearAll(){
//	
//
//
//	for(int i=0; i<densities.size(); i++){
//		Density* d = densities[i];
//		delete (d);
//		d=0;
//	}
//	densities.clear();
//
//	for(int i=0; i<beDensities.size(); i++){
//		Density* d = beDensities[i];
//		delete (d);
//		d=0;
//	}
//	beDensities.clear();
//
//	//deleting bbn news
//	BBN_Auxiliar::deleteNews();
//	BBN_Auxiliar::eliminateAllDNodes();
//	FT_Auxiliar::deleteNews();
//	this->initializeTerminals();
//
//	//for(int i=0; i<et_nodes.size(); i++){
//	//	delete et_nodes[i];
//	//	et_nodes[i]=0;
//	//}
//	et_nodes.clear();
//	ft_nodes.clear();
//	bbn_nodes.clear();
//	et_nodesToSolveFTs.clear();
//	et_nodesToSolveBBNs.clear();
//	ft_nodesToSolveBBNs.clear();
//	this->hasBeenInitialized = false;
//	return 0;
//}
//int Facade::clearEvidence(){
//	int n = BBN_Auxiliar::evidencedDNodes.size();
//	for(int i=0; i<n; i++){
//		BBN_DNode* ni = BBN_Auxiliar::evidencedDNodes[i];
//		ni->removeEvidence();
//	}
//	return 0;	
//}
//
//int Facade::clearEvidence(const string &BBN_nodeLabel){
//	BBN_DNode* node = this->getBBN_node(BBN_nodeLabel);
//	node->removeEvidence();
//	return 0;
//}
//
//
//int Facade::computeCutSets(const string &ESD_nodeTarget, int max_cnt, double min_prob, bool dependent){
//	ET_Node* node = this->getET_node(ESD_nodeTarget);
//	int n = node->getCutCount();
//	this->cuts.clear();
//	this->probs.clear();
//	for(int i=0; i<n; i++){
//		this->cuts.push_back(node->getCutString(i));
//		this->probs.push_back(node->getCutProbability(i));
//	}
//	return 0;
//}
//
//int Facade::computeLatinHyperCube(const int numberOfSamples
//								  , const int intervals
//								  , const string ESD_initiator
//								  , bool sensitivity)
//{
//	if(! hasBeenInitialized){
//		this->initiator = this->getET_node(ESD_initiator);
//		this->et_bdd->setLatinHyperCubeParameters(numberOfSamples, intervals, sensitivity);
//		this->et_bdd->performBDDSets(this->initiator, NULL, true);
//		hasBeenInitialized = true;
//	}
//	return 0;
//
////to be passed to ET_BDD
//	//bool isFound;
//	//int i, j, code, index, k, numberOfStrata = 25, basicEventsCount;
//	//double vy, dify, u, pProb, probAux,
//	//	f0, f, derivative, varianceProbTop, varianceBasicEvent, 
//	//	meanProb, meanSample, meanVarianceSample;
//	//LatinHyperCube *lhc = new LatinHyperCube ();
//	//DESimGenerator *desimgen = new DESimGenerator ();
//	//Density *density;
//	//FT_Node* node;
//	//FT_Node* top = getFT_node(topNodeLabel);
//	//FT_BDD bdd(top);
//	//vector<FT_Node*> basicEvents = bdd.getBasicEvents();
//	//basicEventsCount = (int)basicEvents.size ();
//	//double *mean = new double [numberOfSamples];
//	//double *variance = new double [numberOfSamples];
//	//double *probability = new double [numberOfSamples];
//	//double *aux = new double [numberOfSamples];
//	//double *x = new double [basicEventsCount];
//	//double *a = new double [basicEventsCount];
//	//double *b = new double [basicEventsCount];
//	//double *p = new double [basicEventsCount];
//	//double *topMean = new double [intervals];
//	//double *f_topMean = new double [intervals];
//	//double *F_topMean = new double [intervals];
//	//double *topVariance = new double [intervals];
//	//double *f_topVariance = new double [intervals];
//	//double *F_topVariance = new double [intervals];
//	//double *deriv = new double [intervals];
//	//double *f_deriv = new double [intervals];
//	//double *F_deriv = new double [intervals];
//	//double **percentiles = new double*[numberOfStrata];
//	//for (i = 0; i < numberOfStrata; i++)
//	//	percentiles[i] = new double[basicEventsCount];
//	//double **conditionalVariance = new double*[numberOfSamples];
//	//for (i = 0; i < numberOfSamples; i++)
//	//	conditionalVariance[i] = new double[basicEventsCount];
//	//
//	//if (sensitivity){
//	//	for (k = 0; k < basicEventsCount; k++){
//	//		node = basicEvents[k];
//	//		density = node->getDensity ()->getParameterDensity(0);
//	//		meanProb = density->getMean ();
//	//		node->setProb (meanProb);
//	//	}
//	//	f0 = bdd.getTopProb(top);
//	//}
//
//	//for (i = 0; i < numberOfSamples; i++){
//	//	desimgen->Reset ();
//	//	for (int l = 0; l < numberOfStrata; l++)
//	//		for (int m = 0; m < basicEventsCount; m++)
//	//			percentiles[l][m] = 0.0;
//	//	for (int m = 0; m < basicEventsCount; m++){
//	//		node = basicEvents[m];
//	//		density = node->getDensity ()->getParameterDensity(0);
//	//		density->setNumberOfStrata (numberOfStrata);
//	//		x[m] = 0.0;
//	//		a[m] = density->getLowerBound ();
//	//		p[m] = density->getProb ();
//	//		b[m] = a[m] + p[m];
//	//	}
//	//	for (j = 0; j < numberOfStrata; j++){
//	//		for (k = 0; k < basicEventsCount; k++){
//	//			node = basicEvents[k];
//	//			code = node->getDensity ()->DENSITY_TYPE;
//	//			if (code == this->DIRAC_DENSITY){
//	//				density = node->getDensity()->getParameterDensity(0);
//	//				pProb = density->getQuantile (a[k], b[k]);
//	//			}
//	//			isFound = false;
//	//			while (!isFound){
//	//				u = FT_Auxiliar::desimgen->generateUniformDeviate ();
//	//				index = (int)(u*numberOfStrata);
//	//				probAux = percentiles[index][k];
//	//				if (probAux == 0){
//	//					isFound = true;
//	//					percentiles[index][k] = pProb;
//	//				}
//	//			}
//	//			a[k] = b[k];
//	//			b[k] = b[k] + p[k];
//	//		}
//	//	}
//	//	meanSample = 0.0;
//	//	meanVarianceSample = 0.0;
//	//	varianceProbTop = 0.0;
//	//	for (j = 0; j < numberOfStrata; j++){
//	//		for (k = 0; k < basicEventsCount; k++){
//	//			node = basicEvents[k];
//	//			x[k] = x[k] + (1.0/numberOfStrata)*percentiles[j][k];
//	//			node->setProb (percentiles[j][k]);
//	//		}
//	//		f = bdd.getTopProb(top);
//	//		meanSample += (1.0/numberOfStrata)*f;
//	//		meanVarianceSample += pow (f, 2);
//	//	}
//	//	meanVarianceSample = (1.0/numberOfStrata)*meanVarianceSample 
//	//		- pow (meanSample, 2);
//	//	if (meanVarianceSample < 0)
//	//		meanVarianceSample = 0.0;
//	//	mean[i] = meanSample;
//	//	variance[i] = meanVarianceSample;
//	//	probability[i] = 1.0/numberOfSamples;
//	//	if (sensitivity){
//	//		dify = mean[i] - f0;
//	//		for (k = 0; k < basicEventsCount; k++){
//	//			node = basicEvents[k];
//	//			density = node->getDensity ()->getParameterDensity(0);
//	//			varianceBasicEvent = density->getVariance();
//	//			meanProb = density->getMean ();
//	//			probAux = x[k];
//	//			derivative = dify/(probAux - meanProb);
//	//			vy = pow (derivative, 2)*varianceBasicEvent;
//	//			conditionalVariance[i][k] = vy;
//	//			varianceProbTop += vy;
//	//		}
//	//		for (k = 0; k < basicEventsCount; k++)
//	//			conditionalVariance[i][k] /= varianceProbTop;
//	//	}
//	//}
//	//lhc->QuickSort (mean, 0, numberOfSamples - 1);
//	//lhc->QuickSort (variance, 0, numberOfSamples - 1);
//	//cout << "Mean" << "\t" << "f(t)" << "\t" << "F(t)" << endl;
//	//lhc->reduce (intervals, numberOfSamples
//	//	, mean, probability, topMean, f_topMean, F_topMean);
//	//cout << "Variance" << "\t" << "f(t)" << "\t" << "F(t)" << endl;
//	//lhc->reduce (intervals, numberOfSamples
//	//	, variance, probability, topVariance, f_topVariance, F_topVariance);
//	//top->setCentralTendencyMeasures (intervals, topMean
//	//	, f_topMean, F_topMean);
//	//top->setDispersionMeasures (intervals, topMean
//	//	, f_topMean, F_topMean);
//	//if (sensitivity){
//	//	for (k = 0; k < basicEventsCount; k++){
//	//		node = basicEvents[k];
//	//		for (i = 0; i < numberOfSamples; i++)
//	//			aux[i] = conditionalVariance[i][k];
//	//		lhc->QuickSort (aux, 0, numberOfSamples - 1);
//	//		cout << "Variance dfdx" << k + 1 << "\t" << "f(t)" << "\t" << "F(t)" << endl;
//	//		lhc->reduce (intervals, numberOfSamples, 
//	//			aux, probability, deriv, deriv, deriv);
//	//		node->setDerivativeMeasures (intervals, deriv
//	//			, f_deriv, F_deriv);
//	//	}
//	//}
//
//
//	//deleting
//	//top->deleteMeasures ();
//	//for (k = 0; k < basicEventsCount; k++){
//	//	node = basicEvents[k];
//	//	node->deleteMeasures (sensitivity);
//	//}//
//
//
//	//Criar PDF da media e do desvio da media do evento topo
//	//Ordenar e Criar CDF
//	
//	//delete [] mean;
//	//delete [] variance;
//	//delete [] probability;
//	//delete [] aux;
//	//delete [] x;
//	//delete [] a;
//	//delete [] b;
//	//delete [] p;
//	//delete [] topMean;
//	//delete [] f_topMean;
//	//delete [] F_topMean;
//	//delete [] topVariance;
//	//delete [] f_topVariance;
//	//delete [] F_topVariance;
//	//delete [] deriv;
//	//delete [] f_deriv;
//	//delete [] F_deriv;
//	//for (i = 0; i < numberOfSamples; i++)
//	//	delete [] conditionalVariance[i];
//	//delete [] conditionalVariance;
//	//for (i = 0; i < numberOfStrata; i++)
//	//	delete [] percentiles[i];
//	//delete [] percentiles;
//	//delete lhc;
//	//delete desimgen;
//
//	//runLatinHyperCube(bdd)...
//	//pra pegar prob do evento topo: bdd.getTopProb(top);
//	//pra pegar density: bdd.getBasicEvents()[i]->getDensity()->getParameterDensity(parameterIndex)
//	return 0;
//}
//
//int Facade::containsFT(const string &FT_label){
//	int result = 0;
//	FT_Node* node = getFT_node(FT_label);
//	if (node != 0 && node->isAdded()) {
//		result = 1;
//	}
//	return result;
//}
//int Facade::containsBE(const string &BE_label){
//	int result = 0;
//	FT_Node* node = getFT_node(BE_label);
//	if (node != 0 && node->isAdded()) {
//		result = 1;
//	}
//	return result;
//}
//
//int Facade::containsBBN(const string &BBN_label){
//	int result = 0;
//	BBN_DNode* node = getBBN_node(BBN_label);
//	if (node != 0 && node->isAdded()) {
//		result = 1;
//	}
//	return result;
//}
//
//int Facade::containsESD(const string &ESD_label){
//	int result = 0;
//	ET_Node* node = getET_node(ESD_label);
//	if (node != 0 && node->isAdded()) {
//		result = 1;
//	}
//	return result;
//}
////int Facade::createBlockDiagram(string diagramLabel){
////	vector<string> vec(0);
////	this->addFTNode(diagramLabel, FT_Auxiliar::LOG_AND, 0,vec);
////	return 0;
////}
//
//void Facade::evaluateTimeProbability(const string& FT_nodeLabel, vector<double>& times, vector<double>& unreliabilities){
//	double unreliability = 0.0,
//		diff = 1,
//		delta = .1,
//		time = 0;
//	//FT_Node* top = this->getFT_node(FT_nodeLabel);
//	//FT_BDD *ft_bdd = new FT_BDD();
//	//CALCULATING   t FOR WHICH F(t)=1
//	//getting the lower and upper bounds of t
//	int i=0;
//	double
//		tLower = 0,
//		tUpper = 0,
//		tBeforeLower=0;
//	while(unreliability==0){
//		i++;
//		tBeforeLower = tLower;
//		tLower = tUpper;
//		tUpper = pow(2.0,i);
//		this->et_bdd->evaluateDynamicTopProb(this->initiator->actualBddSet, this->initiator->getChildS(), 0, tUpper);
//		unreliability = this->initiator->getChildS()->getProb();
//	}
//	time = tLower;
//	while(diff>0){
//		i++;
//		tBeforeLower = tLower;
//		tLower = tUpper;
//		tUpper = pow(2.0,i);
//		diff = -unreliability;
//		this->et_bdd->evaluateDynamicTopProb(this->initiator->actualBddSet, this->initiator->getChildS(), 0, tUpper);
//		unreliability = this->initiator->getChildS()->getProb();
//		diff += unreliability;
//	}
//	tUpper = tLower;
//	tLower = tBeforeLower;
//	//refining the search
//	double t = tUpper;//SE AFTER... this->getSimulationTime(tLower, tUpper, this->initiator, unreliability);
//	
//	//ELABORATING THE CDF
//	int numberOfEvaluations = 200;
//	delta = (t-0)/numberOfEvaluations;
//	time+= delta;
//	while(time<=t && diff!=0){
//		this->et_bdd->evaluateDynamicTopProb(this->initiator->actualBddSet, this->initiator->getChildS(), 0, time);
//		diff = -unreliability;
//		unreliability = this->initiator->getChildS()->getProb();
//		diff += unreliability;
//		unreliabilities.push_back(unreliability);
//		times.push_back(time);
//		time+=delta;
//	}
//	cout<<"# iterations= "<<(time/delta)<<endl;
//}
//
//int Facade::fixEvent(const string &ESD_nodeLabel, double ESD_nodeProb){
//	ET_Node* node = getET_node(ESD_nodeLabel);
//	node->setProb(ESD_nodeProb);
//	return 0;
//}
//
//int Facade::fixEvent(const string &ESD_nodeLabel, const int& DENSITY_CODE, const vector<string>& parameters ){
//	ET_Node* node = getET_node(ESD_nodeLabel);
//	this->addBENode(ESD_nodeLabel, DENSITY_CODE, parameters);
//	FT_Node* topEvent = this->getFT_node(ESD_nodeLabel);
//	node->setFT_TopEvent(topEvent);
//	return 0;
//}
//
//BBN_DNode* Facade::getBBN_node(string bbn_nodeLabel){
//	BBN_DNode* node =NULL;
//	if(belongsToBBNNodes(this->bbn_nodes, bbn_nodeLabel))
//		node = this->bbn_nodes[this->searchedIndex];
//	return node;
//}
//
//double* Facade::getBBNNodeDensity(string &BBN_nodeLabel){
//	BBN_DNode* node = this->getBBN_node(BBN_nodeLabel);
//	double* result = new double[node->getDensity().size()];
//	for (int i = 0; i < node->getDensity().size(); i++){
//		result[i] = node->getDensity()[i];
//	}
//	
//	return result;
//}
//
////double Facade::getInverseValue(const string& BE_nodeLabel, const int parameterIndex, const double CDF_value){
////	FT_Node* node = getFT_node(BE_nodeLabel);
////	double value = node->getDensity()->getParameterDensity(parameterIndex)->getInverseValue(CDF_value);
////	return value;
////}
//double Facade::getCDF(const int& DENSITY_CODE, const vector<double>& parameters, double time){
//	Density * density = NULL;
//	if(DENSITY_CODE == this->DIRAC_DENSITY){//PROBABILITY
//		density = new Dirac(parameters[0]);
//		//node->setDensity(density);
//		//node->setProb(parameters[0]);
//	}
//	else if(DENSITY_CODE == this->EXPONENTIAL_DENSITY){//SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)//there is a bug, the scaling is in fact the rate
//		density = new Exponential(parameters[0]);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->GAMMA_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		density = new Gamma(parameters[0], parameters[1]);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->NON_PARAMETRIC_DISCRETE_DENSITY){//(x0, f_x0), (x1, f_x1),... (each pair of values implies in one value and its respective probability)
//		int n = parameters.size()/2;
//		double* x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		double* F_x = FT_Auxiliar::getNewDouble(n);//new double[n];
//		for(int i=0, j = 0; i<n; i++, j++){
//			x[i] = parameters[i + j];
//			F_x[i] = parameters[i + j +1];//modified
//		}
//		density = new NonParametricProbabilityDistribution(x, F_x, n);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->LOGNORMAL_DENSITY){//MEDIAN, STANDARD DEVIATION
//		density = new Lognormal(parameters[0], parameters[1]);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->WEIBULL_DENSITY){//SHAPPING, SCALING (the measure unit of the SCALING is the same of the time, i. e., hours, days, ...)
//		density = new Weibull(parameters[0], parameters[1]);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->TRIANGULAR_DENSITY){//LOWER, MODE, UPPER
//		density = new Triangular(parameters[0], parameters[1],parameters[2]);
//		//node->setDensity(density);
//	}
//	else if(DENSITY_CODE == this->UNIFORM_DENSITY){//LOWER, UPPER
//		density = new Uniform(parameters[0], parameters[1]);
//		//node->setDensity(density);
//	}
//	//node->getDensity()->setNumberOfParametersDensities(parameters.size());
//	double result = density->getCDF(time);
//	delete density;
//	return result;
//}
//
//int Facade::getSystemState(const string firstBlockLabel){
//	FT_Node* top = this->getFT_node(firstBlockLabel);
//	FT_BDD topBdd;
//	int result = topBdd.getSystemState(top);
//	return result;
//}
//
//int Facade::getCutCount(){
//	return this->cuts.size();
//}
//
//double Facade::getCutProbability(int index){
//	return this->probs[index];
//}
//
//vector<string> Facade::getCutString(int index){
//	return this->cuts[index];
//}
//
//Density* Facade::getDensity(string densityLabel){
//	Density* density = NULL;
//	if(belongsToDensities(Facade::densities, densityLabel))
//		density = Facade::densities[this->searchedIndex];
//	return density ;
//}
//
//ET_Node* Facade::getET_node(string et_nodeLabel){
//	ET_Node* node =NULL;
//	if(belongsToESDNodes(this->et_nodes, et_nodeLabel))
//		node = this->et_nodes[this->searchedIndex];
//	return node;
//}
//FT_Node* Facade::getFT_node(string ft_nodeLabel){
//	FT_Node* node =NULL;
//	if(belongsToFTNodes(this->ft_nodes, ft_nodeLabel))
//		node = this->ft_nodes[this->searchedIndex];
//	return node;
//}
//double Facade::getSimulationTime(double tLower, double tUpper, ET_Node* top, const double unreliability){
//	double 	
//		tBefore = (tLower+tUpper)/2, 
//		t=tBefore, 
//		percetnError = (tUpper-tLower)/(tUpper+1e-8),
//		diff=0,
//		dynamicUnreliability = unreliability;
//	this->et_bdd->evaluateDynamicTopProb(top->actualBddSet,top->getChildS(), 0, tBefore);
//	dynamicUnreliability =   top->getChildS()->getProb();
//	diff = unreliability-dynamicUnreliability;
//	while ( percetnError> 1e-2){
//		while(diff==0 && percetnError> 1e-2){
//			//pensar........
//			t = tBefore;
//			tUpper = t;
//			tBefore = (tLower+tUpper)/2;
//			percetnError = (tUpper-tLower)/(tUpper+1e-8);
//			this->et_bdd->evaluateDynamicTopProb(top->actualBddSet,top->getChildS(), 0, tBefore);;
//			dynamicUnreliability =   top->getChildS()->getProb();
//			diff = unreliability - dynamicUnreliability;
//		}
//		if( percetnError> 1e-2){
//			tLower = tBefore;
//			double tAfter = (tLower+tUpper)/2;
//			this->et_bdd->evaluateDynamicTopProb(top->actualBddSet, top->getChildS(), 0, tAfter);
//			dynamicUnreliability =   top->getChildS()->getProb();
//			diff = unreliability-dynamicUnreliability;
//			while(diff!=0 && percetnError> 1e-2){
//				tLower = tAfter;
//				tAfter = (tLower+tUpper)/2;
//				percetnError = (tUpper-tLower)/(tUpper+1e-8);
//				this->et_bdd->evaluateDynamicTopProb(top->actualBddSet, top->getChildS(), 0, tAfter);
//				dynamicUnreliability =   top->getChildS()->getProb();
//				diff = unreliability - dynamicUnreliability;
//			}
//			tUpper = tAfter;
//			percetnError = (tUpper-tLower)/(tUpper+1e-8);
//		}
//	}
//	return t;
//}
//
//int Facade::elaborate_k_out_n_gate(int k, const vector<string> children, vector<string>& andChildren, int* indexes){
//		//adding the actual combination
//		//FT_Node* andChild = new FT_Node(Facade::FT_AND, this->ET_domain);
//		char count[200];
//		static int inc = -1;
//		inc++;
//		_itoa(inc,  count, 200); 
//		string label = "andChild_";
//		label += count;
//		andChildren.push_back(label);//andChild->setLabel(label);
//		vector<string> actualChildren(0);
//		int i =0;
//		//cout<<endl;
//		for(int j=0; j<k; j++){
//			i = indexes[j];
//			string sti = children[i];
//			actualChildren.push_back(sti);
//			//cout<<i<<", ";
//			//FT_Node* childi = NULL;
//			//if(!this->belongsToFTNodes(this->ft_nodes, sti)){
//			//	childi = new FT_Node(FT_Auxiliar::LOG_NULL, gate->getET_Domain());
//			//	childi->setLabel(sti);
//			//	this->ft_nodes.insert(this->ft_nodes.begin()+this->searchedIndex, childi);
//			//}
//			//else{
//			//	FT_Node* original = this->ft_nodes[this->searchedIndex];
//			//	childi = original->getClone(NULL);	
//			//}
//			//andChild->addChild(childi);
//		}
//		Facade::addFTNode(label, Facade::FT_AND, 0, actualChildren);
//		//gate->addChild(andChild);
//
//		//componding the next combination
//		int n = children.size();
//		i = k-1;
//		for(i; indexes[i]==n-(k-i) && i>=0; i--){
//			//need do nothing!!!
//		}
//		if(i>=0){
//			indexes[i]++;
//			for(int j = i+1; j<k; j++){
//				indexes[j] = indexes[j-1]+1;
//			}
//			this->elaborate_k_out_n_gate(k, children, andChildren, indexes);
//		}
//		//else{
//		//	Facade::addFTNode(topLabel, Facade::FT_OR, 0, topChildren);
//		//}
//	return 0;
//}
//
//void Facade::initializeTerminals(){
//	terminalsLabels.push_back("Sucess");
//	terminalsLabels.push_back("Failure");
//	if(this->et_bdd!=0)
//		delete this->et_bdd;
//	this->et_bdd = new ET_BDD();
////	this->Sucess = new ET_Node (this->terminalsLabels[0]);
////	this->Failure = new ET_Node (this->terminalsLabels[1]);
////	this->et_nodes.push_back(Failure);
////	this->et_nodes.push_back(Sucess);
//	FT_Auxiliar::inicializeTerminals();
//}
//int Facade::linkESDToBBNNodeLevel(const string &ESD_nodeLabel, const string &postulatedBBN, const string &linkedLevel){
//	BBN_DNode* bbn_node = getBBN_node(postulatedBBN);
//	bool levelFound = false;
//	int i=0;
//	while(!levelFound){
//		if(bbn_node->getLevelName(i)==linkedLevel){
//			levelFound = true;
//			bbn_node->linkedESDIndex = i;
//		}
//		i++;
//	}
//	ET_Node* et_node = getET_node(ESD_nodeLabel);
////	this->updateBBNDomain(bbn_node, et_node->getET_Domain());
//	et_node->BBN_effect = bbn_node;
//	this->et_nodesToSolveBBNs.push_back(et_node);
//	return 0;
//}
//
//int Facade::linkEvent(const string &ESD_nodeLabel, const string &postulatedBBN){
//	BBN_DNode* bbn_node = getBBN_node(postulatedBBN);
//	ET_Node* et_node = getET_node(ESD_nodeLabel);
//	this->updateBBNDomain(bbn_node, et_node->getET_Domain());
//	et_node->BBN_effect = bbn_node;
//	this->et_nodesToSolveBBNs.push_back(et_node);
//	return 0;
//}
//
//double Facade::quantify(const string & ESD_targetNodeLabel){
//	ET_Node* node = this->getET_node(ESD_targetNodeLabel);
//	return node->getProb();
//}
//int Facade::quantifyMeanUncertainty(const string & ESD_targetNodeLabel, double*& x
//									, double*& fx, double*& Fx, double*& percentiles, int& n){
//	const int k = 7;
//	double p[k] = {0.01, 0.05, 0.10, 0.50, 0.90, 0.95, 0.99};
//	percentiles = new double [k];
//	ET_Node* node = this->getET_node(ESD_targetNodeLabel);
//	node->getMeanUncertaintyDistributions(x, fx, Fx);
//	n = node->FT_TopEvent->uncertainty_meanVectorSize;
//	for (int j = 0; j < k; j++){
//		int i = 0;
//		while(Fx[i]<p[j] && i<n-1){
//			i++;
//		}
//		double v = 0;
//		if(i>0){
//			double x_ = x[i-1];
//			double y = x[i];
//			double F_x = Fx[i-1];
//			double Fy = Fx[i];
//			double f = (Fy - F_x)/(y-x_);
//			v = (p[j]-F_x)/f + x_;
//		}
//		else{
//			if(x[0]/x[n-1]-1< 10e-100)
//				v = x[0];
//			else
//				v = p[j]*x[0] / Fx[0];
//		}
//		percentiles[j] = v;/*FT_Auxiliar::desimgen->generateContinuousEmpiricalDeviate
//						(n, p[j], x, Fx);*/
//	}
//	return 0;
//}
//
////int Facade::quantifyVarUncertainty(const string & ESD_targetNodeLabel, double*& x, double*& fx, double*& Fx, int& n){
////	ET_Node* node = this->getET_node(ESD_targetNodeLabel);
////	node->getVarUncertaintyDistributions(x, fx, Fx);
////	n = node->FT_TopEvent->uncertainty_varVectorSize;
////	return 0;
////}
//int Facade::select(const string &ESD_initiator, const string &ESD_endstate){
//	ET_BDD* et_bdd = new ET_BDD();
//	et_bdd->evaluateActualPath(this->getET_node(ESD_initiator), this->getET_node(ESD_endstate));
//	delete(et_bdd);
//	return 0;
//}
//
//int Facade::selectAll(const string &ESD_initiator){
//	//int m = this->ft_nodesToSolveBBNs.size();
//	//for(int i=0; i<m; i++){
//	//	FT_Node* ni = this->ft_nodesToSolveBBNs[i];
//	//	if(ni->getProb()<0)
//	//		ni->setProb(ni->BBN_effect);
//	//}
//	//int n = this->et_endStates.size();
//	//for(int i=0; i<n; i++){
//	//	string acEnd = this->et_endStates[i]->getLabel();
//	//	this->select(ESD_initiator, acEnd);
//	//}
//	//this->et_endStates.clear();
//
//	//int m = this->bbn_nodes.size();
//	//for(int i=0; i<m; i++){
//	//	cout<<this->bbn_nodes[i]->getLabel()<<endl;
//	//}
//	if(! hasBeenInitialized){
//		this->initiator = this->getET_node(ESD_initiator);
//		this->solveET("");
//		hasBeenInitialized = true;
//	}
//	return 0;
//}
//int Facade::setCPT(const string &BBN_nodeLabel, const vector<string>& parents, const vector<double> &cpt){
//	BBN_DNode* bbn_node = this->getBBN_node(BBN_nodeLabel);
//	int nLevels = bbn_node->getLevelsCount();
//	int nRows = cpt.size()/nLevels;
//	int k=0;
//	bbn_node->generateCPT(nRows, nLevels);
//	for(int i=0; i<nRows; i++)
//		for(int j=0; j<nLevels; j++){
//			bbn_node->setProb(i, j, cpt[k]);
//			k++;
//		}
//	return 0;
//}
//
//int Facade::setEventState(const string blockLabel, const int eventState){
//	FT_Node* node = this->getFT_node(blockLabel);
//	node->setEventState(eventState);
//	return 0;
//}
//
//int Facade::setEvidence(const string &BBN_nodeLabel,int state){
//	BBN_DNode* node = this->getBBN_node(BBN_nodeLabel);
//	node->setEmpiricalEvidence(state);
//	return 0;
//}
//
//int Facade::setEvidence(const string &BBN_nodeLabel, vector<double>& likelihood){
//	BBN_DNode* node = this->getBBN_node(BBN_nodeLabel);
//	node->setSubejctiveEvidence(likelihood);
//	return 0;
//}
//int Facade::setMissionTime(const double missionTime){
//	FT_Auxiliar::MISSION_TIME = missionTime;
//	return 0;
//}
//
//void Facade::solveBBN(const string BBN_nodeLabel){
//	BBN_DNode* node = this->getBBN_node(BBN_nodeLabel);
//	vector<BBN_DNode*> newForest (0);
//	newForest.push_back(node);
//	node->wasVisited = true;
//	BBN_Auxiliar::loadAssociatedForest(node, newForest);
//	int size = newForest.size();
//	for(int i=0; i<size; i++){
//		BBN_DNode* ni = newForest[i];
//		ni->setOrder(i);
//	}
//	BBN_Auxiliar::allDNodes = newForest;
//
//	BBN_UNode uNode(true);
//	uNode.calculePosteriori();
//	BBN_Auxiliar::evidencedDNodes = BBN_Auxiliar::auxEvidencedDNodes;
//
//	BBN_Auxiliar::readDensities();
//}
//void Facade::solveET(const string ESD_initiatorLabel){
//	//ET_Node* initiator = this->initiator;
////	this->et_bdd->readET_BDD(initiator);
//	//int n = FT_Auxiliar::repeatedEvents.size();
//	//for(int i=n-1; i>=0; i--){
//	//	FT_Node* nodei = FT_Auxiliar::repeatedEvents[i];
//	//	if(nodei->getLogic()!='n')
//	//		FT_Auxiliar::repeatedEvents.erase(FT_Auxiliar::repeatedEvents.begin()+i);
//	//}
//	//n = this->ft_nodesToSolveBBNs.size();
//	//for(int i=0; i<n; i++){
//	//	FT_Node* ni = this->ft_nodesToSolveBBNs[i];
//	//	ni->setProb(ni->BBN_effect);
//	//}
//	//n = this->et_nodesToSolveFTs.size();
//	//for(int i=0; i<n; i++){
//	//	ET_Node* nodei = this->et_nodesToSolveFTs[i];
//	//	//FT_Node::Test::readVecRepEvents();
//	//	//FT_Node::Test::readTree(nodei->FT_TopEvent);
//	//	nodei->setProb(nodei->FT_TopEvent);
//	//}
//	//n = this->et_nodesToSolveBBNs.size();
//	//for(int i=0; i<n; i++){
//	//	ET_Node* ni = this->et_nodesToSolveBBNs[i];
//	//	ni->setProb(ni->BBN_effect);
//	//}
//
//	this->et_bdd->performBDDSets(this->initiator, NULL, false);
//	//vector<ET_path> vecPaths = this->et_bdd->getSpecificResults();
//	//vector<ET_overallResult> vecOverallPaths = this->et_bdd->getOverallResults();
//	//this->et_bdd->readET_BDDPaths(vecPaths);
//	//this->et_bdd->readET_BDDOverallPaths(vecOverallPaths);
//	//cout<<"overall fault Probability= "<<this->et_bdd->getOverallFaultProbability()<<endl;
//	//ET_Node* childF = this->getET_node("F2");
//	//n = childF->getCutCount();
//	//cout<<childF->getLabel()<<": "<<childF->getProb()<<endl;
//	//for(int i=0; i<n; i++){
//	//	cout<<childF->getCutString(i)<<", "<<childF->getCutProbability(i)<<endl;
//	//}
////	FT_Auxiliar::inicializeTerminals();
//}
//void Facade::solveFT(const string FT_topLabel){
//	int n = this->ft_nodesToSolveBBNs.size();
//	for(int i=0; i<n; i++){
//		FT_Node* ni = this->ft_nodesToSolveBBNs[i];
//		ni->setProb(ni->BBN_effect);
//	}
//	FT_Node* top = this->getFT_node(FT_topLabel);
//	FT_BDD* bdd = new FT_BDD(top);
//
//	//vector<MCS> mcs = bdd->getMCSs();
//	//bdd->readMCSs(mcs);
//	//cout<<"topProb= "<<	bdd->getTopProb(top)<<endl;
//}
//
//Facade::Facade(void){
//	this->et_bdd = 0;
//	int tmpFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );
//
//	// Turn on leak-checking bit.
//	tmpFlag |= _CRTDBG_LEAK_CHECK_DF;
//
//	// Turn off CRT block checking bit.
//	tmpFlag &= ~_CRTDBG_CHECK_CRT_DF;
//
//	// Set flag to the new value.
//	_CrtSetDbgFlag( tmpFlag );
//
//	this->initializeTerminals();
//	hasBeenInitialized = false;
//}
//
//void Facade::updateBBNDomain(BBN_DNode* bbn, string domain){
//	//if(!bbn->wasVisited2){
//	//	bbn->domain = domain;
//	//	bbn->wasVisited2 = true;
//	//	int nPar = bbn->getParentsCount();
//	//	for(int i=0; i<nPar; i++){
//	//		BBN_DNode* pari  = bbn->getParent(i);
//	//		updateBBNDomain(pari, domain);
//	//	}
//	//}
//}
//Facade::~Facade(void){
//	//FT_Auxiliar::deleteNews();
//	this->et_bdd->deleteNews();
//	delete this->et_bdd;
//	this->et_bdd=0;
//	delete FT_Auxiliar::t0;
//	delete FT_Auxiliar::t1;
//	delete FT_Auxiliar::desimgen;
//
//}
//}
