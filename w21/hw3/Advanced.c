// Advanced C File By Samuel Briones-Plascencia

#include "Constants.h"
#include "Advanced.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

void Noise(int np,unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	int i, x, y, n;	
	n = np * WIDTH * HEIGHT / 100;
	
	//Random Seed based on time
	srand(time(NULL));
	for(i = 0; i < n ; i++){
		//random (x,y) coordinates and using it to place a white pixel
		x = rand() % WIDTH;
		y = rand() % HEIGHT;

		R[x][y] = MAX_PIXEL;
		G[x][y] = MAX_PIXEL;
		B[x][y] = MAX_PIXEL;
	}
}

void Posterize(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits){
	int i, j;
	//Go through each pixel and modifying it based on bitwise operations
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++){
			
			//bitwise operations that uses number/binary to compare to pixel's binary value
			R[i][j] = R[i][j] & (255 - (1 << (rbits - 1)));
			R[i][j] = R[i][j] | ((1 << (rbits - 1)) - 1);
			G[i][j] = G[i][j] & (255 - (1 << (gbits - 1)));
			G[i][j] = G[i][j] | ((1 << (gbits - 1)) - 1);
			B[i][j] = B[i][j] & (255 - (1 << (bbits - 1)));
			B[i][j] = B[i][j] | ((1 << (bbits - 1)) - 1);
		}
	}
}

void Negative(unsigned char R[WIDTH][HEIGHT],unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT]){
	int i, j;

	//Goes through each pixel and makes inverse number
	for(i = 0; i < WIDTH; i++){
		for(j = 0; j < HEIGHT; j++ ){
			R[i][j] = 255 - R[i][j];
			G[i][j] = 255 - G[i][j];
			B[i][j] = 255 - B[i][j];
		}
	}
}
