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

namespace CalibrationEngine{

	int General_Auxiliar::id= 0;
	int General_Auxiliar::maxGeneration= 0;

	vector<int*> General_Auxiliar::intsToDelete(0);
	vector<double*> General_Auxiliar::doublesToDelete(0);
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