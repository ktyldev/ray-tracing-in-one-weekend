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
            double r = double(x) / (WIDTH - 1);
            double g = double(y) / (HEIGHT - 1);
            double b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << std::endl;
        }
    }

    std::cerr << "\nDone." << std::endl;
}

