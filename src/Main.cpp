/*
 * Copyright (c) 2017
 *     Andrea Bulgarelli, Andrea Zoli (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
 *
 *	Output: 
	tstart T0, tstop T0, numero di fotoni T0, numero fotoni esposizione T0, fotoni/esposizione T0 ,tstart T1, tstop T1, numero di fotoni  		T1, numero fotoni esposizione T1,tstart T2, tstop T2, numero di fotoni T2, numero fotoni esposizione T2, off , somma delle due mappe 		di bkg (T1 e T2) come fotoni e exp, Li&Ma
*/

#include <iostream>
#include <fstream>
#include <string.h>

//#define DEBUG 1

#include <PilParams.h>
#include "BinEvaluator.h"
#include "LiMa.h"

using namespace std; 

const char* startString = {
"################################################################\n"
"###                   Task AG_lm6 v1.0.0 -               ###"
};

const char* endString = {
"### Task AG_lm6 exiting .................................... ###\n"
"################################################################"
};

const PilDescription paramsDescr[] = {
    { PilString, "outfile", "Output file name" },
    { PilString, "ctsT0", "Input T0 cts file name" },
    { PilString, "expT0", "Input T0 exp file name" },
    { PilString, "ctsT1", "Input T1 cts file name" },
    { PilString, "expT1", "Input T1 exp file name" },
    { PilString, "ctsT2", "Input T2 cts file name" },
    { PilString, "expT2", "Input T2 exp file name" },
    { PilReal, "l", "Longitude of GRB centroid (galactic)" },
    { PilReal, "b", "Latitude of GRB centroid (galactic)" },
    { PilReal, "radius", "Li&Ma radius of analysis" },   
    { PilNone, "", "" }
};



int main(int argc, char *argv[])
{
    cout << startString << endl;
	int statusCts = 0;
	int statusExp = 0;
    
    PilParams params(paramsDescr);
   
    if (!params.Load(argc, argv))
        return EXIT_FAILURE;
     

	const char *ctsT0FilePath = params["ctsT0"];
	const char *expT0FilePath = params["expT0"];
	const char *ctsT1FilePath = params["ctsT1"];
	const char *expT1FilePath = params["expT1"];
	const char *ctsT2FilePath = params["ctsT2"];
	const char *expT2FilePath = params["expT2"];
	double l = params["l"];
	double b = params["b"];
	double radius = params["radius"];
	
	const char * outfile = params["outfile"];

/*
	const char *ctsT0FilePath = "../MAPFORTEST/T0.cts.gz";
	const char *expT0FilePath = "../MAPFORTEST/T0.exp.gz";
	const char *ctsT1FilePath = "../MAPFORTEST/T1.cts.gz";
	const char *expT1FilePath = "../MAPFORTEST/T1.exp.gz";
	const char *ctsT2FilePath = "../MAPFORTEST/T2.cts.gz";
	const char *expT2FilePath = "../MAPFORTEST/T2.exp.gz";
	double l = 45;
	double b = 30;
	double radius = 10;
	
	const char * outfile = "../outfile.txt";
*/

    	ofstream resText(outfile);
    	resText.setf(ios::fixed); 
	
    
	 
	// ANALYSIS OF SOURCE MAP T0

 
	BinEvaluator expT0(expT0FilePath,l,b,radius);
	statusExp = expT0.sumBin();
 
	BinEvaluator ctsT0(ctsT0FilePath,l,b,radius);
	statusCts = ctsT0.sumBin();
 
	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT0.tmin << " " << ctsT0.tmax << " ";
		resText << setprecision(2);
		resText << ctsT0.binSum << " " << expT0.binSum << " ";
		resText << setprecision(10) << ctsT0.binSum / (double) expT0.binSum << " ";
	}
	else if(statusCts != 0){
		cout <<"Error: the radius exceeds the border of the .cts map" << endl;
		return statusCts;
	}
	else if(statusExp != 0){
		cout <<"Error: the radius exceeds the border of the .exp map" << endl;
		return statusExp;
	}

 
	

	// ANALYSIS OF MAP T1
	
	BinEvaluator ctsT1(ctsT1FilePath,l,b,radius);
	statusCts = ctsT1.sumBin();
	
	BinEvaluator expT1(expT1FilePath,l,b,radius);
	statusExp = expT1.sumBin();

	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT1.tmin << " " << ctsT1.tmax << " ";
		resText << setprecision(2);
		resText << ctsT1.binSum<< " " << expT1.binSum << " ";

	}
	else if(statusCts != 0){
		cout <<"Error: the radius exceeds the border of the .cts map" << endl;
		return statusCts;
	}
	else if(statusExp != 0){
		cout <<"Error: the radius exceeds the border of the .exp map" << endl;
		return statusExp;
	}
	
	// ANALYSIS OF MAP T2
	
	BinEvaluator ctsT2(ctsT2FilePath,l,b,radius);
	statusCts = ctsT2.sumBin();
	
	BinEvaluator expT2(expT2FilePath,l,b,radius);
	statusExp = expT2.sumBin();


	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT2.tmin << " " << ctsT2.tmax << " ";
		resText << setprecision(2);
		resText << ctsT2.binSum << " " << expT2.binSum << " ";

	}
	else if(statusCts != 0){
		cout <<"Error: the radius exceeds the border of the .cts map" << endl;
		return statusCts;
	}
	else if(statusExp != 0){
		cout <<"Error: the radius exceeds the border of the .exp map" << endl;
		return statusExp;
	}
	


	// LI&MA Analysis
	
 	LiMa lm(ctsT0.binSum,ctsT1.binSum,ctsT2.binSum,expT0.binSum,expT1.binSum,expT2.binSum);
	double S = lm.computeLiMiValue();


	resText << lm.alpha << " " << std::setprecision(2)  << " off " << lm.bkg << " " << lm.expBgSum << " " << std::setprecision(10) << lm.bkg / (double) (lm.expBgSum)<< " " << S << endl;	//resText << SA << endl;
    
    resText.close();


    return 0;
}
