#include "colour.h"
#include "vec3.h"
#include "ray.h"

#include <iostream>

const double ASPECT_RATIO = 16.0 / 9.0;
const int WIDTH = 384;
const int HEIGHT = static_cast<int>(WIDTH / ASPECT_RATIO);

double hitSphere(const point3& centre, double radius, const ray& r)
{
    vec3 oc = r.origin() - centre;

    auto a = r.direction().lengthSquared();
    auto halfB = dot(oc, r.direction());
    auto c = oc.lengthSquared() - radius*radius;

    auto discriminant = halfB*halfB - a*c;

    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-halfB - sqrt(discriminant)) / a;
    }
}

colour rayColour(const ray& r)
{
    auto t = hitSphere(point3(0,0,-1), 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unitVector(r.at(t) - vec3(0,0,-1));
        return 0.5*colour(N.x()+1, N.y()+1, N.z()+1);
    }

    vec3 unitDirection = unitVector(r.direction());
    t = 0.5 * (unitDirection.y() + 1.0);

    auto a = colour(1.0, 0.5, 0.6);
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

