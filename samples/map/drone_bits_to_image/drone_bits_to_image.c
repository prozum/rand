//
// Created by Lee on 15/11/2016.
//
#include "drone_bits_to_image.h"

void extract_begin()
{
    FILE *bits_file = fopen(/*fil*/, "r");

}

void expand_bytes()
{

}



void insert_bits_into_image ()
{
    FILE *image = fopen("image.pbm", "w");
    if (image == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    /* write image file headers */
    fprintf(image, "P1\n90 90\n"); // image size 90x90 pixels

    /* write bits into image file */
    int buffer[8100];

    while(fgets(buffer, sizeof(buffer), bits_file))
    {
        printf("%s", buffer);
        fprintf(image, "%s", buffer);
    }

    fclose(image);
}