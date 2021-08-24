#include "DIPs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "Image.h"
/* Example of DIP */
/* age the image to make it look like old picture */

IMAGE *Aging(IMAGE *image){
	int x, y;
	unsigned char newRG , newB;
	unsigned int H, W;
	H = ImageHeight(image);
	W = ImageWidth(image);
	
	assert(image);

	for(y = 0; y < H; y++){
		for(x = 0; x < W; x++){
			newB = (GetPixelR(image, x, y) + GetPixelG(image, x, y) + GetPixelB(image, x, y)) / 5;

			SetPixelB(image, x, y, newB);
	
			newRG = GetPixelB(image, x, y) * 1.6;

			SetPixelR(image, x, y, newRG);
			SetPixelG(image, x, y, newRG);
		}
	}
	return image;
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image){
	IMAGE *temp;
	int i, j, k, m, R_sum, G_sum, B_sum, newR, newG, newB;
	unsigned int W, H;
	assert(image);
	
	W = ImageWidth(image);
	H = ImageHeight(image);
	
	temp = CreateImage(W, H);

	for(i = 0; i < H; i++){
		for(j = 0; j < W; j++){
			SetPixelR(temp, j, i, GetPixelR(image, j, i));
			SetPixelG(temp, j, i, GetPixelG(image, j, i));
			SetPixelB(temp, j, i, GetPixelB(image, j, i));
		}
	}

	for(i = 0; i < H; i++){
		for(j = 0; j < W; j++){
			R_sum = 0;
			G_sum = 0;
			B_sum = 0;

			//Edge cases 
			if(i == 0 || i == H - 1 || j == W - 1 || j == 0){
				continue;
			} else {
				//For loops sum
				for(k = 0; k < 3; k++){
					for(m = 0; m < 3; m++){
						R_sum += GetPixelR(temp, j + k - 1, i + m - 1);
						G_sum += GetPixelG(temp, j + k - 1, i + m - 1);
						B_sum += GetPixelB(temp, j + k - 1, i + m - 1);
					}
				}
				newR = ((10 * GetPixelR(temp, j, i)) - R_sum); 
				newG = ((10 * GetPixelG(temp, j, i)) - G_sum);
				newB = ((10 * GetPixelB(temp, j, i)) - B_sum);

				/*if(newR < 0)
					newR = 0;
				if(newG < 0)
					newG = 0;
				if(newB < 0)
					newB = 0;
				*/
				newR = (newR > 255)?255:(newR < 0)?0:newR;
				newG = (newG > 255)?255:(newG < 0)?0:newG;
				newB = (newB > 255)?255:(newB < 0)?0:newB;
        

				SetPixelR(image, j, i, newR);
				SetPixelG(image, j, i, newG);
				SetPixelB(image, j, i, newB);
			}

		}
	}
	
	DeleteImage(temp);
		
	return image;
}


// edge detection function
IMAGE *EdgeDetection(IMAGE *image){
	IMAGE *temp;
	int i, j, k, m, R_sum, G_sum, B_sum, newR, newG, newB;
	unsigned W, H;
	assert(image);
	
	W = ImageWidth(image);
	H = ImageHeight(image);

	temp = CreateImage(W, H);
	
	//Create temp image
	for(i = 0; i < H; i++){
		for(j = 0; j < W; j++){
			SetPixelR(temp, j, i, GetPixelR(image, j, i));
			SetPixelG(temp, j, i, GetPixelG(image, j, i));
			SetPixelB(temp, j, i, GetPixelB(image, j, i));
		}
	}

	for(i = 0; i < H; i++){
		for(j = 0; j < W; j++){
			R_sum = 0;
			G_sum = 0;
			B_sum = 0;
			
			//Edge cases
			if(i == 0 || i == H - 1 || j == W - 1 || j == 0){
				SetPixelR(image, j, i, 0);
				SetPixelG(image, j, i, 0);
				SetPixelB(image, j, i, 0);
			} else {
				//For loops sum
				for(k = 0; k < 3; k++){
					for(m = 0; m < 3; m++){
						R_sum += GetPixelR(temp, j + k - 1, i + m - 1);
						G_sum += GetPixelG(temp, j + k - 1, i + m - 1);
						B_sum += GetPixelB(temp, j + k - 1, i + m - 1);
					}
				}
				newR = ((9 * GetPixelR(temp, j, i)) - R_sum);
				newG = ((9 * GetPixelG(temp, j, i)) - G_sum);
				newB = ((9 * GetPixelB(temp, j, i)) - B_sum);
				
				newR = (newR > 255) ? 255 : (newR < 0) ?  0 : newR;
				newG = (newG > 255) ? 255 : (newG < 0) ?  0 : newG;
				newB = (newB > 255) ? 255 : (newB < 0) ?  0 : newB;

				SetPixelR(image, j, i, newR);
				SetPixelG(image, j, i, newG);
				SetPixelB(image, j, i, newB);
			}
		}
	}
	DeleteImage(temp);

	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
