#include <stdio.h>
#include "Test.h"
#include "Image.h"
#include "FileIO.h"
#include "DIPs.h"
#include "Advanced.h"

int AutoTest(void) {
    int result;
    const char fname[SLEN] = "drinks";
    

    IMAGE *image = NULL;
    
    image = LoadImage(fname);
    result = SaveImage("original", image);
    if (result) return result;
#ifdef DEBUG
    printf("LoadImage & SaveImage tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

   
    image = LoadImage(fname);
    if (! image) return 11;
    image = Aging(image);
    if (! image) return 12;
    result = SaveImage("aging", image);
    if (result) return result;
#ifdef DEBUG
    printf("Aging tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;


    image = LoadImage(fname);
    if (! image) return 13;
    image = Sharpen(image);
    if (! image) return 14;
    result = SaveImage("sharpen", image);
    if (result) return result;
#ifdef DEBUG
    printf("Sharpen tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 15;
    image = EdgeDetection(image);
    if (! image) return 16;
    result = SaveImage("edge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Edge tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 17;
    image = Noise(image, NOISE_PERCENTAGE);
    if (! image) return 18;
    result = SaveImage("noise", image);
    if (result) return result;
#ifdef DEBUG
    printf("Noise tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 19;
    image = Posterize(image, RBITS, GBITS, BBITS);
    if (! image) return 20;
    result = SaveImage("posterize", image);
    if (result) return result;
#ifdef DEBUG
    printf("Posterization tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 21;
    image = NegativeFilter(image);
    if (! image) return 22;
    result = SaveImage("negative", image);
    if (result) return result;
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = Enlarge(image, ENLARGE_PERCENTAGE);
    if (! image) return 24;
    result = SaveImage("enlarge", image);
    if (result) return result;
#ifdef DEBUG
    printf("Enlarge tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 25;
    image = Square(image, X_OFFSET, Y_OFFSET, SQUARE_SIZE);
    if (! image) return 26;
    result = SaveImage("square", image);
    if (result) return result;
#ifdef DEBUG
    printf("Square tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    image = LoadImage(fname);
    if (! image) return 23;
    image = BrightnessandContrast(image, BRIGHTNESS, CONTRAST);
    if (! image) return 24;
    result = SaveImage("brightnessandcontrast", image);
    if (result) return result;
#ifdef DEBUG
    printf("Brightness and Contrast tested!\n\n");
#endif
    DeleteImage(image);
    image = NULL;

    return 0; /* success! */
}
