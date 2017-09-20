/*
 * Copyright (c) 2017
 *     Andrea Bulgarelli, Andrea Zoli (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

//#define DEBUG 1

//#include <FitsUtils.h>
//#include <Selection.h>
//#include <Eval.h>
#include <PilParams.h>
#include "BinEvaluator.h"

using namespace std; 

const char* startString = {
"################################################################\n"
"###                   Task AG_lm6 v1.0.0 -               ###"
};

const char* endString = {
"### Task AG_lm5 exiting .................................... ###\n"
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
	//output: 
	//tstart, tstop, numero di fotoni, numero fotoni esposizione, fotoni/esposizione , si prosegue per ogni mappa....
	//off , somma delle due mappe di bkg (T1 e T2) come fotoni e exp, due formule di Li&Ma
    
	 
	// ANALYSIS OF SOURCE MAP T0

 
	BinEvaluator expT0(expT0FilePath,l,b,radius);
	statusExp = expT0.evalExpAndCounts();
 
	BinEvaluator ctsT0(ctsT0FilePath,l,b,radius);
	statusCts = ctsT0.evalExpAndCounts();
 
	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT0.tmin << " " << ctsT0.tmax << " ";
		resText << setprecision(2);
		resText << ctsT0.photonsCount << " " << expT0.photonsCount << " ";
		resText << setprecision(10) << ctsT0.photonsCount / (double) expT0.photonsCount << " ";
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
	statusCts = ctsT1.evalExpAndCounts();
	
	BinEvaluator expT1(expT1FilePath,l,b,radius);
	statusExp = expT1.evalExpAndCounts();

	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT1.tmin << " " << ctsT1.tmax << " ";
		resText << setprecision(2);
		resText << ctsT1.photonsCount<< " " << expT1.photonsCount << " ";

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
	statusCts = ctsT2.evalExpAndCounts();
	
	BinEvaluator expT2(expT2FilePath,l,b,radius);
	statusExp = expT2.evalExpAndCounts();


	if(statusCts == 0 && statusExp == 0) {
		resText << setprecision(1);
		resText << ctsT2.tmin << " " << ctsT2.tmax << " ";
		resText << setprecision(2);
		resText << ctsT2.photonsCount << " " << expT2.photonsCount << " ";

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
	
 

	int bkg = ctsT1.photonsCount + ctsT2.photonsCount;
	int source = ctsT0.photonsCount;
	int N_on = source + bkg;
	int N_off = bkg;
	double alpha = expT0.photonsCount / (expT1.photonsCount + expT2.photonsCount);
	
	double alp1 = alpha / (1 + alpha);
	double alp2 = alpha + 1;

	//cout << "bkg " << bkg << endl;
	//cout << "source " << source << endl;
	//cout << "N_on " << N_on << endl;
	//cout << "N_off " << N_off << endl;
	//cout << "alpha " << alpha << endl;
	//cout << "alp1 " << alp1 << endl;
	//cout << "alp2 " << alp2 << endl;
	
	cout << "sig cts  " << source << endl;
	cout << "sig exp  " << expT0.photonsCount << endl;
	cout << "sig rate " << setprecision(10) << source / (double) expT0.photonsCount << endl;
	cout << "bkg cts  " << bkg << endl;
	cout << "bkg exp  " << (expT1.photonsCount + expT2.photonsCount) << endl;
	cout << "bkg rate " << setprecision(10) << bkg / (double) (expT1.photonsCount + expT2.photonsCount) << endl;
	

	resText << alpha << " ";
	resText << std::setprecision(2);
	resText << " off " << bkg << " " << expT1.photonsCount + expT2.photonsCount << " " << std::setprecision(10) << bkg / (double) (expT1.photonsCount + expT2.photonsCount)<< " ";
	
	double S = 0;
	double SA = 0;
	if ((source > 0) and (bkg > 0)) {
		double source1 = source;
		double bkg1 = bkg;
		double L1 = pow(((source1 + bkg1) / source1) * alp1, source);
		double L2 = pow(((bkg1 + source1) / bkg1) / alp2, bkg);
		double L = L1 * L2;
		S = sqrt(-2. * log(L));
		SA = sqrt(2.) * sqrt(source * log( (1 / alp1 ) * ( source / (double)(source + bkg) )) + bkg * log( alp2 * ( bkg / (double)( source + bkg ) ) ) );
		cout <<  "Li&Ma sigma " << S << endl;
		cout <<  "Li&Ma sigma " << SA << endl;

		
	} else {
		cout << "Alpha: 0" << endl;
		cout << "Li&Ma sigma 0" << endl;
	
	}
	resText << S << endl;
	//resText << SA << endl;
				
    
    resText.close();


    return 0;
}
