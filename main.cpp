#include "tgaimage.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

// Bresenham's Line Algorithm
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{

    float err = .5;
    float delta_x = x1 - x0;
    float delta_y = y1 - y0;
    float m = delta_y / delta_x; // this is our slope
    while (x0 < x1)
    { // Loop through all the x coordinates
        image.set(x0, y0, white);
        x0 += 1;  // step x to the right
        err += m; // Error equals the slope
        if (err > .5)
        {
            y0 += 1;
            err -= 1;
        }
    }
}

int main(int argc, char **argv)
{
    TGAImage image(100, 100, TGAImage::RGB);
    line(13, 20, 80, 250, image, white);
    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    return 0;
}