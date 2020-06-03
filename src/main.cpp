#include "colour.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

colour rayColour(const ray& r)
{
    vec3 unitDirection = unitVector(r.direction());
    double t = 0.5 * (unitDirection.y() + 1.0);

    auto a = colour(1.0, 1.0, 1.0);
    auto b = colour(0.0, 0.0, 0.0);

    return lerp(a, b, t);
}

int main()
{
    auto viewportHeight = 2.0;
    auto viewportWidth = ASPECT_RATIO * viewportHeight;
    auto focalLength = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewportWidth, 0, 0);
    auto vertical = vec3(0, viewportHeight, 0);
    auto lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0,0,focalLength);

    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; ++x)
        {
            auto u = double(x) / (WIDTH-1);
            auto v = double(y) / (HEIGHT-1);
            ray r(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
            
            colour pixelColour = rayColour(r);
            writeColour(std::cout, pixelColour);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

