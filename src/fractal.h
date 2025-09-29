#ifndef FRACTAL_H
#define FRACTAL_H

typedef struct
{
    int start_row, end_row;
    unsigned char *image;
    int width, height;
    double zoom, center_x, center_y, c_re, c_im;
    int max_iter;
} ThreadData;

void *thread_render_julia(void *arg);

#endif // FRACTAL_H