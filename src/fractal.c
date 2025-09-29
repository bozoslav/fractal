#include <math.h>
#include "fractal.h"

static void color_pixel(unsigned char *pixel, int iter, int max_iter)
{
    if (iter == max_iter)
    {
        pixel[0] = pixel[1] = pixel[2] = 0;
    }
    else
    {
        double t = (double)iter / max_iter;
        int green = (int)(255.0 * sqrt(t) * 2);
        pixel[0] = 0;
        pixel[1] = green;
        pixel[2] = green / 2;
    }
}

void render_julia(unsigned char *image, int width, int height,
                  double zoom, double center_x, double center_y,
                  double c_re, double c_im, int max_iter)
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double z_re = (x - width / 2.0) * (4.0 / width) / zoom + center_x;
            double z_im = (y - height / 2.0) * (4.0 / width) / zoom + center_y;
            int iter = 0;
            while (z_re * z_re + z_im * z_im < 4.0 && iter < max_iter)
            {
                double tmp = z_re * z_re - z_im * z_im + c_re;
                z_im = 2.0 * z_re * z_im + c_im;
                z_re = tmp;
                iter++;
            }
            color_pixel(&image[3 * (y * width + x)], iter, max_iter);
        }
    }
}