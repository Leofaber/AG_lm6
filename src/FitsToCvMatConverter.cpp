
/*
 * Copyright (c) 2017
 *     Andrea Bulgarelli, Andrea Zoli (IASF-Bologna),
 *
 * Any information contained in this software
 * is property of the AGILE TEAM and is strictly
 * private and confidential.
*/



#include "FitsToCvMatConverter.h"


FitsToCvMatConverter::FitsToCvMatConverter()
{
}


double * FitsToCvMatConverter::convertFitsToCvMat(const char * fitsPath) {
	
//CFITSIO
	fitsfile *fptr;   /* FITS file pointer, defined in fitsio.h */
	int status = 0;   /* CFITSIO status value MUST be initialized to zero! */
	int bitpix, naxis, ii, anynul;
	long naxes[2] = { 1, 1 }, fpixel[2] = { 1, 1 };
	double *pixels;
	char format[20], hdformat[20];
			

	if (!fits_open_file(&fptr, fitsPath, READONLY, &status))
	{									// 16   , 2     , {166,166}
		if (!fits_get_img_param(fptr, 2, &bitpix, &naxis, naxes, &status))
		{
			if (naxis > 2 || naxis == 0)
			{
				printf("Error: only 1D or 2D images are supported\n");
				//return false;
			}			
			else
			{	 
				rows = (int)naxes[0]; 
				cols = (int)naxes[1];
				image = new double*[rows];
				for (int i = 0; i < rows; ++i){
					image[i] = new double[cols];
				}

				/* get memory for 1 row */
				pixels = (double *)malloc(naxes[0] * sizeof(double));

				if (pixels == NULL)
				{
					printf("Memory allocation error - Press any key to exit\n");
					//return false;
				}
				else
				{
					/* loop over all the rows in the image, top to bottom */

					int col_index = 0;
					int row_index = 0;
					for (fpixel[1] = naxes[1]; fpixel[1] >= 1; fpixel[1]--)
					{
						if (fits_read_pix(fptr, TDOUBLE, fpixel, naxes[0], NULL, pixels, NULL, &status))  /* read row of pixels */
							break;  /* jump out of loop on error */

						for (ii = 0; ii < naxes[0]; ii++)
						{
							image[row_index][col_index] = (double)pixels[ii];
							col_index++;
						}
						col_index = 0;
						row_index++;
					}

					free(pixels);
				}
			}

		}

		fits_close_file(fptr, &status);

	}
	if (status>0)
	{
		printf("Can't open fits file - Press any key to exit\n");
		//return false;	
		return *image;
	}
}


/*
Mat FitsToCvMatConverter::convertFitsToCvMat(const char * fitsPath)
{

	 
	//CFITSIO
	fitsfile *fptr;   /* FITS file pointer, defined in fitsio.h */
	/*int status = 0;   CFITSIO status value MUST be initialized to zero! 
	int bitpix, naxis, ii, anynul;
	long naxes[2] = { 1, 1 }, fpixel[2] = { 1, 1 };
	double *pixels;
	char format[20], hdformat[20];

	//OPENCV
	Mat* image;

	if (!fits_open_file(&fptr, fitsPath, READONLY, &status))
	{									// 16   , 2     , {166,166}
		if (!fits_get_img_param(fptr, 2, &bitpix, &naxis, naxes, &status))
		{
			if (naxis > 2 || naxis == 0)
				printf("Error: only 1D or 2D images are supported\n");
			else
			{	//OPENCV
				image = new Mat(naxes[0], naxes[1], CV_64FC1, Scalar(0));

				/* get memory for 1 row */
				/*pixels = (double *)malloc(naxes[0] * sizeof(double));

				if (pixels == NULL)
				{
					printf("Memory allocation error - Press any key to exit\n");
				}
				else
				{
					/* loop over all the rows in the image, top to bottom */

					/*int col_index = 0;
					int row_index = 0;
					for (fpixel[1] = naxes[1]; fpixel[1] >= 1; fpixel[1]--)
					{
						if (fits_read_pix(fptr, TDOUBLE, fpixel, naxes[0], NULL, pixels, NULL, &status))  /* read row of pixels */
							//break;  /* jump out of loop on error */

						/*for (ii = 0; ii < naxes[0]; ii++){
							image->at<double>(row_index, col_index) = (double)pixels[ii];
							col_index++;

						}

						col_index = 0;
						row_index++;
					}

					free(pixels);
				}
			}

		}

		fits_close_file(fptr, &status);

	}
	if (status>0){
		cout << "Error: can't open fits file." << endl;
	}

	return *image;
}*/









