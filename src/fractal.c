#include <math.h>
#include "fractal.h"
#include <pthread.h>
#include <unistd.h>

static void color_pixel(unsigned char *pixel, int iter, int max_iter);

void *thread_render_julia(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    for (int y = data->start_row; y < data->end_row; ++y)
    {
        for (int x = 0; x < data->width; ++x)
        {
            double z_re = (x - data->width / 2.0) * (4.0 / data->width) / data->zoom + data->center_x;
            double z_im = (y - data->height / 2.0) * (4.0 / data->width) / data->zoom + data->center_y;
            int iter = 0;
            while (z_re * z_re + z_im * z_im < 4.0 && iter < data->max_iter)
            {
                double tmp = z_re * z_re - z_im * z_im + data->c_re;
                z_im = 2.0 * z_re * z_im + data->c_im;
                z_re = tmp;
                iter++;
            }
            color_pixel(&data->image[3 * (y * data->width + x)], iter, data->max_iter);
        }
    }
    return NULL;
}

static void color_pixel(unsigned char *pixel, int iter, int max_iter)
{
    if (iter == max_iter)
    {
        pixel[0] = pixel[1] = pixel[2] = 0;
    }
    else
    {
        double log_iter = log((double)iter);

        double r = 0.5 * (1 + cos(0.3 * log_iter));
        double g = 0.5 * (1 + sin(0.3 * log_iter + 2.0));
        double b = 0.5 * (1 + sin(0.3 * log_iter + 4.0));

        pixel[0] = (unsigned char)(255 * r);
        pixel[1] = (unsigned char)(255 * g);
        pixel[2] = (unsigned char)(255 * b);
    }
}
