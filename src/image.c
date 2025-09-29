#include <stdio.h>
#include "image.h"

void save_ppm(const char *filename, unsigned char *image, int width, int height)
{
    FILE *f = fopen(filename, "wb");

    fprintf(f, "P6\n%d %d\n255\n", width, height);
    fwrite(image, 3, width * height, f);
    fclose(f);
}