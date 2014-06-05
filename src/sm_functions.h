#ifndef _SM_FUNCTIONS_H_
#define _SM_FUNCTIONS_H_

#include "camera.h"
#include "sub_matriz.h"

void sm_grey_scale(sub_matriz *cam);
void sm_binarize(sub_matriz *cam, int threshold);
void sm_euclidian_distance(sub_matriz *atual, sub_matriz *anterior, int threshold);
void sm_sobel(sub_matriz *atual, sub_matriz *alvo, int threshold);

#endif