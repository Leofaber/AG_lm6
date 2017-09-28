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
#include "ExpRatioEvaluator.h"

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
	

    float minTreshold = 0;
    float maxTreshold = 100;

    
	if(argc > 11) {
		cout << "lol" << endl;
		minTreshold = atof(argv[11]);
		maxTreshold = atof(argv[12]);
	}
	
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

	int statusCts = 0;
	int statusExp = 0;

    // EXPRATIOEVALUATOR OF EXPTO
	ExpRatioEvaluator expRatioT0(expT0FilePath,minTreshold ,maxTreshold,l,b); 
	double *outputT0 = expRatioT0.computeExpRatioValues(); 
	if(expRatioT0.isRectangleInside()) {
		cout << "ExpRatioEvaluator of expT0:" << endl;
		for(int i=0; i<4; i++) {
			cout << outputT0[i] << endl;
			}
		}
	 
	// ANALYSIS OF SOURCE MAP T0

 
	BinEvaluator expT0(expT0FilePath,l,b,radius);
	if(! expT0.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "expT0 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusExp = expT0.sumBin();
	if(statusExp != 0)
	{
		fprintf(stderr,"expT0 Error: the radius exceeds the border of the .exp map\n");
		exit (EXIT_FAILURE);
	}

 
	BinEvaluator ctsT0(ctsT0FilePath,l,b,radius);
	if(! ctsT0.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "ctsT0 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusCts = ctsT0.sumBin();
 	if(statusCts != 0)
	{
		fprintf(stderr,"ctsT0 Error: the radius exceeds the border of the .cts map\n");
		exit (EXIT_FAILURE);
	}

	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT0.tmin << " " << ctsT0.tmax << " ";
		resText << setprecision(2);
		resText << ctsT0.binSum << " " << expT0.binSum << " ";
		resText << setprecision(10) << ctsT0.binSum / (double) expT0.binSum << " ";
		resText << setprecision(5);
		resText << outputT0[0] << " " << outputT0[1] << " " << outputT0[2] << " " << outputT0[3] << " ";
	}
	
	
	
	
	
 
	// EXPRATIOEVALUATOR OF EXPT1
	ExpRatioEvaluator expRatioT1(expT1FilePath,minTreshold ,maxTreshold,l,b);
	double *outputT1 = expRatioT1.computeExpRatioValues(); 
	if(expRatioT1.isRectangleInside()) {
		cout << "ExpRatioEvaluator of expT1:" << endl;
		for(int i=0; i<4; i++) {
			cout << outputT1[i] << endl;
			}
		}

	// ANALYSIS OF MAP T1
	BinEvaluator expT1(expT1FilePath,l,b,radius);
	if(! expT1.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "expT1 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusExp = expT1.sumBin();
	if(statusExp != 0)
	{
		fprintf(stderr,"expT1 Error: the radius exceeds the border of the .exp map\n");
		exit (EXIT_FAILURE);
	}

 
	BinEvaluator ctsT1(ctsT1FilePath,l,b,radius);
	if(! ctsT1.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "ctsT1 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusCts = ctsT1.sumBin();
 	if(statusCts != 0)
	{
		fprintf(stderr,"ctsT1 Error: the radius exceeds the border of the .cts map\n");
		exit (EXIT_FAILURE);
	}

	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT1.tmin << " " << ctsT1.tmax << " ";
		resText << setprecision(2);
		resText << ctsT1.binSum << " " << expT1.binSum << " ";
		resText << setprecision(5);
		resText << outputT1[0] << " " << outputT1[1] << " " << outputT1[2] << " " << outputT1[3] << " ";
	}
	
	
	// EXPRATIOEVALUATOR OF EXP T2
	ExpRatioEvaluator expRatioT2(expT2FilePath,minTreshold ,maxTreshold,l,b);
	double *outputT2 = expRatioT2.computeExpRatioValues(); 
	if(expRatioT2.isRectangleInside()) {
		cout << "ExpRatioEvaluator of expT2: "<< endl;
		for(int i=0; i<4; i++) {
			cout << outputT2[i] << endl;
			}
		}

	 
	// ANALYSIS OF MAP T2
	BinEvaluator expT2(expT2FilePath,l,b,radius);
	if(! expT2.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "expT2 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusExp = expT2.sumBin();
	if(statusExp != 0)
	{
		fprintf(stderr,"expT2 Error: the radius exceeds the border of the .exp map\n");
		exit (EXIT_FAILURE);
	}

 
	BinEvaluator ctsT2(ctsT2FilePath,l,b,radius);
	if(! ctsT2.convertFitsDataToMatrix() )
	{
		fprintf( stderr, "ctsT2 convertFitsDataToMatrix() Error reading fits file\n");
		exit (EXIT_FAILURE);
	}

	statusCts = ctsT2.sumBin();
 	if(statusCts != 0)
	{
		fprintf(stderr,"ctsT2 Error: the radius exceeds the border of the .cts map\n");
		exit (EXIT_FAILURE);
	}

	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT2.tmin << " " << ctsT2.tmax << " ";
		resText << setprecision(2);
		resText << ctsT2.binSum << " " << expT2.binSum << " ";
		resText << setprecision(5);
		resText << outputT2[0] << " " << outputT2[1] << " " << outputT2[2] << " " << outputT2[3] << " ";
		
	}
	
	


	//cout << ctsT0.binSum <<" "<<ctsT1.binSum <<" "<<ctsT2.binSum <<" "<<expT0.binSum <<" "<<expT1.binSum <<" "<<expT2.binSum<<endl;

	// LI&MA Analysis
	double S;
	cout << "\nLI&MA Analysis: " << endl;
	LiMa lm(ctsT0.binSum,ctsT1.binSum,ctsT2.binSum,expT0.binSum,expT1.binSum,expT2.binSum);
	if(expRatioT0.isRectangleInside() || expRatioT1.isRectangleInside() || expRatioT2.isRectangleInside()) { 
		S = lm.computeLiMiValue();
	}else{
		S=-1;
	}
	


	resText << lm.alpha << " " << std::setprecision(2)  << " off " << lm.bkg << " " << lm.expBgSum << " " << std::setprecision(10) << lm.bkg / (double) (lm.expBgSum)<< " " << S << endl;	//resText << SA << endl;
    
    resText.close();


    return 0;
}
