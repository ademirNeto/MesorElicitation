
#pragma once
#ifndef METHOD_H
#define METHOD_H
#include<iostream>
#include<vector>
#include <stdlib.h>
#include <math.h>
#include <time.h>

namespace Engine{
using namespace std;

class Method
{
public:
	const static int PROBABILITY_ELICITATION = 1;
	const static int NUMBER_OF_OCCURRENCES_ELICITATION = 2;
	const static int RATE_ELICITATION = 3;
	const static int TIME_ELICITATION = 4;

	const static int MINUTE_TIME_UNIT = 1;
	const static int HOUR_TIME_UNIT = 2;
	const static int DAY_TIME_UNIT = 3;
	const static int MONTH_TIME_UNIT = 4;
	const static int YEAR_TIME_UNIT = 5;

	Method(void);
	~Method(void);
};};

#endif