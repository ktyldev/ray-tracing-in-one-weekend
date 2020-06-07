#include "rtweekend.h"

#include "hittable_list.h"
#include "sphere.h"
#include "colour.h"
#include "camera.h"
#include "material.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);
const int SAMPLES_PER_PIXEL = 100;
const int MAX_DEPTH = 50;

colour ray_colour(const ray& r, const hittable& world, int depth)
{
    hit_record rec;
    if (depth <= 0)
    {
        return colour(0,0,0);
    }

    if (world.hit(r, 0.001, infinity, rec))
    {
        ray     scattered;
        colour  attenuation;

        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_colour(scattered, world, depth-1);
        }

        return colour(0,0,0);
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);

    auto a = colour(0.5, 0.6, 0.7);
    auto b = colour(0.5, 0.5, 0.5);

    return lerp(a, b, t);
}

int main()
{
    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

    hittable_list world;
    
    world.add(make_shared<sphere>(
        point3(0,0,-1),
        0.5,
        make_shared<lambertian>(colour(0.1,0.2,0.5))));
    world.add(make_shared<sphere>(
        point3(0,-100.5,-1),
        100,
        make_shared<lambertian>(colour(0.8,0.8,0.0))));

    world.add(make_shared<sphere>(
        point3(1,0,-1),
        0.5,
        make_shared<metal>(colour(0.8,0.6,0.2), 0.0)));
    world.add(make_shared<sphere>(
        point3(-1,0,-1),
        0.5,
        make_shared<dielectric>(1.5)));
    world.add(make_shared<sphere>(
        point3(-1,0,-1),
        -0.45,
        make_shared<dielectric>(1.5)));

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
                pixel_colour += ray_colour(r, world, MAX_DEPTH);
            }

            write_colour(std::cout, pixel_colour, SAMPLES_PER_PIXEL);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

