#pragma once
#ifndef CAL_BISSECAO_H
#define CAL_BISSECAO_H
#include "Calibration.h"
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

namespace CalibrationEngine{
	using namespace std;

	class Cal_Bissecao :	public Calibration{
	private:
		vector<double>lower, upper;
	public:
		Cal_Bissecao();
		~Cal_Bissecao();	
	};
};

#endif
