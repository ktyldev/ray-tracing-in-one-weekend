#include "colour.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

double hit_sphere(const point3& centre, double radius, const ray& r)
{
    vec3 oc = r.origin() - centre;

    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-half_b - sqrt(discriminant)) / a;
    }
}

colour ray_colour(const ray& r)
{
    auto t = hit_sphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unit_vector(r.at(t) - vec3(0,0,-1));
        return 0.5*colour(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);

    auto a = colour(1.0, 0.5, 0.6);
    auto b = colour(0.0, 0.0, 0.0);

    return lerp(a, b, t);
}

int main()
{
    auto viewport_height = 2.0;
    auto viewport_width = ASPECT_RATIO * viewport_height;
    auto focal_length = 1.0;

    auto origin = point3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0,0,focal_length);

    std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";

    for (int y = HEIGHT - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
        for (int x = 0; x < WIDTH; ++x)
        {
            auto u = double(x) / (WIDTH-1);
            auto v = double(y) / (HEIGHT-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            
            colour pixel_colour = ray_colour(r);
            write_colour(std::cout, pixel_colour);
        }
    }

    std::cerr << "\nDone." << std::endl;
}

