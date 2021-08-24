/*********************************************************************/
/* PhotoLab.c: Assignment 2 for EECS 22, Winter 2020				 */
/*									 */
/* modifications:							 */
/* 01/13/21	 QV  Adjusted for W21								 */
/* 01/11/20	WL	adjusted for W20				 */
/* 10/1/18	MC  adjusted for F18					 */
/* 09/27/17	RD	adjusted for lecture usage			 */
/*********************************************************************/
/* Enter your name, last name and UCInet ID below:
 * ***************************************************************** *
 * First Name: Samuel
 * Last Name: Briones-Plascenica
 * UCInetID: 78995822
 */

/*** header files ***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*** global definitions ***/

#define WIDTH  600		/* image width */
#define HEIGHT 400		/* image height */
#define SLEN	64		/* maximum length of file names */

// added new defines for edge detection filter
// you can use these or not (not necessary, but we used it for convenience)
#define MAX_PIXEL 255	/* max pixel value */
#define MIN_PIXEL 0		/* min pixel value */

/*** function declarations ***/

/* print a menu */
int PrintMenu(void);

/* read image from a file */
/* written for you; should not been modified */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* save a processed image */
/* written for you; should not been modified */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* aging the photo */
/* sample function to get you started */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* detect edges in a picture (black background with white edges) */
void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* sharpen the image */
void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

int main(void)
{
	/* Two dimensional arrays to hold the current image data, */
	/* one array for each color component.					*/
	unsigned char   R[WIDTH][HEIGHT];
	unsigned char   G[WIDTH][HEIGHT];
	unsigned char   B[WIDTH][HEIGHT];
	char fName[SLEN] = "";
	int input;

	/* Please replace the following code with proper menu  */
	/* with function calls for DIP operations		   */
	do{
		system("clear");
		switch(input){
			case 1 : 
				//Load PPM image
				printf("Name of file you want to modify: ");
				scanf("%s", fName);
				LoadImage(fName, R, G, B);
				break;
			case 2 :
				//Save image in PPM and JPEG format
				scanf("%s", fName);
				SaveImage(fName, R, G, B);
				break;
			case 3 :
				//Run aging filter
				Aging(R, G, B);
				break;
			case 4 :
				//Run edge detection filter
				EdgeDetection(R, G, B);
				break;
			case 5 :
				//Run sharpen filter
				Sharpen(R, G, B);
				break;
			case 22: 
				//Test all functions
				AutoTest(R, G ,B);
				break;
		}	

		input = PrintMenu();
	}while(input != 99);

	/* End of replacing */
	return 0;
}

/* takes in a file name without extension */
/* writes file into R, G, B arrays */
int LoadImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE *File;
	char Type[SLEN];
	int  Width, Height, MaxValue;
	int  x, y;
	char ftype[] = ".ppm";
	char fname_ext[SLEN + sizeof(ftype)];

	strcpy(fname_ext, fname);
	strcat(fname_ext, ftype);

	File = fopen(fname_ext, "r");
	if (!File) {
		printf("\nCannot open file \"%s\" for reading!\n", fname);
		return 1;
	}
	fscanf(File, "%79s", Type);
	if (Type[0] != 'P' || Type[1] != '6' || Type[2] != 0) {
		printf("\nUnsupported file format!\n");
		return 2;
	}
	fscanf(File, "%d", &Width);
	if (Width != WIDTH) {
		printf("\nUnsupported image width %d!\n", Width);
		return 3;
	}
	fscanf(File, "%d", &Height);
	if (Height != HEIGHT) {
		printf("\nUnsupported image height %d!\n", Height);
		return 4;
	}
	fscanf(File, "%d", &MaxValue);
	if (MaxValue != 255) {
		printf("\nUnsupported image maximum value %d!\n", MaxValue);
		return 5;
	}
	if ('\n' != fgetc(File)) {
		printf("\nCarriage return expected!\n");
		return 6;
	}
	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			R[x][y] = fgetc(File);
			G[x][y] = fgetc(File);
			B[x][y] = fgetc(File);
		}
	}
	if (ferror(File)) {
		printf("\nFile error while reading from file!\n");
		return 7;
	}
	printf("%s was read successfully!\n", fname_ext);
	fclose(File);
	return 0;
}

/* takes R, G, B arrays and writes it in a file */
/* filename (fname) has no extension */
int SaveImage(const char fname[SLEN], unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	FILE *File;
	char ftype[] = ".ppm";
	char fname_ext[SLEN + sizeof(ftype)];
	char SysCmd[SLEN * 5];
	int  x, y;

	strcpy(fname_ext, fname);
	strcat(fname_ext, ftype);

	File = fopen(fname_ext, "w");
	if (!File) {
		printf("\nCannot open file \"%s\" for writing!\n", fname);
		return 1;
	}
	fprintf(File, "P6\n");
	fprintf(File, "%d %d\n", WIDTH, HEIGHT);
	fprintf(File, "255\n");

	for (y = 0; y < HEIGHT; y++) {
		for (x = 0; x < WIDTH; x++) {
			fputc(R[x][y], File);
			fputc(G[x][y], File);
			fputc(B[x][y], File);
		}
	}

	if (ferror(File)) {
		printf("\nFile error while writing to file!\n");
		return 2;
	}
	fclose(File);
	printf("%s was saved successfully. \n", fname_ext);

	/*
	 * rename file to image.ppm, convert it to ~/public_html/<fname>.jpg
	 * and make it world readable
	 */
	sprintf(SysCmd, "~eecs22/bin/pnmtojpeg_hw2.tcsh %s", fname_ext);
	if (system(SysCmd) != 0) {
		printf("\nError while converting to JPG:\nCommand \"%s\" failed!\n", SysCmd);
		return 3;
	}
	printf("%s.jpg was stored for viewing. \n", fname);

	return 0;
}


