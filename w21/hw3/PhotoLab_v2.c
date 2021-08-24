//PhotoLab v2 C file by Samuel Briones-Plascencia

/*** header files ***/

#include <stdio.h>
#include "Constants.h"
#include "DIPs.h"
#include "FileIO.h"
#include "Advanced.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu(void);

/* test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]);

// print menu only
void PrintMenu()
{	printf("\n-------------------------\n");
	printf(" 1: Load a PPM image\n");
	printf(" 2: Save the image in PPM and JPEG format\n");
	printf(" 3: Run aging filter\n");
	printf(" 4: Run edge detection filter\n");
	printf(" 5: Run sharpen filter\n");
	printf(" 6: Run noise filter\n");
	printf(" 7: Run posterize filter\n");
	printf(" 8: Run negative filter\n");
	printf("%d: Test all functions\n", AUTOTEST);
	printf("%d: Exit\n", EXIT);
	printf("--------------------------\n");
	printf("Please make your choice: ");
}

int main(void)
{
	/* Two dimensional arrays to hold the current image data, */
	/* one array for each color component.					  */
	unsigned char	R[WIDTH][HEIGHT];
	unsigned char	G[WIDTH][HEIGHT];
	unsigned char	B[WIDTH][HEIGHT];

	/* Please replace the following code with proper menu  */
	/* with function calls for DIP operations			   */
	
	int option, np, rbits, gbits, bbits;			// user input option
	char fname[SLEN];	// input file name

	//Debugging executeable 
	#ifdef DEBUG
		AutoTest(R, G, B);
		return 0;
	#endif

	// print welcome message only once
	printf("Welcome to Photo Lab 2021 - v1!");
	PrintMenu();
	scanf("%d", &option);
	
	int rc = -1;		// return code of LoadImage()

	while (option != EXIT)
	{	
		// menu item 2-4 requires image is loaded first
		if (option == 1)
		{	printf("Please input the file name to load: ");
			scanf("%s", fname);
			rc = LoadImage(fname, R, G, B);
		}
		else if (option >= 2 && option <= 8)
		{	if (rc != 0)
			{	printf("No image was read.\n");
			}
			else
			{	switch(option)
				{	case 2:
						printf("Please input the file name to save: ");
						scanf("%s", fname);
						SaveImage(fname, R, G, B);
						break;
					case 3:
						Aging(R, G, B);
						printf("\"Aging\" operation is done!\n");
						break;
					case 4:
						EdgeDetection(R, G, B);
						printf("\"Edge Detection\" operation is done!\n");
						break;
					case 5:
						Sharpen(R, G, B);
						printf("\"Sharpen\" operation is done!\n");
						break;
					case 6:
						printf("\nPlease input noise percentage: ");
						scanf("%d", &np);	
						Noise(np ,R, G, B);
						printf("\"Noise\" operation is done!\n");
						break;
					case 7:
						printf("\nEnter the number of posterization bits for R channel (1 to 8): ");
						scanf("%d", &rbits);
						
						printf("\nEnter the number of posterization bits for G channel (1 to 8): ");
						scanf("%d", &gbits);
						
						printf("\nEnter the number of posterization bits for B channel (1 to 8): ");
						scanf("%d", &bbits);
						
						Posterize(R, G, B, rbits, gbits, bbits);
						printf("\"Posterize\" operation is done!\n");
						break;
					case 8:
						Negative(R, G, B);
						printf("\"Negative\" operation is done!\n");
						break;
					default:
						break;
				}	
			}
		}
		else if (option == AUTOTEST)
		{	AutoTest(R, G, B);
		}
		else
		{	printf("Invalid selection!\n");
		}
		// Process finished, waiting for anothre input
		PrintMenu();
		
		scanf("%d", &option);	
	}


	printf("Exiting program.\n");
	/* End of replacing */
	return SUCCESS;
}

/* Test all functions */
void AutoTest(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	char fname[SLEN] = "pigeon";

	//All ifdef is for printing the tested function when debug is defined
	LoadImage(fname, R, G, B);
	Aging(R, G, B);
	SaveImage("age", R, G, B);
	#ifdef DEBUG
		printf("Aging tested!");
	#endif

	LoadImage(fname, R, G, B);
	EdgeDetection(R, G, B);
	SaveImage("edge", R, G, B);
	#ifdef DEBUG
		printf("Edge Detection tested!");
	#endif

	LoadImage(fname, R, G, B);
	Sharpen(R, G, B);
	SaveImage("sharpen", R, G, B);
	#ifdef DEBUG
		printf("Sharpen tested!");
	#endif

	LoadImage(fname, R, G, B);
	Noise(30 , R, G, B);
	SaveImage("noise", R, G, B);
	#ifdef DEBUG
		printf("Noise tested!");
	#endif

	LoadImage(fname, R, G, B);
	Posterize(R, G, B, 7, 7, 7);
	SaveImage("posterize", R, G, B);
	#ifdef DEBUG
		printf("Posterize tested!");
	#endif

	LoadImage(fname, R, G, B);
	Negative(R, G, B);
	SaveImage("negative", R, G, B);
	#ifdef DEBUG
		printf("Negative tested!");
	#endif	
}
