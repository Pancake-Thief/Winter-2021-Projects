/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22                   */
/*                                                                   */
/* This is an "A" level representation of PhotoLab v1.               */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution (and all associated files) is for your reference    */
/* for this course and is copyright belongs to the authors below.    */
/* Reproduction or sharing of this code outside of this class is     */
/* prohibited except with the express written consent of the authors.*/
/*                                                                   */
/* Author: Mina Moghadam, Ned Beigipar, QV Dang, Samuel Briones-Plascencia*/
/* Date:   11/8/2017	  08/17/2020    02/02/2021   03/07/2021      */
/*                                                                   */
/* Comments:                                                         */
/* added info about negative filter                                  */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Image.h"
#include "Test.h"

/*** function declarations ***/

/* print a menu */
void PrintMenu();

int main()
{

#ifdef DEBUG
	int rc = 0;
	AutoTest();
	if(rc){
		printf("AutoTest failed, error code %d", rc);
	} else if(!rc){
		printf("AutoTest finished successfully.\n");
	}
#else
    IMAGE *rc;

    rc = NULL;
    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    
    PrintMenu();
    scanf("%d", &option);

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    /* Square() parameter */
    int x_offset, y_offset, L;

    /* Enlarge() parameter*/
    int percentage;

    /* BrightnessandContrast() parameter*/
    int brightness, contrast;

    /* Error check var*/
    int error = 0;
    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
	    if(rc)
		DeleteImage(rc);
            rc = LoadImage(fname);
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 12) {
            if (! rc)     {
                printf("No image to process.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, rc);
                        break;
                    case 3:
                        Aging(rc);
                        printf("\"Aging\" operation is done!\n");
                        break;
                    case 4:
                        EdgeDetection(rc);
                        printf("\"Edge Detection\" operation is done!\n");
                        break;
                    case 5:
                        Sharpen(rc);
                        printf("\"Sharpen\" operation is done!\n");
			break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        Noise(rc, n);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        Posterize(rc, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;

		    case 8:
                        NegativeFilter(rc);
                        printf("\"Negative Filter\" operation is done!\n");
                        break;
			
		    case 9:
			error = 0;
			do{
				if(error)
					printf("Invalid percentage!! (input < 100) Please try again.\n");
				printf("Please input the enlarging percentage (integer between 100 - 200): ");
				scanf("%d", &percentage);
				error = 1;
			} while(percentage < 100);
			rc = Enlarge(rc, percentage);
			printf("\"Enlarge the image\" operation is done!");
			break;

		    case 10:
			printf("Please enter the X offset value: ");
			scanf("%d", &x_offset);
			
			printf("Please enter the Y offset value: ");
			scanf("%d", &y_offset);
			
			printf("Please input the maximum cropped square size: ");
			scanf("%d", &L);

			rc = Square(rc, x_offset, y_offset, L);
			printf("\"Square\" operation is done!\n");
			break;
		    case 11:
			printf("Please input the brightness level (integer between -255 - 255): ");
			scanf("%d", &brightness);
			
			printf("Please input the contrast level (integer between -255 - 255): ");
			scanf("%d", &contrast);

			rc = BrightnessandContrast(rc, brightness, contrast);
			printf("\"Brightness and Contrast Adjustment\" operation is done!");
		    default:
                        break;

                }
            }
        }

        else if (option == 22) {
		error = 0;
		error = AutoTest();
		if(error){
			printf("AutoTest failed, error code %d\n", error);
		} else if(!error){
			printf("AutoTest finished successfully.\n");
		}
	}
        else {
		printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    if(rc){
	DeleteImage(rc);
    }
    printf("You exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save image in PPM and JPEG format\n");
    printf(" 3: Run aging\n");
    printf(" 4: Run edge detection filter\n");
    printf(" 5: Run sharpen filter\n");
    printf(" 6: Run noise filter\n");
    printf(" 7: Run posterize filter\n");
    printf(" 8: Run negative filter\n");
    printf(" 9: Enlarge image\n");
    printf(" 10: Create square (crop) image\n");
    printf(" 11: Adjust brightness and contrast\n");
    printf("22: Test all functions\n");
    printf("99: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}
 
/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
