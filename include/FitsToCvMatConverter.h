#pragma once

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
