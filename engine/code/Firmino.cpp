#include "stdafx.h"
#include ".\firmino.h"
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

namespace Engine{
Firmino::Firmino(){
}

Firmino::Firmino(double min, double max){
	vector<double> pr(2);
	int answer = 0;
	pr[answer]= 1.0; pr[1-answer] = 1 - pr[answer];//the chose interval was [min, max], with cr=100%
	//this->root = new Node(min, max, pr);
	//zoomInto(root, pr, 0);
}
Firmino::Firmino(Node* root){
	this->root = root;
	vector<double> pr(2);
	int answer = 0;
	pr[answer]= 1.0; pr[1-answer] = 1 - pr[answer];//the chose interval was [min, max], with cr=100%
//	zoomInto(root, pr, 0);
}
void Firmino::readLeafs(Node* node){//BUGGED
	if(node->getChildrenCount()==0){
		double parCred = 1;
		if(node->getParentsCount()>0){
			Node* parent = node->getParent(0);
			parCred = parent->credibility;
		}
		node->credibility*=parCred;
		double fx = node->credibility/(node->upper - node->lower);
		cout<<"f("<<node->lower<<", "<<node->upper<<")="<<fx<<"\t";
	}
	else{
		readLeafs(node->getChild(0));
		readLeafs(node->getChild(1));
	}
}

int Firmino::readLeafs(Node*& node, string& xfx, int & nPairs, vector<double>& x, vector<double>& Fx, double & parentProb){//BUG
	if(node->getChildrenCount()==0){
		//double parCred = 1;
		//if(node->getParentsCount()>0){
		//	Node* parent = node->getParent(0);
		//	parCred = parent->credibility;
		//}
		//node->credibility*=parCred;//BUG: everytime readLeafs is called, node cred is updated, what in turn is wrong...
		double nodeCred = parentProb*node->credibility;
		char sLower[4000], sUpper[4000];
		sprintf_s(sLower, "%f", node->lower);
		sprintf_s(sUpper, "%f", node->upper);
		double _fx = nodeCred /(node->upper - node->lower);
		char sf[4000];
		sprintf_s(sf, "%f", _fx);
		xfx += sLower; xfx += ";";xfx += sf; xfx += ";"; xfx += sUpper; xfx += ";";xfx += sf; xfx+=";";
		nPairs += 2;
		//TO MAKE THE CDF FOR STATISTICAL MEASURES...
		x.push_back(node->upper);
		int before = Fx.size()-1;
		Fx.push_back(nodeCred +Fx[before]);
	}
	else{
		parentProb*= node->credibility;
		Node* ch0 = node->getChild(0);
		readLeafs(ch0, xfx, nPairs, x, Fx, parentProb);
		Node* ch1 = node->getChild(1);
		readLeafs(ch1, xfx, nPairs, x, Fx, parentProb);
	}
	return 1;
}

void Firmino::zoomInto(Node* parent, vector<double> pr, int answer){
	//static int nAnswers = 0;
	//cout<<endl;
	//readLeafs(this->root);
	//if(pr[answer]>.5){
	//	double answerTime=clock();
	//	nAnswers++;
	//	double middle = (parent->lower + parent->upper)/2.0;
	//	cout<<endl;
	//	char sLower[4000], sUpper[4000], sMiddle[4000];
	//	sprintf_s(sLower, "%f", parent->lower);
	//	sprintf_s(sMiddle, "%f", middle);
	//	sprintf_s(sUpper, "%f", parent->upper);
	////	_itoa(parent->lower,  sLower, 1000); _itoa(middle,  sMiddle, 1000); _itoa(parent->upper,  sUpper, 1000); 
	//	string strDecisionItem = ") Eh mais provavel que a variavel pertenca a (0) [";
	//	strDecisionItem += sLower;
	//	strDecisionItem +=", ";
	//	strDecisionItem +=sMiddle;
	//	strDecisionItem +="] ou a (1) [";
	//	strDecisionItem +=sMiddle;
	//	strDecisionItem +=", ";
	//	strDecisionItem +=sUpper;
	//	strDecisionItem +="] ? ";
	//	//setDecisionItem(str);
	//	//setDecisionItemUncertainty
	//	cout<<nAnswers<<strDecisionItem ;
	//	cin>>answer	;
	//	answerTime=clock();
	//	string strUncertainItem = "	* Qual nivel de credibilidade voce atribui para sua escolha? ";
	//	cout<<endl<<strUncertainItem ;
	//	cin>>pr[answer];
	//	pr[1-answer] = 1 - pr[answer];
	//	vector<Node*> node(2);
	//	node[0] = new Node(parent->lower, middle, pr[0]);
	//	node[1] = new Node(middle, parent->upper, pr[1]);
	//	parent->addChild(node[0]);
	//	parent->addChild(node[1]);
	//	zoomInto(node[answer], pr, answer);
	//	answerTime-=clock();
	//	//judgments_cout<<nAnswers<<") Do you think the quantity most probably belong to (0) ["<<triple[0]<<", "<<triple[1]<<"] or to (1) ["<<triple[1]<<", "<<triple[2]<<"] ?"<<answer;
	//	//judgments_cout<<"; answerTime: "<<(-answerTime/CLOCKS_PER_SEC)<<" sec."<<endl;
	//	//judgments_cout<<"	, What credibility do you assign to this answer ? "<<pr[answer];		
	//	//judgments_cout<<"; answerTime: "<<(-answerTime/CLOCKS_PER_SEC)<<" sec."<<endl;
	//}
}

Firmino::~Firmino()
{
}
}
