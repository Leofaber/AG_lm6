#include <iostream>
#include <stdlib.h> 
#include "fitsio.h" 
#include "AgileMap.h"
#include "Eval.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <cstring>
#include <prj.h>
#include <wcstrig.h>
#include <sph.h>
#include <CalibUtils.h>
#include <FitsUtils.h>
#include <MathUtils.h>

#include "Selection.h"



 
using namespace std;



class ExpRatioEvaluator
{
	public: ExpRatioEvaluator(const char * expPath,bool normalize, double minTreshold, double maxTreshold, double l, double b);


	const char* expPath;
	bool normalize;
	double normalizationFactor;
	double tStart;
	double tStop;
	double timeFactor;
	double spatialFactor;
	
	
	// If pixel value is not inside [minThreshold, maxThreshold], increments nBad.
	double minThreshold;
	double maxThreshold;
	
	// The spot coordinates (galactic and pixels)
	double l;
	double b; 
	int x;
	int y;
	AgileMap* agileMap;

	// The size of the rectangle (x-size , x+size, y-size, y+size)
	float size;

	// Check if the  rectangle is completely inside the image
	bool isRectangleInside();

	// We convert fits data into a matrix of double
	int rows;
	int cols;
	double ** image;
	bool convertFitsDataToMatrix();
	
	// The output array  [ exp-ratio, nBad, nTot, greyLevelMean ]	
	double output[4];



	/*
		Computes and returns the output array. 
		exp-ratio is defined as nBad/nTot. 
		If the rectangle is not entirely inside the image, it fails.
	*/	
	double* computeExpRatioValues();	
	
	
};
