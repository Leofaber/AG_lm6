#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <AgileMap.h>
#include "FitsToCvMatConverter.h"
 
using namespace std;

class BinEvaluator {
	public:
		BinEvaluator(const char * fitsFilePath, double l, double b, double radius);
		int evalExpAndCounts();
		bool isRadiusInside();

		const char * fitsFilePath;
		Mat image; 
		double l, b, radius;
		double photonsCount;
		double tmin;
		double tmax;
		AgileMap * agileMapUtils;
		
		
};

#endif
