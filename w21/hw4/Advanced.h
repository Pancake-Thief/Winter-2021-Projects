#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* noise filter */
IMAGE *Noise(IMAGE *image, int n);

/* posterize filter */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

/* negative filter */
IMAGE *NegativeFilter(IMAGE *image);

/* square modification*/
IMAGE *Square(IMAGE *image, int x_offset, int y_offset, int L);

/* enlarge modification*/
IMAGE *Enlarge(IMAGE *image, int percentage);

/* brightness and contrast modification*/
IMAGE *BrightnessandContrast(IMAGE *image, int brightness, int contrast);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
