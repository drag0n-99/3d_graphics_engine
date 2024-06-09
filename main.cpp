#include <iostream>
using namespace std;
#include <vector>
#include <cmath>
#include "tgaimage.h"
#include "model.h"
#include "geometry.h"

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red   = TGAColor(255, 0,   0,   255);
Model *model = NULL;
const int width  = 800;
const int height = 800;

// Bresenham's Line Algorithm
/*
The main idea behind Bresenham's line algorithm is to determine whether to step horizontally or vertically
*/
/// Optimized Bresenham's algorithm using integers
// void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color) {
//     int dx = abs(x1 - x0);
//     int dy = abs(y1 - y0);
//     int sx = (x0 < x1) ? 1 : -1;
//     int sy = (y0 < y1) ? 1 : -1;
//     int err = dx - dy;

//     while (true) {
//         image.set(x0, y0, color);
//         if (x0 == x1 && y0 == y1) break;
//         int e2 = 2 * err;
//         if (e2 > -dy) {
//             err -= dy;
//             x0 += sx;  
//         }
//         if (e2 < dx) {  
//             err += dx;
//             y0 += sy;  
//         }
//     }
// }


// Unoptimized but more intuitive Bresenham's algorithm using floats
void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    float err = 0;

    int x = x0;
    int y = y0;


    if (dx > dy)
    {
        float m = (float)dy / (float)dx;
        while (x != x1)
        {
            image.set(x, y, color);
            err += m;
            if (err >= 0.5)
            {
                y += sy;
                err -= 1.0;
            }
            x += sx;
        }
    }
    else
    {
        float m = (float)dx / (float)dy;
        while (y != y1)
        {
            image.set(x, y, color);
            err += m;
            if (err >= 0.5)
            {
                x += sx;
                err -= 1.0;
            }
            y += sy;
        }
    }

    image.set(x1, y1, color);
}





int main(int argc, char **argv)
{
 if (2==argc) {
        model = new Model(argv[1]);
    } else {
        model = new Model("obj/african_head.obj");
    }

    TGAImage image(width, height, TGAImage::RGB);
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j=0; j<3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j+1)%3]);
            int x0 = (v0.x+1.)*width/2.;
            int y0 = (v0.y+1.)*height/2.;
            int x1 = (v1.x+1.)*width/2.;
            int y1 = (v1.y+1.)*height/2.;
            line(x0, y0, x1, y1, image, white);
        }
    }

    image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    image.write_tga_file("output.tga");
    delete model;
    return 0;
}