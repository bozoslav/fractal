#include <stdio.h>
#include <stdlib.h>
#include "fractal.h"
#include "image.h"

int main(int argc, char *argv[])
{
    int width = 3840, height = 2160;
    double zoom = 1.0, center_x = 0.0, center_y = 0.0;
    double c_re = -0.7, c_im = 0.27015;

    unsigned char *image = (unsigned char *)malloc(3 * width * height);

    render_julia(image, width, height, zoom, center_x, center_y, c_re, c_im, 10000);
    save_ppm("output/output.ppm", image, width, height);

    free(image);

    return 0;
}
