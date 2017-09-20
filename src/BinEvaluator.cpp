#include "BinEvaluator.h"

BinEvaluator::BinEvaluator(const char *_fitsFilePath, double _l, double _b, double _radius) {
	fitsFilePath=_fitsFilePath;
	l=_l;
	b=_b;
	radius=_radius;
	photonsCount=0;
	agileMapUtils = new AgileMap(_fitsFilePath);
	image= FitsToCvMatConverter::convertFitsToCvMat(_fitsFilePath);
}

int BinEvaluator::evalExpAndCounts() {
	
	
	int status,i,j;
	double greyLevel;
	
	if(isRadiusInside()) { 
		for(int i = 0; i < image.rows; i++){
			for(int j=0; j < image.cols; j++){
					greyLevel = image.at<double>(i,j);
					if(greyLevel>0 && agileMapUtils->SrcDist(i,j,l,b)<=radius){
						photonsCount+=greyLevel;

				}
			}
		}
	}else{
		return -1;
	}
	return 0;
}

bool BinEvaluator::isRadiusInside() {
	
	for(int i = 0; i < image.rows; i++){
			double distSX = agileMapUtils->SrcDist(i,0,l,b);
			double distDX = agileMapUtils->SrcDist(i,image.cols,l,b);
			//cout << "Pixel i,j" << i << ","<<0<<"  gal: "<<agileMapUtils->l(i,0)<<","<<agileMapUtils->b(i,0) << endl;
 
			if(distSX < radius || distDX < radius) {
				//cout << "bordo sx: "<< dist1 << " > " << radius << "  bordo dx: " << dist2 << " > " << radius << endl;  
				return false;
			}
		}
	for(int j=0; j < image.cols; j++){
			if(agileMapUtils->SrcDist(0,j,l,b)<radius || agileMapUtils->SrcDist(image.rows,j,l,b)<radius) {
				return false;
			}
		}
	
	return true;
}
