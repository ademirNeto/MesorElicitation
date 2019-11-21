#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "stdlib.h"

#include "vcclr.h"
#include <string>
#include "Node.h"
#include "EngineFacade.h"

using namespace std;
using namespace System;

namespace Engine {

	public ref class EngineInterface
	{
		static EngineFacade ef;
	public:
		static char FIRMINO = 'F';
		static char BISECTION = 'B';
		//static String^ nextQuestion = "";
		static double nextLower = -1;
		static double nextUpper = -2;
		//static char DIRECT = 'D';

		/*
		question is appended with the partition {[lower, center), [center, upper]}:
			If Firmino's method is considerer, then center=(lower+upper)/2. If bisection method is considered, center= local median ;
		cred is the level of credibility assigned to the expert choice: 
			If Firmino's method is considerer, cred is assigned by the expert. If bisection method is considered, cred=0.5;
		index == (-1) means that if -1, [lower, upper] is the root interval; index != (-1) is usefull for Firmino's method:
				if 0 the expert has chose [lower, middle]; if 1 the expert has chose [middle, upper]); 
		it is returned q = "a; b; n; xi; yi; Mean; Median; Mode; Variance; L1; L2;L3" where

		(q[0], q[1])= [a, b], the next interval to be partitioned:	
			If Firmino's method is considerer, then [a, b] is chose by the expert. If bisection method is considered, [a,b] is the next minimum quantile;
		q[2]: n is the number of points of the histogram
		q[3], q[4], ..., q[2+2*n]: (xi, yi) is the iº point to be scatched in the histogram
		q[q.size() - 8]:Mean
		q[q.size() - 7]:Median
		q[q.size() - 6]:Mode 
		q[q.size() - 5]:Variance //
		q[q.size() - 4]: L0 is the conditioning part of the next question (" Dado que o valor da variável está entre ...")
		q[q.size() - 3]: L1 is the first part of the next question (" seu verdadeiro valor mais provavelmente pertenca a:")
		q[q.size() - 2]: L2 is the second part of the next question ("[lower, middle)")
		q[q.size() - 1]: L3 is the third part of the next question ("[middle, upper]")
		*/
		static String^ getNextBinaryQuestion(double lower, double center, double upper, double cred, int index, char METHOD){
			Node* root = 0;
			String^ q = "";
			double middle = -999;

			if(index==-1){//Root question (min, max)
				if(ef.nodeDistribution!=NULL){
					ef.getNodeDistributionRoot(root);
					delete root;
				}
				middle = center;
				root = new Node(lower, center, upper, 1.0);
				ef.initializeNodeDistribution(root);			
				ef.updateNodeDistribution(root, root->str_xfx, root->xSize);
				nextLower= lower; nextUpper=upper;
				//cout<<root->xSize<<": "<<endl<<root->str_xfx<<endl;
			} else{
				ef.getNodeDistributionRoot(root);
				Node* parent = NULL;
				/*ef.getNode(root, lower, upper, parent);	*/
				//double key = (lower+upper)/2.0;
				ef.getNode(root, lower, upper, parent);	
				ef.updateLastParent(parent);
				//if(parent->getChildrenCount()>0)
					//parent->removeChildren();
				vector<Node*> ch(2);
				ch[0]= new Node(lower, (lower+center)/2, center, .5); parent->addChild(ch[0]);//ver se alterações em ch[i] sao atualizadas em getChild[i]...OK!!
				ch[1]= new Node(center, (center+upper)/2, upper, .5);parent->addChild(ch[1]);
				if (METHOD==BISECTION){//for bisection method
					parent->center = center;
					Node* next = 0; ef.getNodeFromSameGeneration(root, parent->getGeneration(), next);
					lower = next->lower;
					middle = next->center;
					upper = next->upper;
					nextLower= lower; nextUpper=upper;
				}
				else if (METHOD==FIRMINO){//for Firmino's method
					if(index==0){
						nextLower= lower; nextUpper=center;
						middle = (lower+center)/2.0;
						upper=center;
					}else if(index == 1){
						nextLower= center; nextUpper=upper;
						middle = (center+upper)/2.0;
						lower=center; 
					}
					ch[index]->credibility= cred;
					ch[1-index]->credibility = (1-cred);
				}
				
				//cout<<node->xSize<<": "<<endl<<node->str_xfx<<endl;
			}
			ef.updateNodeDistribution(root, root->str_xfx, root->xSize);
			String^ L0 = " Dado que a quantidade assume valores entre ";
			String^ L1 = "seu verdadeiro valor mais provavelmente está entre:; ";
			String^ L2 = "[";
			String^ L3 = "[";
			L0 += lower; L0+=" e "; L0+= upper; L0+= ",;";
			L2 += lower; L2 +=", "; L2 +=middle;L2 +=") ou entre ; "; 
			L3 +=middle; L3 +=", "; L3 +=upper; L3 +="] ? ";
			q+=nextLower; q+=";"; q+=nextUpper;q+=";"; 
			q+=(root->xSize+";");
			q+=(gcnew String(root->str_xfx.c_str()));
			q+=L0; q+=L1; q+=L2; q+=L3;
			//q+= "trash";
			return q;//gcnew String(q.c_str());
		}
		//static int split(char* str, char* separator, vector<char*> list){
		//	char *frase = NULL;
		//	char *token = NULL;
		//	strcpy( frase, str );
		//	token= strtok( frase, separator);
		//	while( token ){
		//		list.push_back(token);
		//		token = strtok( NULL, " " );
		//	}
		//	return 1;

		//}

		//static int Somar(int valor1, int valor2){

		//	int resultado = valor1 + valor2;
		//	return resultado;

		//}

		//__declspec(dllexport) string getOption(double lower, double upper, int index){
		//	double middle = (lower + upper)/2.0;
		//	char sLower[4000], sUpper[4000];
		//	if(index == 0){
		//		sprintf_s(sLower, "", lower);
		//		sprintf_s(sUpper, "", middle);
		//	}else{
		//		sprintf_s(sLower, "", middle);
		//		sprintf_s(sUpper, "", upper);
		//	}
		//	string result =  "["; result+= sLower; result +=", "; result+=sUpper; result+= "]";

		//	return result;

		//}
		//__declspec(dllexport) wchar_t* getOption(double lower, double upper, int index){
		//	double middle = (lower + upper)/2.0;
		//	char sLower[4000], sUpper[4000];
		//	if(index == 0){
		//		sprintf_s(sLower, "", lower);
		//		sprintf_s(sUpper, "", middle);
		//	}else{
		//		sprintf_s(sLower, "", middle);
		//		sprintf_s(sUpper, "", upper);
		//	}
		//	wchar_t* result =  "["; result+= sLower; result +=", "; result+=sUpper; result+= "]";

		//	return result;

		//}
		//static String^ getQuestionInterface(String^ s, double lower, double upper, double cred, int index){

		//	char c[100000];
		//	string str = getQuestion(c, lower, upper, cred, index);
		//	//return str;
		//	//char *c2 = str;
		//	return gcnew String(str.c_str());
		//}


		/*
		question is initialized with the name of the parameter and appended with the [lower, upper] partition, regarding it middle point;
		cred is the level of credibility assigned to the expert choice
		index is the expert choice (if -1, [lower, upper] is the root interval; if 0 the expert has chose [lower, middle]; if 1 the expert has chose [middle, upper]; 
		*/
		//static string getQuestion(string question, double lower, double upper, double cred, int index){
		//	Node* node = new Node(lower, upper, cred);
		//	string q(question);

		//	double middle = (lower + upper)/2.0;
		//	if(index == 0){
		//		upper=middle;
		//	}else if(index == 1){
		//		lower = middle;
		//	}

		//	char sLower[4000], sUpper[4000], sMiddle[4000];
		//	sprintf_s(sLower, "%f", lower);
		//	sprintf_s(sMiddle,"%f", middle);
		//	sprintf_s(sUpper, "%f", upper);
		//	//	_itoa(parent->lower,  sLower, 1000); _itoa(middle,  sMiddle, 1000); _itoa(parent->upper,  sUpper, 1000); 
		//	q += " mais provavelmente pertenca a:; [";
		//	q += sLower;
		//	q +=", ";
		//	q +=sMiddle;
		//	q +="] ou a ; [";
		//	q +=sMiddle;
		//	q +=", ";
		//	q +=sUpper;
		//	q +="] ? ";
		//	//cout<<q<<endl;
		//	//question = q;

		//	//string s = "Hello";
		//	//char *sz;

		//	//sz = new char[s.length() + 1];
		//	//strcpy(question, q.c_str());
		//	return q;
		//}
		/*
		question is appended with the [lower, upper] partition, regarding its middle point: middle=(lower+upper)/2 ;
		cred is the level of credibility assigned to the expert choice
		index is the expert choice (if -1, [lower, upper] is the root interval; if 0 the expert has chose [lower, middle]; if 1 the expert has chose [middle, upper]; 
		it is returned q = "a; b; n; xi; yi; Mean; Median; Mode; Variance; L1; L2;L3" where
		q[0], q[1]: [a, b] is the interval chose by the expert
		q[2]: n is the number of points of the histogram
		q[3], q[4], ..., q[2+2*n]: (xi, yi) is the iº point to be scatched in the histogram
		q[q.size() - 7]:Mean
		q[q.size() - 6]:Median
		q[q.size() - 5]:Mode 
		q[q.size() - 4]:Variance 
		q[q.size() - 3]: L1 is the first part of the next question (" mais provavelmente pertenca a:")
		q[q.size() - 2]: L2 is the second part of the next question ("[lower, middle]")
		q[q.size() - 1]: L3 is the third part of the next question ("[middle, upper]")
		*/
		//static String^ getFirminoQuestion(double lower, double upper, double cred, int index){
		//	Node* node = 0;
		//	string q = "";
		//	double middle = (lower + upper)/2.0;
		//	char sLower[4000], sUpper[4000], sMiddle[4000], s_nPairs[400];
		//	sprintf_s(sLower, "%f", lower); sprintf_s(sMiddle,"%f", middle); sprintf_s(sUpper, "%f", upper);

		//	if(index==-1){
		//		node = new Node(lower, upper, 1.0);
		//		ef.initializeFirmino(node);			
		//		ef.updateFirminoDensity(node, node->str_xfx, node->xSize);
		//		//_itoa(this->id,  string, 1000);
		//		sprintf_s(s_nPairs, "%d", node->xSize);
		//		q+= sLower; q+=";"; q+=sUpper; q+=";"; q+=s_nPairs;q+=";";q+=node->str_xfx;
		//		cout<<node->xSize<<": "<<endl<<node->str_xfx<<endl;
		//	} else{
		//		Node* root = 0; ef.getFirminoRoot(root);
		//		Node* parent = NULL;
		//		double key = -1;
		//		if(index==0){
		//			key = upper;
		//			q+= sLower; q+=";"; q+=sMiddle; q+=";";
		//		}else if(index == 1){
		//			key = lower;
		//			q+= sMiddle; q+=";"; q+=sUpper; q+=";";
		//		}
		//		ef.getNode(root, key, parent);	
		//		node = parent->getChild(index);
		//		node->credibility = cred;
		//		parent->getChild(1-index)->credibility = (1-cred);
		//		ef.updateFirminoDensity(root, root->str_xfx, root->xSize);
		//		sprintf_s(s_nPairs, "%d", root->xSize);
		//		q+=s_nPairs;q+=";";q+=root->str_xfx;
		//		cout<<node->xSize<<": "<<endl<<node->str_xfx<<endl;
		//	}
		//	Node* ch0 = new Node(lower, middle, .5); node->addChild(ch0);
		//	Node* ch1 = new Node(middle, upper, .5); node->addChild(ch1);

		//	q += " mais provavelmente pertenca a:; ["; q += sLower; q +=", "; q +=sMiddle; q +="] ou a ; ["; q +=sMiddle; q +=", "; q +=sUpper; q +="] ? ";
		//	//q+= "trash";
		//	return gcnew String(q.c_str());
		//}

/*
		grid: the partition (vector of points) of the interval [min, max], previously determined by the expert
		cumulative: for a given point xi from the partition, it represents the cumulative P(X<=xi), the probabilirty of X be lesser than xi
		nPoints: the cardinality of the partition
		it is returned the string q = "Mean; Median; Mode; Variance" 

		*/
		static String^ getMeasuresFromPDF(array<double>^ grid, array<double>^ cumulative, int nPoints){
			int k=nPoints; //double* _x = new double; double* _Fx = cumulative;
			vector<double> x(k), Fx(k);
			for(int i=0; i<k; i++){
				x[i]=grid[i]; Fx[i] = cumulative[i];
			}
			string q = "";
			ef.getStatisticalMeasures(x, Fx, q, k); 

			return gcnew String(q.c_str());
		}
		//static String^ getMeasuresFromCDF(String^ xFx, int nPoints){
		//	int k=nPoints; 
		//	///*wchar_t*/String^ ch = ";";
		//	//array<String^> list= xFx->Split(ch);
		//	////vector<char*> list(0);
		//	////char* aux = toChar(xFx);
		//	////split(aux, ";", list);
		//	//
		//	//
		//	////double* _x = grid; double* _Fx = cumulative;
		//	//vector<double> x(k+1), Fx(k+1);
		//	//int j=0;
		//	//for(int i=0; i<=k; i++){
		//	//	x[i]=System::Convert::ToDouble(list[j]);j++;
		//	//	Fx[i]=System::Convert::ToDouble(list[j]);j++;
		//	//}
		//	string q = "";
		//	//ef.getStatisticalMeasures(x, Fx, q, k); 

		//	return gcnew String(q.c_str());
		//	//		return gcnew String("");
		//}
		////static String^  getFirmino_x(){
		////	Node* root = 0; ef.getFirminoRoot(root);
		////	return gcnew String(root->str_x.c_str());
		////}
		////static String^  getFirmino_fx(){
		////	Node* root = 0; ef.getFirminoRoot(root);
		////	return gcnew String(root->str_fx.c_str());
		////}
		////static int getFirmino_xSize(){
		////	Node* root = 0; ef.getFirminoRoot(root);
		////	return root->xSize;
		////}
		////static String^  getFirmino_actualPair(double lower, double upper){
		////	double key = (lower+upper)/2.0;
		////	Node* node = 0; ef.getNode(key);
		////	return gcnew String(root->str_fx.c_str());
		////}
		//static char* toChar(String^ s){

		//	pin_ptr<const wchar_t> wch = PtrToStringChars(s);

		//	// Convert to a char*
		//	size_t origsize = wcslen(wch) + 1;
		//	const size_t newsize = 100;
		//	size_t convertedChars = 0;
		//	char nstring[newsize];
		//	wcstombs_s(&convertedChars, nstring, origsize, wch, _TRUNCATE);

		//	return nstring;
		//}
		static int deleteNews(){
			Node* root = 0; ef.getNodeDistributionRoot(root);
			delete root;
			ef.deleteNews();
			return 1;
		}
		static void deleteChildren(double lower, double center, double upper){
			Node* lastParent= 0;
			ef.getLastParent(lastParent);
			lastParent->removeChildren();
			if(lastParent->getParentsCount() > 0){
				lastParent = lastParent->getParent(0);
			}
			ef.updateLastParent(lastParent);
			//Node* root=0;
			//ef.getNodeDistributionRoot(root);
			//Node* node = NULL;
			//ef.getNode(root, lower, upper, node);
			////node->removeChildren();
			////node->center = (node->lower+parent->upper)/2.0;
			//if(node->getParentsCount()>0){
			//	Node* parent = node->getParent(0);
			//	parent->removeChildren();
			////	parent->center = (parent->lower+parent->upper)/2.0;
			//}
		}
		//static void trash(){
		//	nextQuestion = "";
		//	nextQuestion += "FFFFFFFFFFF";
		//	nextLower = 100;
		//	nextUpper = 200;
		//	//return
		//}
	};
}
