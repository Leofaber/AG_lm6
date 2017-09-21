/*
 * Copyright (c) 2017
 *     Andrea Bulgarelli, Andrea Zoli (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <AgileMap.h>
#include "FitsToCvMatConverter.h"
 
using namespace std;

class BinEvaluator {
	public:
		BinEvaluator(const char * fitsFilePath, double l, double b, double radius);
		int sumBin();
		bool isRadiusInside();

		const char * fitsFilePath;
		Mat image; 
		double l, b, radius;
		double binSum;
		double tmin;
		double tmax;
		AgileMap * agileMapUtils;
		
		
};

#endif
