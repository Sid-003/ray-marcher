#include <stdio.h>
#include "marcher.h"

#define WIDTH 1000
#define HEIGHT 1000

int main() {
    FILE* fp = fopen("marched.ppm", "w");

    fprintf(fp, "P3\n%d %d\n255\n", (int) WIDTH, (int ) HEIGHT);

    double ar = WIDTH * 1.0 / HEIGHT;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            //double sx = (2 * ((x + 0.5) / (1.0 * WIDTH)) - 1.0) * ar;
            //double sy = (1.0 - 2 * ((y + 0.5) / (1.0 * HEIGHT)));

            double sx = ((x + 0.5) - 0.5 * WIDTH) / HEIGHT;
            double sy = (1 - ((y + 0.5) - 0.5 * HEIGHT)) / HEIGHT;
            Vector3 rayDir = {.x = sx, .y = sy, .z = 1.0};
            normalize(&rayDir);

            Vector3 camera = {.x =10, .y = 2, .z = -2};

            Vector3 color = get_color(camera, rayDir, among_gus);

            fprintf(fp, "%d %d %d\n", (int) (color.x * 255), (int) (color.y * 255), (int) (color.z * 255));
        }
    }
    printf("among us");
    fclose(fp);
}