/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	//Aging
	LoadImage("lambo", R, G, B);
	Aging(R, G, B);
	SaveImage("aging", R, G, B);
	printf("Aging tested!\n\n");
	
	//Edge detection
	LoadImage("lambo", R, G, B);
	EdgeDetection(R, G, B);
	SaveImage("edge", R, G, B);
	printf("Edge Detection tested!\n\n");
	
	//Sharpen
	LoadImage("lambo", R, G, B);
	Sharpen(R, G, B);
	SaveImage("sharpen", R, G, B);
	printf("Sharpen tested!\n\n");
}

/**************************************************************/
/* Please complete and add function definitions below...	  */
/**************************************************************/

/* age the image to make it look like old picture */
void Aging(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x, y;

	for( y = 0; y < HEIGHT; y++ ) {
		for( x = 0; x < WIDTH; x++ ) {
		B[x][y] = ( R[x][y]+G[x][y]+B[x][y] )/5;
			R[x][y] = (unsigned char) (B[x][y]*1.6);
			G[x][y] = (unsigned char) (B[x][y]*1.6);
		}
	}
	printf("\"Aging\" operation is done!\n");
}

void EdgeDetection(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{   
	int i, j, k, m, R_sum, G_sum, B_sum, newR, newG, newB;
	unsigned char R_OG[WIDTH][HEIGHT], G_OG[WIDTH][HEIGHT], B_OG[WIDTH][HEIGHT];
	
	//copying image as an unmodified foundation
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			R_OG[j][i] = R[j][i];
			G_OG[j][i] = G[j][i];
			B_OG[j][i] = B[j][i];
		}
	}
	
	//modifying image
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			R_sum = 0;
			G_sum = 0;
			B_sum = 0;
			
			//Edge cases turned dark
			if(i == 0 || i == HEIGHT - 1|| j == WIDTH - 1 || j == 0){
				R[j][i] = 0;
				G[j][i] = 0;
				B[j][i] = 0;
			} else {		
				//for loops for sum 
				for(k = 0; k < 3; k++){
					for(m = 0; m < 3; m++){
						R_sum += R_OG[j + k - 1][i + m - 1];
						G_sum += G_OG[j + k - 1][i + m - 1];
						B_sum += B_OG[j + k - 1][i + m - 1];
					}
				}
					
				newR = ((9 * R_OG[j][i]) - R_sum);
				newG = ((9 * G_OG[j][i]) - G_sum);
				newB = ((9 * B_OG[j][i]) - B_sum);

				//if value goes beyond 0-255 then cap it
				if(newR < 0)
					newR = 0;
				if(newG < 0)
					newG = 0;
				if(newB < 0)
					newB = 0;
				
				//Finally assigning the values
				R[j][i] = newR;
				G[j][i] = newG;
				B[j][i] = newB;
			}
		}
	}
	printf("\"Edge Detection\" operation is done!\n");
} 

void Sharpen(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int i, j, k, m, R_neg, G_neg, B_neg, R_new, G_new, B_new;
	unsigned char R_OG[WIDTH][HEIGHT], G_OG[WIDTH][HEIGHT], B_OG[WIDTH][HEIGHT];

	//temp array as a foundation
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			R_OG[j][i] = R[j][i];
			G_OG[j][i] = G[j][i];
			B_OG[j][i] = B[j][i];
		}
	}

	//modify the image
	for(i = 0; i < HEIGHT; i++){
		for(j = 0; j < WIDTH; j++){
			R_neg = 0;
			G_neg = 0;
			B_neg = 0;
			
			//check for edge cases
			if(i == 0 || i == HEIGHT - 1 || j == 0 || j == WIDTH - 1){
				continue;
			} else {
				for(k = 0; k < 3; k++){
					for(m = 0; m < 3; m++){
						R_neg += R_OG[j + k - 1][i + m - 1];
						G_neg += G_OG[j + k - 1][i + m - 1];
						B_neg += B_OG[j + k - 1][i + m - 1];
					}
				}
				
				R_new = (10 * R_OG[j][i]) - R_neg;
				G_new = (10 * G_OG[j][i]) - G_neg;
				B_new = (10 * B_OG[j][i]) - B_neg;

				//Greater than 255
				if(R_new > 255)
					R_new = 255;
				if(G_new > 255)
					G_new = 255;
				if(B_new > 255)
					B_new = 255;
				//Less than 0 
				if(R_new < 0)
					R_new = 0;
				if(G_new < 0)
					G_new = 0;
				if(B_new < 0)
					B_new = 0;

				//Assign values
				R[j][i] = R_new;
				G[j][i] = G_new;
				B[j][i] = B_new;
			}
		}
	}
	printf("\"Sharpen\" operation is done!\n");
}

int PrintMenu(void)
{
	int i;

	printf("Welcome to Photo Lab 2021 - v1!\n\n");
	printf("--------------------------------------------\n\n");
	printf(" 1: Load PPM image\n");
	printf(" 2: Save image in PPM and JPEG format\n");
	printf(" 3: Run aging filter\n");
	printf(" 4: Run edge detection filter\n");
	printf(" 5: Run sharpen filter\n");
	printf("22: Test all functions\n");
	printf("99: Exit\n");
	printf("--------------------------------------------\n\n");
	printf("Please make your choice: ");
	scanf("%d", &i);
	return i;
}

/* MORE COMING SOON */

/* EOF */
