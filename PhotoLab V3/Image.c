#include "Image.h"

#include<assert.h>
#include<stdlib.h>
#include<stdio.h>

unsigned char GetPixelR(const IMAGE *image, unsigned int x, unsigned int y){
	unsigned char tempR;
	int width;

	assert(image);

	width = ImageWidth(image);
	tempR = image->R[x + y * width];
	return tempR;
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x, unsigned int y){
	unsigned char tempG;
	int width;
	
	assert(image);
	
	width = ImageWidth(image);
	tempG = image->G[x + y * width];
	return tempG;
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x, unsigned int y){
	unsigned char tempB;
	int width;
	
	assert(image);
	
	width = ImageWidth(image);
	tempB = image->B[x + y * width];
	return tempB;
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r){
	int width;

	assert(image);

	width = ImageWidth(image);
	image->R[x + y * width] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g){
	int width;
	
	assert(image);

	width = ImageWidth(image);
	image->G[x + y * width] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b){
	int width;
	
	assert(image);
	
	width = ImageWidth(image);
	image->B[x + y * width] = b;
}

IMAGE *CreateImage(unsigned int Width, unsigned int Height){
	IMAGE *img;
	img = malloc(sizeof(IMAGE));
	if(!img){
		perror("Error");
	}
	img->W = Width;
	img->H = Height;
	img->R = malloc(sizeof(unsigned char) * Height * Width);
	img->G = malloc(sizeof(unsigned char) * Height * Width);
	img->B = malloc(sizeof(unsigned char) * Height * Width);

	return img;
}

void DeleteImage(IMAGE *image){
	//Make sure the image exists
	assert(image);
	
	//For RGB free the mem and point it to null
	free(image->R);
	image->R = NULL;
	free(image->G);
	image->G = NULL;
	free(image->B);
	image->B = NULL;
	//Free the image itself
	free(image);
	image = NULL;
}

unsigned int ImageWidth(const IMAGE *image){
	unsigned int width;

	assert(image);

	width = image->W;	
	return width;
}

unsigned int ImageHeight(const IMAGE *image){
	unsigned int height;

	assert(image);

	height = image->H;
	return height;
}
