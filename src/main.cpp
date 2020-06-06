#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "colour.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

colour ray_colour(const ray& r, const hittable& world)
{
    hit_record rec;
    if (world.hit(r, 0, infinity, rec))
    {
        return 0.5 * (rec.normal + colour(1,1,1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);

    auto a = colour(1.0, 0.5, 0.6);
    auto b = colour(0.0, 0.0, 0.0);

    return lerp(a, b, t);
}

int main()
{
    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

    auto viewport_height = 2.0;
    auto viewport_width = ASPECT_RATIO * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0,-100.5,-1), 100));

    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; ++x)
        {
            auto u = double(x) / (WIDTH-1);
            auto v = double(y) / (HEIGHT-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            
            colour pixel_colour = ray_colour(r, world);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

