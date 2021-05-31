#include <stdio.h>
#include <math.h>
#include "marcher.h"

#define WIDTH 1000
#define HEIGHT 1000

struct Color {
    char r, g, b;
};


int main() {
    FILE* fp = fopen("marched.ppm", "wb");

    fprintf(fp, "P6\n%d %d\n255\n", (int) WIDTH, (int ) HEIGHT);

    double ar = WIDTH * 1.0 / HEIGHT;
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            double sx = ((x + 0.5) - 0.5 * WIDTH) / HEIGHT;
            double sy = (1 - ((y + 0.5) - 0.5 * HEIGHT)) / HEIGHT;

            Vector3 rayDir = {.x = sx, .y = sy, .z = 1.0};
            normalize(&rayDir);

            Vector3 camera = {.x =0, .y = 0, .z = -2.5};

            Vector3 color = get_color(camera, rayDir, scene);

            color.x = pow(color.x, 0.4545);
            color.y = pow(color.y, 0.4545);
            color.z = pow(color.z, 0.4545);

            struct Color c = {
                    .r = (char) (255 * color.x),
                    .g = (char) (255 * color.y),
                    .b = (char) (255 * color.z)
            };

            fwrite(&c, sizeof(struct Color), 1, fp);
        }
    }
    printf("done");
    fclose(fp);
}