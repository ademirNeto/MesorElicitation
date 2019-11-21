#include "stdafx.h"
#include "General_Auxiliar.h"
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

using namespace std;
namespace Engine{

int General_Auxiliar::id= 0;
int General_Auxiliar::maxGeneration= 0;

vector<Node*> General_Auxiliar::rootNodes(0);
vector<Node*> General_Auxiliar::leafNodes(0);
vector<Node*> General_Auxiliar::allNodes(0);
//vector<Node*> General_Auxiliar::nodesToDelete(0);
vector<int*> General_Auxiliar::intsToDelete(0);
vector<double*> General_Auxiliar::doublesToDelete(0);
double General_Auxiliar::getExp(double x){
	double result=0;
	if(x > ZERO_EXP){
		if(x < INF_EXP)
			result = exp(x);
		else{
			result = 1.7976931348623158e+308;//DBL_MAX;
			//cout<<"::DANGER: EXP(X)=INF!!"<<endl;
		}
	}
	return result;
}

double General_Auxiliar::getLog(double x){
	double result=LOG_ZERO;
	if(x > 0){
		result = log(x);
	}
	return result;
}
int General_Auxiliar::getPointLocationByBinarySearch(const vector<double> sample, const double value, int lower, int upper){
		bool indexFound = false;
		int mid=0;
		int min = lower;
		int max = upper;
		while(!indexFound && lower!=upper){
			mid = (int) (upper+lower)/2;
			double sampleKey = sample[mid];
			if(value==sampleKey)
				indexFound = true;
			else{
				if(upper-lower>1){
					if (value>sampleKey)
						lower = mid;
					else
						upper = mid;
				}else{
					if (value>sampleKey){
						mid++;
						lower = upper;
					}else{
						mid--;
						upper = lower;
					}
				}
			}
		}
		//if(nComp > max_nComp){
		//	max_nComp = nComp;
		//	cout<<"max_nComp = "<<max_nComp<<endl;
		//}
		//cout<<nComp<<endl;
		if(mid<min)
			mid=min;
		else if(mid > max)
			mid = max;
		return mid;
	}

bool General_Auxiliar::addSortedNodes(vector<Node*>& vec, Node* node){
	bool indexFound = false;
	int size = (int)vec.size();
	int upper = size;
	upper = (upper>0?upper--:upper);
	int lower = 0;
	int mid=0;
	while(!indexFound && lower!=upper){
		mid = (int) (upper+lower)/2;
		if(node->getLabel()==vec[mid]->getLabel())
			indexFound = true;
		else{
			if(upper-lower<=1){
				if (node->getLabel()>vec[mid]->getLabel()){
					mid++;
					lower = upper;
				}else{
					mid--;
					upper = lower;
				}
			}else{
				if (node->getLabel()>vec[mid]->getLabel())
					lower = mid;
				else
					upper = mid;
			}
		}
	}
	if(mid<0)
		mid=0;
	if(!indexFound){
		vector<Node*>::iterator it = vec.begin();
		//cout<<endl<<"here"<<endl;
		vec.insert(it+mid, node);
	}
	return indexFound;
}
bool General_Auxiliar::addSortedDouble(vector<double>& vec, double value){
	bool indexFound = false;
	int size = (int)vec.size();
	int upper = size;
	upper = (upper>0?upper--:upper);
	int lower = 0;
	int mid=0;
	while(!indexFound && lower!=upper){
		mid = (int) (upper+lower)/2;
		if(vec[mid]==value)
			indexFound = true;
		else{
			if(upper-lower<=1){
				if (value>vec[mid]){
					mid++;
					lower = upper;
				}else{
					mid--;
					upper = lower;
				}
			}else{
				if (value>vec[mid])
					lower = mid;
				else
					upper = mid;
			}
		}
	}
	if(mid<0)
		mid=0;
	vec.insert(vec.begin()+mid, value);
	return indexFound;
}

void General_Auxiliar::deleteNews(){
	int n = (int)intsToDelete.size();
	for(int i=n-1; i>=0; i--){
		delete[]intsToDelete[i];
		intsToDelete[i] = 0;
	}

}
void General_Auxiliar::eliminateAllNodes(){
	allNodes.clear();
	rootNodes.clear();
	leafNodes.clear();
}

void General_Auxiliar::inicializeVariables(){
	rootNodes.clear();
	leafNodes.clear();
	allNodes.clear();
//	updateCount=0;
}
void General_Auxiliar::readVecNodes(){
	int size = (int)allNodes.size();
	cout<<">BBN Ordered Variables: "<<endl;
		for(int i=0; i<size; i++)
			allNodes[i]->readCharacteristics();
			//allNodes[i]->readBBN();
			//cout<<allNodes[i]->getLabel()<<", ";
	cout<<endl;
}
bool General_Auxiliar::removeSortedNodes(vector<Node*>& vec, Node* node){
	bool indexFound = false;
	int size = (int)vec.size();
	int upper = size;
	upper = (upper>0?upper--:upper);
	int lower = 0;
	int mid=0;
	while(!indexFound && lower!=upper){
		mid = (int) (upper+lower)/2;
		if(node->getLabel()==vec[mid]->getLabel())
			indexFound = true;
		else{
			if(upper-lower<=1){
				if (node->getLabel()>vec[mid]->getLabel()){
					mid++;
					lower = upper;
				}else{
					mid--;
					upper = lower;
				}
			}else{
				if (node->getLabel()>vec[mid]->getLabel())
					lower = mid;
				else
					upper = mid;
			}
		}
	}
	if(mid<0)
		mid=0;
	if(indexFound)
		vec.erase(vec.begin()+mid);
	return indexFound;
}


General_Auxiliar::~General_Auxiliar(){}
General_Auxiliar::General_Auxiliar(){}
void General_Auxiliar::setMeanAndVariance(vector<double> x, double & mean,double& var){
		int n = (int)x.size();
		double sxi = 0.0;
		double sxi2  = 0.0;
		for(int i=0; i<n; i++){
			sxi += x[i];
			sxi2 += pow(x[i], 2.0);
		}
		var = (sxi2 - pow(sxi, 2.0)/n)/(n-1);
		mean = sxi/n;
		//cout<<"S2: "<<S2<<", xBarr: "<<xBarr<<endl;
}

}