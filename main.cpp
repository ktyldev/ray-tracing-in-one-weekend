#include "colour.h"
#include "vec3.h"

#include <iostream>

const int WIDTH = 256;
const int HEIGHT = 256;

int main()
{
    std::cout << "P3" << std::endl;
    std::cout << WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;

        for (int x = 0; x < WIDTH; ++x)
        {
            colour pixelColour(double(x)/(WIDTH-1), double(y)/(HEIGHT-1), 0.25);
            writeColour(std::cout, pixelColour);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

