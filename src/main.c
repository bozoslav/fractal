#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "fractal.h"
#include "image.h"

int main(int argc, char *argv[])
{
    int width = 7680, height = 4320;
    double zoom = 1.2, center_x = 0.0, center_y = 0.0;
    double c_re = -0.7, c_im = 0.27015;
    int max_iter = 1000000;

    unsigned char *image = (unsigned char *)malloc(3 * width * height);

    int num_threads = sysconf(_SC_NPROCESSORS_ONLN);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];
    int rows_per_thread = height / num_threads;
    for (int i = 0; i < num_threads; ++i)
    {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i == num_threads - 1) ? height : (i + 1) * rows_per_thread;
        thread_data[i].image = image;
        thread_data[i].width = width;
        thread_data[i].height = height;
        thread_data[i].zoom = zoom;
        thread_data[i].center_x = center_x;
        thread_data[i].center_y = center_y;
        thread_data[i].c_re = c_re;
        thread_data[i].c_im = c_im;
        thread_data[i].max_iter = max_iter;
        pthread_create(&threads[i], NULL, thread_render_julia, &thread_data[i]);
    }

    for (int i = 0; i < num_threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    save_ppm("output/output.ppm", image, width, height);
    free(image);
    return 0;
}

// compile with: gcc -O3 -ffast-math -flto -funroll-loops -pipe src/*.c -o fractal -pthread -lm
// run with: ./fractal