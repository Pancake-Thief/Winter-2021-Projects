#ifndef DIPS_H_INCLUDED_
#define DIPS_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* aging filter */
IMAGE *Aging(IMAGE *image);

/* sharpen filter */
IMAGE *Sharpen(IMAGE *image);

/* edge filter */
IMAGE *EdgeDetection(IMAGE *image);

#endif /* DIPS_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
