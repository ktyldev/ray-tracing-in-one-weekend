#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "colour.h"
#include "camera.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
const int SAMPLES_PER_PIXEL = 100;

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

    camera cam;

    for (int j = HEIGHT - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < WIDTH; ++i)
        {
            colour pixel_colour(0,0,0);

            for (int s = 0; s < SAMPLES_PER_PIXEL; ++s)
            {
                auto u = (i + random_double()) / (WIDTH-1);
                auto v = (j + random_double()) / (HEIGHT-1);
                ray r = cam.get_ray(u, v);
                pixel_colour += ray_colour(r, world);
            }

            write_colour(std::cout, pixel_colour, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

