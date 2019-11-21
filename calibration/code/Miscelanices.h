#pragma once

namespace CalibrationEngine{

	typedef vector<int> v_int;

	struct Question{
		int index;
		int decision;
		int correctAnswer;
		double credibility;
	};

	struct Subinterval{
		int index;
		double min, max, alpha, beta, lowerQuantile, spMean, quantile_50, upperQuantile, postMean;
		vector<v_int> _alpha;
		vector<double> sp;
		vector<int> questionId;
		vector<int> evidence;
		bool isUnderconfident, isOverconfident;
	};
	
	enum CalibrationMethod{
		Firmino,
		Direto,
		Bissecao
	};

	enum CurvaCalibracao{
		Calibrated,
		Underconfident,
		Overconfident
	};
	/*public*/ static const int FIRMINO = 1;
	/*public */static const int DIRECT = 2;
	/*public */static const int BISECTION = 3;

}

