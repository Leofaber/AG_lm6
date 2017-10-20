
/*
 * Copyright (c) 2017
 *     Leonardo Baroncelli, Giancarlo Zollino
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
 * 
 * https://github.com/Leofaber/AG_lm6
*/

#include <iostream>
#include <fstream>
#include <string.h>
 

#include <PilParams.h>
#include "BinEvaluator.h"
#include "LiMa.h"
#include "ExpRatioEvaluator.h"

using namespace std; 

const char* startString = {
"################################################################\n"
"###                   Task AG_lm6 v1.0.6 -               ###"
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
    { PilString, "normalize", "true if exp should be normalized, false otherwise" },
    { PilString, "createExpRatioMap", "true if ExpRatioMap have to be created, false otherwise" },
    { PilNone, "", "" }
};



int main(int argc, char *argv[])
{
    cout << startString << endl;

	// PARAMETRI OPZIONALI - VALORI DI DEFAULT    
	float minThreshold = 120;
	float maxThreshold = 140;
	int squareSize = 20;
	bool doNormalization;
	bool boolcreateExpRatioMap;
	
	 
	

	// CONTROLLO NUMERO PARAMETRI (TOO FEW, TOO MUCH)	
	if(argc < 13 || argc > 16)
	{
		printf("\nAt least 12 arguments expected (+ 3 optional)\n   - The name of the output file\n   - The Input T0 cts file name\n   - The Input T0 exp file name\n   - The Input T1 cts file name\n   - The Input T1 exp file name\n   - The Input T2 cts file name\n   - The Input T2 exp file name\n   - The l coordinate\n   - The b coordinate\n   - The radius size\n   - The normalize boolean: true if exp-ratio must be computed on a normalized map, false otherwise\n   - The createExpRatioMap boolean: true if ExpRatioMap have to be created\n\n(Optional)\n   - The minThreshold (default value = 120)\n   - The maxThreshold (default value = 140)\n   - The square size (default value = 10)\n\n ");
		cout << endString << endl;		
		exit (EXIT_FAILURE);
	}

	PilParams params(paramsDescr);
    if (!params.Load(argc, argv))
        return EXIT_FAILURE;
	

	// PARAMETRI OBBLIGATORI
	const char *outfile = params["outfile"];
	const char *ctsT0FilePath = params["ctsT0"];
	const char *expT0FilePath = params["expT0"];
	const char *ctsT1FilePath = params["ctsT1"];
	const char *expT1FilePath = params["expT1"];
	const char *ctsT2FilePath = params["ctsT2"];
	const char *expT2FilePath = params["expT2"];
	double l = params["l"];
	double b = params["b"];
	double radius = params["radius"]; 
	const char *normalize = params["normalize"];
	const char *createExpRatioMap = params["createExpRatioMap"];
	
	if( strcmp(normalize, "true") == 0 )
		doNormalization = true;
	else
		doNormalization = false;
		
	
	if( strcmp(createExpRatioMap, "true") == 0 )
		boolcreateExpRatioMap = true;
	else
		boolcreateExpRatioMap = false;
	
	
		

	// PARAMETRI OPZIONALI
    if(argc == 14) 	
    {
		if(((string)argv[13])!="d")
			minThreshold = atof(argv[13]);
		
    }
	if(argc == 15) 
	{
		if(((string)argv[13])!="d")
			minThreshold = atoi(argv[13]);
		if(((string)argv[14])!="d")		
			maxThreshold = atof(argv[14]);
	}
	if(argc == 16) 
	{
		if(((string)argv[13])!="d")
			minThreshold = atoi(argv[13]);
		if(((string)argv[14])!="d")		
			maxThreshold = atof(argv[14]);
		if(((string)argv[15])!="d")		
			squareSize = atof(argv[15]);
	}
		
	
   
 
	ofstream resText(outfile);
   	resText.setf(ios::fixed); 




	int statusCts = 0;
	int statusExp = 0;
	
	

    // EXPRATIOEVALUATOR OF EXPT0
	
	ExpRatioEvaluator expRatioT0(expT0FilePath, doNormalization,boolcreateExpRatioMap,minThreshold, maxThreshold, squareSize);
	double expRatioValueT0 = expRatioT0.computeExpRatioValues(l,b); 
	if(expRatioValueT0!=-1) { 
		cout << "ExpRatio evaluation of expT0: " << (int)round(expRatioValueT0)<< endl;		
	}
	 
		
	// ANALYSIS OF SOURCE MAP T0
 	// Exp
 	BinEvaluator * beT0;
	if(doNormalization) {
		double **normalizedImageT0 = expRatioT0.getNormalizedMap();
		beT0 = new BinEvaluator(expT0FilePath,normalizedImageT0,l,b,radius);
	}
	else{
		beT0 = new BinEvaluator(expT0FilePath,l,b,radius);
	}
	
	statusExp = beT0->sumBin();
	if(statusExp != 0)
		{
			fprintf(stderr,"expT1 Error: the radius exceeds the border of the .exp map\n");
			exit (EXIT_FAILURE);
		}
 
	
 	// Cts
	BinEvaluator ctsT0(ctsT0FilePath,l,b,radius);
	
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
		resText << (int) ctsT0.binSum << " " << beT0->binSum << " ";
		resText << setprecision(10) << ctsT0.binSum / (double) beT0->binSum << " ";
		resText << setprecision(5); 
		resText << (int)round(expRatioValueT0) << " ";		
	}
	
	
	
	
	
 
	// EXPRATIOEVALUATOR OF EXPT1

	ExpRatioEvaluator expRatioT1(expT1FilePath, doNormalization,boolcreateExpRatioMap,minThreshold, maxThreshold, squareSize);
	double expRatioValueT1 = expRatioT1.computeExpRatioValues(l,b); 
	if(expRatioValueT1!=-1) {	
		cout << "ExpRatio evaluation of expT1: " << (int)round(expRatioValueT1)<< endl;				
	}

	// ANALYSIS OF MAP T1
	BinEvaluator * beT1;
	if(doNormalization) {
		double **normalizedImageT1 = expRatioT1.getNormalizedMap();
		beT1 = new BinEvaluator(expT1FilePath,normalizedImageT1,l,b,radius);
	}
	else{
		beT1 = new BinEvaluator(expT1FilePath,l,b,radius);
	}

	statusExp = beT1->sumBin();
		if(statusExp != 0)
		{
			fprintf(stderr,"expT1 Error: the radius exceeds the border of the .exp map\n");
			exit (EXIT_FAILURE);
		}
	

	

 
	BinEvaluator ctsT1(ctsT1FilePath,l,b,radius);
	

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
		resText << (int) ctsT1.binSum << " " << beT1->binSum << " ";
		resText << setprecision(5);
		resText << (int)round(expRatioValueT1) << " ";	
	}
	
	
	// EXPRATIOEVALUATOR OF EXP T2

	ExpRatioEvaluator expRatioT2(expT2FilePath,doNormalization,boolcreateExpRatioMap, minThreshold, maxThreshold, squareSize);
	double expRatioValueT2 = expRatioT2.computeExpRatioValues(l,b); 
	if(expRatioValueT2!=-1) {
		cout << "ExpRatio evaluation of expT2: " << (int)round(expRatioValueT2)<< endl;			
	}

	 
	// ANALYSIS OF MAP T2
	BinEvaluator * beT2;
	if(doNormalization) {
		double **normalizedImageT2 = expRatioT2.getNormalizedMap();
		beT2 = new BinEvaluator(expT2FilePath,normalizedImageT2,l,b,radius);
	}
	else{
		beT2 = new BinEvaluator(expT2FilePath,l,b,radius);
	}

	statusExp = beT2->sumBin();
		if(statusExp != 0)
		{
			fprintf(stderr,"expT2 Error: the radius exceeds the border of the .exp map\n");
			exit (EXIT_FAILURE);
		}
	

 
	BinEvaluator ctsT2(ctsT2FilePath,l,b,radius);
	

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
		resText << (int) ctsT2.binSum << " " << beT2->binSum << " ";
		resText << setprecision(5);
		resText << (int)round(expRatioValueT2) << " ";		
		
	}
	
	


	//cout << ctsT0.binSum <<" "<<ctsT1.binSum <<" "<<ctsT2.binSum <<" "<<expT0.binSum <<" "<<expT1.binSum <<" "<<expT2.binSum<<endl;

	// LI&MA Analysis
	double S;
	cout << "\nLI&MA Analysis: " << endl;
	LiMa lm(ctsT0.binSum,ctsT1.binSum,ctsT2.binSum,beT0->binSum,beT1->binSum,beT2->binSum);
	
	//if(expRatioArrayT0 != -1 && expRatioArrayT1 != -1 && expRatioArrayT2 != -1) { 		//elimintao [0]
		S = lm.computeLiMiValue();
	/*}else{
		S=-1;
	}*/
	


	resText << lm.alpha << " " << std::setprecision(2)  << " off " << lm.bkg << " " << lm.expBgSum << " " << std::setprecision(10) << lm.bkg / (double) (lm.expBgSum)<< " " << S << endl;	//resText << SA << endl;
    
    resText.close();

	cout << endString << endl;

    return 0;
  
}
