#include "Advanced.h"
#include "Image.h" 

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>


/* Add noise to an image */
IMAGE *Noise(IMAGE *image, int n){
	int x, y, i;
	int num, H, W;
	assert(image);
	
	H = ImageHeight(image);
	W = ImageWidth(image);

	num = (n * H * W) / 100;
	srand(time(NULL));

	for(i = 0; i < num; i++){
		x = ((double) rand()/RAND_MAX) * (W - 1);
		y = ((double) rand()/RAND_MAX) * (H - 1);
		SetPixelR(image, x, y, 255);
		SetPixelG(image, x, y, 255);
		SetPixelB(image, x, y, 255);
	}
	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits){
	int x, y;
	int W, H;
	assert(image);

	W = ImageWidth(image);
	H = ImageHeight(image);

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			unsigned char one = 1;
			int i;
			for(i = 0; i < rbits - 1; i++){
				SetPixelR(image, x, y, GetPixelR(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelR(image, x, y, GetPixelR(image, x, y) & one);

			one = 1;
			for(i = 0; i < gbits - 1; i++){
				SetPixelG(image, x, y, GetPixelG(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelG(image, x, y, GetPixelG(image, x, y) & one);

			one = 1;
			for(i = 0; i < bbits - 1; i++){
				SetPixelB(image, x, y, GetPixelB(image, x, y) | one);
				one <<= 1;
			}
			one = ~one;
			SetPixelB(image, x, y, GetPixelB(image, x, y) & one);
		}
	}

	return image;
}

// Negative Filter
IMAGE *NegativeFilter(IMAGE *image){
	int x, y;
	int W, H;
	assert(image);

	W = ImageWidth(image);
	H = ImageHeight(image);

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			SetPixelR(image, x, y, 255 - GetPixelR(image, x, y));
			SetPixelG(image, x, y, 255 - GetPixelG(image, x, y));
			SetPixelB(image, x, y, 255 - GetPixelB(image, x, y));
		}
	}

	return image;
}

//Square Image modification
IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int L){
	IMAGE *temp;
	int x, y;
	int W, H;
	assert(image);
	
	W = ImageWidth(image);
	H = ImageHeight(image);
	//Checking boundaries of X axis
	if(L > W){
		x_offset = 0;
	}else if(x_offset + L > W){
		W = W - x_offset;
	} else {
		W = L;
	}

	if(L > H){
		y_offset = 0;
	} else if(y_offset + L > H){
		H = H - y_offset;
	} else {
		H = L;
	}
	
	if(W < H ){
		H = W;
	} else if (H < W){
		W = H;
	}

	temp = CreateImage(W, H);

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			SetPixelR(temp, x, y, GetPixelR(image, x_offset + x, y_offset + y));
			SetPixelG(temp, x, y, GetPixelG(image, x_offset + x, y_offset + y));
			SetPixelB(temp, x, y, GetPixelB(image, x_offset + x, y_offset + y));
		}
	}
	DeleteImage(image);
	
	return temp;
}

//Enlarge Image
IMAGE *Enlarge(IMAGE *image, int percentage){
	IMAGE *temp;
	int x, y, W, H, oldX, oldY;
	assert(image);

	W = (int) ImageWidth(image) * (percentage / 100.00);
	H = (int) ImageHeight(image) * (percentage / 100.00);

	temp = CreateImage(W, H);

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			oldX = x / (percentage / 100.00);
			oldY = y / (percentage / 100.00);
			SetPixelR(temp, x, y, GetPixelR(image, oldX, oldY));
			SetPixelG(temp, x, y, GetPixelG(image, oldX, oldY));
			SetPixelB(temp, x, y, GetPixelB(image, oldX, oldY));
		}
	}

	DeleteImage(image);

	return temp;
}

IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast){
	int x, y, W, H, newR, newG, newB, factor;
	W = ImageWidth(image);
	H = ImageHeight(image);
	assert(image);

	for(x = 0; x < W; x++){
		for(y = 0; y < H; y++){
			
			//Set brightness
			newR = GetPixelR(image, x, y) + brightness;
			newG = GetPixelG(image, x, y) + brightness;
			newB = GetPixelB(image, x, y) + brightness;
	
			newR = (newR > 255)?255:(newR < 0)?0:newR;
			newG = (newG > 255)?255:(newG < 0)?0:newG;
			newB = (newB > 255)?255:(newB < 0)?0:newB;

			//Set Contrast
			factor = (double)(259 * (contrast + 255)) / (double) (255 * (259 - contrast));
			
			newR = (int)(factor * (newR - 128) + 128);
			newG = (int)(factor * (newG - 128) + 128);
			newB = (int)(factor * (newB - 128) + 128);

			newR = (newR > 255)?255:(newR < 0)?0:newR;
			newG = (newG > 255)?255:(newG < 0)?0:newG;
			newB = (newB > 255)?255:(newB < 0)?0:newB;

			SetPixelR(image, x, y, newR);
			SetPixelG(image, x, y, newG);
			SetPixelB(image, x, y, newB);
		}
	}
	return image;
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
