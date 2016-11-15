//
// Created by Lee on 15/11/2016.
//

#ifndef BITS_TO_PBM_DRONE_BITS_TO_IMAGE_H
#define BITS_TO_PBM_DRONE_BITS_TO_IMAGE_H
#include <stdio.h>
#define POINTER_TO_EEP_ROM_BEGINNING /* smid pointer værdien ind her */

void extract_begin();
void expand_bytes();
void insert_bits_into_image ();

#endif //BITS_TO_PBM_DRONE_BITS_TO_IMAGE_H
