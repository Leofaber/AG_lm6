/*
 * Copyright (c) 2017
 *     Andrea Bulgarelli, Andrea Zoli (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/


#include "fitsio.h"
#include <opencv2/core/core.hpp>
#include <string>
#include <iostream>

using namespace cv;
using namespace std;

class FitsToCvMatConverter
{
public:
	static Mat convertFitsToCvMat(const char * fitsPath);
private:
    FitsToCvMatConverter();

};
